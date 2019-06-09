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

#ifndef _TESTS_WX_CHARTS_WXCHARTSTESTSFRAME_H_
#define _TESTS_WX_CHARTS_WXCHARTSTESTSFRAME_H_

#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/textctrl.h>

class wxChartsTestsFrame : public wxFrame
{
public:
    wxChartsTestsFrame(const wxString& title);

private:
    void OnExit(wxCommandEvent& evt);
    void OnDefaultTheme(wxCommandEvent& evt);
    void OnChartsRectangleElement(wxCommandEvent& evt);
    void OnChartsLabelElement(wxCommandEvent& evt);
    void OnChartsCategoricalAxisElement(wxCommandEvent& evt);
    void OnChartsNumericalAxisElement(wxCommandEvent& evt);
    void OnChartsGridElement(wxCommandEvent& evt);
    void OnAreaChart(wxCommandEvent& evt);
    void OnBarChart(wxCommandEvent& evt);
    void OnBoxPlot(wxCommandEvent& evt);
    void OnBubbleChart(wxCommandEvent& evt);
    void OnCandlestickChart(wxCommandEvent& evt);
    void OnColumnChart(wxCommandEvent& evt);
    void OnDoughnutChart(wxCommandEvent& evt);
    void OnHistogram(wxCommandEvent& evt);
    void OnLineChart(wxCommandEvent& evt);
    void OnPieChart(wxCommandEvent& evt);
    void OnPolarAreaChart(wxCommandEvent& evt);
    void OnStackedBarChart(wxCommandEvent& evt);
    void OnStackedColumnChart(wxCommandEvent& evt);
    void OnRunAllTests(wxCommandEvent& evt);

    void SwitchPanel(wxPanel* newPanel);

private:
    wxPanel* m_mainPanel;
    wxTextCtrl* m_output;

    wxPanel* m_currentPanel;
    wxPanel* m_chartsDefaultThemePanel;
    wxPanel* m_chartsRectanglePanel;
    wxPanel* m_chartsLabelPanel;
    wxPanel* m_chartsCategoricalAxisPanel;
    wxPanel* m_chartsNumericalAxisPanel;
    wxPanel* m_chartsGridPanel;
    wxPanel* m_areaChartPanel;
    wxPanel* m_barChartPanel;
    wxPanel* m_boxPlotPanel;
    wxPanel* m_bubbleChartPanel;
    wxPanel* m_candlestickChartPanel;
    wxPanel* m_columnChartPanel;
    wxPanel* m_doughnutChartPanel;
    wxPanel* m_histogramPanel;
    wxPanel* m_lineChartPanel;
    wxPanel* m_pieChartPanel;
    wxPanel* m_polarAreaChartPanel;
    wxPanel* m_stackedBarChartPanel;
    wxPanel* m_stackedColumnChartPanel;

    wxDECLARE_EVENT_TABLE();
};

#endif
