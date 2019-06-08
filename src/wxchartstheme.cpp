/*
    Copyright (c) 2017-2019 Xavier Leclercq

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

/// @file

#include "wxchartstheme.h"

wxChartsTheme::wxChartsTheme()
    : m_areaChartOptions(new wxAreaChartOptions()),
    m_barChartOptions(new wxBarChartOptions()),
    m_boxPlotOptions(new wxBoxPlotOptions()),
    m_bubbleChartOptions(new wxBubbleChartOptions()),
    m_candlestickChartOptions(new wxCandlestickChartOptions()),
    m_columnChartOptions(new wxColumnChartOptions()),
    m_doughnutChartOptions(new wxDoughnutChartOptions()),
    m_histogramChartOptions(new wxHistogramChartOptions()),
    m_lineChartOptions(new wxLineChartOptions()),
    m_math2DPlotOptions(new wxMath2DPlotOptions()),
    m_ohlcChartOptions(new wxOHLCChartOptions()),
    m_pieChartOptions(new wxPieChartOptions()),
    m_polarAreaChartOptions(new wxPolarAreaChartOptions()),
    m_radarChartOptions(new wxRadarChartOptions()),
    m_scatterPlotOptions(new wxScatterPlotOptions()),
    m_stackedBarChartOptions(new wxStackedBarChartOptions()),
    m_stackedColumnChartOptions(new wxStackedColumnChartOptions()),
    m_timeSeriesChartOptions(new wxTimeSeriesChartOptions())
{
    wxSharedPtr<wxChartsDatasetTheme> datasetTheme0(new wxChartsDatasetTheme());
    wxBarChartDatasetOptions barDatasetOptions0(wxChartsPenOptions(wxColor(220, 220, 220, 0xCC), 2), wxChartsBrushOptions(wxColor(220, 220, 220, 0x7F)));
    datasetTheme0->SetBarChartDatasetOptions(barDatasetOptions0);
    wxLineChartDatasetOptions lineDatasetOptions0(wxColor(220, 220, 220), wxColor(255, 255, 255));
    datasetTheme0->SetLineChartDatasetOptions(lineDatasetOptions0);
    wxColumnChartDatasetOptions columnDatasetOptions0(wxChartsPenOptions(wxColor(220, 220, 220, 0xCC), 2), wxChartsBrushOptions(wxColor(220, 220, 220, 0x7F)));
    datasetTheme0->SetColumnChartDatasetOptions(columnDatasetOptions0);
    wxStackedBarChartDatasetOptions stackedBarDatasetOptions0(wxChartsPenOptions(wxColor(96, 83, 77, 0x6C), 2), wxChartsBrushOptions(wxColor(96, 83, 77, 0x3F)));
    datasetTheme0->SetStackedBarChartDatasetOptions(stackedBarDatasetOptions0);
    wxStackedColumnChartDatasetOptions stackedColumnDatasetOptions0(wxChartsPenOptions(wxColor(96, 83, 77, 0x6C), 2), wxChartsBrushOptions(wxColor(96, 83, 77, 0x3F)));
    datasetTheme0->SetStackedColumnChartDatasetOptions(stackedColumnDatasetOptions0);
    m_datasetThemes[wxChartsDatasetId::CreateImplicitId(0)] = datasetTheme0;

    wxSharedPtr<wxChartsDatasetTheme> datasetTheme1(new wxChartsDatasetTheme());
    wxBarChartDatasetOptions barDatasetOptions1(wxChartsPenOptions(wxColor(151, 187, 205, 0xFF), 2), wxChartsBrushOptions(wxColor(151, 187, 205, 0x7F)));
    datasetTheme1->SetBarChartDatasetOptions(barDatasetOptions1);
    wxLineChartDatasetOptions lineDatasetOptions1(wxColor(151, 187, 205), wxColor(255, 255, 255));
    datasetTheme1->SetLineChartDatasetOptions(lineDatasetOptions1);
    wxColumnChartDatasetOptions columnDatasetOptions1(wxChartsPenOptions(wxColor(151, 187, 205, 0xFF), 2), wxChartsBrushOptions(wxColor(151, 187, 205, 0x7F)));
    datasetTheme1->SetColumnChartDatasetOptions(columnDatasetOptions1);
    wxStackedBarChartDatasetOptions stackedBarDatasetOptions1(wxChartsPenOptions(wxColor(220, 220, 220, 0xCC), 2), wxChartsBrushOptions(wxColor(220, 220, 220, 0x7F)));
    datasetTheme1->SetStackedBarChartDatasetOptions(stackedBarDatasetOptions1);
    wxStackedColumnChartDatasetOptions stackedColumnDatasetOptions1(wxChartsPenOptions(wxColor(220, 220, 220, 0xCC), 2), wxChartsBrushOptions(wxColor(220, 220, 220, 0x7F)));
    datasetTheme1->SetStackedColumnChartDatasetOptions(stackedColumnDatasetOptions1);
    m_datasetThemes[wxChartsDatasetId::CreateImplicitId(1)] = datasetTheme1;

    wxSharedPtr<wxChartsDatasetTheme> datasetTheme2(new wxChartsDatasetTheme());
    wxStackedBarChartDatasetOptions stackedBarDatasetOptions2(wxChartsPenOptions(wxColor(151, 187, 205, 0xFF), 2), wxChartsBrushOptions(wxColor(151, 187, 205, 0x7F)));
    datasetTheme2->SetStackedBarChartDatasetOptions(stackedBarDatasetOptions2);
    wxStackedColumnChartDatasetOptions stackedColumnDatasetOptions2(wxChartsPenOptions(wxColor(151, 187, 205, 0xFF), 2), wxChartsBrushOptions(wxColor(151, 187, 205, 0x7F)));
    datasetTheme2->SetStackedColumnChartDatasetOptions(stackedColumnDatasetOptions2);
    m_datasetThemes[wxChartsDatasetId::CreateImplicitId(2)] = datasetTheme2;
}

wxSharedPtr<wxAreaChartOptions> wxChartsTheme::GetAreaChartOptions()
{
    return m_areaChartOptions;
}

wxSharedPtr<wxBarChartOptions> wxChartsTheme::GetBarChartOptions()
{
    return m_barChartOptions;
}

wxSharedPtr<wxBoxPlotOptions> wxChartsTheme::GetBoxPlotOptions()
{
    return m_boxPlotOptions;
}

wxSharedPtr<wxBubbleChartOptions> wxChartsTheme::GetBubbleChartOptions()
{
    return m_bubbleChartOptions;
}

wxSharedPtr<wxCandlestickChartOptions> wxChartsTheme::GetCandlestickChartOptions()
{
    return m_candlestickChartOptions;
}

wxSharedPtr<wxColumnChartOptions> wxChartsTheme::GetColumnChartOptions()
{
    return m_columnChartOptions;
}

wxSharedPtr<wxDoughnutChartOptions> wxChartsTheme::GetDoughnutChartOptions()
{
    return m_doughnutChartOptions;
}

wxSharedPtr<wxHistogramChartOptions> wxChartsTheme::GetHistogramChartOptions()
{
    return m_histogramChartOptions;
}

wxSharedPtr<wxLineChartOptions> wxChartsTheme::GetLineChartOptions()
{
    return m_lineChartOptions;
}

wxSharedPtr<wxMath2DPlotOptions> wxChartsTheme::GetMath2DPlotOptions()
{
    return m_math2DPlotOptions;
}

wxSharedPtr<wxOHLCChartOptions> wxChartsTheme::GetOHLCChartOptions()
{
    return m_ohlcChartOptions;
}

wxSharedPtr<wxPieChartOptions> wxChartsTheme::GetPieChartOptions()
{
    return m_pieChartOptions;
}

wxSharedPtr<wxPolarAreaChartOptions> wxChartsTheme::GetPolarAreaChartOptions()
{
    return m_polarAreaChartOptions;
}

wxSharedPtr<wxRadarChartOptions> wxChartsTheme::GetRadarChartOptions()
{
    return m_radarChartOptions;
}

wxSharedPtr<wxScatterPlotOptions> wxChartsTheme::GetScatterPlotOptions()
{
    return m_scatterPlotOptions;
}

wxSharedPtr<wxStackedBarChartOptions> wxChartsTheme::GetStackedBarChartOptions()
{
    return m_stackedBarChartOptions;
}

wxSharedPtr<wxStackedColumnChartOptions> wxChartsTheme::GetStackedColumnChartOptions()
{
    return m_stackedColumnChartOptions;
}

wxSharedPtr<wxTimeSeriesChartOptions> wxChartsTheme::GetTimeSeriesChartOptions()
{
    return m_timeSeriesChartOptions;
}

wxSharedPtr<wxChartsDatasetTheme> wxChartsTheme::GetDatasetTheme(const wxChartsDatasetId& id)
{
    return m_datasetThemes[id];
}

wxSharedPtr<wxChartsTheme> wxChartsDefaultTheme(new wxChartsTheme());
