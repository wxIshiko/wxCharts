/*
    Copyright (c) 2016-2018 Xavier Leclercq and the wxCharts contributors

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

#include "wxpiechart.h"

wxPieChartData::wxPieChartData()
{
}

const std::map<wxString,wxChartSliceData>& wxPieChartData::GetSlices() const
{
    return m_value;
}

void wxPieChartData::AppendSlice(const wxChartSliceData &slice)
{
    Add(slice);
    Notify();
}

void wxPieChartData::UpdateSlices(const wxVector<wxChartSliceData> &slices)
{
    m_value.clear();
    AddSlices(slices);
}

void wxPieChartData::AddSlices(const wxVector<wxChartSliceData> &slices)
{
    for(const auto &slice : slices)
        Add(slice);

    Notify();
}

void wxPieChartData::Add(const wxChartSliceData &slice)
{
    auto key = slice.GetLabel();
	auto it = m_value.find(key);
    if( it == m_value.end())
		m_value.insert(std::make_pair(key,slice));
	else
		it->second.SetValue(it->second.GetValue()+slice.GetValue());
}

wxPieChart::wxPieChart(const wxPieChartData &data,
                       const wxSize &size) : wxDoughnutAndPieChartBase(size)
{
    Initialize(data);
}

wxPieChart::wxPieChart(const wxPieChartData &data,
                       const wxPieChartOptions &options,
                       const wxSize &size)
    : wxDoughnutAndPieChartBase(size), m_options(options)
{
    Initialize(data);
}

const wxChartCommonOptions& wxPieChart::GetCommonOptions() const
{
    return m_options.GetCommonOptions();
}

void wxPieChart::Initialize(const wxPieChartData &data)
{
    SetData(data.GetSlices());
}

const wxDoughnutAndPieChartOptionsBase& wxPieChart::GetOptions() const
{
    return m_options;
}
