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

#ifndef _WX_CHARTS_WXAREACHARTDATASETOPTIONS_H_
#define _WX_CHARTS_WXAREACHARTDATASETOPTIONS_H_

#include "dlimpexp.h"
#include <wx/colour.h>

class WXDLLIMPEXP_ISHIKO_CHARTS wxAreaChartDatasetOptions
{
public:
    wxAreaChartDatasetOptions(const wxColor &dotColor);

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

private:
    bool m_showDots;
    wxColor m_dotColor;
    bool m_showLine;
    wxColor m_lineColor;
};

#endif
