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

#include "wxstackedbarchart.h"
#include "wxchartcategoricalaxis.h"
#include "wxchartnumericalaxis.h"
#include <sstream>

wxStackedBarChart::Bar::Bar(wxDouble value,
                            const wxChartTooltipProvider::ptr tooltipProvider,
                            wxDouble x,
                            wxDouble y,
                            const wxColor &fillColor,
                            const wxColor &strokeColor,
                            int directions)
    : wxChartRectangle(x, y, tooltipProvider, wxChartRectangleOptions(fillColor, strokeColor, directions)),
    m_value(value)
{
}

bool wxStackedBarChart::Bar::HitTest(const wxPoint &point) const
{
    return ((point.y >= GetPosition().m_y) &&
        (point.y <= (GetPosition().m_y + GetHeight())));
}

wxDouble wxStackedBarChart::Bar::GetValue() const
{
    return m_value;
}

wxStackedBarChart::Dataset::Dataset()
{
}

const wxVector<wxStackedBarChart::Bar::ptr>& wxStackedBarChart::Dataset::GetBars() const
{
    return m_bars;
}

void wxStackedBarChart::Dataset::AppendBar(Bar::ptr column)
{
    m_bars.push_back(column);
}

wxStackedBarChart::wxStackedBarChart(const wxChartsCategoricalData &data,
                                     const wxSize &size)
    : m_grid(
        wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetRight()),
        size,
        wxChartCategoricalAxis::make_shared(data.GetLabels(), m_options.GetGridOptions().GetXAxisOptions()),
        wxChartNumericalAxis::make_shared(GetCumulativeMinValue(data.GetDatasets()), GetCumulativeMaxValue(data.GetDatasets()), m_options.GetGridOptions().GetYAxisOptions()),
        m_options.GetGridOptions()
        )
{
    const wxVector<wxChartsDoubleDataset::ptr>& datasets = data.GetDatasets();
    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxChartsDoubleDataset& dataset = *datasets[i];
        Dataset::ptr newDataset(new Dataset());

        int border = wxTOP | wxBOTTOM;
        if (i == (datasets.size() - 1))
        {
            border |= wxRIGHT;
        }

        const wxVector<wxDouble>& datasetData = dataset.GetData();
        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << datasetData[j];
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic(data.GetLabels()[j], tooltip.str(), dataset.GetFillColor())
                );

            newDataset->AppendBar(Bar::ptr(new Bar(
                datasetData[j],
                tooltipProvider,
                25, 50,
                dataset.GetFillColor(), dataset.GetStrokeColor(),
                border
                )));
        }

        m_datasets.push_back(newDataset);
    }
}

wxStackedBarChart::wxStackedBarChart(const wxChartsCategoricalData &data,
                                     const wxStackedBarChartOptions &options, 
                                     const wxSize &size)
    : m_options(options),
    m_grid(
        wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetRight()),
        size,
        wxChartCategoricalAxis::make_shared(data.GetLabels(), m_options.GetGridOptions().GetXAxisOptions()),
        wxChartNumericalAxis::make_shared(GetCumulativeMinValue(data.GetDatasets()), GetCumulativeMaxValue(data.GetDatasets()), m_options.GetGridOptions().GetYAxisOptions()),
        m_options.GetGridOptions()
        )
{
    const wxVector<wxChartsDoubleDataset::ptr>& datasets = data.GetDatasets();
    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxChartsDoubleDataset& dataset = *datasets[i];
        Dataset::ptr newDataset(new Dataset());

        int border = wxTOP | wxBOTTOM;
        if (i == (datasets.size() - 1))
        {
            border |= wxRIGHT;
        }

        const wxVector<wxDouble>& datasetData = dataset.GetData();
        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << datasetData[j];
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic(data.GetLabels()[j], tooltip.str(), dataset.GetFillColor())
                );

            newDataset->AppendBar(Bar::ptr(new Bar(
                datasetData[j],
                tooltipProvider,
                25, 50,
                dataset.GetFillColor(), dataset.GetStrokeColor(),
                border
                )));
        }

        m_datasets.push_back(newDataset);
    }
}

