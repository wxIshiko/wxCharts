/*
    Copyright (c) 2017 Xavier Leclercq and the wxCharts contributors.

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

#include "WxMath2DInteractiveFrame.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>
#include <cmath>

WxMath2DInteractiveFrame::WxMath2DInteractiveFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxMath2DPlotData chartData;
    wxMath2DPlotOptions options;
    options.SetShowTooltips(false);

    wxVector<wxPoint2DDouble> points1,points2,points3;
    auto pi = 3.1415926535897;
    auto tstart = -2*pi;
    for(auto i = 0u;i<100;i++)
    {
        auto x = tstart+0.1*i;
        points1.push_back(wxPoint2DDouble(x,cos(x)*sin(x)));
        points2.push_back(wxPoint2DDouble(x,cos(x)+sin(x)));
        points3.push_back(wxPoint2DDouble(x,cos(x)-sin(x)));
    }

    wxMath2DPlotDataset::ptr dataset1(
        new wxMath2DPlotDataset(
            wxColor(250, 20, 20, 0x78),
            wxColor(0, 0, 0, 0xB8),
            points1,wxCHARTTYPE_STEM)
        );
    chartData.AddDataset(dataset1);

     wxMath2DPlotDataset::ptr dataset2(
        new wxMath2DPlotDataset(
            wxColor(0, 70, 140, 0x78),
            wxColor(50, 210, 105, 0xB8),
            points2,wxCHARTTYPE_STEPPED)
        );
    chartData.AddDataset(dataset2);

     wxMath2DPlotDataset::ptr dataset3(
        new wxMath2DPlotDataset(
            wxColor(28, 200, 10, 0x78),
            wxColor(230, 125, 60, 0x33),points3));
    chartData.AddDataset(dataset3);

    wxMath2DPlotCtrl* math2dPlotCtrl = new wxMath2DPlotCtrl(panel, wxID_ANY, chartData,options);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(math2dPlotCtrl, 1, wxEXPAND);
    panel->SetSizer(panelSizer);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(topSizer);
}
