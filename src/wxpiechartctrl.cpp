/*
    Copyright (c) 2016-2018 Xavier Leclercq

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

#include "wxpiechartctrl.h"

wxPieChartCtrl::wxPieChartCtrl(wxWindow *parent,
                               wxWindowID id,
                               wxPieChartData &data,
                               const wxPoint &pos,
                               const wxSize &size, 
                               long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_pieChart(data, size)
{
    SetMinSize(wxSize(100, 100));
	data.AddObserver(this);
}

wxPieChartCtrl::wxPieChartCtrl(wxWindow *parent,
                               wxWindowID id,
                               wxPieChartData &data,
                               const wxPieChartOptions &options,
                               const wxPoint &pos,
                               const wxSize &size,
                               long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_pieChart(data, options, size)
{
    data.AddObserver(this);
}

wxPieChart& wxPieChartCtrl::GetChart()
{
    return m_pieChart;
}

void wxPieChartCtrl::OnUpdate(const std::unordered_map<wxString,wxChartSliceData> &data)
{
    m_pieChart.SetData(data);
    auto parent = this->GetParent();
    if(parent)
        parent->Layout();
}
