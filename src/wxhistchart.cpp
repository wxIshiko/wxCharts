/*
    Copyright (c) 2018 Xavier Leclercq and the wxCharts contributors.

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

/*
    Part of this file were copied from the Chart.js project (http://chartjs.org/)
    and translated into C++.

    The files of the Chart.js project have the following copyright and license.

    Copyright (c) 2013-2017 Nick Downie
    Released under the MIT license
    https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

#include "wxhistchart.h"
#include <wx/dcmemory.h>
#include <sstream>
#include <algorithm>

wxHistogramChartDataset::wxHistogramChartDataset(
    const wxColor &lineColor,
    const wxColor &fillColor,
    wxVector<wxDouble> &data)
    : m_lineColor(lineColor),m_fill(true),
      m_fillColor(fillColor),m_data(data)
{
}

bool wxHistogramChartDataset::Fill() const
{
    return m_fill;
}

const wxColor& wxHistogramChartDataset::GetFillColor() const
{
    return m_fillColor;
}

const wxColor& wxHistogramChartDataset::GetLineColor() const
{
    return m_lineColor;
}

const wxVector<wxDouble>& wxHistogramChartDataset::GetData() const
{
    return m_data;
}

wxHistogramChartData::wxHistogramChartData(
    wxHistogramChartDataset::ptr dataset, std::size_t n) : m_dataset(dataset),m_nbins(n)
{
}

const wxHistogramChartDataset::ptr& wxHistogramChartData::GetDataset() const
{
    return m_dataset;
}

std::size_t wxHistogramChartData::GetNBins() const
{
    return m_nbins;
}

wxHistogramChart::Dataset::Dataset(
    wxDouble min,wxDouble max,std::size_t n,
    const wxColor &lineColor,const wxColor &fillColor)
    :  m_lineColor(lineColor), m_fillColor(fillColor), m_fill(true)
{
    m_buckets = wxVector<Bucket>(n);
    double step = (max-min)/n;
    for(std::size_t i = 0; i<n; i++)
    {
        m_buckets[i].m_begin = min+i*step;
        m_buckets[i].m_end = min+(i+1)*step;
        m_buckets[i].m_count = 0;
    }
}

bool wxHistogramChart::Dataset::Fill() const
{
    return m_fill;
}

const wxColor& wxHistogramChart::Dataset::GetFillColor() const
{
    return m_fillColor;
}

const wxColor& wxHistogramChart::Dataset::GetLineColor() const
{
    return m_lineColor;
}

const wxVector<wxHistogramChart::Bucket>& wxHistogramChart::Dataset::GetBuckets() const
{
    return m_buckets;
}

void wxHistogramChart::Dataset::AppendValue(wxDouble value)
{
    auto it = std::find_if(m_buckets.begin(),m_buckets.end(),
                           [&value](const Bucket &b)
    {
        return (value>=b.m_begin && value<b.m_end);
    });
    if(it != m_buckets.end())
        it->m_count++;
    else
        m_buckets.rbegin()->m_count++;
}

wxHistogramChart::wxHistogramChart(const wxHistogramChartData &data,
                                   const wxSize &size)
    : m_grid(
          wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetRight()),
          size,0,0,0,0, m_options.GetGridOptions())
{
    Initialize(data);
}

wxHistogramChart::wxHistogramChart(const wxHistogramChartData &data,
                                   const wxHistogramChartOptions &options,
                                   const wxSize &size)
    : m_options(options),
      m_grid(
          wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetRight()),
          size,0,0,0,0, m_options.GetGridOptions())
{
    Initialize(data);
}

void wxHistogramChart::Initialize(const wxHistogramChartData &data)
{
    auto dataset = data.GetDataset();
    auto datasetData = dataset->GetData();
    if(datasetData.empty())
        return;
    auto minmax = std::minmax_element(datasetData.begin(),datasetData.end());
    m_dataset.reset(new Dataset(*minmax.first,*minmax.second,data.GetNBins(),
                                dataset->GetLineColor(),dataset->GetFillColor()));

    for (size_t j = 0; j < datasetData.size(); ++j)
        m_dataset->AppendValue(datasetData[j]);

    auto buckets = m_dataset->GetBuckets();

    auto maxY = std::max_element(buckets.begin(),buckets.end(),
                                 [](const Bucket &a,const Bucket b)
    {
        return a.m_count < b.m_count;
    });

    m_grid.UpdateAxisLimit("x",*minmax.first,*minmax.second);
    m_grid.UpdateAxisLimit("y",0,maxY->m_count);
}

const wxChartCommonOptions& wxHistogramChart::GetCommonOptions() const
{
    return m_options.GetCommonOptions();
}

void wxHistogramChart::Save(const wxString &filename,
                            const wxBitmapType &type,
                            const wxSize &size)
{
    wxBitmap bmp(size.GetWidth(), size.GetHeight());
    wxMemoryDC mdc(bmp);
    mdc.Clear();
    wxGraphicsContext* gc = wxGraphicsContext::Create(mdc);
    if (gc)
    {
        DoDraw(*gc, true);
        bmp.SaveFile(filename, type);
        delete gc;
    }
}

void wxHistogramChart::DoSetSize(const wxSize &size)
{
    wxSize newSize(
        size.GetWidth() - m_options.GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options.GetPadding().GetTotalVerticalPadding()
    );
    m_grid.Resize(newSize);
}

void wxHistogramChart::DoFit()
{
}

void wxHistogramChart::DoDraw(wxGraphicsContext &gc,
                              bool suppressTooltips)
{
    m_grid.Draw(gc);
    Fit();

    auto buckets = m_dataset->GetBuckets();

    if (buckets.size() > 0)
    {
        wxGraphicsPath path = gc.CreatePath();
        bool is_first = true;

        for (size_t j = 0; j < buckets.size(); ++j)
        {
            Bucket value = buckets[j];
            if(is_first)
            {
                path.MoveToPoint(m_grid.GetMapping().GetWindowPosition(value.m_begin, 0));
                is_first = false;
            }
            path.AddLineToPoint(m_grid.GetMapping().GetWindowPosition(value.m_begin, value.m_count));
            path.AddLineToPoint(m_grid.GetMapping().GetWindowPosition(value.m_end, value.m_count));
            path.AddLineToPoint(m_grid.GetMapping().GetWindowPosition(value.m_end, 0));
        }

        wxPen pen(m_dataset->GetLineColor(), m_options.GetLineWidth());
        gc.SetPen(pen);
        gc.StrokePath(path);
        if(m_dataset->Fill())
            gc.SetBrush(wxBrush(m_dataset->GetFillColor()));

        gc.FillPath(path);
    }

    if (!suppressTooltips)
    {
        DrawTooltips(gc);
    }
}

wxSharedPtr<wxVector<const wxChartElement*> > wxHistogramChart::GetActiveElements(const wxPoint &point)
{
    return wxSharedPtr<wxVector<const wxChartElement*> >(new wxVector<const wxChartElement*>());
}
