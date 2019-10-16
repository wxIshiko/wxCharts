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

#include "wxbarchartpanel.h"
#include <wx/sizer.h>
#include <wx/choice.h>

wxBarChartPanel::wxBarChartPanel(wxWindow* parent)
    : wxPanel(parent)
{
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString str;
    str.Add("first");
    str.Add("second");
    wxChoice* choice = new wxChoice(this, -1, wxDefaultPosition, wxDefaultSize, str);
    sizer->Add(choice);

    // Create the data for the bar chart widget
    wxVector<wxString> labels;
    labels.push_back("January");
    labels.push_back("February");
    labels.push_back("March");
    labels.push_back("April");
    labels.push_back("May");
    labels.push_back("June");
    labels.push_back("July");
    wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared(labels);

    // Add the first dataset
    wxVector<wxDouble> points1;
    points1.push_back(3);
    points1.push_back(2.5);
    points1.push_back(1.2);
    points1.push_back(3);
    points1.push_back(6);
    points1.push_back(5);
    points1.push_back(1);
    wxChartsDoubleDataset::ptr dataset1(new wxChartsDoubleDataset("Dataset 1", points1));
    chartData->AddDataset(dataset1);

    // Create the column chart widget
    m_barChart = new wxBarChartCtrl(this, wxID_ANY, chartData);
    sizer->Add(m_barChart, 1, wxEXPAND);

    SetSizer(sizer);
}
