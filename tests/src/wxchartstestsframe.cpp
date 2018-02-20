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

#include "wxchartstestsframe.h"
#include "wxchartstestsmenubar.h"
#include "wxchartstestswindowids.h"
#include "wxchartrectanglepanel.h"
#include "wxchartlabelseriespanel.h"
#include "wxchartcategoricalaxispanel.h"
#include "wxchartnumericalaxispanel.h"
#include "wxchartgridpanel.h"
#include "wxbarchartpanel.h"
#include "wxbubblechartpanel.h"
#include "wxcolumnchartpanel.h"
#include "wxpiechartpanel.h"
#include "wxpolarareachartpanel.h"
#include <wx/sizer.h>

wxChartsTestsFrame::wxChartsTestsFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720)), 
    m_currentPanel(0),
    m_chartRectanglePanel(0), m_chartGridPanel(0),
    m_chartCategoricalAxisPanel(0), m_chartNumericalAxisPanel(0),
    m_columnChartPanel(0), m_pieChartPanel(0)
{
    SetMenuBar(new wxChartsTestsMenuBar());

    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    m_chartRectanglePanel = new wxChartRectanglePanel(this);
    sizer->Add(m_chartRectanglePanel, 1, wxEXPAND);
    m_chartRectanglePanel->Hide();

    m_chartLabelPanel = new wxChartLabelSeriesPanel(this);
    sizer->Add(m_chartLabelPanel, 1, wxEXPAND);
    m_chartLabelPanel->Hide();

    m_chartCategoricalAxisPanel = new wxChartCategoricalAxisPanel(this);
    sizer->Add(m_chartCategoricalAxisPanel, 1, wxEXPAND);
    m_chartCategoricalAxisPanel->Hide();

    m_chartNumericalAxisPanel = new wxChartNumericalAxisPanel(this);
    sizer->Add(m_chartNumericalAxisPanel, 1, wxEXPAND);
    m_chartNumericalAxisPanel->Hide();

    m_chartGridPanel = new wxChartGridPanel(this);
    sizer->Add(m_chartGridPanel, 1, wxEXPAND);
    m_chartGridPanel->Hide();

    m_barChartPanel = new wxBarChartPanel(this);
    sizer->Add(m_barChartPanel, 1, wxEXPAND);
    m_barChartPanel->Hide();

    m_bubbleChartPanel = new wxBubbleChartPanel(this);
    sizer->Add(m_bubbleChartPanel, 1, wxEXPAND);
    m_bubbleChartPanel->Hide();

    m_columnChartPanel = new wxColumnChartPanel(this);
    sizer->Add(m_columnChartPanel, 1, wxEXPAND);
    m_columnChartPanel->Hide();

    m_pieChartPanel = new wxPieChartPanel(this);
    sizer->Add(m_pieChartPanel, 1, wxEXPAND);
    m_pieChartPanel->Hide();

    m_polarAreaChartPanel = new wxPolarAreaChartPanel(this);
    sizer->Add(m_polarAreaChartPanel, 1, wxEXPAND);
    m_polarAreaChartPanel->Hide();

    m_currentPanel = m_columnChartPanel;
    m_currentPanel->Show();

    SetSizer(sizer);
}

void wxChartsTestsFrame::OnExit(wxCommandEvent& evt)
{
    Close();
}

void wxChartsTestsFrame::OnChartRectangleElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartRectanglePanel);
}

void wxChartsTestsFrame::OnChartLabelElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartLabelPanel);
}

void wxChartsTestsFrame::OnChartCategoricalAxisElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartCategoricalAxisPanel);
}

void wxChartsTestsFrame::OnChartNumericalAxisElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartNumericalAxisPanel);
}

void wxChartsTestsFrame::OnChartGridElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartGridPanel);
}

void wxChartsTestsFrame::OnBarChart(wxCommandEvent& evt)
{
    SwitchPanel(m_barChartPanel);
}

void wxChartsTestsFrame::OnBubbleChart(wxCommandEvent& evt)
{
    SwitchPanel(m_bubbleChartPanel);
}

void wxChartsTestsFrame::OnColumnChart(wxCommandEvent& evt)
{
    SwitchPanel(m_columnChartPanel);
}

void wxChartsTestsFrame::OnPieChart(wxCommandEvent& evt)
{
    SwitchPanel(m_pieChartPanel);
}

void wxChartsTestsFrame::OnPolarAreaChart(wxCommandEvent& evt)
{
    SwitchPanel(m_polarAreaChartPanel);
}

void wxChartsTestsFrame::SwitchPanel(wxPanel* newPanel)
{
    m_currentPanel->Hide();
    m_currentPanel = newPanel;
    m_currentPanel->Show();
    Layout();
}

wxBEGIN_EVENT_TABLE(wxChartsTestsFrame, wxFrame)
    EVT_MENU(wxID_EXIT, wxChartsTestsFrame::OnExit)
    EVT_MENU(wxID_RECTANGLE_ELEMENT, wxChartsTestsFrame::OnChartRectangleElement)
    EVT_MENU(wxID_LABEL_ELEMENT, wxChartsTestsFrame::OnChartLabelElement)
    EVT_MENU(wxID_CATEGORICALAXIS_ELEMENT, wxChartsTestsFrame::OnChartCategoricalAxisElement)
    EVT_MENU(wxID_NUMERICALAXIS_ELEMENT, wxChartsTestsFrame::OnChartNumericalAxisElement)
    EVT_MENU(wxID_GRID_ELEMENT, wxChartsTestsFrame::OnChartGridElement)
    EVT_MENU(wxID_BAR_CHART, wxChartsTestsFrame::OnBarChart)
    EVT_MENU(wxID_BUBBLE_CHART, wxChartsTestsFrame::OnBubbleChart)
    EVT_MENU(wxID_COLUMN_CHART, wxChartsTestsFrame::OnColumnChart)
    EVT_MENU(wxID_PIE_CHART, wxChartsTestsFrame::OnPieChart)
    EVT_MENU(wxID_POLARAREA_CHART, wxChartsTestsFrame::OnPolarAreaChart)
wxEND_EVENT_TABLE()
