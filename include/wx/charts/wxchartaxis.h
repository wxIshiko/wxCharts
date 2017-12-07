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

/*
    Part of this file were copied from the Chart.js project (http://chartjs.org/)
    and translated into C++.

    The files of the Chart.js project have the following copyright and license.

    Copyright (c) 2013-2016 Nick Downie
    Released under the MIT license
    https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

/// @file

#ifndef _WX_CHARTS_WXCHARTAXIS_H_
#define _WX_CHARTS_WXCHARTAXIS_H_

#include "wxchartelement.h"
#include "wxchartaxisoptions.h"
#include "wxchartlabelgroup.h"
#include <wx/graphics.h>

enum wxChartAxisType
{
    wxCHARTAXISTYPE_GENERIC = 0,
    wxCHARTAXISTYPE_NUMERICAL = 1
};

/// This class represents an axis.
class wxChartAxis : public wxChartElement
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxChartAxis> ptr;

    virtual bool HitTest(const wxPoint &point) const;

    virtual wxPoint2DDouble GetTooltipPosition() const;

    /// Draws the axis.
    /// @param gc The graphics context.
    void Draw(wxGraphicsContext &gc);

    /// Updates the size of each label using the 
    /// font details specified in the axis options
    /// and the provided graphics context.
    /// @param gc The graphics context.
    void UpdateLabelSizes(wxGraphicsContext &gc);
    void Fit(wxPoint2DDouble startPoint, wxPoint2DDouble endPoint);
    void UpdateLabelPositions();

    wxChartAxisType GetType() const;
    /// Gets the labels.
    /// @return The list of labels.
    const wxChartLabelGroup& GetLabels() const;
    void SetLabels(const wxVector<wxChartLabel> &labels);

    wxPoint2DDouble CalculateLabelPosition(size_t index);
    size_t GetNumberOfTickMarks() const;
    wxDouble GetDistanceBetweenTickMarks() const;
    wxPoint2DDouble GetTickMarkPosition(size_t index) const;
    wxPoint2DDouble GetPosition(wxDouble relativeValue) const;

    const wxChartAxisOptions& GetOptions() const;

protected:
    /// Construcs a wxChartAxis element.
    /// @param type The type of axis.
    /// @param options The settings to be used for the axis.
    wxChartAxis(wxChartAxisType type, const wxChartAxisOptions &options);
    /// Constructs a wxChartAxis element.
    /// @param labels The labels to display along the axis.
    /// @param options The settings to be used for the axis.
    wxChartAxis(const wxVector<wxString> &labels, const wxChartAxisOptions &options);

private:
    void DrawTickMarks(wxGraphicsContext &gc);

private:
    wxChartAxisType m_type;
    wxChartAxisOptions m_options;
    wxPoint2DDouble m_startPoint;
    wxPoint2DDouble m_endPoint;
    wxChartLabelGroup m_labels;
};

#endif
