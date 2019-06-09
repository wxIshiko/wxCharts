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

#include "wxchartstestsframe.h"
#include "wxchartstestsmenubar.h"
#include "wxchartstestswindowids.h"
#include "wxchartsdefaultthemepanel.h"
#include "wxchartsrectanglepanel.h"
#include "wxchartslabelseriespanel.h"
#include "wxchartscategoricalaxispanel.h"
#include "wxchartsnumericalaxispanel.h"
#include "wxchartsgridpanel.h"
#include "wxareachartpanel.h"
#include "wxbarchartpanel.h"
#include "wxboxplotpanel.h"
#include "wxbubblechartpanel.h"
#include "wxcandlestickchartpanel.h"
#include "wxcolumnchartpanel.h"
#include "wxdoughnutchartpanel.h"
#include "wxhistogrampanel.h"
#include "wxlinechartpanel.h"
#include "wxpiechartpanel.h"
#include "wxpolarareachartpanel.h"
#include "wxstackedbarchartpanel.h"
#include "wxstackedcolumnchartpanel.h"
#include "tests/testsuite.h"
#include <wx/sizer.h>
#include <wx/splitter.h>

wxChartsTestsFrame::wxChartsTestsFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720)), 
    m_currentPanel(0),
    m_chartsRectanglePanel(0), m_chartsGridPanel(0),
    m_chartsCategoricalAxisPanel(0), m_chartsNumericalAxisPanel(0),
    m_columnChartPanel(0), m_pieChartPanel(0)
{
    SetMenuBar(new wxChartsTestsMenuBar());

    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxSplitterWindow* splitterWindow = new wxSplitterWindow(this, wxID_ANY);
    splitterWindow->SetMinimumPaneSize(50);

    m_mainPanel = new wxPanel(splitterWindow);

    wxSizer* mainPanelSizer = new wxBoxSizer(wxVERTICAL);
    m_mainPanel->SetSizer(mainPanelSizer);

    m_chartsDefaultThemePanel = new wxChartsDefaultThemePanel(m_mainPanel);
    mainPanelSizer->Add(m_chartsDefaultThemePanel, 1, wxEXPAND);
    m_chartsDefaultThemePanel->Hide();

    m_chartsRectanglePanel = new wxChartsRectanglePanel(m_mainPanel);
    mainPanelSizer->Add(m_chartsRectanglePanel, 1, wxEXPAND);
    m_chartsRectanglePanel->Hide();

    m_chartsLabelPanel = new wxChartsLabelSeriesPanel(m_mainPanel);
    mainPanelSizer->Add(m_chartsLabelPanel, 1, wxEXPAND);
    m_chartsLabelPanel->Hide();

    m_chartsCategoricalAxisPanel = new wxChartsCategoricalAxisPanel(m_mainPanel);
    mainPanelSizer->Add(m_chartsCategoricalAxisPanel, 1, wxEXPAND);
    m_chartsCategoricalAxisPanel->Hide();

    m_chartsNumericalAxisPanel = new wxChartsNumericalAxisPanel(m_mainPanel);
    mainPanelSizer->Add(m_chartsNumericalAxisPanel, 1, wxEXPAND);
    m_chartsNumericalAxisPanel->Hide();

    m_chartsGridPanel = new wxChartsGridPanel(m_mainPanel);
    mainPanelSizer->Add(m_chartsGridPanel, 1, wxEXPAND);
    m_chartsGridPanel->Hide();

    m_areaChartPanel = new wxAreaChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_areaChartPanel, 1, wxEXPAND);
    m_areaChartPanel->Hide();

    m_barChartPanel = new wxBarChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_barChartPanel, 1, wxEXPAND);
    m_barChartPanel->Hide();

    m_boxPlotPanel = new wxBoxPlotPanel(m_mainPanel);
    mainPanelSizer->Add(m_boxPlotPanel, 1, wxEXPAND);
    m_boxPlotPanel->Hide();

    m_bubbleChartPanel = new wxBubbleChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_bubbleChartPanel, 1, wxEXPAND);
    m_bubbleChartPanel->Hide();

    m_candlestickChartPanel = new wxCandlestickChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_candlestickChartPanel, 1, wxEXPAND);
    m_candlestickChartPanel->Hide();

    m_columnChartPanel = new wxColumnChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_columnChartPanel, 1, wxEXPAND);
    m_columnChartPanel->Hide();

    m_doughnutChartPanel = new wxDoughnutChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_doughnutChartPanel, 1, wxEXPAND);
    m_doughnutChartPanel->Hide();

    m_histogramPanel = new wxHistogramPanel(m_mainPanel);
    mainPanelSizer->Add(m_histogramPanel, 1, wxEXPAND);
    m_histogramPanel->Hide();

    m_lineChartPanel = new wxLineChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_lineChartPanel, 1, wxEXPAND);
    m_lineChartPanel->Hide();

    m_pieChartPanel = new wxPieChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_pieChartPanel, 1, wxEXPAND);
    m_pieChartPanel->Hide();

    m_polarAreaChartPanel = new wxPolarAreaChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_polarAreaChartPanel, 1, wxEXPAND);
    m_polarAreaChartPanel->Hide();

    m_stackedBarChartPanel = new wxStackedBarChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_stackedBarChartPanel, 1, wxEXPAND);
    m_stackedBarChartPanel->Hide();

    m_stackedColumnChartPanel = new wxStackedColumnChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_stackedColumnChartPanel, 1, wxEXPAND);
    m_stackedColumnChartPanel->Hide();

    wxPanel* outputPanel = new wxPanel(splitterWindow);
    wxSizer* outputPanelSizer = new wxBoxSizer(wxVERTICAL);
    outputPanel->SetSizer(outputPanelSizer);

    m_output = new wxTextCtrl(outputPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    outputPanelSizer->Add(m_output, 1, wxEXPAND);

    splitterWindow->SplitHorizontally(m_mainPanel, outputPanel);
    sizer->Add(splitterWindow, 1, wxEXPAND);

    m_currentPanel = m_columnChartPanel;
    m_currentPanel->Show();

    SetSizer(sizer);
}

