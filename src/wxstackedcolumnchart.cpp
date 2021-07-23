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

/*
    Part of this file were copied from the Chart.js project (http://chartjs.org/)
    and translated into C++.

    The files of the Chart.js project have the following copyright and license.

    Copyright (c) 2013-2016 Nick Downie
    Released under the MIT license
    https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

#include "wxstackedcolumnchart.h"
#include "wxchartstheme.h"
#include "wxchartscategoricalaxis.h"
#include "wxchartsnumericalaxis.h"
#include <sstream>

wxStackedColumnChart::Column::Column(wxDouble value,
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

bool wxStackedColumnChart::Column::HitTest(const wxPoint &point) const
{
    return ((point.x >= GetPosition().m_x) &&
        (point.x <= (GetPosition().m_x + GetWidth())));
}

wxDouble wxStackedColumnChart::Column::GetValue() const
{
    return m_value;
}

wxStackedColumnChart::ColumnSet::ColumnSet()
{
}

const wxVector<wxSharedPtr<wxStackedColumnChart::Column>>& wxStackedColumnChart::ColumnSet::GetColumns() const
{
    return m_columns;
}

void wxStackedColumnChart::ColumnSet::AppendColumn(wxSharedPtr<Column> column)
{
    m_columns.push_back(column);
}

wxStackedColumnChart::wxStackedColumnChart(wxChartsCategoricalData::ptr &data,
                                           const wxSize &size)
    : m_options(wxChartsDefaultTheme->GetStackedColumnChartOptions())
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
        wxSharedPtr<wxStackedColumnChartDatasetOptions> datasetOptions = datasetTheme->GetStackedColumnChartDatasetOptions();

        const wxVector<wxDouble>& datasetData = dataVectors[i];
        wxSharedPtr<ColumnSet> newDataset(new ColumnSet());

        int border = wxLEFT | wxRIGHT;
        if (i == (dataVectors.size() - 1))
        {
            border |= wxTOP;
        }

        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << datasetData[j];
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic(data->GetCategories()[j], tooltip.str(), datasetOptions->GetBrushOptions().GetColor())
                );

            newDataset->AppendColumn(wxSharedPtr<Column>(new Column(
                datasetData[j],
                tooltipProvider,
                25, 50,
                datasetOptions->GetPenOptions(), datasetOptions->GetBrushOptions(),
                border
                )));
        }

        m_datasets.push_back(newDataset);
    }
}

const wxChartCommonOptions& wxStackedColumnChart::GetCommonOptions() const
{
    return m_options->GetCommonOptions();
}

wxDouble wxStackedColumnChart::GetCumulativeMinValue(const wxVector<wxVector<wxDouble>>& datasets)
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

wxDouble wxStackedColumnChart::GetCumulativeMaxValue(const wxVector<wxVector<wxDouble>>& datasets)
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

wxSize wxStackedColumnChart::DoGetBestSize()
{
    // TODO
    return wxSize(200, 200);
}

void wxStackedColumnChart::DoSetSize(const wxSize &size)
{
    m_grid.Resize(size);
}

void wxStackedColumnChart::DoFit()
{
    wxVector<wxDouble> heightOfPreviousDatasets;
    for (size_t i = 0; i < m_datasets[0]->GetColumns().size(); ++i)
    {
        heightOfPreviousDatasets.push_back(0);
    }

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        ColumnSet& currentDataset = *m_datasets[i];
        for (size_t j = 0; j < currentDataset.GetColumns().size(); ++j)
        {
            Column& column = *(currentDataset.GetColumns()[j]);

            wxPoint2DDouble upperLeftCornerPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(j, column.GetValue());
            upperLeftCornerPosition.m_x += m_options->GetColumnSpacing();
            upperLeftCornerPosition.m_y -= heightOfPreviousDatasets[j];
            wxPoint2DDouble upperRightCornerPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(j + 1, column.GetValue());
            upperRightCornerPosition.m_x -= m_options->GetColumnSpacing();
            upperRightCornerPosition.m_y -= heightOfPreviousDatasets[j];

            wxPoint2DDouble bottomLeftCornerPosition = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(j);

            column.SetPosition(upperLeftCornerPosition);
            column.SetSize(upperRightCornerPosition.m_x - upperLeftCornerPosition.m_x,
                (bottomLeftCornerPosition.m_y - heightOfPreviousDatasets[j]) - upperLeftCornerPosition.m_y);

            heightOfPreviousDatasets[j] = bottomLeftCornerPosition.m_y - upperLeftCornerPosition.m_y;
        }
    }
}

void wxStackedColumnChart::DoDraw(wxGraphicsContext &gc,
                                  bool suppressTooltips)
{
    m_grid.Fit(gc);
    m_grid.Draw(gc);

    Fit();

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        ColumnSet& currentDataset = *m_datasets[i];
        for (size_t j = 0; j < currentDataset.GetColumns().size(); ++j)
        {
            currentDataset.GetColumns()[j]->Draw(gc);
        }
    }

    if (!suppressTooltips)
    {
        DrawTooltips(gc);
    }
}

wxSharedPtr<wxVector<const wxChartsElement*>> wxStackedColumnChart::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartsElement*>> activeElements(new wxVector<const wxChartsElement*>());

    // Dataset are iterated in reverse order so that the tooltip items
    // are in the same order as the stacked columns
    for (int i = m_datasets.size() - 1; i >= 0; --i)
    {
        const wxVector<wxSharedPtr<Column>>& columns = m_datasets[i]->GetColumns();
        for (size_t j = 0; j < columns.size(); ++j)
        {
            if (columns[j]->HitTest(point))
            {
                activeElements->push_back(columns[j].get());
            }
        }
    }

    return activeElements;
}
