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

#include "wxchartlegendctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxChartLegendItem::wxChartLegendItem(const wxColor &color, 
									 const wxString &label)
	: m_color(color), m_label(label)
{
}

const wxColor& wxChartLegendItem::GetColor() const
{
	return m_color;
}

const wxString& wxChartLegendItem::GetLabel() const
{
	return m_label;
}

wxChartLegendData::wxChartLegendData()
{
}

void wxChartLegendData::Append(const wxChartLegendItem &item)
{
	m_items.push_back(item);
}

const wxVector<wxChartLegendItem>& wxChartLegendData::GetItems() const
{
	return m_items;
}

wxChartLegendCtrl::wxChartLegendCtrl(wxWindow *parent,
									 wxWindowID id,
									 const wxChartLegendData &data,
									 const wxPoint &pos,
									 const wxSize &size,
									 long style)
	: wxControl(parent, id, pos, size, style), m_items(data.GetItems())
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(*wxWHITE);
}

void wxChartLegendCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		wxFont font(wxSize(0, m_options.GetFontSize()),
			m_options.GetFontFamily(), m_options.GetFontStyle(), wxFONTWEIGHT_NORMAL);
		gc->SetFont(font, m_options.GetFontColor());

		wxDouble y = 0;
		for (size_t i = 0; i < m_items.size(); ++i)
		{
			wxGraphicsPath path = gc->CreatePath();

			path.AddRoundedRectangle(0, y, 10, 10, 0.1);

			wxBrush brush(m_items[i].GetColor());
			gc->SetBrush(brush);
			gc->FillPath(path);
			
			gc->DrawText(m_items[i].GetLabel(), 30, y);
			y += m_options.GetFontSize();
		}

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxChartLegendCtrl, wxControl)
	EVT_PAINT(wxChartLegendCtrl::OnPaint)
END_EVENT_TABLE()
