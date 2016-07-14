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

#include "wxchartctrl.h"
#include "wxcharttooltip.h"
#include "wxchartmultitooltip.h"
#include <wx/dcbuffer.h>

wxChartCtrl::wxChartCtrl(wxWindow *parent,
						 wxWindowID id,
						 const wxPoint &pos,
						 const wxSize &size,
						 long style)
	: wxControl(parent, id, pos, size, style),
	m_activeElements(new wxVector<const wxChartElement*>())
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(*wxWHITE);
}

void wxChartCtrl::DrawTooltips(wxGraphicsContext &gc)
{
	if (m_activeElements->size() == 1)
	{
		// If only one element is active draw a normal tooltip
		wxChartTooltip tooltip((*m_activeElements)[0]->GetTooltipPosition(), 
			(*m_activeElements)[0]->GetTooltipProvider()->GetTooltipText());
		tooltip.Draw(gc);
	}
	else if (m_activeElements->size() > 1)
	{
		// If more than one element is active draw a multi-tooltip
		wxChartMultiTooltip multiTooltip((*m_activeElements)[0]->GetTooltipProvider()->GetTooltipTitle(),
            GetOptions().GetMultiTooltipOptions());
		for (size_t j = 0; j < m_activeElements->size(); ++j)
		{
			wxChartTooltip tooltip((*m_activeElements)[j]->GetTooltipPosition(),
				(*m_activeElements)[j]->GetTooltipProvider());
			multiTooltip.AddTooltip(tooltip);
		}
		multiTooltip.Draw(gc);
	}
}

void wxChartCtrl::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        DoDraw(*gc);
        DrawTooltips(*gc);
        delete gc;
    }
}

void wxChartCtrl::OnSize(wxSizeEvent &evt)
{
	if (GetOptions().IsResponsive())
	{
		Resize(evt.GetSize());
		Refresh();
	}
}

void wxChartCtrl::OnMouseOver(wxMouseEvent &evt)
{
	if (GetOptions().ShowTooltips())
	{
		m_activeElements = GetActiveElements(evt.GetPosition());
		Refresh();
	}
}

BEGIN_EVENT_TABLE(wxChartCtrl, wxControl)
    EVT_PAINT(wxChartCtrl::OnPaint)
	EVT_SIZE(wxChartCtrl::OnSize)
	EVT_MOTION(wxChartCtrl::OnMouseOver)
END_EVENT_TABLE()
