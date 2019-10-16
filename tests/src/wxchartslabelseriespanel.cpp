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

#include "wxchartslabelseriespanel.h"
#include "wxchartslabelpanel.h"
#include <wx/splitter.h>
#include <wx/sizer.h>

wxChartsLabelSeriesPanel::wxChartsLabelSeriesPanel(wxWindow* parent)
    : wxPanel(parent)
{
    wxSplitterWindow* splitterWindow = new wxSplitterWindow(this, wxID_ANY);
    splitterWindow->SetMinimumPaneSize(50);

    wxPanel* panel1 = new wxChartsLabelPanel(splitterWindow);
    wxPanel* panel2 = new wxChartsLabelPanel(splitterWindow);

    splitterWindow->SplitVertically(panel1, panel2);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(splitterWindow, 1, wxEXPAND);
    SetSizer(topSizer);
}
