/*
    Copyright (c) 2018 Xavier Leclercq

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

#ifndef _WX_CHARTS_WXCHARTLEGENDITEM_H_
#define _WX_CHARTS_WXCHARTLEGENDITEM_H_

#include "wxchartslicedata.h"
#include "wxlinechartctrl.h"
#include <wx/vector.h>
#include <wx/colour.h>
#include <wx/string.h>

#include <unordered_map>

/// Class that represents items of the wxChartLegendData class.
class wxChartLegendItem
{
public:
    /// Constructs a wxChartLegendItem instance.
    /// @param color The color associated with this
    /// item on the chart.
    /// @param label The text to be display in the legend.
    wxChartLegendItem(const wxColor &color,
        const wxString &label);
    /// Constructs a wxChartLegendItem instance from a
    /// slice data.
    /// @param slice The slice of the chart this legend item
    /// corresponds to.
    wxChartLegendItem(const wxChartSliceData &slice);
    /// Constructs a wxChartLegendItem instance from a
    /// line chart dataset.
    /// @param dataset The dataset this legend item
    /// corresponds to.
    wxChartLegendItem(const wxLineChartDataset &dataset);

    /// Gets the color of the item.
    /// @return The color of the item.
    const wxColor& GetColor() const;
    /// Gets the label of the item.
    /// @return The label of the item.
    const wxString& GetLabel() const;

private:
    wxColor m_color;
    wxString m_label;
};

typedef wxVector<wxChartLegendItem> wxChartLegendItems;

/// Data for the wxChartLegendCtrl control.
class wxChartLegendData
{
public:
    /// Constructs a wxChartLegendData
    /// instance.
    wxChartLegendData();
    /// Constructs a wxChartLegendData instance from
    /// a list of slices. This can be used to build
    /// a legend for the wxPieChartCtrl and
    /// wxDoughnutChartCtrl controls for instance.
    /// @param slices List of slices.
    wxChartLegendData(const std::unordered_map<wxString,wxChartSliceData>& slices);
    /// Constructs a wxChartLegendData instance from
    /// a list of datasets. This can be used to build
    /// a legend for the wxLineChartCtrl control.
    /// @param datasets List of datasets.
    wxChartLegendData(const wxVector<wxLineChartDataset::ptr>& datasets);

    /// Appends an item to the legend.
    /// @param item The new item.
    void Append(const wxChartLegendItem &item);

    /// Gets the list of items in the legend.
    /// @return The list of legend items.
    const wxVector<wxChartLegendItem>& GetItems() const;

private:
    wxVector<wxChartLegendItem> m_items;
};

#endif
