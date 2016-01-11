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

#include "wxpolarareachartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxPolarAreaChartData::wxPolarAreaChartData(const wxVector<wxString> &labels)
	: m_labels(labels)
{
}

const wxVector<wxString>& wxPolarAreaChartData::GetLabels() const
{
	return m_labels;
};

wxPolarAreaChartCtrl::wxPolarAreaChartCtrl(wxWindow *parent,
										   wxWindowID id,
										   const wxPoint &pos,
										   const wxSize &size,
										   long style)
	: wxChart(parent, id, pos, size, style), m_grid(size)
{
}

void wxPolarAreaChartCtrl::Resize(const wxSize &size)
{
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
