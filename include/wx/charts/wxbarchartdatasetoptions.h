/*
    Copyright (c) 2019-2024 Xavier Leclercq

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

#ifndef _WX_CHARTS_WXBARCHARTDATASETOPTIONS_H_
#define _WX_CHARTS_WXBARCHARTDATASETOPTIONS_H_

#include "wxchartspenoptions.h"
#include "wxchartsbrushoptions.h"

class WXDLLIMPEXP_ISHIKO_CHARTS wxBarChartDatasetOptions
{
public:
    /// Constructs a wxBarChartDatasetOptions instance.
    /// @param penOptions The options for the pen used to
    /// draw the outline of the bar.
    /// @param brushOptions The options for the brush used to 
    /// fill the bar.
    wxBarChartDatasetOptions(const wxChartsPenOptions &penOptions,
        const wxChartsBrushOptions &brushOptions);

    /// Gets the options for the pen used to draw the outline
    /// of the bar.
    /// @return The options for the pen used to draw the 
    /// outline of the bar.
    const wxChartsPenOptions& GetPenOptions() const;

    /// Gets the options for the brush used to fill the bar.
    /// @return The options for the brush used to fill the bar.
    const wxChartsBrushOptions& GetBrushOptions() const;

private:
    wxChartsPenOptions m_penOptions;
    wxChartsBrushOptions m_brushOptions;
};

#endif
