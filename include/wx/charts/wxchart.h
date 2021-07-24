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

#ifndef _WX_CHARTS_WXCHART_H_
#define _WX_CHARTS_WXCHART_H_

#include "wxchartcommonoptions.h"
#include "wxchartselement.h"
#include "wxchartslabel.h"
#include <wx/sharedptr.h>

/// \defgroup chartclasses

/// Base class for the chart classes.

/// \ingroup chartclasses
class wxChart
{
public:
    /// Constructs an instance of the wxChart class.
    /**
     * This constructor creates a new instance of the wxChart.
     * 
     * @param title The title of the chart. An empty string indicates that the
     *        chart doesn't have a title.
     * @param size The size of the chart.
     */
    wxChart(const wxString& title, const wxSize& size);

    /// Constructs an incomplete instance of the wxChart class.
    /**
     * This constructor creates a new instance of the wxChart class whose
     * construction need to be completed by calling one of the Create
     * functions.
     */
    wxChart();

    /// Completes the creation of a wxChart instance.
    /**
     * This function completes the creation of a wxChart instance that was
     * created by the wxChart() constructor.
     *
     * @param title The title of the chart. An empty string indicates that the
     *        chart doesn't have a title.
     * @param size The size of the chart.
     */
    void Create(const wxString& title, const wxSize& size);

    void SetTitle(const wxString& text, const wxChartsLabelOptions& options);

    /// Gets the common options for the chart.
    /// @return The options.
    virtual const wxChartCommonOptions& GetCommonOptions() const = 0;

    /// Returns the preferred size for the chart. 
    /**
     * This function returns the preferred size for the chart. The preferred
     * size of a chart is the minium size that allows all elements of the chart
     * to fit in an area of that size. It takes into account the current
     * contents of the chart and current options.
     *
     * @return The referred size for the chart.
     */
    wxSize GetBestSize() const;

    /// Returns the position of the top left corner of the client area. 
    /**
     * This function returns the position of the top left corner of the client
     * area. The client area is the area of the chart that contains the actual
     * chart and excludes any title and padding.
     * 
     * @return The position of the top left corner of the client area.
     */
    wxPoint GetClientAreaOrigin() const;

    /// Returns the size of the client area. 
    /**
     * This function returns the size of of the client area. The client area is
     * the area of the chart that contains the actual chart and excludes any
     * title and padding.
     *
     * @return The size of the client area.
     */
    wxSize GetClientSize() const;
    void SetSize(const wxSize &size);
    void Draw(wxGraphicsContext &gc);
    void ActivateElementsAt(const wxPoint &point);

protected:
    void Fit();
    void DrawTooltips(wxGraphicsContext &gc);

private:
    virtual wxSize DoGetBestSize() const = 0;
    virtual void DoSetSize(const wxSize &size) = 0;
    virtual void DoFit() = 0;
    virtual void DoDraw(wxGraphicsContext &gc, bool suppressTooltips) = 0;
    virtual wxSharedPtr<wxVector<const wxChartsElement*>> GetActiveElements(const wxPoint &point) = 0;

private:
    wxSize m_size;
    wxSharedPtr<wxChartsLabel> m_title;
    bool m_needsFit;
    wxSharedPtr<wxVector<const wxChartsElement*>> m_activeElements;
};

#endif
