/*
    Copyright (c) 2018 Xavier Leclercq

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

class wxChartsTestsFrame : public wxFrame
{
public:
    wxChartsTestsFrame(const wxString& title);

private:
    void OnExit(wxCommandEvent& evt);
    void OnChartRectangleElement(wxCommandEvent& evt);
    void OnChartLabelElement(wxCommandEvent& evt);
    void OnChartCategoricalAxisElement(wxCommandEvent& evt);
    void OnChartNumericalAxisElement(wxCommandEvent& evt);
    void OnChartGridElement(wxCommandEvent& evt);
    void OnAreaChart(wxCommandEvent& evt);
    void OnBarChart(wxCommandEvent& evt);
    void OnBubbleChart(wxCommandEvent& evt);
    void OnCandlestickChart(wxCommandEvent& evt);
    void OnColumnChart(wxCommandEvent& evt);
    void OnPieChart(wxCommandEvent& evt);
    void OnPolarAreaChart(wxCommandEvent& evt);
    void OnRunAllTests(wxCommandEvent& evt);

    void SwitchPanel(wxPanel* newPanel);

private:
    wxPanel* m_currentPanel;
    wxPanel* m_chartRectanglePanel;
    wxPanel* m_chartLabelPanel;
    wxPanel* m_chartCategoricalAxisPanel;
    wxPanel* m_chartNumericalAxisPanel;
    wxPanel* m_chartGridPanel;
    wxPanel* m_areaChartPanel;
    wxPanel* m_barChartPanel;
    wxPanel* m_bubbleChartPanel;
    wxPanel* m_candlestickChartPanel;
    wxPanel* m_columnChartPanel;
    wxPanel* m_pieChartPanel;
    wxPanel* m_polarAreaChartPanel;

    wxDECLARE_EVENT_TABLE();
};

#endif
