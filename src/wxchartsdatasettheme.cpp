/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "wxchartsdatasettheme.h"

wxChartsDatasetTheme::wxChartsDatasetTheme()
    : m_barChartDatasetOptions(new wxBarChartDatasetOptions(wxChartsPenOptions(*wxBLACK, 2), wxChartsBrushOptions(*wxWHITE))),
    m_columnChartDatasetOptions(new wxColumnChartDatasetOptions(wxChartsPenOptions(*wxBLACK, 2), wxChartsBrushOptions(*wxWHITE)))
{
}

wxSharedPtr<wxBarChartDatasetOptions> wxChartsDatasetTheme::GetBarChartDatasetOptions()
{
    return m_barChartDatasetOptions;
}

wxSharedPtr<wxColumnChartDatasetOptions> wxChartsDatasetTheme::GetColumnChartDatasetOptions()
{
    return m_columnChartDatasetOptions;
}

void wxChartsDatasetTheme::SetBarChartDatasetOptions(const wxBarChartDatasetOptions& options)
{
    m_barChartDatasetOptions = new wxBarChartDatasetOptions(options);
}

void wxChartsDatasetTheme::SetColumnChartDatasetOptions(const wxColumnChartDatasetOptions& options)
{
    m_columnChartDatasetOptions = new wxColumnChartDatasetOptions(options);
}