const wxStackedBarChartOptions& wxStackedBarChart::GetOptions() const
{
    return m_options;
}

wxDouble wxStackedBarChart::GetCumulativeMinValue(const wxVector<wxChartsDoubleDataset::ptr>& datasets)
{
    wxDouble result = 0;

    size_t i = 0;
    while (true)
    {
        wxDouble sum = 0;
        bool stop = true;
        for (size_t j = 0; j < datasets.size(); ++j)
        {
            const wxChartsDoubleDataset& dataset = *datasets[j];
            if (i < dataset.GetData().size())
            {
                sum += dataset.GetData()[i];
                stop = false;
            }
        }
        if (sum < result)
        {
            result = sum;
        }
        if (stop)
        {
            break;
        }
        ++i;
    }

    return result;
}

wxDouble wxStackedBarChart::GetCumulativeMaxValue(const wxVector<wxChartsDoubleDataset::ptr>& datasets)
{
    wxDouble result = 0;

    size_t i = 0;
    while (true)
    {
        wxDouble sum = 0;
        bool stop = true;
        for (size_t j = 0; j < datasets.size(); ++j)
        {
            const wxChartsDoubleDataset& dataset = *datasets[j];
            if (i < dataset.GetData().size())
            {
                sum += dataset.GetData()[i];
                stop = false;
            }
        }
        if (sum > result)
        {
            result = sum;
        }
        if (stop)
        {
            break;
        }
        ++i;
    }

    return result;
}

void wxStackedBarChart::DoSetSize(const wxSize &size)
{
    wxSize newSize(
        size.GetWidth() - m_options.GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options.GetPadding().GetTotalVerticalPadding()
        );
    m_grid.Resize(newSize);
}

void wxStackedBarChart::DoFit()
{
    wxVector<wxDouble> widthOfPreviousDatasets;
    for (size_t i = 0; i < m_datasets[0]->GetBars().size(); ++i)
    {
        widthOfPreviousDatasets.push_back(0);
    }

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        Dataset& currentDataset = *m_datasets[i];
        for (size_t j = 0; j < currentDataset.GetBars().size(); ++j)
        {
            Bar& bar = *(currentDataset.GetBars()[j]);

            wxPoint2DDouble upperLeftCornerPosition = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(j + 1);
            upperLeftCornerPosition.m_x += widthOfPreviousDatasets[j];
            upperLeftCornerPosition.m_y += m_options.GetBarSpacing();
            wxPoint2DDouble bottomLeftCornerPosition = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(j);
            bottomLeftCornerPosition.m_x += widthOfPreviousDatasets[j];
            bottomLeftCornerPosition.m_y -= m_options.GetBarSpacing();

            wxPoint2DDouble upperRightCornerPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(j + 1, bar.GetValue());
            upperRightCornerPosition.m_x += widthOfPreviousDatasets[j];

            bar.SetPosition(upperLeftCornerPosition);
            bar.SetSize(upperRightCornerPosition.m_x - upperLeftCornerPosition.m_x,
                bottomLeftCornerPosition.m_y - upperLeftCornerPosition.m_y);

            widthOfPreviousDatasets[j] += (upperRightCornerPosition.m_x - upperLeftCornerPosition.m_x);
        }
    }
}

void wxStackedBarChart::DoDraw(wxGraphicsContext &gc,
                               bool suppressTooltips)
{
    m_grid.Fit(gc);
    m_grid.Draw(gc);

    Fit();

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        Dataset& currentDataset = *m_datasets[i];
        for (size_t j = 0; j < currentDataset.GetBars().size(); ++j)
        {
            currentDataset.GetBars()[j]->Draw(gc);
        }
    }

    if (!suppressTooltips)
    {
        DrawTooltips(gc);
    }
}

wxSharedPtr<wxVector<const wxChartElement*> > wxStackedBarChart::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        const wxVector<Bar::ptr>& bars = m_datasets[i]->GetBars();
        for (size_t j = 0; j < bars.size(); ++j)
        {
            if (bars[j]->HitTest(point))
            {
                activeElements->push_back(bars[j].get());
            }
        }
    }

    return activeElements;
}
