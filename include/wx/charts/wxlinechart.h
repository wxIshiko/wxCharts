/*
    Copyright (c) 2016-2018 Xavier Leclercq

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
#include "wxlinechartoptions.h"
#include "wxchartgrid.h"
#include "wxchartpoint.h"

enum wxLineType
{
    wxLINETYPE_STRAIGHTLINE,
    wxLINETYPE_STEPPEDLINE
};

/// Stores the information about a dataset to be shown on a wxLineChartCtrl.

/// \ingroup dataclasses
class wxLineChartDataset
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxLineChartDataset> ptr;

    /// Constructs a wxLineChartDataset instance.
    /// @param label The name of the dataset. This
    /// is the name that will be used in the legend.
    /// @param dotColor The color of the points.
    /// @param dotStrokeColor The color of the pen
    /// used to draw the outline of the points.
    /// @param fillColor The part of the graph between
    /// the X-axis and the line will be filled using
    /// this color.
    /// @param data The list of values.
    wxLineChartDataset(const wxString &label,
        const wxColor &dotColor, const wxColor &dotStrokeColor,
        const wxColor &fillColor, const wxVector<wxDouble> &data,
        const wxLineType &lineType=wxLINETYPE_STRAIGHTLINE);

    /// Gets the name of the dataset.
    /// @return The name of the dataset.
    const wxString& GetLabel() const;
    /// Whether to show the points on the chart.
    /// @retval true Show the points.
    /// @retval false Don't show the points.
    bool ShowDots() const;
    const wxColor& GetDotColor() const;
    const wxColor& GetDotStrokeColor() const;
    /// Whether to show the line on the chart.
    /// @retval true Show the line.
    /// @retval false Don't show the line.
    bool ShowLine() const;
    const wxColor& GetLineColor() const;
    /// Whether to fill the part of the chart
    /// between the line and X-axis with the
    /// color returned by GetFillColor().
    /// @retval true Fill.
    /// @retval false Don't fill.
    bool Fill() const;
    /// Returns the color with which to
    /// fill the part of the chart between
    /// the line and the X-axis.
    /// @return The fill color.
    const wxColor& GetFillColor() const;
    const wxVector<wxDouble>& GetData() const;
    const wxLineType& GetType() const;

private:
    wxString m_label;
    bool m_showDots;
    wxColor m_dotColor;
    wxColor m_dotStrokeColor;
    bool m_showLine;
    wxColor m_lineColor;
    bool m_fill;
    wxColor m_fillColor;
    wxVector<wxDouble> m_data;
    wxLineType m_type;
};

/// Data for the wxLineChartCtrl control.

/// \ingroup dataclasses
class wxLineChartData
{
public:
    /// Constructs a wxLineChartData instance.
    /// @param labels The labels of the X axis.
    wxLineChartData(const wxVector<wxString> &labels);

    /// Adds a dataset.
    /// @param dataset The dataset to add.
    void AddDataset(wxLineChartDataset::ptr dataset);

    /// Gets the labels of the X axis.
    /// @return A vector containing the labels of the
    /// X axis.
    const wxVector<wxString>& GetLabels() const;
    const wxVector<wxLineChartDataset::ptr>& GetDatasets() const;

private:
    wxVector<wxString> m_labels;
    wxVector<wxLineChartDataset::ptr> m_datasets;
};

/// A line chart.

/// \ingroup chartclasses
class wxLineChart : public wxChart
{
public:
    wxLineChart(const wxLineChartData &data, const wxSize &size);
    wxLineChart(const wxLineChartData &data, const wxLineChartOptions &options,
        const wxSize &size);

    virtual const wxChartCommonOptions& GetCommonOptions() const;

    void Save(const wxString &filename, const wxBitmapType &type,
        const wxSize &size);

private:
    void Initialize(const wxLineChartData &data);
    static wxDouble GetMinValue(const wxVector<wxLineChartDataset::ptr>& datasets);
    static wxDouble GetMaxValue(const wxVector<wxLineChartDataset::ptr>& datasets);

    virtual void DoSetSize(const wxSize &size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext &gc, bool suppressTooltips);
    virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point);

private:
    class Point : public wxChartPoint
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

    class Dataset
    {
    public:
        typedef wxSharedPtr<Dataset> ptr;

        Dataset(bool showDots, bool showLine, const wxColor &lineColor,
                bool fill, const wxColor &fillColor,
                const wxLineType &lineType=wxLINETYPE_STRAIGHTLINE);

        bool ShowDots() const;
        bool ShowLine() const;
        const wxColor& GetLineColor() const;
        bool Fill() const;
        const wxColor& GetFillColor() const;
        const wxLineType& GetType() const;

        const wxVector<Point::ptr>& GetPoints() const;
        void AppendPoint(Point::ptr point);

    private:
        bool m_showDots;
        bool m_showLine;
        wxColor m_lineColor;
        bool m_fill;
        wxColor m_fillColor;
        wxLineType m_type;
        wxVector<Point::ptr> m_points;
    };

private:
    wxLineChartOptions m_options;
    wxChartGrid m_grid;
    wxVector<Dataset::ptr> m_datasets;
};

#endif
