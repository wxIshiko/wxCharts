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

#include "wxlinechartctrl.h"
#include <wx/dcclient.h>
#include <wx/graphics.h>

wxLineChartOptions::wxLineChartOptions()
	: m_gridLineWidth(1), m_gridLineColor(0, 0, 0, 0x20)
{
}

unsigned int wxLineChartOptions::GetGridLineWidth() const
{
	return m_gridLineWidth;
}

const wxColor& wxLineChartOptions::GetGridLineColor() const
{
	return m_gridLineColor;
}

wxLineChartCtrl::wxLineChartCtrl(wxWindow *parent,
								 wxWindowID id,
								 const std::vector<std::string> &labels,
								 const wxPoint &pos,
								 const wxSize &size,
								 long style)
	: wxControl(parent, id, pos, size, style), 
	m_grid(labels, m_options.GetGridLineWidth(),m_options.GetGridLineColor())
{
	SetBackgroundColour(*wxWHITE);
}

void wxLineChartCtrl::AddData()
{
}

void wxLineChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxPaintDC dc(this);
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		delete gc;
	}
}

void wxLineChartCtrl::OnSize(wxSizeEvent& evt)
{
	Refresh();
}

BEGIN_EVENT_TABLE(wxLineChartCtrl, wxControl)
	EVT_PAINT(wxLineChartCtrl::OnPaint)
	EVT_SIZE(wxLineChartCtrl::OnSize)
END_EVENT_TABLE()
