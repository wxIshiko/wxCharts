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

#include "wxdoughnutandpiechartbase.h"

wxDoughnutAndPieChartBase::SliceArc::SliceArc(const wxChartSliceData &slice,
											  wxDouble x,
											  wxDouble y,
											  wxDouble startAngle,
											  wxDouble endAngle,
											  wxDouble outerRadius,
											  wxDouble innerRadius,
											  unsigned int strokeWidth)
	: wxChartArc(x, y, startAngle, endAngle, outerRadius, innerRadius, 
		slice.GetTooltipText(), wxChartArcOptions(strokeWidth, slice.GetColor())),
	m_value(slice.GetValue())
{
}

void wxDoughnutAndPieChartBase::SliceArc::Resize(const wxSize &size,
												 const wxDoughnutAndPieChartOptionsBase& options)
{
	wxDouble x = (size.GetX() / 2) - 2;
	wxDouble y = (size.GetY() / 2) - 2;
	wxDouble outerRadius = ((x < y) ? x : y) - (GetOptions().GetOutlineWidth() / 2);
	wxDouble innerRadius = outerRadius * ((wxDouble)options.GetPercentageInnerCutout()) / 100;

	SetCenter(x, y);
	SetRadiuses(outerRadius, innerRadius);
}

wxDouble wxDoughnutAndPieChartBase::SliceArc::GetValue() const
{
	return m_value;
}

wxDoughnutAndPieChartBase::wxDoughnutAndPieChartBase(wxWindow *parent,
													 wxWindowID id,
													 const wxPoint &pos,
													 const wxSize &size,
													 long style)
	: wxChartCtrl(parent, id, pos, size, style), m_total(0)
{
}

void wxDoughnutAndPieChartBase::Add(const wxChartSliceData &slice)
{
	Add(slice, m_slices.size());
}

void wxDoughnutAndPieChartBase::Add(const wxChartSliceData &slice, size_t index)
{
	m_total += slice.GetValue();

	wxDouble x = (GetSize().GetX() / 2) - 2;
	wxDouble y = (GetSize().GetY() / 2) - 2;
	wxDouble outerRadius = ((x < y) ? x : y) - (GetOptions().GetSliceStrokeWidth() / 2);
	wxDouble innerRadius = outerRadius * ((wxDouble)GetOptions().GetPercentageInnerCutout()) / 100;

	SliceArc::ptr newSlice = SliceArc::ptr(new SliceArc(slice,
		x, y, 0, 0, outerRadius, innerRadius, GetOptions().GetSliceStrokeWidth()));
	m_slices.insert(m_slices.begin() + index, newSlice);
}

void wxDoughnutAndPieChartBase::DoDraw(wxGraphicsContext &gc)
{
    wxDouble startAngle = 0.0;
    for (size_t i = 0; i < m_slices.size(); ++i)
    {
        SliceArc& currentSlice = *m_slices[i];

        wxDouble endAngle = startAngle + CalculateCircumference(currentSlice.GetValue());
        currentSlice.SetAngles(startAngle, endAngle);
        startAngle = endAngle;

        currentSlice.Draw(gc);
    }
}

void wxDoughnutAndPieChartBase::Resize(const wxSize &size)
{
	for (size_t i = 0; i < m_slices.size(); ++i)
	{
		m_slices[i]->Resize(size, GetOptions());
	}
}

wxSharedPtr<wxVector<const wxChartElement*> > wxDoughnutAndPieChartBase::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	for (size_t i = 0; i < m_slices.size(); ++i)
	{
		if (m_slices[i]->HitTest(point))
		{
			activeElements->push_back(m_slices[i].get());
		}
	}
	return activeElements;
}

double wxDoughnutAndPieChartBase::CalculateCircumference(wxDouble value)
{
	if (m_total > 0)
	{
		return (value * 2 * M_PI / m_total);
	}
	else
	{
		return 0;
	}
}
