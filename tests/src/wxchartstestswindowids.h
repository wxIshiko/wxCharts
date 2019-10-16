/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#ifndef _TESTS_WX_CHARTS_WXCHARTSTESTSWINDOWIDS_H_
#define _TESTS_WX_CHARTS_WXCHARTSTESTSWINDOWIDS_H_

#include <wx/defs.h>

const wxWindowID wxID_DEFAULT_THEME = wxID_HIGHEST + 1;

const wxWindowID wxID_RECTANGLE_ELEMENT = wxID_DEFAULT_THEME + 1;
const wxWindowID wxID_LABEL_ELEMENT = wxID_RECTANGLE_ELEMENT + 1;
const wxWindowID wxID_CATEGORICALAXIS_ELEMENT = wxID_LABEL_ELEMENT + 1;
const wxWindowID wxID_NUMERICALAXIS_ELEMENT = wxID_CATEGORICALAXIS_ELEMENT + 1;
const wxWindowID wxID_GRID_ELEMENT = wxID_NUMERICALAXIS_ELEMENT + 1;

const wxWindowID wxID_AREA_CHART = wxID_GRID_ELEMENT + 1;
const wxWindowID wxID_BAR_CHART = wxID_AREA_CHART + 1;
const wxWindowID wxID_BOX_PLOT = wxID_BAR_CHART + 1;
const wxWindowID wxID_BUBBLE_CHART = wxID_BOX_PLOT + 1;
const wxWindowID wxID_CANDLESTICK_CHART = wxID_BUBBLE_CHART + 1;
const wxWindowID wxID_COLUMN_CHART = wxID_CANDLESTICK_CHART + 1;
const wxWindowID wxID_DOUGHNUT_CHART = wxID_COLUMN_CHART + 1;
const wxWindowID wxID_HISTOGRAM = wxID_DOUGHNUT_CHART + 1;
const wxWindowID wxID_LINE_CHART = wxID_HISTOGRAM + 1;
const wxWindowID wxID_PIE_CHART = wxID_LINE_CHART + 1;
const wxWindowID wxID_POLARAREA_CHART = wxID_PIE_CHART + 1;
const wxWindowID wxID_STACKEDBAR_CHART = wxID_POLARAREA_CHART + 1;
const wxWindowID wxID_STACKEDCOLUMN_CHART = wxID_STACKEDBAR_CHART + 1;

const wxWindowID wxID_ALL_TESTS = wxID_STACKEDCOLUMN_CHART + 1;

#endif
