/*
	Copyright (c) 2016 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

#include "wxchartgrid.h"
#include "wxchartutilities.h"

wxChartGrid::wxChartGrid(const wxVector<wxString> &labels,
						 const wxChartGridOptions& options)
	: m_options(options), m_xLabels(labels), m_yLabelMaxWidth(0),
	m_xPaddingLeft(0), m_needsFit(true)
{
	wxVector<wxDouble> dummy;
	wxDouble valueRange = CalculateGridRange(dummy);
}

void wxChartGrid::Draw(wxGraphicsContext &gc)
{
	wxFont font(wxSize(0, m_options.GetFontSize()), 
		m_options.GetFontFamily(), m_options.GetFontStyle(), wxFONTWEIGHT_NORMAL);
	Fit(m_steps, gc, font);

	wxDouble yLabelGap = 50 / m_steps;
	wxDouble xStart = m_xPaddingLeft;

	for (size_t i = 0; i < m_yLabels.size(); ++i)
	{
		wxDouble yLabelCenter = yLabelGap * i;
		wxDouble linePositionY = yLabelCenter;
		
		// We always show the X-axis
		bool drawHorizontalLine = (m_options.ShowHorizontalLines() || (i == 0));

		gc.SetFont(font, m_options.GetFontColor());
		gc.DrawText(m_yLabels[i], xStart - 10 - m_yLabelWidths[i], yLabelCenter);

		if (drawHorizontalLine)
		{
			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(xStart, linePositionY);
			path.AddLineToPoint(100, linePositionY);
			path.CloseSubpath();

			if (i > 0)
			{
				wxPen pen(m_options.GetGridLineColor(), m_options.GetGridLineWidth());
				gc.SetPen(pen);
				gc.StrokePath(path);
			}
			else
			{
				wxPen pen(m_options.GetAxisLineColor(), m_options.GetAxisLineWidth());
				gc.SetPen(pen);
				gc.StrokePath(path);
			}

			wxGraphicsPath path2 = gc.CreatePath();
			path.MoveToPoint(xStart - 5, linePositionY);
			path.AddLineToPoint(xStart, linePositionY);
			path2.CloseSubpath();

			wxPen pen(m_options.GetAxisLineColor(), m_options.GetAxisLineWidth());
			gc.SetPen(pen);
			gc.StrokePath(path2);
		}
	}

	for (size_t i = 0; i < m_xLabels.size(); ++i)
	{
		wxGraphicsPath path = gc.CreatePath();

		wxDouble xPos = CalculateX(i);
		path.MoveToPoint(xPos, 10);
		path.AddLineToPoint(xPos, 100);
		path.CloseSubpath();

		wxPen pen(m_options.GetGridLineColor(), m_options.GetGridLineWidth());
		gc.SetPen(pen);
		gc.StrokePath(path);
	}
}

void wxChartGrid::Fit(size_t steps, 
					  wxGraphicsContext &gc,
					  const wxFont &font)
{
	if (!m_needsFit)
	{
		return;
	}

	BuildYLabels(steps, gc, font);
	CalculateXLabelRotation(m_yLabelMaxWidth);

	m_needsFit = false;
}

void wxChartGrid::BuildYLabels(size_t steps, 
							   wxGraphicsContext &gc, 
							   const wxFont &font)
{
	m_yLabels.clear();
	m_yLabelMaxWidth = 0;

	size_t stepDecimalPlaces = wxChartUtilities::GetDecimalPlaces();

	for (size_t i = 0; i <= steps; ++i)
	{
		m_yLabels.push_back("10");
		wxDouble labelWidth = wxChartUtilities::GetTextWidth(gc, font, "10");
		m_yLabelWidths.push_back(labelWidth);
		if (labelWidth > m_yLabelMaxWidth)
		{
			m_yLabelMaxWidth = labelWidth;
		}
	}
	m_yLabelMaxWidth += 10;
}

void wxChartGrid::CalculateXLabelRotation(wxDouble yLabelMaxWidth)
{
	m_xPaddingLeft = yLabelMaxWidth;
}

double wxChartGrid::CalculateX(size_t index)
{
	wxDouble innerWidth = 100;
	wxDouble valueWidth = innerWidth / m_xLabels.size();
	wxDouble valueOffset = (valueWidth * index);

	return valueOffset;
}

double wxChartGrid::CalculateGridRange(const wxVector<wxDouble> &values)
{
	// Set a minimum step of two - a point at the top of the graph, and a point at the base
	m_steps = 2;

	wxDouble maxValue = 0;
	wxDouble minValue = 0;
	if (values.size() > 0)
	{
		maxValue = values[0];
		minValue = values[0];
		for (size_t i = 1; i < values.size(); ++i)
		{
			if (values[i] > maxValue)
			{
				maxValue = values[i];
			}
			if (values[i] < minValue)
			{
				minValue = values[i];
			}
		}
	}

	// We need some degree of separation here to calculate the scales if all the values are the same
	// Adding/minusing 0.5 will give us a range of 1.
	if (maxValue == minValue)
	{
		maxValue += 0.5;
		minValue -= 0.5;
	}

	wxDouble valueRange = maxValue - minValue;
	if (valueRange < 0)
	{
		valueRange = -valueRange;
	}

	return valueRange;
}
