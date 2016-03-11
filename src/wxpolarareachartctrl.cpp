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

#include "wxpolarareachartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxPolarAreaChartData::wxPolarAreaChartData()
{
}

void wxPolarAreaChartData::AppendSlice(const wxChartSliceData &slice)
{
	m_slices.push_back(slice);
}

const wxVector<wxChartSliceData>& wxPolarAreaChartData::GetSlices() const
{
	return m_slices;
}

wxPolarAreaChartCtrl::SliceArc::SliceArc(const wxChartSliceData &slice,
                                         wxDouble x,
                                         wxDouble y,
                                         wxDouble startAngle,
                                         wxDouble endAngle,
                                         wxDouble radius)
    : wxChartArc(x, y, startAngle, endAngle, radius, 0,
        slice.GetTooltipText(), wxChartArcOptions(2, slice.GetColor())),
    m_value(slice.GetValue())
{
}

void wxPolarAreaChartCtrl::SliceArc::Resize(const wxSize &size)
{
    wxDouble x = (size.GetX() / 2);
    wxDouble y = (size.GetY() / 2);
    wxDouble radius = ((x < y) ? x : y);
    
    SetCenter(x, y);
}

wxDouble wxPolarAreaChartCtrl::SliceArc::GetValue() const
{
    return m_value;
}

wxPolarAreaChartCtrl::wxPolarAreaChartCtrl(wxWindow *parent,
										   wxWindowID id,
										   const wxPolarAreaChartData &data,
										   const wxPoint &pos,
										   const wxSize &size,
										   long style)
	: wxChartCtrl(parent, id, pos, size, style), 
	m_grid(size, GetMinValue(data.GetSlices()), GetMaxValue(data.GetSlices()),
	m_options.GetGridOptions())
{
	const wxVector<wxChartSliceData>& slices = data.GetSlices();
	for (size_t i = 0; i < slices.size(); ++i)
	{
		Add(slices[i]);
	}
}

wxPolarAreaChartCtrl::wxPolarAreaChartCtrl(wxWindow *parent,
										   wxWindowID id,
										   const wxPolarAreaChartData &data,
                                           const wxPolarAreaChartOptions &options,
										   const wxPoint &pos,
										   const wxSize &size,
										   long style)
	: wxChartCtrl(parent, id, pos, size, style), m_options(options),
	m_grid(size, GetMinValue(data.GetSlices()), GetMaxValue(data.GetSlices()),
	m_options.GetGridOptions())
{
	const wxVector<wxChartSliceData>& slices = data.GetSlices();
	for (size_t i = 0; i < slices.size(); ++i)
	{
		Add(slices[i]);
	}
}

const wxPolarAreaChartOptions& wxPolarAreaChartCtrl::GetOptions() const
{
	return m_options;
}

void wxPolarAreaChartCtrl::Add(const wxChartSliceData &slice)
{
	Add(slice, m_slices.size());
}

void wxPolarAreaChartCtrl::Add(const wxChartSliceData &slice, size_t index)
{
    wxDouble x = (GetSize().GetX() / 2);
    wxDouble y = (GetSize().GetY() / 2);
    wxDouble radius = ((x < y) ? x : y);

    SliceArc::ptr newSlice = SliceArc::ptr(new SliceArc(slice,
        x, y, 0, 0, radius));
    m_slices.insert(m_slices.begin() + index, newSlice);
}

wxDouble wxPolarAreaChartCtrl::GetMinValue(const wxVector<wxChartSliceData> &slices)
{
	wxDouble result = 0;
	if (slices.size() > 0)
	{
		result = slices[0].GetValue();
	}
	for (size_t i = 1; i < slices.size(); ++i)
	{
		wxDouble v = slices[i].GetValue();
		if (v < result)
		{
			result = v;
		}
	}
	return result;
}

wxDouble wxPolarAreaChartCtrl::GetMaxValue(const wxVector<wxChartSliceData> &slices)
{
	wxDouble result = 0;
	if (slices.size() > 0)
	{
		result = slices[0].GetValue();
	}
	for (size_t i = 1; i < slices.size(); ++i)
	{
		wxDouble v = slices[i].GetValue();
		if (v > result)
		{
			result = v;
		}
	}
	return result;
}

void wxPolarAreaChartCtrl::Resize(const wxSize &size)
{
    wxSize newSize(
        size.GetWidth() - m_options.GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options.GetPadding().GetTotalVerticalPadding()
        );

    m_grid.Resize(newSize);
    for (size_t i = 0; i < m_slices.size(); ++i)
    {
        m_slices[i]->Resize(newSize);
    }
}

wxSharedPtr<wxVector<const wxChartElement*> > wxPolarAreaChartCtrl::GetActiveElements(const wxPoint &point)
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

void wxPolarAreaChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
        wxDouble startAngle = m_options.GetStartAngle();
        wxDouble angleIncrement = ((2 * M_PI) / m_slices.size());

        for (size_t i = 0; i < m_slices.size(); ++i)
        {
            SliceArc& currentSlice = *m_slices[i];

            wxDouble endAngle = startAngle + angleIncrement;
            currentSlice.SetAngles(startAngle, endAngle);
            currentSlice.SetRadiuses(m_grid.GetRadius(currentSlice.GetValue()), 0);
            startAngle = endAngle;

            currentSlice.Draw(*gc);
        }

        m_grid.Draw(*gc);

        DrawTooltips(*gc);

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxPolarAreaChartCtrl, wxChartCtrl)
	EVT_PAINT(wxPolarAreaChartCtrl::OnPaint)
END_EVENT_TABLE()
