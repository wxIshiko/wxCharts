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

wxChartAxis::wxChartAxis(const wxVector<wxString> &labels)
{
	for (size_t i = 0; i < labels.size(); ++i)
	{
		m_labels.push_back(wxChartLabel(labels[i]));
	}
}

wxChartAxis::wxChartAxis()
{
}

void wxChartAxis::Fit(wxGraphicsContext &gc,
					  const wxFont &font)
{
	UpdateLabelSizes(gc, font);
}

void wxChartAxis::BuildYLabels(wxDouble minValue,
							   size_t steps,
							   wxDouble stepValue,
							   wxGraphicsContext &gc,
							   const wxFont &font,
							   wxDouble &yLabelMaxWidth)
{
	m_labels.clear();
	yLabelMaxWidth = 0;

	size_t stepDecimalPlaces = wxChartUtilities::GetDecimalPlaces();

	for (size_t i = 0; i <= steps; ++i)
	{
		wxDouble value = minValue + (i * stepValue);//.toFixed(stepDecimalPlaces);
		std::stringstream valueStr;
		valueStr << value;

		wxDouble labelWidth;
		wxDouble labelHeight;
		wxChartUtilities::GetTextSize(gc, font, valueStr.str(), labelWidth, labelHeight);
		if (labelWidth > yLabelMaxWidth)
		{
			yLabelMaxWidth = labelWidth;
		}

		m_labels.push_back(wxChartLabel(valueStr.str(), labelWidth, labelHeight));
	}
	yLabelMaxWidth += 10;
}

bool wxChartAxis::HitTest(const wxPoint &point) const
{
	return false;
}

const wxVector<wxChartLabel>& wxChartAxis::GetLabels()
{
	return m_labels;
}

void wxChartAxis::UpdateLabelSizes(wxGraphicsContext &gc,
								   const wxFont &font)
{
	for (size_t i = 0; i < m_labels.size(); ++i)
	{
		wxDouble labelWidth;
		wxDouble labelHeight;
		wxChartUtilities::GetTextSize(gc, font, m_labels[i].GetText(), labelWidth, labelHeight);
		m_labels[i].SetSize(labelWidth, labelHeight);
	}
}
