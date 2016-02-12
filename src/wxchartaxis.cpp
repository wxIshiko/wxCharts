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

wxChartAxis::wxChartAxis()
	: m_leftPadding(0), m_startPoint(0),
	m_endPoint(0), m_length(0), m_labelMaxWidth(0)
{
}

wxChartAxis::wxChartAxis(const wxVector<wxString> &labels,
						 const wxChartAxisOptions &options)
	: m_options(options), m_leftPadding(0), m_startPoint(0),
	m_endPoint(0), m_length(0), m_labelMaxWidth(0)
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

void wxChartAxis::Draw1(wxGraphicsContext &gc)
{
	// Draw the axis
	wxGraphicsPath path = gc.CreatePath();
	path.MoveToPoint(m_leftPadding, m_endPoint);
	path.AddLineToPoint(m_leftPadding, m_startPoint - 3);
	path.CloseSubpath();

	wxPen pen(m_options.GetLineColor(), m_options.GetLineWidth());
	gc.SetPen(pen);
	gc.StrokePath(path);

	// Draw the little lines corresponding to the labels
	wxDouble yLabelGap = (m_endPoint - m_startPoint) / (m_labels.size() - 1);
	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		wxDouble yLabelCenter = m_endPoint - (yLabelGap * i);
		wxDouble linePositionY = yLabelCenter;

		wxGraphicsPath path2 = gc.CreatePath();
		path2.MoveToPoint(m_leftPadding - 5, linePositionY);
		path2.AddLineToPoint(m_leftPadding, linePositionY);
		path2.CloseSubpath();

		wxPen pen(m_options.GetLineColor(), m_options.GetLineWidth());
		gc.SetPen(pen);
		gc.StrokePath(path2);
	}
	
	// Draw the labels
	wxFont font = m_options.GetFontOptions().GetFont();
	gc.SetFont(font, m_options.GetFontOptions().GetColor());
	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		m_labels[i].Draw(gc);
	}
}

void wxChartAxis::Draw2(wxGraphicsContext &gc)
{
	wxPen pen(m_options.GetLineColor(), m_options.GetLineWidth());
	gc.SetPen(pen);

	// Draw the axis
	wxGraphicsPath path = gc.CreatePath();
	path.MoveToPoint(m_leftPadding, m_endPoint);
	path.AddLineToPoint(m_leftPadding + m_length, m_endPoint);
	path.CloseSubpath();

	gc.StrokePath(path);

	// Draw the little lines corresponding to the labels
	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		wxDouble linePosition = GetMarkerPosition(i).m_x;

		wxGraphicsPath path2 = gc.CreatePath();
		path2.MoveToPoint(linePosition, m_endPoint);
		path2.AddLineToPoint(linePosition, m_endPoint + 5);
		path2.CloseSubpath();

		gc.StrokePath(path2);
	}

	// Draw the labels
	wxFont font = m_options.GetFontOptions().GetFont();
	gc.SetFont(font, m_options.GetFontOptions().GetColor());
	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		m_labels[i].Draw(gc);
	}
}

void wxChartAxis::Fit(wxDouble leftPadding,
					  wxDouble startPoint,
					  wxDouble endPoint,
					  wxDouble length)
{
	m_leftPadding = leftPadding;
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

void wxChartAxis::UpdateLabelPositions1()
{
	wxDouble yLabelGap = (m_endPoint - m_startPoint) / (m_labels.size() - 1);

	for (size_t i = 0; i < m_labels.size(); ++i)
	{		
		wxDouble yLabelCenter = m_endPoint - (yLabelGap * i);
		m_labels[i].SetPosition(m_leftPadding - 10 - m_labels[i].GetSize().GetWidth(), 
			yLabelCenter - (m_labels[i].GetSize().GetHeight() / 2));
	}
}

void wxChartAxis::UpdateLabelPositions2()
{
	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		wxDouble labelPosition = CalculateLabelPosition(i);
		m_labels[i].SetPosition(labelPosition - (m_labels[i].GetSize().GetWidth() / 2),
			m_endPoint + 8);
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
	wxDouble leftPadding = m_leftPadding;
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

wxPoint2DDouble wxChartAxis::GetMarkerPosition(size_t index) const
{
	wxDouble innerWidth = m_length;
	wxDouble valueWidth = innerWidth / m_labels.size();
	wxDouble valueOffset = m_leftPadding + (valueWidth * index);

	return wxPoint2DDouble(valueOffset, m_endPoint);
}
