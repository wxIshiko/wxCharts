/*
	Copyright (c) 2016 Xavier Leclercq

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

/*
	Part of this file were copied from the Chart.js project (http://chartjs.org/)
	and translated into C++.

	The files of the Chart.js project have the following copyright and license.

	Copyright (c) 2013-2016 Nick Downie
	Released under the MIT license
	https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

/// @file

#ifndef _WX_CHARTS_WXBARCHART_H_
#define _WX_CHARTS_WXBARCHART_H_

#include "wxchart.h"
#include "wxbarchartdata.h"
#include "wxbarchartoptions.h"
#include "wxchartgrid.h"
#include "wxchartrectangle.h"

/// A bar chart.
class wxBarChart : public wxChart
{
public:
    wxBarChart(const wxBarChartData &data, const wxSize &size);
    wxBarChart(const wxBarChartData &data, const wxBarChartOptions &options,
        const wxSize &size);

    virtual const wxBarChartOptions& GetOptions() const wxOVERRIDE;

private:
    void Initialize(const wxBarChartData &data);
    static wxDouble GetMinValue(const wxVector<wxBarChartDataset::ptr>& datasets);
    static wxDouble GetMaxValue(const wxVector<wxBarChartDataset::ptr>& datasets);

    virtual void DoSetSize(const wxSize &size) wxOVERRIDE;
    virtual void DoFit() wxOVERRIDE;
    virtual void DoDraw(wxGraphicsContext &gc) wxOVERRIDE;
    virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point) wxOVERRIDE;

    wxDouble GetBarHeight() const;

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
    wxBarChartOptions m_options;
    wxChartGrid m_grid;
    wxVector<Dataset::ptr> m_datasets;
};

#endif
