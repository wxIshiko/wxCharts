/*
    Copyright (c) 2018-2021 Xavier Leclercq

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

#include "wxchartsrectanglepanel.h"
#include <wx/sharedptr.h>
#include <wx/sizer.h>

wxChartsRectanglePanel::wxChartsRectanglePanel(wxWindow* parent)
    : wxPanel(parent)
{
    wxChartsRectangleOptions options(wxChartsPenOptions(*wxBLACK, 2), *wxRED, 0);
    m_rectangle = new wxChartsRectangle(
        0, 0,
        wxSharedPtr<wxChartTooltipProvider>(),
        options
    );
    m_rectangle->SetSize(100, 20);

    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    m_canvas = new ElementCanvasWindow(this);
    m_canvas->setElement(m_rectangle);
    sizer->Add(m_canvas, 1, wxEXPAND);

    SetSizer(sizer);
}
