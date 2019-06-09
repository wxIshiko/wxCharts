/*
    Copyright (c) 2019 Xavier Leclercq and the wxCharts contributors.

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

#include "wxcategoricalscatterplotoptions.h"

wxCategoricalScatterPlotOptions::wxCategoricalScatterPlotOptions()
{
    m_gridOptions.GetXAxisOptions().SetStartMarginType(wxCHARTSAXISMARGINTYPE_TICKMARKOFFSET);
    m_gridOptions.GetXAxisOptions().SetEndMarginType(wxCHARTSAXISMARGINTYPE_TICKMARKOFFSET);
    m_gridOptions.GetHorizontalGridLineOptions().SetMajorGridLineColor(wxColor(0, 0, 0, 0x30));
    m_gridOptions.GetHorizontalGridLineOptions().SetNumberOfMinorGridLinesBetweenTickMarks(4);
    m_gridOptions.GetVerticalGridLineOptions().SetMajorGridLineColor(wxColor(0, 0, 0, 0x30));
}

const wxChartsGridOptions& wxCategoricalScatterPlotOptions::GetGridOptions() const
{
    return m_gridOptions;
}

wxChartsGridOptions& wxCategoricalScatterPlotOptions::GetGridOptions()
{
    return m_gridOptions;
}
