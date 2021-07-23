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

#include "wxcandlestickchartctrl.h"

wxCandlestickChartCtrl::wxCandlestickChartCtrl(wxWindow *parent,
                                               wxWindowID id,
                                               const wxCandlestickChartData &data,
                                               const wxPoint &pos,
                                               const wxSize &size,
                                               long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_candlestickChart(data, size)
{
}

wxCandlestickChartCtrl::wxCandlestickChartCtrl(wxWindow *parent,
                                               wxWindowID id,
                                               const wxCandlestickChartData &data,
                                               wxCandlestickChartOptions::ptr options,
                                               const wxPoint &pos,
                                               const wxSize &size,
                                               long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_candlestickChart(data, options, size)
{
}

const wxCandlestickChart& wxCandlestickChartCtrl::GetChart() const
{
    return m_candlestickChart;
}

wxCandlestickChart& wxCandlestickChartCtrl::GetChart()
{
    return m_candlestickChart;
}
