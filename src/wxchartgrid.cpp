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

wxChartGrid::wxChartGrid(const wxSize &size,
						 const wxVector<wxString> &labels,
						 const wxChartGridOptions& options)
	: m_options(options), m_size(size), 
	m_startPoint(0), m_endPoint(0),
	m_xLabels(labels), m_yLabelMaxWidth(0),
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

	wxDouble yLabelGap = (m_endPoint - m_startPoint) / m_steps;
	wxDouble xStart = m_xPaddingLeft;

	for (size_t i = 0; i < m_yLabels.size(); ++i)
	{
		wxDouble yLabelCenter = m_endPoint - (yLabelGap * i);
		wxDouble linePositionY = yLabelCenter;
		
		// We always show the X-axis
		bool drawHorizontalLine = (m_options.ShowHorizontalLines() || (i == 0));

		gc.SetFont(font, m_options.GetFontColor());
		gc.DrawText(m_yLabels[i], xStart - 10 - m_yLabelWidths[i], yLabelCenter - (m_yLabelHeights[i] / 2));

		if (drawHorizontalLine)
		{
			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(xStart, linePositionY);
			path.AddLineToPoint(m_size.GetWidth(), linePositionY);
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
			path2.MoveToPoint(xStart - 5, linePositionY);
			path2.AddLineToPoint(xStart, linePositionY);
			path2.CloseSubpath();

			wxPen pen(m_options.GetAxisLineColor(), m_options.GetAxisLineWidth());
			gc.SetPen(pen);
			gc.StrokePath(path2);
		}
	}

	for (size_t i = 0; i < m_xLabels.size(); ++i)
	{
		// We always show the Y-axis
		bool drawVerticalLine = (m_options.ShowVerticalLines() || (i == 0));

		if (drawVerticalLine)
		{
			wxDouble linePos = CalculateX(i);

			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(linePos, m_endPoint);
			path.AddLineToPoint(linePos, m_startPoint - 3);
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

			// Small lines at the bottom of the base grid line
			wxGraphicsPath path2 = gc.CreatePath();
			path2.MoveToPoint(linePos, m_endPoint);
			path2.AddLineToPoint(linePos, m_endPoint + 5);
			path2.CloseSubpath();

			wxPen pen(m_options.GetAxisLineColor(), m_options.GetAxisLineWidth());
			gc.SetPen(pen);
			gc.StrokePath(path2);
		}
	}
}

void wxChartGrid::Resize(const wxSize &size)
{
	m_size = size;
	m_needsFit = true;
}

void wxChartGrid::Fit(size_t steps, 
					  wxGraphicsContext &gc,
					  const wxFont &font)
{
	if (!m_needsFit)
	{
		return;
	}

	m_startPoint = m_options.GetFontSize();
	m_endPoint = m_size.GetHeight() - (m_options.GetFontSize() * 1.5) - 5; // -5 to pad labels

	// Apply padding settings to the start and end point.
	//this.startPoint += this.padding;
	//this.endPoint -= this.padding;


	BuildYLabels(steps, gc, font);
	CalculateXLabelRotation(m_yLabelMaxWidth);

	m_needsFit = false;
}

void wxChartGrid::BuildYLabels(size_t steps, 
							   wxGraphicsContext &gc, 
							   const wxFont &font)
{
	m_yLabels.clear();
	m_yLabelWidths.clear();
	m_yLabelHeights.clear();
	m_yLabelMaxWidth = 0;

	size_t stepDecimalPlaces = wxChartUtilities::GetDecimalPlaces();

	for (size_t i = 0; i <= steps; ++i)
	{
		m_yLabels.push_back("10");
		wxDouble labelWidth;
		wxDouble labelHeight;
		wxChartUtilities::GetTextSize(gc, font, "10", labelWidth, labelHeight);
		m_yLabelWidths.push_back(labelWidth);
		if (labelWidth > m_yLabelMaxWidth)
		{
			m_yLabelMaxWidth = labelWidth;
		}
		m_yLabelHeights.push_back(labelHeight);
	}
	m_yLabelMaxWidth += 10;
}

void wxChartGrid::CalculateXLabelRotation(wxDouble yLabelMaxWidth)
{
	m_xPaddingLeft = yLabelMaxWidth;
}

double wxChartGrid::CalculateX(size_t index)
{
	wxDouble innerWidth = m_size.GetWidth() - (m_xPaddingLeft);
	wxDouble valueWidth = innerWidth / m_xLabels.size();
	wxDouble valueOffset = m_xPaddingLeft + (valueWidth * index);

	/*
				innerWidth = this.width - (this.xScalePaddingLeft + this.xScalePaddingRight),
				valueWidth = innerWidth/Math.max((this.valuesCount - ((this.offsetGridLines) ? 0 : 1)), 1),
				valueOffset = (valueWidth * index) + this.xScalePaddingLeft;

			if (this.offsetGridLines){
				valueOffset += (valueWidth/2);
			}

			return Math.round(valueOffset);
			*/
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
