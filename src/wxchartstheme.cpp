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
    m_bubbleChartOptions(new wxBubbleChartOptions()),
    m_candlestickChartOptions(new wxCandlestickChartOptions()),
    m_columnChartOptions(new wxColumnChartOptions()),
    m_doughnutChartOptions(new wxDoughnutChartOptions()),
    m_histogramChartOptions(new wxHistogramChartOptions()),
    m_lineChartOptions(new wxLineChartOptions()),
    m_stackedBarChartOptions(new wxStackedBarChartOptions()),
    m_stackedColumnChartOptions(new wxStackedColumnChartOptions())
{
}

wxSharedPtr<wxAreaChartOptions> wxChartsTheme::GetAreaChartOptions()
{
    return m_areaChartOptions;
}

wxSharedPtr<wxBarChartOptions> wxChartsTheme::GetBarChartOptions()
{
    return m_barChartOptions;
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

wxSharedPtr<wxStackedBarChartOptions> wxChartsTheme::GetStackedBarChartOptions()
{
    return m_stackedBarChartOptions;
}

wxSharedPtr<wxStackedColumnChartOptions> wxChartsTheme::GetStackedColumnChartOptions()
{
    return m_stackedColumnChartOptions;
}

wxSharedPtr<wxChartsTheme> wxChartsDefaultTheme(new wxChartsTheme());
