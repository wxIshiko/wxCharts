/*
    Copyright (c) 2018 Xavier Leclercq and the wxCharts contributors.

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

#include "wxhistchartoptions.h"

wxHistogramChartOptions::wxHistogramChartOptions() : m_lineWidth(2)
{
    wxChartMultiTooltipOptions& options = GetCommonOptions().GetMultiTooltipOptions();
    options.SetShowTitle(false);
    options.SetAlignment(wxALIGN_TOP);
}

const wxChartGridOptions& wxHistogramChartOptions::GetGridOptions() const
{
    return m_gridOptions;
}

wxChartGridOptions& wxHistogramChartOptions::GetGridOptions()
{
    return m_gridOptions;
}

unsigned int wxHistogramChartOptions::GetLineWidth() const
{
    return m_lineWidth;
}

