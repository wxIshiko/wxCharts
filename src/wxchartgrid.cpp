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
#include <wx/pen.h>
#include <sstream>

wxChartGrid::wxChartGrid(const wxSize &size,
						 const wxVector<wxString> &labels,
						 wxDouble minValue,
						 wxDouble maxValue,
						 const wxChartGridOptions& options)
	: m_options(options), m_mapping(size, labels.size()), 
	m_XAxis(labels, options.GetXAxisOptions()), m_YAxis(options.GetYAxisOptions()), 
	m_needsFit(true)
{
	wxDouble effectiveMinValue = minValue;
	if (options.GetYAxisOptions().GetStartValueMode() == wxCHARTAXISVALUEMODE_EXPLICIT)
	{
		effectiveMinValue = options.GetYAxisOptions().GetStartValue();
	}
	wxDouble effectiveMaxValue = maxValue;
	if (options.GetYAxisOptions().GetEndValueMode() == wxCHARTAXISVALUEMODE_EXPLICIT)
	{
		effectiveMaxValue = options.GetYAxisOptions().GetEndValue();
	}

	wxDouble graphMinValue;
	wxDouble graphMaxValue;
	wxDouble valueRange = 0;
	wxChartUtilities::CalculateGridRange(effectiveMinValue, effectiveMaxValue,
		graphMinValue, graphMaxValue, valueRange, m_steps, m_stepValue);
	m_mapping.SetMinValue(graphMinValue);
	m_mapping.SetMaxValue(graphMaxValue);

	wxVector<wxChartLabel> yLabels;
	BuildYLabels(m_mapping.GetMinValue(), m_steps, m_stepValue, yLabels);
	m_YAxis.SetLabels(yLabels);
}

bool wxChartGrid::HitTest(const wxPoint &point) const
{
	return false;
}

wxPoint2DDouble wxChartGrid::GetTooltipPosition() const
{
	return wxPoint2DDouble(0, 0);
}

void wxChartGrid::Draw(wxGraphicsContext &gc)
{
	Fit(m_steps, gc);

	wxDouble yLabelGap = (m_mapping.GetEndPoint() - m_mapping.GetStartPoint()) / m_steps;
	wxDouble xStart = m_mapping.GetLeftPadding();

	if (m_options.ShowHorizontalLines())
	{
		for (size_t i = 1; i < m_YAxis.GetLabels().size(); ++i)
		{
			wxDouble yLabelCenter = m_mapping.GetEndPoint() - (yLabelGap * i);
			wxDouble linePositionY = yLabelCenter;

			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(xStart, linePositionY);
			path.AddLineToPoint(m_mapping.GetSize().GetWidth(), linePositionY);
			
			wxPen pen1(m_options.GetGridLineColor(), m_options.GetGridLineWidth());
			gc.SetPen(pen1);
			gc.StrokePath(path);
		}
	}

	if (m_options.ShowVerticalLines())
	{
		for (size_t i = 1; i < m_XAxis.GetLabels().size(); ++i)
		{
			wxDouble linePosition = m_XAxis.GetTickMarkPosition(i).m_x;

			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(linePosition, m_mapping.GetEndPoint());
			path.AddLineToPoint(linePosition, m_mapping.GetStartPoint() - 3);
			
			wxPen pen1(m_options.GetGridLineColor(), m_options.GetGridLineWidth());
			gc.SetPen(pen1);
			gc.StrokePath(path);
		}
	}

	m_XAxis.Draw(gc);
	m_YAxis.Draw(gc);
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

void wxChartGrid::Fit(size_t steps,
					  wxGraphicsContext &gc)
{
	if (!m_needsFit)
	{
		return;
	}

	wxDouble startPoint = m_options.GetYAxisOptions().GetFontOptions().GetSize();
	wxDouble endPoint = m_mapping.GetSize().GetHeight() - (m_options.GetYAxisOptions().GetFontOptions().GetSize() + 15) - 5; // -5 to pad labels

	// Apply padding settings to the start and end point.
	//this.startPoint += this.padding;
	//this.endPoint -= this.padding;

	m_YAxis.UpdateLabelSizes(gc);
	

	m_XAxis.UpdateLabelSizes(gc);

	wxDouble leftPadding = 0;
	if (m_options.GetXAxisOptions().GetPosition() == wxCHARTAXISPOSITION_BOTTOM)
	{
		leftPadding = CalculateLeftPadding(m_XAxis.GetLabels(), m_YAxis.GetLabelMaxWidth());
		m_XAxis.Fit(leftPadding, 0, endPoint, m_mapping.GetSize().GetWidth() - leftPadding);
		m_YAxis.Fit(leftPadding, startPoint, endPoint, 0);
	}
	else if (m_options.GetXAxisOptions().GetPosition() == wxCHARTAXISPOSITION_LEFT)
	{
		leftPadding = CalculateLeftPadding(m_YAxis.GetLabels(), m_XAxis.GetLabelMaxWidth());
		m_XAxis.Fit(leftPadding, startPoint, endPoint, 0);
		m_YAxis.Fit(leftPadding, 0, endPoint, m_mapping.GetSize().GetWidth() - leftPadding);
	}

	

	m_XAxis.UpdateLabelPositions();
	m_YAxis.UpdateLabelPositions();

	m_mapping.Fit(leftPadding, startPoint, endPoint);

	m_needsFit = false;
}

void wxChartGrid::BuildYLabels(wxDouble minValue,
							   size_t steps,
							   wxDouble stepValue,
							   wxVector<wxChartLabel> &labels)
{
	size_t stepDecimalPlaces = wxChartUtilities::GetDecimalPlaces();

	for (size_t i = 0; i <= steps; ++i)
	{
		wxDouble value = minValue + (i * stepValue);//.toFixed(stepDecimalPlaces);
		std::stringstream valueStr;
		valueStr << value;

		labels.push_back(wxChartLabel(valueStr.str()));
	}
}

wxDouble wxChartGrid::CalculateLeftPadding(const wxVector<wxChartLabel> &xLabels,
										   wxDouble yLabelMaxWidth)
{
	// Either the first x label or any of the y labels can be the widest
	// so they are all taken into account to compute the left padding
	wxDouble leftPadding = yLabelMaxWidth;
	if ((xLabels.size() > 0) && ((xLabels[0].GetSize().GetWidth() / 2) > leftPadding))
	{
		leftPadding = (xLabels[0].GetSize().GetWidth() / 2);
	}
	return leftPadding;
}
