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

#include "wxchartsnumericalaxispanel.h"
#include <wx/sizer.h>

wxChartsNumericalAxisPanel::wxChartsNumericalAxisPanel(wxWindow* parent)
    : wxPanel(parent)
{
    m_axis = new wxChartsNumericalAxis("id0", 0, 100, wxChartsAxisOptions(wxCHARTSAXISPOSITION_LEFT));

    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    m_canvas = new ElementCanvasWindow(this);
    m_canvas->setElement(m_axis);
    sizer->Add(m_canvas, 1, wxEXPAND);

    SetSizer(sizer);
}
