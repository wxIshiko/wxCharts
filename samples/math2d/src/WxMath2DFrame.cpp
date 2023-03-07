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

#include "WxMath2DFrame.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>
#include <cmath>

const int ID_LineChart = 1;
const int ID_StemChart = 2;
const int ID_StepChart = 3;
const int ID_CustomXAxis = 4;
const int ID_CustomYAxis = 5;
const int ID_Grid = 6;

WxMath2DFrame::WxMath2DFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    m_menubar = new wxMenuBar( 0 );
    m_typeMenu = new wxMenu();
    wxMenuItem* m_line = new wxMenuItem( m_typeMenu, ID_LineChart, wxString( wxT("Line") ), wxEmptyString, wxITEM_RADIO );
    m_typeMenu->Append( m_line );

    wxMenuItem* m_stem = new wxMenuItem( m_typeMenu, ID_StemChart, wxString( wxT("Stem") ), wxEmptyString, wxITEM_RADIO );
    m_typeMenu->Append( m_stem );

    wxMenuItem* m_step = new wxMenuItem( m_typeMenu, ID_StepChart, wxString( wxT("Step") ), wxEmptyString, wxITEM_RADIO );
    m_typeMenu->Append( m_step );

    m_menubar->Append( m_typeMenu, wxT("ChartType") );

    m_axisMenu = new wxMenu();

    wxMenuItem* m_customX = new wxMenuItem( m_axisMenu, ID_CustomXAxis, wxString( wxT("CustomX(exp)") ), wxEmptyString, wxITEM_CHECK );
    m_axisMenu->Append( m_customX );

    wxMenuItem* m_customY = new wxMenuItem( m_axisMenu, ID_CustomYAxis, wxString( wxT("CustomY(exp)") ), wxEmptyString, wxITEM_CHECK );
    m_axisMenu->Append( m_customY );

    m_menubar->Append( m_axisMenu, wxT("AxisType") );

    m_gridMenu = new wxMenu();
    wxMenuItem* m_grid = new wxMenuItem( m_gridMenu, ID_Grid, wxString( wxT("Grid") ), wxEmptyString, wxITEM_CHECK );
    m_gridMenu->Append( m_grid );
    m_grid->Check( true );

    m_menubar->Append( m_gridMenu, wxT("Grid") );
    this->SetMenuBar( m_menubar );

    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxMath2DPlotData chartData;
    wxSharedPtr<wxMath2DPlotOptions> options(new wxMath2DPlotOptions());
    options->GetCommonOptions().SetShowTooltips(false);

    wxVector<wxPoint2DDouble> points;
    auto pi = 3.1415926535897;
    auto tstart = -2*pi;
    for(auto i = 0u; i<100; i++)
    {
        auto x = tstart+0.1*i;
        points.push_back(wxPoint2DDouble(x,cos(x)*sin(x)));
    }

    wxMath2DPlotDataset::ptr dataset(
        new wxMath2DPlotDataset(
            wxColor(255, 255, 255, 0),
            wxColor(250, 20, 20, 0x78),
            wxColor(0, 0, 0, 0xB8),
            points)
    );
    chartData.AddDataset(dataset);

    math2dPlotCtrl = new wxMath2DPlotCtrl(panel, wxID_ANY, chartData, options);
    wxChartsGridOptions opt = math2dPlotCtrl->GetGridOptions();
    opt.GetHorizontalGridLineOptions().SetMajorGridLineColor(wxColour("Grey"));
    opt.GetVerticalGridLineOptions().SetMajorGridLineColor(wxColour("Grey"));
    math2dPlotCtrl->SetGridOptions(opt);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(math2dPlotCtrl, 1, wxEXPAND);
    panel->SetSizer(panelSizer);

    Binds();
}

void WxMath2DFrame::Binds()
{
    m_gridMenu->Bind(wxEVT_COMMAND_MENU_SELECTED,[&](wxCommandEvent &)
    {
        auto opt = math2dPlotCtrl->GetGridOptions();
        opt.SetShowGridLines(m_gridMenu->IsChecked(ID_Grid));
        math2dPlotCtrl->SetGridOptions(opt);
    }, ID_Grid);

    m_axisMenu->Bind(wxEVT_COMMAND_MENU_SELECTED,[&](wxCommandEvent &)
    {
        auto opt = math2dPlotCtrl->GetChartOptions();
        if (m_axisMenu->IsChecked(ID_CustomXAxis))
            opt.SetAxisFuncX([](wxDouble x){return std::exp(x);});
        else
            opt.SetAxisFuncX([](wxDouble x){return x;});
        math2dPlotCtrl->SetChartOptions(opt);
    }, ID_CustomXAxis);
    m_axisMenu->Bind(wxEVT_COMMAND_MENU_SELECTED,[&](wxCommandEvent &)
    {
        auto opt = math2dPlotCtrl->GetChartOptions();
        if (m_axisMenu->IsChecked(ID_CustomYAxis))
            opt.SetAxisFuncY([](wxDouble x){return std::exp(x);});
        else
            opt.SetAxisFuncY([](wxDouble x){return x;});
        math2dPlotCtrl->SetChartOptions(opt);
    }, ID_CustomYAxis);
    m_typeMenu->Bind(wxEVT_COMMAND_MENU_SELECTED,[&](wxCommandEvent &)
    {
        math2dPlotCtrl->SetChartType(0,wxCHARTTYPE_LINE);
    }, ID_LineChart);
    m_typeMenu->Bind(wxEVT_COMMAND_MENU_SELECTED,[&](wxCommandEvent &)
    {
        math2dPlotCtrl->SetChartType(0,wxCHARTTYPE_STEPPED);
    }, ID_StepChart);
    m_typeMenu->Bind(wxEVT_COMMAND_MENU_SELECTED,[&](wxCommandEvent &)
    {
        math2dPlotCtrl->SetChartType(0,wxCHARTTYPE_STEM);
    }, ID_StemChart);
}
