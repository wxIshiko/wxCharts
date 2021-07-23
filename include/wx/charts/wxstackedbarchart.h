/*
    Copyright (c) 2016-2021 Xavier Leclercq

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

#ifndef _WX_CHARTS_WXSTACKEDBARCHART_H_
#define _WX_CHARTS_WXSTACKEDBARCHART_H_

#include "wxchart.h"
#include "wxchartscategoricaldata.h"
#include "wxstackedbarchartoptions.h"
#include "wxchartsgrid.h"
#include "wxchartsrectangle.h"

/// A stacked bar chart.

/// \ingroup chartclasses
class wxStackedBarChart : public wxChart
{
public:
    wxStackedBarChart(wxSharedPtr<wxChartsCategoricalData> &data, const wxSize &size);
    wxStackedBarChart(wxSharedPtr<wxChartsCategoricalData> &data,
        const wxStackedBarChartOptions &options, const wxSize &size);

    virtual const wxChartCommonOptions& GetCommonOptions() const;

private:
    void Initialize(wxSharedPtr<wxChartsCategoricalData> &data, const wxSize &size);
    static wxDouble GetCumulativeMinValue(const wxVector<wxVector<wxDouble>> &datasets);
    static wxDouble GetCumulativeMaxValue(const wxVector<wxVector<wxDouble>> &datasets);

    virtual wxSize DoGetBestSize();
    virtual void DoSetSize(const wxSize &size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext &gc, bool suppressTooltips);
    virtual wxSharedPtr<wxVector<const wxChartsElement*>> GetActiveElements(const wxPoint &point);

private:
    class Bar : public wxChartsRectangle
    {
    public:
        Bar(wxDouble value,
            const wxSharedPtr<wxChartTooltipProvider> tooltipProvider,
            wxDouble x, wxDouble y,
            const wxChartsPenOptions &penOptions,
            const wxChartsBrushOptions &brushOptions,
            int borders);

        virtual bool HitTest(const wxPoint &point) const;

        wxDouble GetValue() const;

    private:
        wxDouble m_value;
    };

    class BarSet
    {
    public:
        BarSet();

        const wxVector<wxSharedPtr<Bar>>& GetBars() const;
        void AppendBar(wxSharedPtr<Bar> bar);

    private:
        wxVector<wxSharedPtr<Bar>> m_bars;
    };

private:
    wxSharedPtr<wxStackedBarChartOptions> m_options;
    wxChartsGrid m_grid;
    wxVector<wxSharedPtr<BarSet>> m_datasets;
};

#endif
