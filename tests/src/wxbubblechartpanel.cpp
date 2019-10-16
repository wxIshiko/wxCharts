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

#include "wxbubblechartpanel.h"
#include <wx/sizer.h>
#include <wx/choice.h>

wxBubbleChartPanel::wxBubbleChartPanel(wxWindow* parent)
    : wxPanel(parent)
{
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Create the data for the bubble chart widget
    wxBubbleChartData chartData;

    // Add the first dataset
    wxVector<wxDoubleTriplet> points1;
    points1.push_back(wxDoubleTriplet(-0.2, 3.5, 1));
    points1.push_back(wxDoubleTriplet(0.5, 2.5, 1));
    points1.push_back(wxDoubleTriplet(1.2, 0.1, 1));
    points1.push_back(wxDoubleTriplet(1.5, 1.6, 2));
    points1.push_back(wxDoubleTriplet(2, 1.8, 2));
    points1.push_back(wxDoubleTriplet(2.2, 2.1, 3));
    points1.push_back(wxDoubleTriplet(2.7, 2, 3));
    wxBubbleChartDataset::ptr dataset1(
        new wxBubbleChartDataset(
            wxColor(250, 20, 20, 0x78),
            *wxWHITE,
            points1)
    );
    chartData.AddDataset(dataset1);

    // Add the second dataset
    wxVector<wxDoubleTriplet> points2;
    points2.push_back(wxDoubleTriplet(-0.3, 6.5, 0.5));
    points2.push_back(wxDoubleTriplet(0.2, -1.5, 0.5));
    points2.push_back(wxDoubleTriplet(1.6, 0.7, 1));
    points2.push_back(wxDoubleTriplet(1.5, 4.1, 1));
    points2.push_back(wxDoubleTriplet(1.8, 2.7, 2));
    points2.push_back(wxDoubleTriplet(2.1, 2, 2));
    points2.push_back(wxDoubleTriplet(2.3, 6, 5));
    wxBubbleChartDataset::ptr dataset2(
        new wxBubbleChartDataset(
            wxColor(20, 20, 20, 0x58),
            *wxWHITE,
            points2)
    );
    chartData.AddDataset(dataset2);

    // Create the bubble chart widget
    m_bubbleChart = new wxBubbleChartCtrl(this, wxID_ANY, chartData);
    sizer->Add(m_bubbleChart, 1, wxEXPAND);

    SetSizer(sizer);
}
