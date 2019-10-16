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

#include "wxareachartpanel.h"
#include <wx/sizer.h>

wxAreaChartPanel::wxAreaChartPanel(wxWindow* parent)
    : wxPanel(parent)
{
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Create the data for the area chart widget
    wxAreaChartData chartData;

    // Add a dataset
    wxVector<wxPoint2DDouble> points1;
    points1.push_back(wxPoint2DDouble(3, 3));
    points1.push_back(wxPoint2DDouble(3.5, 4));
    points1.push_back(wxPoint2DDouble(6, 2));
    points1.push_back(wxPoint2DDouble(7, -1));
    points1.push_back(wxPoint2DDouble(5, 0));
    points1.push_back(wxPoint2DDouble(4.5, 1.7));
    wxAreaChartDataset::ptr dataset1(new wxAreaChartDataset(points1));
    chartData.AddDataset(dataset1);

    // Create the area chart widget
    m_areaChart = new wxAreaChartCtrl(this, wxID_ANY, chartData);
    sizer->Add(m_areaChart, 1, wxEXPAND);

    SetSizer(sizer);
}
