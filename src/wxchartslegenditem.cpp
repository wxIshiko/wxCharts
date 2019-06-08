/*
    Copyright (c) 2018 Xavier Leclercq and the wxCharts contributors

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

#include "wxchartlegenditem.h"

wxChartLegendItem::wxChartLegendItem(const wxColor &color,
                                     const wxString &label)
    : m_color(color), m_label(label)
{
}

wxChartLegendItem::wxChartLegendItem(const wxChartSliceData &slice)
    : m_color(slice.GetColor()), m_label(slice.GetLabel())
{
}

wxChartLegendItem::wxChartLegendItem(const wxLineChartDataset &dataset)
    : m_color(*wxWHITE), m_label(dataset.GetLabel())
{
    if (dataset.ShowDots())
    {
        m_color = dataset.GetDotColor();
    }
    else if (dataset.ShowLine())
    {
        m_color = dataset.GetLineColor();
    }
    else if (dataset.Fill())
    {
        m_color = dataset.GetFillColor();
    }
}

const wxColor& wxChartLegendItem::GetColor() const
{
    return m_color;
}

const wxString& wxChartLegendItem::GetLabel() const
{
    return m_label;
}

wxChartLegendData::wxChartLegendData()
{
}

wxChartLegendData::wxChartLegendData(const std::map<wxString, wxChartSliceData>& slices)
{
    for (const auto &slice : slices)
    {
        m_items.push_back(wxChartLegendItem(slice.second));
    }
}

wxChartLegendData::wxChartLegendData(const wxVector<wxLineChartDataset::ptr>& datasets)
{
    for (size_t i = 0; i < datasets.size(); ++i)
    {
        m_items.push_back(wxChartLegendItem(*datasets[i]));
    }
}

void wxChartLegendData::Append(const wxChartLegendItem &item)
{
    m_items.push_back(item);
}

const wxVector<wxChartLegendItem>& wxChartLegendData::GetItems() const
{
    return m_items;
}
