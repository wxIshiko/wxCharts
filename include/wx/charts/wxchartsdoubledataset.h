/*
    Copyright (c) 2017-2018 Xavier Leclercq

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

#ifndef _WX_CHARTS_WXCHARTSDOUBLEDATASET_H_
#define _WX_CHARTS_WXCHARTSDOUBLEDATASET_H_

#include "wxchartsdataset.h"

#include <wx/colour.h>
#include <wx/sharedptr.h>

/// Stores the information about a dataset to be shown on one of the bar chart controls.

/// The wxBarChartCtrl, wxColumnChartCtrl, wxStackedBarChartCtrl and wxStackedColumnChartCtrl use this class.
/// \ingroup dataclasses
class wxChartsDoubleDataset : public wxChartsDataset
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxChartsDoubleDataset> ptr;

    /// Constructs a wxBarChartDataset instance.
    /// @param fillColor The color of the brush used to 
    /// fill the bar.
    /// @param strokeColor The color of the pen used to
    /// draw the outline of the bar.
    /// @param data The list of values.
    wxChartsDoubleDataset(const wxColor &fillColor, const wxColor &strokeColor,
        const wxVector<wxDouble> &data);

    /// Gets the color of the brush used to fill the
    /// bar.
    /// @return The color of the brush used to fill the
    /// bar.
    const wxColor& GetFillColor() const;
    /// Gets the color of the pen used to draw the outline
    /// of the bar.
    /// @return The color of the pen used to draw the 
    /// outline of the bar.
    const wxColor& GetStrokeColor() const;
    const wxVector<wxDouble>& GetData() const;

private:
    wxColor m_fillColor;
    wxColor m_strokeColor;
    wxVector<wxDouble> m_data;
};

#endif
