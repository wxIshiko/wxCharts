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
#include <sstream>

wxChartAxis::wxChartAxis()
	: m_leftPadding(0), m_length(0), m_labelMaxWidth(0)
{
}

wxChartAxis::wxChartAxis(const wxVector<wxString> &labels)
	: m_leftPadding(0), m_length(0), m_labelMaxWidth(0)
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

void wxChartAxis::Draw(wxGraphicsContext &gc)
{
	wxFont font(wxSize(0, m_options.GetFontSize()), m_options.GetFontFamily(), 
		m_options.GetFontStyle(), wxFONTWEIGHT_NORMAL);
	gc.SetFont(font, m_options.GetFontColor());
	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		m_labels[i].Draw(gc);
	}
}

void wxChartAxis::Fit(wxDouble leftPadding,
					  wxDouble length)
{
	m_leftPadding = leftPadding;
	m_length = length;
}

void wxChartAxis::UpdateLabelSizes(wxGraphicsContext &gc)
{
	m_labelMaxWidth = 0;

	wxFont font(wxSize(0, m_options.GetFontSize()), m_options.GetFontFamily(),
		m_options.GetFontStyle(), wxFONTWEIGHT_NORMAL);

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

void wxChartAxis::BuildYLabels(wxDouble minValue,
							   size_t steps,
							   wxDouble stepValue)
{
	m_labels.clear();

	size_t stepDecimalPlaces = wxChartUtilities::GetDecimalPlaces();

	wxFont font(wxSize(0, m_options.GetFontSize()), m_options.GetFontFamily(),
		m_options.GetFontStyle(), wxFONTWEIGHT_NORMAL);

	for (size_t i = 0; i <= steps; ++i)
	{
		wxDouble value = minValue + (i * stepValue);//.toFixed(stepDecimalPlaces);
		std::stringstream valueStr;
		valueStr << value;

		m_labels.push_back(wxChartLabel(valueStr.str()));
	}
}

void wxChartAxis::UpdateLabelPositions(wxDouble startPoint,
									   wxDouble endPoint)
{
	wxDouble yLabelGap = (endPoint - startPoint) / (m_labels.size() - 1);

	for (size_t i = 0; i < m_labels.size(); ++i)
	{		
		wxDouble yLabelCenter = endPoint - (yLabelGap * i);
		m_labels[i].SetPosition(m_leftPadding - 10 - m_labels[i].GetSize().GetWidth(), 
			yLabelCenter - (m_labels[i].GetSize().GetHeight() / 2));
	}
}

void wxChartAxis::UpdateLabelPosition(size_t index,
									  wxDouble x,
									  wxDouble y)
{
	m_labels[index].SetPosition(x, y);
}

const wxVector<wxChartLabel>& wxChartAxis::GetLabels()
{
	return m_labels;
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

	if (m_options.GetLabelAlignment() == wxCHARTLABELALIGNMENT_BETWEEN_LINES)
	{
		valueOffset += (valueWidth / 2);
	}

	/*
	return Math.round(valueOffset);
	*/

	return valueOffset;
}
