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

/*
    Part of this file were copied from the Chart.js project (http://chartjs.org/)
    and translated into C++.

    The files of the Chart.js project have the following copyright and license.

    Copyright (c) 2013-2016 Nick Downie
    Released under the MIT license
    https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

/// @file

#ifndef _WX_CHARTS_WXLINECHART_H_
#define _WX_CHARTS_WXLINECHART_H_

#include "wxchart.h"
#include "wxchartscategoricaldata.h"
#include "wxlinechartoptions.h"
#include "wxchartsgrid.h"
#include "wxchartspoint.h"

enum wxChartsLineType
{
    wxCHARTSLINETYPE_STRAIGHT,
    wxCHARTSLINETYPE_STEPPED
};

/// A line chart.

/// \ingroup chartclasses
class wxLineChart : public wxChart
{
public:
    wxLineChart(wxSharedPtr<wxChartsCategoricalData>& data, const wxChartsLineType& lineType,
        const wxSize& size);
    wxLineChart(wxSharedPtr<wxChartsCategoricalData>& data, const wxChartsLineType& lineType,
        const wxLineChartOptions& options, const wxSize& size);

    virtual const wxChartCommonOptions& GetCommonOptions() const;

    void Save(const wxString &filename, const wxBitmapType &type,
        const wxSize &size, const wxColor &backgroundColor);

private:
    void Initialize(wxSharedPtr<wxChartsCategoricalData>& data, const wxSize& size);
    static wxDouble GetMinValue(const wxVector<wxVector<wxDouble>>& datasets);
    static wxDouble GetMaxValue(const wxVector<wxVector<wxDouble>>& datasets);

    virtual void DoSetSize(const wxSize &size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext &gc, bool suppressTooltips);
    virtual wxSharedPtr<wxVector<const wxChartsElement*>> GetActiveElements(const wxPoint &point);

private:
    class Point : public wxChartsPoint
    {
    public:
        typedef wxSharedPtr<Point> ptr;

        Point(wxDouble value,
            const wxChartTooltipProvider::ptr tooltipProvider,
            wxDouble x, wxDouble y, wxDouble radius,
            unsigned int strokeWidth, const wxColor &strokeColor,
            const wxColor &fillColor, wxDouble hitDetectionRange);

        virtual bool HitTest(const wxPoint &point) const;

        wxDouble GetValue() const;

    private:
        wxDouble m_value;
        wxDouble m_hitDetectionRange;
    };

    class PointSet
    {
    public:
        PointSet(bool showDots, bool showLine, const wxColor &lineColor,
                bool fill, const wxColor &fillColor,
                const wxChartsLineType &lineType);

        bool ShowDots() const;
        bool ShowLine() const;
        const wxColor& GetLineColor() const;
        bool Fill() const;
        const wxColor& GetFillColor() const;
        const wxChartsLineType& GetType() const;

        const wxVector<Point::ptr>& GetPoints() const;
        void AppendPoint(Point::ptr point);

    private:
        bool m_showDots;
        bool m_showLine;
        wxColor m_lineColor;
        bool m_fill;
        wxColor m_fillColor;
        wxChartsLineType m_type;
        wxVector<Point::ptr> m_points;
    };

private:
    wxSharedPtr<wxLineChartOptions> m_options;
    wxChartsGrid m_grid;
    wxVector<wxSharedPtr<PointSet>> m_datasets;
    wxChartsLineType m_lineType;
};

#endif
