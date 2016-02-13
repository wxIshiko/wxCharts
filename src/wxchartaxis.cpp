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

#include "wxchartaxis.h"
#include "wxchartutilities.h"
#include <wx/pen.h>

wxChartAxis::wxChartAxis(const wxChartAxisOptions &options)
	: m_options(options), m_startPoint(0, 0), m_endPoint(0, 0), 
	m_length(0), m_labelMaxWidth(0)
{
}

wxChartAxis::wxChartAxis(const wxVector<wxString> &labels,
						 const wxChartAxisOptions &options)
	: m_options(options), m_startPoint(0, 0), m_endPoint(0, 0), 
	m_length(0), m_labelMaxWidth(0)
{
	for (size_t i = 0; i < labels.size(); ++i)
	{
		m_labels.push_back(wxChartLabel(labels[i]));
	}
}

bool wxChartAxis::HitTest(const wxPoint &point) const
{
	return false;
}

wxPoint2DDouble wxChartAxis::GetTooltipPosition() const
{
	return wxPoint2DDouble(0, 0);
}

void wxChartAxis::Draw(wxGraphicsContext &gc)
{
	wxPen pen(m_options.GetLineColor(), m_options.GetLineWidth());
	gc.SetPen(pen);

	// Draw the axis
	wxGraphicsPath path = gc.CreatePath();
	if (m_options.GetPosition() == wxCHARTAXISPOSITION_LEFT)
	{
		path.MoveToPoint(m_startPoint);
		path.AddLineToPoint(m_endPoint.m_x, m_endPoint.m_y - 3);
	}
	else if (m_options.GetPosition() == wxCHARTAXISPOSITION_BOTTOM)
	{
		path.MoveToPoint(m_startPoint);
		path.AddLineToPoint(m_startPoint.m_x + m_length, m_startPoint.m_y);
	}
	gc.StrokePath(path);

	DrawTickMarks(gc);	// Draw the little lines corresponding to the labels
	DrawLabels(gc);
}

void wxChartAxis::Fit(wxPoint2DDouble startPoint,
					  wxPoint2DDouble endPoint,
					  wxDouble length)
{
	m_startPoint = startPoint;
	m_endPoint = endPoint;
	m_length = length;
}

void wxChartAxis::UpdateLabelSizes(wxGraphicsContext &gc)
{
	m_labelMaxWidth = 0;

	wxFont font = m_options.GetFontOptions().GetFont();

	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		wxDouble labelWidth;
		wxDouble labelHeight;
		wxChartUtilities::GetTextSize(gc, font, m_labels[i].GetText(), labelWidth, labelHeight);

		m_labels[i].SetSize(labelWidth, labelHeight);
		if (labelWidth > m_labelMaxWidth)
		{
			m_labelMaxWidth = labelWidth;
		}
	}

	m_labelMaxWidth += 10;
}

void wxChartAxis::UpdateLabelPositions()
{
	if (m_options.GetPosition() == wxCHARTAXISPOSITION_LEFT)
	{
		wxDouble yLabelGap = (m_startPoint.m_y - m_endPoint.m_y) / (m_labels.size() - 1);

		for (size_t i = 0; i < m_labels.size(); ++i)
		{
			wxDouble yLabelCenter = m_startPoint.m_y - (yLabelGap * i);
			m_labels[i].SetPosition(m_startPoint.m_x - 10 - m_labels[i].GetSize().GetWidth(),
				yLabelCenter - (m_labels[i].GetSize().GetHeight() / 2));
		}
	}
	else if (m_options.GetPosition() == wxCHARTAXISPOSITION_BOTTOM)
	{
		for (size_t i = 0; i < m_labels.size(); ++i)
		{
			wxDouble labelPosition = CalculateLabelPosition(i);
			m_labels[i].SetPosition(labelPosition - (m_labels[i].GetSize().GetWidth() / 2),
				m_startPoint.m_y + 8);
		}
	}
}

const wxVector<wxChartLabel>& wxChartAxis::GetLabels()
{
	return m_labels;
}

void wxChartAxis::SetLabels(const wxVector<wxChartLabel> &labels)
{
	m_labels = labels;
}

wxDouble wxChartAxis::GetLabelMaxWidth() const
{
	return m_labelMaxWidth;
}

wxDouble wxChartAxis::CalculateLabelPosition(size_t index)
{
	wxDouble leftPadding = m_startPoint.m_x;
	wxDouble innerWidth = m_length;
	wxDouble valueWidth = innerWidth / m_labels.size();
	wxDouble valueOffset = leftPadding + (valueWidth * index);

	/*
	innerWidth = this.width - (this.xScalePaddingLeft + this.xScalePaddingRight),
	valueWidth = innerWidth/Math.max((this.valuesCount - ((this.offsetGridLines) ? 0 : 1)), 1),
	valueOffset = (valueWidth * index) + this.xScalePaddingLeft;
	*/

	if (m_options.GetLabelType() == wxCHARTAXISLABELTYPE_RANGE)
	{
		valueOffset += (valueWidth / 2);
	}

	/*
	return Math.round(valueOffset);
	*/

	return valueOffset;
}

wxPoint2DDouble wxChartAxis::GetTickMarkPosition(size_t index) const
{
	wxDouble innerWidth = m_length;
	wxDouble valueWidth = innerWidth / m_labels.size();
	wxDouble valueOffset = m_startPoint.m_x + (valueWidth * index);

	return wxPoint2DDouble(valueOffset, m_startPoint.m_y);
}

void wxChartAxis::DrawTickMarks(wxGraphicsContext &gc)
{
	if (m_options.GetPosition() == wxCHARTAXISPOSITION_LEFT)
	{
		wxDouble yLabelGap = (m_startPoint.m_y - m_endPoint.m_y) / (m_labels.size() - 1);
		for (size_t i = 0; i < m_labels.size(); ++i)
		{
			wxDouble yLabelCenter = m_startPoint.m_y - (yLabelGap * i);
			wxDouble linePositionY = yLabelCenter;

			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(m_startPoint.m_x - 5, linePositionY);
			path.AddLineToPoint(m_startPoint.m_x, linePositionY);
			gc.StrokePath(path);
		}
	}
	else if (m_options.GetPosition() == wxCHARTAXISPOSITION_BOTTOM)
	{
		for (size_t i = 0; i < m_labels.size(); ++i)
		{
			wxDouble linePosition = GetTickMarkPosition(i).m_x;

			wxGraphicsPath path = gc.CreatePath();
			path.MoveToPoint(linePosition, m_startPoint.m_y);
			path.AddLineToPoint(linePosition, m_startPoint.m_y + 5);
			gc.StrokePath(path);
		}
	}
}

void wxChartAxis::DrawLabels(wxGraphicsContext &gc)
{
	wxFont font = m_options.GetFontOptions().GetFont();
	gc.SetFont(font, m_options.GetFontOptions().GetColor());
	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		m_labels[i].Draw(gc);
	}
}
