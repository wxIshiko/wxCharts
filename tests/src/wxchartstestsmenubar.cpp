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

#include "wxchartstestsmenubar.h"
#include "wxchartstestswindowids.h"

wxChartsTestsMenuBar::wxChartsTestsMenuBar()
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT, "Exit\tAlt+F4");
    Append(menuFile, "&File");

    wxMenu* menuSettings = new wxMenu;
    menuSettings->Append(wxID_DEFAULT_THEME, "Default Theme");
    Append(menuSettings, "&Settings");

    wxMenu* menuElements = new wxMenu;
    menuElements->Append(wxID_RECTANGLE_ELEMENT, "wxChartsRectangle");
    menuElements->Append(wxID_LABEL_ELEMENT, "wxChartLabel");
    menuElements->Append(wxID_CATEGORICALAXIS_ELEMENT, "wxChartsCategoricalAxis");
    menuElements->Append(wxID_NUMERICALAXIS_ELEMENT, "wxChartsNumericalAxis");
    menuElements->Append(wxID_GRID_ELEMENT, "wxChartsGrid");
    Append(menuElements, "&Elements");

    wxMenu* menuCharts = new wxMenu;
    menuCharts->Append(wxID_AREA_CHART, "wxAreaChartCtrl");
    menuCharts->Append(wxID_BAR_CHART, "wxBarChartCtrl");
    menuCharts->Append(wxID_BOX_PLOT, "wxBoxPlotCtrl");
    menuCharts->Append(wxID_BUBBLE_CHART, "wxBubbleChartCtrl");
    menuCharts->Append(wxID_CANDLESTICK_CHART, "wxCandlestickChartCtrl");
    menuCharts->Append(wxID_COLUMN_CHART, "wxColumnChartCtrl");
    menuCharts->Append(wxID_DOUGHNUT_CHART, "wxDoughnutChartCtrl");
    menuCharts->Append(wxID_HISTOGRAM, "wxHistogramCtrl");
    menuCharts->Append(wxID_LINE_CHART, "wxLineChartCtrl");
    menuCharts->Append(wxID_PIE_CHART, "wxPieChartCtrl");
    menuCharts->Append(wxID_POLARAREA_CHART, "wxPolarAreaChartCtrl");
    menuCharts->Append(wxID_STACKEDBAR_CHART, "wxStackedBarChartCtrl");
    menuCharts->Append(wxID_STACKEDCOLUMN_CHART, "wxStackedColumnChartCtrl");
    Append(menuCharts, "&Charts");

    wxMenu* menuTests = new wxMenu;
    menuTests->Append(wxID_ALL_TESTS, "Run all tests");
    Append(menuTests, "&Tests");
}