void wxChartsTestsFrame::OnExit(wxCommandEvent& evt)
{
    Close();
}

void wxChartsTestsFrame::OnDefaultTheme(wxCommandEvent& evt)
{
    SwitchPanel(m_chartsDefaultThemePanel);
}

void wxChartsTestsFrame::OnChartsRectangleElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartsRectanglePanel);
}

void wxChartsTestsFrame::OnChartsLabelElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartsLabelPanel);
}

void wxChartsTestsFrame::OnChartsCategoricalAxisElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartsCategoricalAxisPanel);
}

void wxChartsTestsFrame::OnChartsNumericalAxisElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartsNumericalAxisPanel);
}

void wxChartsTestsFrame::OnChartsGridElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartsGridPanel);
}

void wxChartsTestsFrame::OnAreaChart(wxCommandEvent& evt)
{
    SwitchPanel(m_areaChartPanel);
}

void wxChartsTestsFrame::OnBarChart(wxCommandEvent& evt)
{
    SwitchPanel(m_barChartPanel);
}

void wxChartsTestsFrame::OnBoxPlot(wxCommandEvent& evt)
{
    SwitchPanel(m_boxPlotPanel);
}

void wxChartsTestsFrame::OnBubbleChart(wxCommandEvent& evt)
{
    SwitchPanel(m_bubbleChartPanel);
}

void wxChartsTestsFrame::OnCandlestickChart(wxCommandEvent& evt)
{
    SwitchPanel(m_candlestickChartPanel);
}

void wxChartsTestsFrame::OnColumnChart(wxCommandEvent& evt)
{
    SwitchPanel(m_columnChartPanel);
}

void wxChartsTestsFrame::OnDoughnutChart(wxCommandEvent& evt)
{
    SwitchPanel(m_doughnutChartPanel);
}

