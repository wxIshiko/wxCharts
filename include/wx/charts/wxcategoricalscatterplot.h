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

#ifndef _WX_CHARTS_WXCATEGORICALSCATTERPLOT_H_
#define _WX_CHARTS_WXCATEGORICALSCATTERPLOT_H_

#include "wxchart.h"
#include "wxcategoricalscatterplotoptions.h"
#include "wxchartsgrid.h"

/// Data for the wxCategoricalScatterPlotCtrl control.

/// \ingroup dataclasses
class wxCategoricalScatterPlotData
{
public:
    wxCategoricalScatterPlotData(const wxVector<wxString> &labels, const wxVector<wxVector<wxDouble>> &data);

    /// Gets the labels of the X axis.
    /// @return A vector containing the labels of the
    /// X axis.
    const wxVector<wxString>& GetLabels() const;
    const wxColor& GetLineColor() const;
    const wxColor& GetFillColor() const;
    unsigned int GetWidth() const;
    const wxVector<wxVector<wxDouble>>& GetData() const;

private:
    wxVector<wxString> m_labels;
    wxColor m_lineColor;
    wxColor m_fillColor;
    unsigned int m_width;
    wxVector<wxVector<wxDouble>> m_data;
};

/// A Boxplot.
/**
    \ingroup chartclasses
*/
class wxCategoricalScatterPlot : public wxChart
{
public:
    /// Constructor.
    /**
        The chart options will be defined by the default theme.

        @param data The data that will be used to initialize the chart.
        @param size The initial size of the chart.
    */
    wxCategoricalScatterPlot(const wxCategoricalScatterPlotData &data, const wxSize &size);

    /// Constructor.
    /**
        @param data The data that will be used to initialize the chart.
        @param options The options to use for the chart.
        @param size The initial size of the chart.
    */
    wxCategoricalScatterPlot(const wxCategoricalScatterPlotData &data, wxCategoricalScatterPlotOptions::ptr options,
        const wxSize &size);

    virtual const wxChartCommonOptions& GetCommonOptions() const;

private:
    void Initialize(const wxCategoricalScatterPlotData &data);
    static wxDouble GetMinValue(const wxCategoricalScatterPlotData &data);
    static wxDouble GetMaxValue(const wxCategoricalScatterPlotData &data);

    virtual void DoSetSize(const wxSize &size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext &gc, bool suppressTooltips);
    virtual wxSharedPtr<wxVector<const wxChartsElement*>> GetActiveElements(const wxPoint &point);

private:
    class Point : public wxChartsElement
    {
    public:
        typedef wxSharedPtr<Point> ptr;

        Point(wxDouble value, const wxColor &lineColor, const wxColor &fillColor,
            unsigned int lineWidth, const wxChartTooltipProvider::ptr tooltipProvider);

        virtual void Draw(wxGraphicsContext &gc) const;
        virtual bool HitTest(const wxPoint &point) const;
        virtual wxPoint2DDouble GetTooltipPosition() const;
        void Update(const wxChartsGridMapping& mapping, size_t index);

    private:
        wxDouble m_value;
        wxPoint2DDouble m_position;
        wxColor m_lineColor;
        wxColor m_fillColor;
        unsigned int m_width;
    };

    class Dataset
    {
    public:
        typedef wxSharedPtr<Dataset> ptr;

        Dataset();

        const wxVector<Point::ptr>& GetPoints() const;
        void AppendPoint(Point::ptr point);

    private:
        wxVector<Point::ptr> m_points;
    };

private:
    wxCategoricalScatterPlotOptions::ptr m_options;
    wxChartsGrid m_grid;
    wxVector<Dataset::ptr> m_data;
};

#endif
