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

wxChartGrid::wxChartGrid(const wxSize &size,
						 const wxVector<wxString> &labels,
						 wxDouble minValue,
						 wxDouble maxValue,
						 const wxChartGridOptions& options)
	: m_options(options), m_mapping(size, labels.size()), 
	m_XAxis(labels, options.GetXAxisOptions()), m_needsFit(true)
{
	wxDouble graphMinValue;
	wxDouble graphMaxValue;
	wxDouble valueRange = 0;
	wxChartUtilities::CalculateGridRange(minValue, maxValue, 
		graphMinValue, graphMaxValue, valueRange, m_steps, m_stepValue);
	m_mapping.SetMinValue(graphMinValue);
	m_mapping.SetMaxValue(graphMaxValue);

	m_YAxis.BuildYLabels(m_mapping.GetMinValue(), m_steps, m_stepValue);
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
			path.CloseSubpath();

			wxPen pen1(m_options.GetGridLineColor(), m_options.GetGridLineWidth());
			gc.SetPen(pen1);
			gc.StrokePath(path);
		}
	}

	if (m_options.ShowVerticalLines())
	{
		for (size_t i = 1; i < m_XAxis.GetLabels().size(); ++i)
		{
			wxPoint2DDouble s;
			wxPoint2DDouble t;
			m_XAxis.GetVerticalLinePositions(i, s, t);
			wxDouble linePosition = s.m_x;

			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(linePosition, m_mapping.GetEndPoint());
			path.AddLineToPoint(linePosition, m_mapping.GetStartPoint() - 3);
			path.CloseSubpath();

			wxPen pen1(m_options.GetGridLineColor(), m_options.GetGridLineWidth());
			gc.SetPen(pen1);
			gc.StrokePath(path);
		}
	}

	m_XAxis.Draw2(gc);
	m_YAxis.Draw1(gc);
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
	wxDouble leftPadding = CalculateLeftPadding(m_XAxis.GetLabels(), m_YAxis.GetLabelMaxWidth());
	m_XAxis.Fit(leftPadding, 0, endPoint, m_mapping.GetSize().GetWidth() - leftPadding);
	m_YAxis.Fit(leftPadding, startPoint, endPoint, 0);

	m_XAxis.UpdateLabelPositions2();
	m_YAxis.UpdateLabelPositions1();

	m_mapping.Fit(leftPadding, startPoint, endPoint);

	m_needsFit = false;
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
