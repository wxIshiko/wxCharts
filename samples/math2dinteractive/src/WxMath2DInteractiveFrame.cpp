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
#include <algorithm>

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
            wxColor(0, 0, 255, 0x8F),
            wxColor(250, 20, 20, 0x78),
            wxColor(0, 0, 0, 0xB8),
            data1, wxCHARTTYPE_LINE, false)
        );
    chartData.AddDataset(dataset1);

    wxVector<wxPoint2DDouble> data2;
    wxMath2DPlotDataset::ptr dataset2(
        new wxMath2DPlotDataset(
            wxColor(0, 0, 0xFF, 0xFF),
            wxColor(0, 0xFF, 0, 0x78),
            wxColor(0xFF, 0, 0, 0x78),
            data2, wxCHARTTYPE_LINE, true, false)
        );
    chartData.AddDataset(dataset2);

    math2dPlotCtrl = new wxMath2DPlotCtrl(panel, wxID_ANY, chartData,options);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(math2dPlotCtrl, 1, wxEXPAND);
    panel->SetSizer(panelSizer);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(topSizer);

    m_timer = new wxTimer(this,wxID_EXECUTE);
    m_timer->Start(25);
    this->Bind(wxEVT_TIMER, [&](wxTimerEvent& )
    {
        const int n = 100;
        static int idx(0);
        static bool first(true);

        static wxVector<wxPoint2DDouble> t0(n);

        const double ofs = 10;
        const double A0 = 5;
        const double A1 = 20;

        const double ow = 2.*M_PI/n * (3.+1./10);
        const double oa = 2.*M_PI/n * (1./40);

        for (int i = 0; i < n; ++i, ++idx)
            t0[i] = wxPoint2DDouble(1.*i / n, ofs + (A0 + A1 * sin(idx*oa)) * sin(idx*ow));


        //t1.push_back(wxPoint2DDouble(++i,distribution(m_generator)));
        //t2.push_back(wxPoint2DDouble(++m_c,distribution(m_generator)));
        //
        if (first) {
            auto xminmax = std::minmax_element(t0.begin(), t0.end(), [&](const wxPoint2DDouble& a, const wxPoint2DDouble& b) {return a.m_x < b.m_x; });
            auto yminmax = std::minmax_element(t0.begin(), t0.end(), [&](const wxPoint2DDouble& a, const wxPoint2DDouble& b) {return a.m_y < b.m_y; });
            
            wxPoint2DDouble xymin(xminmax.first->m_x, ofs - A0 - A1);
            wxPoint2DDouble xymax(xminmax.second->m_x, ofs + A0 + A1);

            math2dPlotCtrl->SetFixedAxesRange(xymin, xymax);
            math2dPlotCtrl->UpdateData(0, t0);
        }
        else
            math2dPlotCtrl->UpdateDataPoints(0, t0);

        first = false;

    if(idx % (n*60) == 0){
        std::normal_distribution<double> distribution(ofs, A0);
        
        wxVector<wxPoint2DDouble> t1;
        t1.push_back(wxPoint2DDouble(double(++m_c)/n, distribution(m_generator)));
        math2dPlotCtrl->AddData(1,t1);
    }
    },wxID_EXECUTE);
}
