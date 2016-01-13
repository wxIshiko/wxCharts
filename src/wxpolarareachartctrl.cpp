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

wxPolarAreaChartCtrl::wxPolarAreaChartCtrl(wxWindow *parent,
										   wxWindowID id,
										   const wxPolarAreaChartData &data,
										   const wxPoint &pos,
										   const wxSize &size,
										   long style)
	: wxChart(parent, id, pos, size, style), m_grid(size, m_options.GetGridOptions())
{
	const wxVector<wxChartSliceData>& slices = data.GetSlices();
	for (size_t i = 0; i < slices.size(); ++i)
	{
		Add(slices[i]);
	}
}

void wxPolarAreaChartCtrl::Add(const wxChartSliceData &slice)
{
	Add(slice, m_slices.size());
}

void wxPolarAreaChartCtrl::Add(const wxChartSliceData &slice, size_t index)
{
	Add(slice, index, false);
}

void wxPolarAreaChartCtrl::Add(const wxChartSliceData &slice, size_t index, bool silent)
{
}

void wxPolarAreaChartCtrl::Resize(const wxSize &size)
{
	m_grid.Resize(size);
}

void wxPolarAreaChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxPolarAreaChartCtrl, wxChart)
	EVT_PAINT(wxPolarAreaChartCtrl::OnPaint)
END_EVENT_TABLE()
