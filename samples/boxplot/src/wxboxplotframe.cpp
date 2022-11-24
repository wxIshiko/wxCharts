/*
    Copyright (c) 2018-2019 Xavier Leclercq and the wxCharts contributors.

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

#include "wxboxplotframe.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>

wxBoxPlotFrame::wxBoxPlotFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    // Create a top-level panel to hold all the contents of the frame
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create the data for the boxplot chart widget
    wxVector<wxString> labels;
    labels.push_back("A1");
    labels.push_back("A2");

    wxVector<wxVector<wxDouble>> data;
    //data from http://www.physics.csbsju.edu/stats/box2.html
    double A1[]={0.22, -0.87, -2.39, -1.79, 0.37, -1.54, 1.28, -0.31, -0.74, 1.72, 0.38, -0.17, -0.62, -1.10, 0.30, 0.15, 2.30, 0.19, -0.50, -0.09};
    double A2[]={-5.13, -2.19, -2.43, -3.83, 0.50, -3.25, 4.32, 1.63, 5.18, -0.43, 7.11, 4.87, -3.10, -5.81, 3.76, 6.31, 2.58, 0.07, 5.76, 3.50}; 
    wxVector<wxDouble> vec1(std::begin(A1),std::end(A1)),vec2(std::begin(A2),std::end(A2));
    data.push_back(vec1);
    data.push_back(vec2);

    wxBoxPlotData chartData(labels, data);

    // Create the boxplot chart widget from the constructed data
    wxBoxPlotCtrl* boxplotChartCtrl = new wxBoxPlotCtrl(panel, wxID_ANY, chartData,
        wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

    // Set up the sizer for the panel
    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(boxplotChartCtrl, 1, wxEXPAND);
    panel->SetSizer(panelSizer);
}
