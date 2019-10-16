/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "wxdoughnutchartpanel.h"
#include <wx/sizer.h>
#include <wx/choice.h>

wxDoughnutChartPanel::wxDoughnutChartPanel(wxWindow* parent)
    : wxPanel(parent)
{
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString str;
    str.Add("three");
    str.Add("four");
    wxChoice* choice = new wxChoice(this, -1, wxDefaultPosition, wxDefaultSize, str);
    sizer->Add(choice);

    // Create the data for the pie chart widget
    wxPieChartData::ptr chartData = wxPieChartData::make_shared();
    chartData->AppendSlice(wxChartSliceData(300, wxColor(0x4A46F7), "Red"));
    chartData->AppendSlice(wxChartSliceData(50, wxColor(0xBDBF46), "Green"));
    chartData->AppendSlice(wxChartSliceData(100, wxColor(0x5CB4FD), "Yellow"));
    chartData->AppendSlice(wxChartSliceData(40, wxColor(0xB19F94), "Grey"));
    chartData->AppendSlice(wxChartSliceData(120, wxColor(0x60534D), "Dark Grey"));

    // Create the pie chart widget
    m_doughnutChart = new wxDoughnutChartCtrl(this, wxID_ANY, chartData,
        wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    sizer->Add(m_doughnutChart, 1, wxEXPAND);

    SetSizer(sizer);
}
