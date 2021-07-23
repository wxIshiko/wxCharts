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

/// @file

#include "wxlinechart.h"
#include "wxchartstheme.h"
#include "wxchartscategoricalaxis.h"
#include "wxchartsnumericalaxis.h"
#include <wx/brush.h>
#include <wx/pen.h>
#include <wx/dcmemory.h>
#include <sstream>

wxLineChart::Point::Point(wxDouble value,
                          const wxChartTooltipProvider::ptr tooltipProvider,
                          wxDouble x,
                          wxDouble y,
                          wxDouble radius,
                          unsigned int strokeWidth,
                          const wxColor &strokeColor,
                          const wxColor &fillColor,
                          wxDouble hitDetectionRange)
    : wxChartsPoint(x, y, radius, tooltipProvider, wxChartsPointOptions(strokeWidth, strokeColor, fillColor)),
    m_value(value), m_hitDetectionRange(hitDetectionRange)
{
}

bool wxLineChart::Point::HitTest(const wxPoint &point) const
{
    wxDouble distance = (point.x - GetPosition().m_x);
    if (distance < 0)
    {
        distance = -distance;
    }
    return (distance < m_hitDetectionRange);
}

wxDouble wxLineChart::Point::GetValue() const
{
    return m_value;
}

wxLineChart::PointSet::PointSet(bool showDots,
                                bool showLine,
                                const wxColor& lineColor,
                                bool fill,
                                const wxColor& fillColor,
                                const wxChartsLineType& lineType)
    : m_showDots(showDots), m_showLine(showLine),
    m_lineColor(lineColor), m_fill(fill),
    m_fillColor(fillColor), m_type(lineType)
{
}

bool wxLineChart::PointSet::ShowDots() const
{
    return m_showDots;
}

bool wxLineChart::PointSet::ShowLine() const
{
    return m_showLine;
}

const wxColor& wxLineChart::PointSet::GetLineColor() const
{
    return m_lineColor;
}

bool wxLineChart::PointSet::Fill() const
{
    return m_fill;
}

const wxColor& wxLineChart::PointSet::GetFillColor() const
{
    return m_fillColor;
}

const wxChartsLineType& wxLineChart::PointSet::GetType() const
{
     return m_type;
}

const wxVector<wxSharedPtr<wxLineChart::Point>>& wxLineChart::PointSet::GetPoints() const
{
    return m_points;
}

void wxLineChart::PointSet::AppendPoint(wxSharedPtr<Point> point)
{
    m_points.push_back(point);
}

wxLineChart::wxLineChart(wxChartsCategoricalData::ptr &data,
                         const wxChartsLineType &lineType,
                         const wxSize &size)
    : m_options(wxChartsDefaultTheme->GetLineChartOptions()),
    m_lineType(lineType)
{
    Initialize(data, size);
}

wxLineChart::wxLineChart(wxChartsCategoricalData::ptr &data,
                         const wxChartsLineType &lineType,
                         const wxLineChartOptions &options,
                         const wxSize &size)
    : m_options(new wxLineChartOptions(options)),
    m_lineType(lineType)
{
    Initialize(data, size);
}

const wxChartCommonOptions& wxLineChart::GetCommonOptions() const
{
    return m_options->GetCommonOptions();
}

void wxLineChart::Save(const wxString &filename,
                       const wxBitmapType &type,
                       const wxSize &size,
                       const wxColor &backgroundColor)
{
    wxBitmap bmp(size.GetWidth(), size.GetHeight());
    wxMemoryDC mdc(bmp);
    mdc.SetBackground(wxBrush(backgroundColor));
    mdc.Clear();
    wxGraphicsContext* gc = wxGraphicsContext::Create(mdc);
    if (gc)
    {
        DoDraw(*gc, true);
        bmp.SaveFile(filename, type);
        delete gc;
    }
}

void wxLineChart::Initialize(wxSharedPtr<wxChartsCategoricalData>& data, const wxSize& size)
{
    wxVector<wxVector<wxDouble>> dataVectors;
    for (const wxSharedPtr<wxChartsDoubleDataset>& dataset : data->GetDatasets())
    {
        dataVectors.push_back(wxVector<wxDouble>());
        dataset->GetData(dataVectors.back());
    }

    m_grid.Create(
        wxPoint2DDouble(m_options->GetPadding().GetLeft(), m_options->GetPadding().GetTop()),
        size,
        wxChartsCategoricalAxis::make_shared("x", data->GetCategories(), m_options->GetGridOptions().GetXAxisOptions()),
        wxChartsNumericalAxis::make_shared("y", GetMinValue(dataVectors), GetMaxValue(dataVectors), m_options->GetGridOptions().GetYAxisOptions()),
        m_options->GetGridOptions()
    );

    for (size_t i = 0; i < dataVectors.size(); ++i)
    {
        wxSharedPtr<wxChartsDatasetTheme> datasetTheme = wxChartsDefaultTheme->GetDatasetTheme(wxChartsDatasetId::CreateImplicitId(i));
        wxSharedPtr<wxLineChartDatasetOptions> datasetOptions = datasetTheme->GetLineChartDatasetOptions();

        wxSharedPtr<PointSet> newDataset(new PointSet(datasetOptions->ShowDots(),
            datasetOptions->ShowLine(), datasetOptions->GetLineColor(),
            datasetOptions->Fill(), datasetOptions->GetFillColor(),
            m_lineType));

        const wxVector<wxDouble>& datasetData = dataVectors[i];
        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << datasetData[j];
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic(data->GetCategories()[j], tooltip.str(), datasetOptions->GetLineColor())
                );

            Point::ptr point(
                new Point(datasetData[j], tooltipProvider, 20 + j * 10, 0,
                    datasetOptions->GetDotRadius(), datasetOptions->GetDotPenOptions().GetWidth(),
                    datasetOptions->GetDotPenOptions().GetColor(), datasetOptions->GetDotBrushOptions().GetColor(),
                    m_options->GetHitDetectionRange())
                );

            newDataset->AppendPoint(point);
        }

        m_datasets.push_back(newDataset);
    }
}

