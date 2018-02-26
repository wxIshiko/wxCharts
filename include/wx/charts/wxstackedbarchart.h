/*
    Copyright (c) 2016-2017 Xavier Leclercq

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
#include "wxchartgrid.h"
#include "wxchartrectangle.h"

/// A stacked bar chart.
class wxStackedBarChart : public wxChart
{
public:
    wxStackedBarChart(const wxChartsCategoricalData &data, const wxSize &size);
    wxStackedBarChart(const wxChartsCategoricalData &data,
        const wxStackedBarChartOptions &options, const wxSize &size);

    virtual const wxStackedBarChartOptions& GetOptions() const;

private:
    static wxDouble GetCumulativeMinValue(const wxVector<wxChartsDoubleDataset::ptr>& datasets);
    static wxDouble GetCumulativeMaxValue(const wxVector<wxChartsDoubleDataset::ptr>& datasets);

    virtual void DoSetSize(const wxSize &size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext &gc, bool suppressTooltips);
    virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point);

private:
    class Bar : public wxChartRectangle
    {
    public:
        typedef wxSharedPtr<Bar> ptr;

        Bar(wxDouble value,
            const wxChartTooltipProvider::ptr tooltipProvider,
            wxDouble x, wxDouble y,
            const wxColor &fillColor, const wxColor &strokeColor,
            int directions);

        virtual bool HitTest(const wxPoint &point) const;

        wxDouble GetValue() const;

    private:
        wxDouble m_value;
    };

    class Dataset
    {
    public:
        typedef wxSharedPtr<Dataset> ptr;

        Dataset();

        const wxVector<Bar::ptr>& GetBars() const;
        void AppendBar(Bar::ptr bar);

    private:
        wxVector<Bar::ptr> m_bars;
    };

private:
    wxStackedBarChartOptions m_options;
    wxChartGrid m_grid;
    wxVector<Dataset::ptr> m_datasets;
};

#endif
