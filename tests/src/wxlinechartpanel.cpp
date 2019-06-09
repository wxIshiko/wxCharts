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

#include "wxlinechartpanel.h"
#include <wx/sizer.h>

wxLineChartPanel::wxLineChartPanel(wxWindow* parent)
    : wxPanel(parent)
{
    // Create the data for the line chart widget
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
    points1.push_back(-2.5);
    points1.push_back(-1.2);
    points1.push_back(3);
    points1.push_back(6);
    points1.push_back(5);
    points1.push_back(1);
    wxChartsDoubleDataset::ptr dataset1(new wxChartsDoubleDataset("My First Dataset", points1));
    chartData->AddDataset(dataset1);

    // Add the second dataset
    wxVector<wxDouble> points2;
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
    points2.push_back(-1.8);
    points2.push_back(0.4);
    wxChartsDoubleDataset::ptr dataset2(new wxChartsDoubleDataset("My Second Dataset", points2));
    chartData->AddDataset(dataset2);

    // Create the line chart widget from the constructed data
    m_lineChart = new wxLineChartCtrl(this, wxID_ANY, chartData, wxCHARTSLINETYPE_STRAIGHT,
        wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

    // Set up the sizer for the panel
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_lineChart, 1, wxEXPAND);

    SetSizer(sizer);
}
