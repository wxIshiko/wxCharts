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

/*
	Part of this file were copied from the Chart.js project (http://chartjs.org/)
	and translated into C++.

	The files of the Chart.js project have the following copyright and license.

	Copyright (c) 2013-2016 Nick Downie
	Released under the MIT license
	https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

#include "wxchartgrid.h"
#include "wxchartutilities.h"
#include <sstream>

wxChartGrid::wxChartGrid(const wxSize &size,
						 const wxVector<wxString> &labels,
						 wxDouble minValue,
						 wxDouble maxValue,
						 const wxChartGridOptions& options)
	: m_options(options), m_mapping(size, labels.size()), 
	m_yLabelMaxWidth(0), m_startYValue(minValue),
	m_needsFit(true)
{
	for (size_t i = 0; i < labels.size(); ++i)
	{
		m_xLabels.push_back(wxChartLabel(labels[i]));
	}

	wxDouble graphMaxValue;
	wxDouble valueRange = 0;
	wxChartUtilities::CalculateGridRange(minValue, maxValue, 
		m_startYValue, graphMaxValue, valueRange, m_steps, m_stepValue);
}

void wxChartGrid::Draw(wxGraphicsContext &gc)
{
	wxFont font(wxSize(0, m_options.GetFontSize()), 
		m_options.GetFontFamily(), m_options.GetFontStyle(), wxFONTWEIGHT_NORMAL);
	Fit(m_startYValue, m_steps, gc, font);

	wxDouble yLabelGap = (m_mapping.GetEndPoint() - m_mapping.GetStartPoint()) / m_steps;
	wxDouble xStart = m_mapping.GetLeftPadding();

	for (size_t i = 0; i < m_yLabels.size(); ++i)
	{
		wxDouble yLabelCenter = m_mapping.GetEndPoint() - (yLabelGap * i);
		wxDouble linePositionY = yLabelCenter;
		
		// We always show the X-axis
		bool drawHorizontalLine = (m_options.ShowHorizontalLines() || (i == 0));

		gc.SetFont(font, m_options.GetFontColor());
		m_yLabels[i].Draw(xStart - 10 - m_yLabelWidths[i], yLabelCenter - (m_yLabelHeights[i] / 2), gc);
		
		if (drawHorizontalLine)
		{
			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(xStart, linePositionY);
			path.AddLineToPoint(m_mapping.GetSize().GetWidth(), linePositionY);
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
		wxDouble labelPosition = CalculateLabelPosition(i);
		wxPoint2DDouble s;
		wxPoint2DDouble t;
		m_mapping.GetVerticalLinePositions(i, s, t);
		wxDouble linePosition = s.m_x;

		// We always show the Y-axis
		bool drawVerticalLine = (m_options.ShowVerticalLines() || (i == 0));

		gc.SetFont(font, m_options.GetFontColor());
		m_xLabels[i].Draw(labelPosition - (m_xLabelsWidths[i] / 2), m_mapping.GetEndPoint() + 8, gc);

		if (drawVerticalLine)
		{
			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(linePosition, m_mapping.GetEndPoint());
			path.AddLineToPoint(linePosition, m_mapping.GetStartPoint() - 3);
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
			path2.MoveToPoint(linePosition, m_mapping.GetEndPoint());
			path2.AddLineToPoint(linePosition, m_mapping.GetEndPoint() + 5);
			path2.CloseSubpath();

			wxPen pen(m_options.GetAxisLineColor(), m_options.GetAxisLineWidth());
			gc.SetPen(pen);
			gc.StrokePath(path2);
		}
	}
}

void wxChartGrid::Resize(const wxSize &size)
{
	m_mapping.SetSize(size);
	m_needsFit = true;
}

const wxChartGridMapping& wxChartGrid::GetMapping() const
{
	return m_mapping;
}

void wxChartGrid::Fit(wxDouble minValue, 
					  size_t steps,
					  wxGraphicsContext &gc,
					  const wxFont &font)
{
	if (!m_needsFit)
	{
		return;
	}

	wxDouble startPoint = m_options.GetFontSize();
	wxDouble endPoint = m_mapping.GetSize().GetHeight() - (m_options.GetFontSize() + 15) - 5; // -5 to pad labels
	m_mapping.Fit(startPoint, endPoint);

	// Apply padding settings to the start and end point.
	//this.startPoint += this.padding;
	//this.endPoint -= this.padding;


	BuildYLabels(minValue, steps, gc, font);
	CalculateXLabelRotation(m_xLabels, m_yLabelMaxWidth, gc, font);

	m_needsFit = false;
}

void wxChartGrid::BuildYLabels(wxDouble minValue,
							   size_t steps,
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
		wxDouble value = minValue + (i * m_stepValue);//.toFixed(stepDecimalPlaces);
		std::stringstream valueStr;
		valueStr << value;

		m_yLabels.push_back(wxChartLabel(valueStr.str()));
		wxDouble labelWidth;
		wxDouble labelHeight;
		wxChartUtilities::GetTextSize(gc, font, valueStr.str(), labelWidth, labelHeight);
		m_yLabelWidths.push_back(labelWidth);
		if (labelWidth > m_yLabelMaxWidth)
		{
			m_yLabelMaxWidth = labelWidth;
		}
		m_yLabelHeights.push_back(labelHeight);
	}
	m_yLabelMaxWidth += 10;
}

void wxChartGrid::CalculateXLabelRotation(const wxVector<wxChartLabel> &xLabels,
										  wxDouble yLabelMaxWidth,
										  wxGraphicsContext &gc,
										  const wxFont &font)
{
	m_xLabelsWidths.clear();
	for (size_t i = 0; i < xLabels.size(); ++i)
	{
		wxDouble labelWidth;
		wxDouble labelHeight;
		wxChartUtilities::GetTextSize(gc, font, xLabels[i].GetText(), labelWidth, labelHeight);
		m_xLabelsWidths.push_back(labelWidth);
	}

	// Either the first x label or any of the y labels can be the widest
	// so they are all taken into account to compute the left padding
	wxDouble leftPadding = yLabelMaxWidth;
	if ((m_xLabelsWidths.size() > 0) && ((m_xLabelsWidths[0] / 2) > leftPadding))
	{
		leftPadding = (m_xLabelsWidths[0] / 2);
	}
	m_mapping.SetLeftPadding(leftPadding);
}

wxDouble wxChartGrid::CalculateLabelPosition(size_t index)
{
	wxDouble leftPadding = m_mapping.GetLeftPadding();
	wxDouble innerWidth = m_mapping.GetSize().GetWidth() - leftPadding;
	wxDouble valueWidth = innerWidth / m_xLabels.size();
	wxDouble valueOffset = leftPadding + (valueWidth * index);

	/*
	innerWidth = this.width - (this.xScalePaddingLeft + this.xScalePaddingRight),
	valueWidth = innerWidth/Math.max((this.valuesCount - ((this.offsetGridLines) ? 0 : 1)), 1),
	valueOffset = (valueWidth * index) + this.xScalePaddingLeft;
	*/

	if (m_options.OffsetGridLines())
	{
		valueOffset += (valueWidth / 2);
	}

	/*
	return Math.round(valueOffset);
	*/
	
	return valueOffset;
}
