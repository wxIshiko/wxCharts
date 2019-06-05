/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#include "elementcanvaswindow.h"
#include <wx/dcbuffer.h>

ElementCanvasWindow::ElementCanvasWindow(wxWindow* parent)
    : wxWindow(parent, wxID_ANY), m_element(0)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(*wxWHITE);
}

void ElementCanvasWindow::setElement(const wxChartsElement* element)
{
    m_element = element;
}

void ElementCanvasWindow::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        DrawGrid(*gc);

        if (m_element)
        {
            m_element->Draw(*gc);
        }
        delete gc;
    }
}

void ElementCanvasWindow::DrawGrid(wxGraphicsContext &gc)
{
    wxPen pen(wxColor(0x7F, 0x7F, 0x7F), 1);
    gc.SetPen(pen);
    for (size_t i = 0; i < 20; i += 10)
    {
        gc.StrokeLine(i, 0, i, 20);
    }
}

BEGIN_EVENT_TABLE(ElementCanvasWindow, wxWindow)
    EVT_PAINT(ElementCanvasWindow::OnPaint)
END_EVENT_TABLE()
