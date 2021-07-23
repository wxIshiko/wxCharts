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

#include "wxstackedbarchart.h"
#include "wxchartstheme.h"
#include "wxchartscategoricalaxis.h"
#include "wxchartsnumericalaxis.h"
#include <sstream>

wxStackedBarChart::Bar::Bar(wxDouble value,
                            const wxChartTooltipProvider::ptr tooltipProvider,
                            wxDouble x,
                            wxDouble y,
                            const wxChartsPenOptions &penOptions,
                            const wxChartsBrushOptions &brushOptions,
                            int borders)
    : wxChartsRectangle(x, y, tooltipProvider, wxChartsRectangleOptions(penOptions, brushOptions, borders)),
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

wxStackedBarChart::BarSet::BarSet()
{
}

const wxVector<wxSharedPtr<wxStackedBarChart::Bar>>& wxStackedBarChart::BarSet::GetBars() const
{
    return m_bars;
}

void wxStackedBarChart::BarSet::AppendBar(wxSharedPtr<Bar> column)
{
    m_bars.push_back(column);
}

wxStackedBarChart::wxStackedBarChart(wxSharedPtr<wxChartsCategoricalData> &data,
                                     const wxSize &size)
    : m_options(wxChartsDefaultTheme->GetStackedBarChartOptions())
{
    Initialize(data, size);
}

wxStackedBarChart::wxStackedBarChart(wxSharedPtr<wxChartsCategoricalData> &data,
                                     const wxStackedBarChartOptions &options, 
                                     const wxSize &size)
    : m_options(new wxStackedBarChartOptions(options))
{
    Initialize(data, size);
}

const wxChartCommonOptions& wxStackedBarChart::GetCommonOptions() const
{
    return m_options->GetCommonOptions();
}

void wxStackedBarChart::Initialize(wxSharedPtr<wxChartsCategoricalData> &data, const wxSize &size)
{
    wxVector<wxVector<wxDouble>> dataVectors;
    for (const wxSharedPtr<wxChartsDoubleDataset>& dataset : data->GetDatasets())
    {
        dataVectors.push_back(wxVector<wxDouble>());
        dataset->GetData(dataVectors.back());
    }

    m_grid.Create(
        wxPoint2DDouble(m_options->GetPadding().GetLeft(), m_options->GetPadding().GetRight()),
        size,
        wxChartsCategoricalAxis::make_shared("x", data->GetCategories(), m_options->GetGridOptions().GetXAxisOptions()),
        wxChartsNumericalAxis::make_shared("y", GetCumulativeMinValue(dataVectors), GetCumulativeMaxValue(dataVectors), m_options->GetGridOptions().GetYAxisOptions()),
        m_options->GetGridOptions()
    );

    for (size_t i = 0; i < dataVectors.size(); ++i)
    {
        wxSharedPtr<wxChartsDatasetTheme> datasetTheme = wxChartsDefaultTheme->GetDatasetTheme(wxChartsDatasetId::CreateImplicitId(i));
        wxSharedPtr<wxStackedBarChartDatasetOptions> datasetOptions = datasetTheme->GetStackedBarChartDatasetOptions();

        const wxVector<wxDouble>& datasetData = dataVectors[i];
        wxSharedPtr<BarSet> barSet(new BarSet());

        int border = wxTOP | wxBOTTOM;
        if (i == (dataVectors.size() - 1))
        {
            border |= wxRIGHT;
        }

        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << datasetData[j];
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic(data->GetCategories()[j], tooltip.str(), datasetOptions->GetBrushOptions().GetColor())
            );

            barSet->AppendBar(wxSharedPtr<Bar>(new Bar(
                datasetData[j],
                tooltipProvider,
                25, 50,
                datasetOptions->GetPenOptions(), datasetOptions->GetBrushOptions(),
                border
            )));
        }

        m_datasets.push_back(barSet);
    }
}

wxDouble wxStackedBarChart::GetCumulativeMinValue(const wxVector<wxVector<wxDouble>>& datasets)
{
    wxDouble result = 0;

    size_t i = 0;
    while (true)
    {
        wxDouble sum = 0;
        bool stop = true;
        for (size_t j = 0; j < datasets.size(); ++j)
        {
            const wxVector<wxDouble>& dataset = datasets[j];
            if (i < dataset.size())
            {
                sum += dataset[i];
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

wxDouble wxStackedBarChart::GetCumulativeMaxValue(const wxVector<wxVector<wxDouble>>& datasets)
{
    wxDouble result = 0;

    size_t i = 0;
    while (true)
    {
        wxDouble sum = 0;
        bool stop = true;
        for (size_t j = 0; j < datasets.size(); ++j)
        {
            const wxVector<wxDouble>& dataset = datasets[j];
            if (i < dataset.size())
            {
                sum += dataset[i];
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

wxSize wxStackedBarChart::DoGetBestSize() const
{
    // TODO
    return wxSize(200, 200);
}

void wxStackedBarChart::DoSetSize(const wxSize &size)
{
    wxSize newSize(
        size.GetWidth() - m_options->GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options->GetPadding().GetTotalVerticalPadding()
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
        BarSet& currentBarSet = *m_datasets[i];
        for (size_t j = 0; j < currentBarSet.GetBars().size(); ++j)
        {
            Bar& bar = *(currentBarSet.GetBars()[j]);

            wxPoint2DDouble upperLeftCornerPosition = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(j + 1);
            upperLeftCornerPosition.m_x += widthOfPreviousDatasets[j];
            upperLeftCornerPosition.m_y += m_options->GetBarSpacing();
            wxPoint2DDouble bottomLeftCornerPosition = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(j);
            bottomLeftCornerPosition.m_x += widthOfPreviousDatasets[j];
            bottomLeftCornerPosition.m_y -= m_options->GetBarSpacing();

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
        BarSet& currentDataset = *m_datasets[i];
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

wxSharedPtr<wxVector<const wxChartsElement*>> wxStackedBarChart::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartsElement*>> activeElements(new wxVector<const wxChartsElement*>());

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        const wxVector<wxSharedPtr<Bar>>& bars = m_datasets[i]->GetBars();
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
