/*
    Copyright (c) 2016-2021 Xavier Leclercq

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
#include <wx/dcbuffer.h>

wxChartCtrl::wxChartCtrl(wxWindow *parent,
                         wxWindowID id,
                         const wxPoint &pos,
                         const wxSize &size,
                         long style)
    : wxControl(parent, id, pos, size, style)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(*wxWHITE);
}

void wxChartCtrl::SetTitle(const wxString& text, const wxChartsLabelOptions& options)
{
    GetChart().SetTitle(text, options);
}

wxSize wxChartCtrl::DoGetBestClientSize() const
{
    return GetChart().GetBestSize();
}

void wxChartCtrl::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        GetChart().Draw(*gc);
        delete gc;
    }
}

void wxChartCtrl::OnSize(wxSizeEvent &evt)
{
    if (GetChart().GetCommonOptions().IsResponsive())
    {
        GetChart().SetSize(evt.GetSize());
        Refresh();
    }
}

void wxChartCtrl::OnMouseOver(wxMouseEvent &evt)
{
    if (GetChart().GetCommonOptions().ShowTooltips())
    {
        GetChart().ActivateElementsAt(evt.GetPosition());
        Refresh();
    }
}

BEGIN_EVENT_TABLE(wxChartCtrl, wxControl)
    EVT_PAINT(wxChartCtrl::OnPaint)
    EVT_SIZE(wxChartCtrl::OnSize)
    EVT_MOTION(wxChartCtrl::OnMouseOver)
END_EVENT_TABLE()
