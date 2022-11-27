/*
    Copyright (c) 2017-2019 Xavier Leclercq

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

#include "wxareachartframe.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>

wxAreaChartFrame::wxAreaChartFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    // Create a top-level panel to hold all the contents of the frame
    wxPanel* panel = new wxPanel(this, wxID_ANY);

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
    wxAreaChartCtrl* areaChartCtrl = new wxAreaChartCtrl(panel, wxID_ANY, chartData);

    // Set up the sizer for the panel
    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(areaChartCtrl, 1, wxEXPAND);
    panel->SetSizer(panelSizer);
}
