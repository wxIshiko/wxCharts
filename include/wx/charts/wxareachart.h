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

/*
    Part of this file were copied from the Chart.js project (http://chartjs.org/)
    and translated into C++.

    The files of the Chart.js project have the following copyright and license.

    Copyright (c) 2013-2017 Nick Downie
    Released under the MIT license
    https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

/// @file

#ifndef _WX_CHARTS_WXAREACHART_H_
#define _WX_CHARTS_WXAREACHART_H_

#include "wxchart.h"
#include "wxareachartoptions.h"
#include "wxchartgrid.h"
#include "wxchartpoint.h"

/// \ingroup dataclasses
class wxAreaChartDataset
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxAreaChartDataset> ptr;

    /// Constructs a AreaChart instance.
    /// @param dotColor The color of the points.
    /// @param data The list of values.
    wxAreaChartDataset(
        const wxColor &dotColor,
        wxVector<wxPoint2DDouble> &data);

    /// Whether to show the points on the chart.
    /// @retval true Show the points.
    /// @retval false Don't show the points.
    bool ShowDots() const;
    const wxColor& GetDotColor() const;
    /// Whether to show the line on the chart.
    /// @retval true Show the line.
    /// @retval false Don't show the line.
    bool ShowLine() const;
    const wxColor& GetLineColor() const;
    const wxVector<wxPoint2DDouble>& GetData() const;

private:
    bool m_showDots;
    wxColor m_dotColor;
    bool m_showLine;
    wxColor m_lineColor;
    wxVector<wxPoint2DDouble> m_data;
};

/// Data for the wxAreaChartCtrl control.

/// \ingroup dataclasses
class wxAreaChartData
{
public:
    /// Constructs a wxAreaChartData instance.
    wxAreaChartData();

    /// Adds a dataset.
    /// @param dataset The dataset to add.
    void AddDataset(wxAreaChartDataset::ptr dataset);

    const wxVector<wxAreaChartDataset::ptr>& GetDatasets() const;

private:
    wxVector<wxAreaChartDataset::ptr> m_datasets;
};

/// An area chart.

/// \ingroup chartclasses
class wxAreaChart : public wxChart
{
public:
    wxAreaChart(const wxAreaChartData &data, const wxSize &size);
    wxAreaChart(const wxAreaChartData &data, wxSharedPtr<wxAreaChartOptions> &options,
        const wxSize &size);

    virtual const wxChartCommonOptions& GetCommonOptions() const;

    void Save(const wxString &filename, const wxBitmapType &type,
        const wxSize &size);

private:
    void Initialize(const wxAreaChartData &data);
    static wxDouble GetMinXValue(const wxVector<wxAreaChartDataset::ptr>& datasets);
    static wxDouble GetMaxXValue(const wxVector<wxAreaChartDataset::ptr>& datasets);
    static wxDouble GetMinYValue(const wxVector<wxAreaChartDataset::ptr>& datasets);
    static wxDouble GetMaxYValue(const wxVector<wxAreaChartDataset::ptr>& datasets);

    virtual void DoSetSize(const wxSize &size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext &gc, bool suppressTooltips);
    virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point);

private:
    class Point : public wxChartPoint
    {
    public:
        typedef wxSharedPtr<Point> ptr;

        Point(wxPoint2DDouble value,
            const wxChartTooltipProvider::ptr tooltipProvider,
            wxDouble x, wxDouble y,wxDouble radius,
            unsigned int strokeWidth,const wxColor &fillColor,
            wxDouble hitDetectionRange);

        virtual wxPoint2DDouble GetTooltipPosition() const;
        virtual bool HitTest(const wxPoint &point) const;

        wxPoint2DDouble GetValue() const;

    private:
        wxPoint2DDouble m_value;
        wxDouble m_hitDetectionRange;
    };

    class Dataset
    {
    public:
        typedef wxSharedPtr<Dataset> ptr;

        Dataset(bool showDots, bool showLine,
            const wxColor &lineColor);

        bool ShowDots() const;
        bool ShowLine() const;
        const wxColor& GetLineColor() const;

        const wxVector<Point::ptr>& GetPoints() const;
        void AppendPoint(Point::ptr point);

    private:
        bool m_showDots;
        bool m_showLine;
        wxColor m_lineColor;
        wxVector<Point::ptr> m_points;
    };

private:
    wxSharedPtr<wxAreaChartOptions> m_options;
    wxChartGrid m_grid;
    wxVector<Dataset::ptr> m_datasets;
};

#endif
