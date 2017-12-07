/*
    Copyright (c) 2016-2017 Xavier Leclercq

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

#ifndef _WX_CHARTS_WXCHARTSCATEGORICALDATA_H_
#define _WX_CHARTS_WXCHARTSCATEGORICALDATA_H_

#include "wxchartsdoubledataset.h"
#include <wx/vector.h>

/// Data for one of the bar chart controls.

/// The wxBarChartCtrl, wxColumnChartCtrl, wxStackedBarChartCtrl and wxStackedColumnChartCtrl use this class.
class wxChartsCategoricalData
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxChartsCategoricalData> ptr;

    /// Constructs a wxBarChartData instance.
    /// @param labels The labels of the X axis.
    wxChartsCategoricalData(const wxVector<wxString> &labels);

    /// Adds a dataset.
    /// @param dataset The dataset to add.
    void AddDataset(wxChartsDoubleDataset::ptr dataset);

    /// Gets the labels of the X axis.
    /// @return A vector containing the labels of the
    /// X axis.
    const wxVector<wxString>& GetLabels() const;
    const wxVector<wxChartsDoubleDataset::ptr>& GetDatasets() const;

private:
    wxVector<wxString> m_labels;
    wxVector<wxChartsDoubleDataset::ptr> m_datasets;
};

#endif
