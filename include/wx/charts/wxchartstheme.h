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

/// @file

#ifndef _WX_CHARTS_WXCHARTSTHEME_H_
#define _WX_CHARTS_WXCHARTSTHEME_H_

#include "wxbarchartoptions.h"
#include "wxcolumnchartoptions.h"
#include "wxstackedbarchartoptions.h"
#include "wxstackedcolumnchartoptions.h"
#include <wx/sharedptr.h>

class wxChartsTheme
{
public:
    wxChartsTheme();

    wxSharedPtr<wxBarChartOptions> GetBarChartOptions();
    wxSharedPtr<wxColumnChartOptions> GetColumnChartOptions();
    wxSharedPtr<wxStackedBarChartOptions> GetStackedBarChartOptions();
    wxSharedPtr<wxStackedColumnChartOptions> GetStackedColumnChartOptions();

private:
    wxSharedPtr<wxBarChartOptions> m_barChartOptions;
    wxSharedPtr<wxColumnChartOptions> m_columnChartOptions;
    wxSharedPtr<wxStackedBarChartOptions> m_stackedBarChartOptions;
    wxSharedPtr<wxStackedColumnChartOptions> m_stackedColumnChartOptions;
};

extern wxSharedPtr<wxChartsTheme> wxChartsDefaultTheme;

#endif
