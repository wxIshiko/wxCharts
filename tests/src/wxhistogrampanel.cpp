/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "wxhistogrampanel.h"
#include <wx/sizer.h>
#include <wx/choice.h>
#include <random>

wxHistogramPanel::wxHistogramPanel(wxWindow* parent)
    : wxPanel(parent)
{
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Create the data for the histogram chart widget
    const std::size_t N = 10000;
    wxVector<wxDouble> data;
    data.reserve(N);
    std::default_random_engine generator;
    std::normal_distribution<wxDouble> distribution(5.0, 2.0);

    for (std::size_t i = 0; i < N; ++i)
    {
        wxDouble number = distribution(generator);
        if ((number >= 0.0) && (number < 10.0))
        {
            data.push_back(number);
        }
    }

    wxHistogramDataset::ptr dataset(
        new wxHistogramDataset(wxColor(134, 134, 134), wxColor(127, 46, 46), data)
    );

    wxHistogramData chartData(dataset, 20);

    // Create the histogram widget
    m_histogram = new wxHistogramCtrl(this, wxID_ANY, chartData);
    sizer->Add(m_histogram, 1, wxEXPAND);

    SetSizer(sizer);
}
