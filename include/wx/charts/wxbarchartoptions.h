/*
    Copyright (c) 2016-2019 Xavier Leclercq

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

#ifndef _WX_CHARTS_WXBARCHARTOPTIONS_H_
#define _WX_CHARTS_WXBARCHARTOPTIONS_H_

#include "wxchartoptions.h"
#include "wxchartsgridoptions.h"
#include <wx/sharedptr.h>

/// The options for the wxBarChartCtrl control.

/// \ingroup chartclasses
class WXDLLIMPEXP_ISHIKO_CHARTS wxBarChartOptions : public wxChartOptions
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxBarChartOptions> ptr;

    /// Constructs a wxBarChartOptions instance.
    wxBarChartOptions();

    /// Gets the options for the grid.
    /// @return The options for the grid.
    const wxChartsGridOptions& GetGridOptions() const;

    /// Gets the amount of space the bars are separated
    /// by. The actual space between bars will be twice
    /// this amount.
    /// @return The separation between bars.
    wxDouble GetBarSpacing() const;

    wxDouble GetDatasetSpacing() const;

private:
    wxChartsGridOptions m_gridOptions;
    wxDouble m_barSpacing;
    wxDouble m_datasetSpacing;
};

#endif