void wxChartsTestsFrame::OnHistogram(wxCommandEvent& evt)
{
    SwitchPanel(m_histogramPanel);
}

void wxChartsTestsFrame::OnLineChart(wxCommandEvent& evt)
{
    SwitchPanel(m_lineChartPanel);
}

void wxChartsTestsFrame::OnPieChart(wxCommandEvent& evt)
{
    SwitchPanel(m_pieChartPanel);
}

void wxChartsTestsFrame::OnPolarAreaChart(wxCommandEvent& evt)
{
    SwitchPanel(m_polarAreaChartPanel);
}

void wxChartsTestsFrame::OnStackedBarChart(wxCommandEvent& evt)
{
    SwitchPanel(m_stackedBarChartPanel);
}

void wxChartsTestsFrame::OnStackedColumnChart(wxCommandEvent& evt)
{
    SwitchPanel(m_stackedColumnChartPanel);
}

void wxChartsTestsFrame::OnRunAllTests(wxCommandEvent& evt)
{
    wxStreamToTextRedirector redirect(m_output);

    TestSuite tests;
    tests.run();
}

void wxChartsTestsFrame::SwitchPanel(wxPanel* newPanel)
{
    m_currentPanel->Hide();
    m_currentPanel = newPanel;
    m_currentPanel->Show();
    m_mainPanel->Layout();
}

wxBEGIN_EVENT_TABLE(wxChartsTestsFrame, wxFrame)
    EVT_MENU(wxID_EXIT, wxChartsTestsFrame::OnExit)
    EVT_MENU(wxID_DEFAULT_THEME, wxChartsTestsFrame::OnDefaultTheme)
    EVT_MENU(wxID_RECTANGLE_ELEMENT, wxChartsTestsFrame::OnChartsRectangleElement)
    EVT_MENU(wxID_LABEL_ELEMENT, wxChartsTestsFrame::OnChartsLabelElement)
    EVT_MENU(wxID_CATEGORICALAXIS_ELEMENT, wxChartsTestsFrame::OnChartsCategoricalAxisElement)
    EVT_MENU(wxID_NUMERICALAXIS_ELEMENT, wxChartsTestsFrame::OnChartsNumericalAxisElement)
    EVT_MENU(wxID_GRID_ELEMENT, wxChartsTestsFrame::OnChartsGridElement)
    EVT_MENU(wxID_AREA_CHART, wxChartsTestsFrame::OnAreaChart)
    EVT_MENU(wxID_BAR_CHART, wxChartsTestsFrame::OnBarChart)
    EVT_MENU(wxID_BOX_PLOT, wxChartsTestsFrame::OnBoxPlot)
    EVT_MENU(wxID_BUBBLE_CHART, wxChartsTestsFrame::OnBubbleChart)
    EVT_MENU(wxID_CANDLESTICK_CHART, wxChartsTestsFrame::OnCandlestickChart)
    EVT_MENU(wxID_COLUMN_CHART, wxChartsTestsFrame::OnColumnChart)
    EVT_MENU(wxID_DOUGHNUT_CHART, wxChartsTestsFrame::OnDoughnutChart)
    EVT_MENU(wxID_HISTOGRAM, wxChartsTestsFrame::OnHistogram)
    EVT_MENU(wxID_LINE_CHART, wxChartsTestsFrame::OnLineChart)
    EVT_MENU(wxID_PIE_CHART, wxChartsTestsFrame::OnPieChart)
    EVT_MENU(wxID_POLARAREA_CHART, wxChartsTestsFrame::OnPolarAreaChart)
    EVT_MENU(wxID_STACKEDBAR_CHART, wxChartsTestsFrame::OnStackedBarChart)
    EVT_MENU(wxID_STACKEDCOLUMN_CHART, wxChartsTestsFrame::OnStackedColumnChart)
    EVT_MENU(wxID_ALL_TESTS, wxChartsTestsFrame::OnRunAllTests)
wxEND_EVENT_TABLE()
