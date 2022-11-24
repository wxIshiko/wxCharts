/*
    Copyright (c) 2017-2019 Xavier Leclercq and the wxCharts contributors.

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
#include <cmath>
#include <chrono>


WxMath2DInteractiveFrame::WxMath2DInteractiveFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title), m_c(1),
    m_generator(std::chrono::system_clock::now().time_since_epoch().count())
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxMath2DPlotData chartData;
    wxSharedPtr<wxMath2DPlotOptions> options(new wxMath2DPlotOptions());
    options->GetCommonOptions().SetShowTooltips(false);

    wxVector<wxPoint2DDouble> data1;
    wxMath2DPlotDataset::ptr dataset1(
        new wxMath2DPlotDataset(
            wxColor(255, 255, 255, 0),
            wxColor(250, 20, 20, 0x78),
            wxColor(0, 0, 0, 0xB8),
            data1)
        );
    chartData.AddDataset(dataset1);

    wxVector<wxPoint2DDouble> data2;
    wxMath2DPlotDataset::ptr dataset2(
        new wxMath2DPlotDataset(
            wxColor(255, 255, 255, 0),
            wxColor(0, 70, 140, 0x78),
            wxColor(50, 210, 105, 0xB8),
            data2)
        );
    chartData.AddDataset(dataset2);

    math2dPlotCtrl = new wxMath2DPlotCtrl(panel, wxID_ANY, chartData,options);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(math2dPlotCtrl, 1, wxEXPAND);
    panel->SetSizer(panelSizer);

    m_timer = new wxTimer(this,wxID_EXECUTE);
    m_timer->Start(1500);
    this->Bind(wxEVT_TIMER, [&](wxTimerEvent& )
    {
        std::uniform_real_distribution<double> distribution (0,100.0);
        wxVector<wxPoint2DDouble> t1,t2;
        t1.push_back(wxPoint2DDouble(++m_c,distribution(m_generator)));
        t2.push_back(wxPoint2DDouble(++m_c,distribution(m_generator)));
        math2dPlotCtrl->AddData(0,t1);
        math2dPlotCtrl->AddData(1,t2);
    },wxID_EXECUTE);
}
