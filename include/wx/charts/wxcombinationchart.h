/*
    Copyright (c) 2017-2021 Xavier Leclercq

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

#ifndef _WX_CHARTS_WXCOMBINATIONCHART_H_
#define _WX_CHARTS_WXCOMBINATIONCHART_H_

#include "wxchart.h"
#include "wxcombinationchartoptions.h"
#include "wxchartscategoricaldata.h"
#include "wxchartsgrid.h"

/// \ingroup chartclasses
class wxCombinationChart : public wxChart
{
public:
    wxCombinationChart();

    void AddColumnChart(const wxChartsCategoricalData &data);

    virtual const wxChartCommonOptions& GetCommonOptions() const;

private:
    virtual wxSize DoGetBestSize() const;
    virtual void DoSetSize(const wxSize &size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext &gc, bool suppressTooltips);
    virtual wxSharedPtr<wxVector<const wxChartsElement*>> GetActiveElements(const wxPoint &point);

private:
    wxCombinationChartOptions m_options;
    wxSharedPtr<wxChartsGrid> m_grid;
};

#endif