wxDouble wxLineChart::GetMinValue(const wxVector<wxVector<wxDouble>>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxDouble>& values = datasets[i];
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j];
                foundValue = true;
            }
            else if (result > values[j])
            {
                result = values[j];
            }
        }
    }

    return result;
}

wxDouble wxLineChart::GetMaxValue(const wxVector<wxVector<wxDouble>>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxDouble>& values = datasets[i];
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j];
                foundValue = true;
            }
            else if (result < values[j])
            {
                result = values[j];
            }
        }
    }

    return result;
}

wxSize wxLineChart::DoGetBestSize() const
{
    return m_grid.GetBestSize();
}

void wxLineChart::DoSetSize(const wxSize &size)
{
    wxSize newSize(
        size.GetWidth() - m_options->GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options->GetPadding().GetTotalVerticalPadding()
        );
    m_grid.Resize(newSize);
}

void wxLineChart::DoFit()
{
}

void wxLineChart::DoDraw(wxGraphicsContext &gc,
                         bool suppressTooltips)
{
    m_grid.Fit(gc);
    m_grid.Draw(gc);

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        const wxVector<Point::ptr>& points = m_datasets[i]->GetPoints();

        wxGraphicsPath path = gc.CreatePath();

        if (points.size() > 0)
        {
            const Point::ptr& point = points[0];
            wxPoint2DDouble firstPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(0, point->GetValue());
            path.MoveToPoint(firstPosition);

            wxPoint2DDouble lastPosition;
            for (size_t j = 1; j < points.size(); ++j)
            {
                const Point::ptr& point = points[j];
                lastPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(j, point->GetValue());
                if (m_datasets[i]->GetType() == wxCHARTSLINETYPE_STEPPED)
                {
                    wxPoint2DDouble temp = m_grid.GetMapping().GetWindowPositionAtTickMark(j, points[j - 1]->GetValue());
                    path.AddLineToPoint(temp);
                }
                path.AddLineToPoint(lastPosition);
            }

            if (m_datasets[i]->ShowLine())
            {
                wxSharedPtr<wxChartsDatasetTheme> datasetTheme = wxChartsDefaultTheme->GetDatasetTheme(wxChartsDatasetId::CreateImplicitId(i));
                wxSharedPtr<wxLineChartDatasetOptions> datasetOptions = datasetTheme->GetLineChartDatasetOptions();

                wxPen pen(m_datasets[i]->GetLineColor(), datasetOptions->GetLineWidth());
                gc.SetPen(pen);
            }
            else
            {
                static const wxColor transparent(255, 255, 255, 0);
                wxPen pen(transparent, 0);
                gc.SetPen(pen);
            }

            gc.StrokePath(path);

            wxPoint2DDouble yPos = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(0);

            path.AddLineToPoint(lastPosition.m_x, yPos.m_y);
            path.AddLineToPoint(firstPosition.m_x, yPos.m_y);
            path.CloseSubpath();

            wxBrush brush(m_datasets[i]->GetFillColor());
            gc.SetBrush(brush);
            gc.FillPath(path);
        }

        if (m_datasets[i]->ShowDots())
        {
            for (size_t j = 0; j < points.size(); ++j)
            {
                const Point::ptr& point = points[j];
                point->SetPosition(m_grid.GetMapping().GetWindowPositionAtTickMark(j, point->GetValue()));
                point->Draw(gc);
            }
        }
        else
        {
            for (size_t j = 0; j < points.size(); ++j)
            {
                const Point::ptr& point = points[j];
                point->SetPosition(m_grid.GetMapping().GetWindowPositionAtTickMark(j, point->GetValue()));
            }
        }
    }

    if (!suppressTooltips)
    {
        DrawTooltips(gc);
    }
}

wxSharedPtr<wxVector<const wxChartsElement*>> wxLineChart::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartsElement*>> activeElements(new wxVector<const wxChartsElement*>());
    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        const wxVector<Point::ptr>& points = m_datasets[i]->GetPoints();
        for (size_t j = 0; j < points.size(); ++j)
        {
            if (points[j]->HitTest(point))
            {
                activeElements->push_back(points[j].get());
            }
        }
    }
    return activeElements;
}
