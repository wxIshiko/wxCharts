/*
    Copyright (c) 2016-2019 Xavier Leclercq

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

wxLineChartDataset::wxLineChartDataset(const wxString &label,
                                       const wxColor &dotColor,
                                       const wxColor &dotStrokeColor,
                                       const wxColor &fillColor,
                                       const wxVector<wxDouble> &data,
                                       const wxLineType &lineType)
    : m_label(label), m_showDots(true), m_dotColor(dotColor),
    m_dotStrokeColor(dotStrokeColor), m_showLine(true),
    m_lineColor(dotColor), m_fill(true), m_fillColor(fillColor),
    m_data(data),m_type(lineType)
{
}

const wxString& wxLineChartDataset::GetLabel() const
{
    return m_label;
}

bool wxLineChartDataset::ShowDots() const
{
    return m_showDots;
}

const wxColor& wxLineChartDataset::GetDotColor() const
{
    return m_dotColor;
}

const wxColor& wxLineChartDataset::GetDotStrokeColor() const
{
    return m_dotStrokeColor;
}

const wxLineType& wxLineChartDataset::GetType() const
{
    return m_type;
}

bool wxLineChartDataset::ShowLine() const
{
    return m_showLine;
}

const wxColor& wxLineChartDataset::GetLineColor() const
{
    return m_lineColor;
}

bool wxLineChartDataset::Fill() const
{
    return m_fill;
}

const wxColor& wxLineChartDataset::GetFillColor() const
{
    return m_fillColor;
}

const wxVector<double>& wxLineChartDataset::GetData() const
{
    return m_data;
}

wxLineChartData::wxLineChartData(const wxVector<wxString> &labels)
    : m_labels(labels)
{
}

void wxLineChartData::AddDataset(wxLineChartDataset::ptr dataset)
{
    m_datasets.push_back(dataset);
}

const wxVector<wxString>& wxLineChartData::GetLabels() const
{
    return m_labels;
}

const wxVector<wxLineChartDataset::ptr>& wxLineChartData::GetDatasets() const
{
    return m_datasets;
}

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

wxLineChart::Dataset::Dataset(bool showDots,
    bool showLine,
    const wxColor &lineColor,
    bool fill,
    const wxColor &fillColor,
    const wxLineType &lineType)
    : m_showDots(showDots), m_showLine(showLine),
    m_lineColor(lineColor), m_fill(fill),
    m_fillColor(fillColor), m_type(lineType)
{
}

bool wxLineChart::Dataset::ShowDots() const
{
    return m_showDots;
}

bool wxLineChart::Dataset::ShowLine() const
{
    return m_showLine;
}

const wxColor& wxLineChart::Dataset::GetLineColor() const
{
    return m_lineColor;
}

bool wxLineChart::Dataset::Fill() const
{
    return m_fill;
}

const wxColor& wxLineChart::Dataset::GetFillColor() const
{
    return m_fillColor;
}

const wxLineType& wxLineChart::Dataset::GetType() const
{
     return m_type;
}

const wxVector<wxLineChart::Point::ptr>& wxLineChart::Dataset::GetPoints() const
{
    return m_points;
}

void wxLineChart::Dataset::AppendPoint(Point::ptr point)
{
    m_points.push_back(point);
}

wxLineChart::wxLineChart(const wxLineChartData &data,
                         const wxSize &size)
    : m_options(wxChartsDefaultTheme->GetLineChartOptions()),
    m_grid(
        wxPoint2DDouble(m_options->GetPadding().GetLeft(), m_options->GetPadding().GetTop()),
        size,
        wxChartsCategoricalAxis::make_shared("x", data.GetLabels(), m_options->GetGridOptions().GetXAxisOptions()),
        wxChartsNumericalAxis::make_shared("y", GetMinValue(data.GetDatasets()), GetMaxValue(data.GetDatasets()), m_options->GetGridOptions().GetYAxisOptions()),
        m_options->GetGridOptions()
        )
{
    Initialize(data);
}

wxLineChart::wxLineChart(const wxLineChartData &data,
                         const wxLineChartOptions &options,
                         const wxSize &size)
    : m_options(new wxLineChartOptions(options)),
    m_grid(
        wxPoint2DDouble(m_options->GetPadding().GetLeft(), m_options->GetPadding().GetTop()),
        size,
        wxChartsCategoricalAxis::make_shared("x", data.GetLabels(), m_options->GetGridOptions().GetXAxisOptions()),
        wxChartsNumericalAxis::make_shared("y", GetMinValue(data.GetDatasets()), GetMaxValue(data.GetDatasets()), m_options->GetGridOptions().GetYAxisOptions()),
        m_options->GetGridOptions()
        )
{
    Initialize(data);
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

void wxLineChart::Initialize(const wxLineChartData &data)
{
    const wxVector<wxLineChartDataset::ptr>& datasets = data.GetDatasets();
    for (size_t i = 0; i < datasets.size(); ++i)
    {
        wxSharedPtr<wxChartsDatasetTheme> datasetTheme = wxChartsDefaultTheme->GetDatasetTheme(wxChartsDatasetId::CreateImplicitId(i));
        wxSharedPtr<wxLineChartDatasetOptions> datasetOptions = datasetTheme->GetLineChartDatasetOptions();

        Dataset::ptr newDataset(new Dataset(datasetOptions->ShowDots(),
            datasets[i]->ShowLine(), datasets[i]->GetLineColor(),
            datasets[i]->Fill(), datasets[i]->GetFillColor(),
            datasets[i]->GetType()));

        const wxVector<wxDouble>& datasetData = datasets[i]->GetData();
        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << datasetData[j];
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic(data.GetLabels()[j], tooltip.str(), datasets[i]->GetLineColor())
                );

            Point::ptr point(
                new Point(datasetData[j], tooltipProvider, 20 + j * 10, 0,
                    datasetOptions->GetDotRadius(), datasetOptions->GetDotStrokeWidth(),
                    datasetOptions->GetDotStrokeColor(), datasetOptions->GetDotColor(),
                    m_options->GetHitDetectionRange())
                );

            newDataset->AppendPoint(point);
        }

        m_datasets.push_back(newDataset);
    }
}

wxDouble wxLineChart::GetMinValue(const wxVector<wxLineChartDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxDouble>& values = datasets[i]->GetData();
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

wxDouble wxLineChart::GetMaxValue(const wxVector<wxLineChartDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxDouble>& values = datasets[i]->GetData();
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
                if(m_datasets[i]->GetType()==wxLINETYPE_STEPPEDLINE)
                 {
                     wxPoint2DDouble temp = m_grid.GetMapping().GetWindowPositionAtTickMark(j, points[j-1]->GetValue());
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
                // TODO : transparent pen
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
