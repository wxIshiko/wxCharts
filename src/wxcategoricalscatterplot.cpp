/*
    Copyright (c) 2019 Xavier Leclercq and the wxCharts contributors.

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

#include "wxcategoricalscatterplot.h"
#include "wxchartstheme.h"
#include "wxchartscategoricalaxis.h"
#include "wxchartsnumericalaxis.h"
#include <wx/brush.h>
#include <wx/pen.h>
#include <sstream>
#include <algorithm>

wxCategoricalScatterPlotData::wxCategoricalScatterPlotData(const wxVector<wxString> &labels,
        const wxVector<wxVector<wxDouble>> &data) : m_labels(labels), 
        m_lineColor(0, 0, 0, 0x80), m_width(3), m_fillColor(0, 205, 0, 0x60), m_data(data)
{
    for(auto &vec : m_data)
        std::sort(vec.begin(),vec.end());
}

const wxVector<wxString>& wxCategoricalScatterPlotData::GetLabels() const
{
    return m_labels;
}

const wxColor& wxCategoricalScatterPlotData::GetLineColor() const
{
    return m_lineColor;
}

const wxColor& wxCategoricalScatterPlotData::GetFillColor() const
{
    return m_fillColor;
}

unsigned int wxCategoricalScatterPlotData::GetWidth() const
{
    return m_width;
}

const wxVector<wxVector<wxDouble>>& wxCategoricalScatterPlotData::GetData() const
{
    return m_data;
}

wxCategoricalScatterPlot::Point::Point(wxDouble value, const wxColor &lineColor,
                                       const wxColor &fillColor, unsigned int lineWidth,
                                       const wxChartTooltipProvider::ptr tooltipProvider)
    : wxChartsElement(tooltipProvider), m_value(value), m_lineColor(lineColor),
      m_fillColor(fillColor), m_width(lineWidth)
{
}

void wxCategoricalScatterPlot::Point::Draw(wxGraphicsContext &gc) const
{
    wxGraphicsPath path = gc.CreatePath();
    auto radius = 10;
    path.AddArc(m_position.m_x, m_position.m_y, radius, 0, 2 * M_PI, false);
    path.CloseSubpath();

    wxBrush brush(m_fillColor);
    gc.SetBrush(brush);
    gc.FillPath(path);

    wxPen pen(m_lineColor, m_width);
    gc.SetPen(pen);
    gc.StrokePath(path);
}

bool wxCategoricalScatterPlot::Point::HitTest(const wxPoint &point) const
{
    wxDouble dx = point.x - m_position.m_x;
    wxDouble dy = point.y - m_position.m_y;
    return ((dx*dx+dy*dy) <= 10);
}

wxPoint2DDouble wxCategoricalScatterPlot::Point::GetTooltipPosition() const
{
    return m_position;
}

void wxCategoricalScatterPlot::Point::Update(const wxChartsGridMapping& mapping, size_t index)
{
    m_position = mapping.GetWindowPositionAtTickMark(index, m_value);
}

wxCategoricalScatterPlot::Dataset::Dataset()
{
}

const wxVector<wxCategoricalScatterPlot::Point::ptr>& wxCategoricalScatterPlot::Dataset::GetPoints() const
{
    return m_points;
}

void wxCategoricalScatterPlot::Dataset::AppendPoint(Point::ptr point)
{
    m_points.push_back(point);
}

wxCategoricalScatterPlot::wxCategoricalScatterPlot(const wxCategoricalScatterPlotData &data,
        const wxSize &size)
    : m_options(wxChartsDefaultTheme->GetCategoricalScatterPlotOptions()),
      m_grid(
          wxPoint2DDouble(m_options->GetPadding().GetLeft(), m_options->GetPadding().GetTop()),
          size,
          wxChartsCategoricalAxis::make_shared("x", data.GetLabels(), m_options->GetGridOptions().GetXAxisOptions()),
          wxChartsNumericalAxis::make_shared("y", GetMinValue(data), GetMaxValue(data), m_options->GetGridOptions().GetYAxisOptions()),
          m_options->GetGridOptions()
      )
{
    Initialize(data);
}

wxCategoricalScatterPlot::wxCategoricalScatterPlot(const wxCategoricalScatterPlotData &data,
        wxCategoricalScatterPlotOptions::ptr options,
        const wxSize &size)
    : m_options(options),
      m_grid(
          wxPoint2DDouble(m_options->GetPadding().GetLeft(), m_options->GetPadding().GetTop()),
          size,
          wxChartsCategoricalAxis::make_shared("x", data.GetLabels(), m_options->GetGridOptions().GetXAxisOptions()),
          wxChartsNumericalAxis::make_shared("y", GetMinValue(data), GetMaxValue(data), m_options->GetGridOptions().GetYAxisOptions()),
          m_options->GetGridOptions()
      )
{
    Initialize(data);
}

const wxChartCommonOptions& wxCategoricalScatterPlot::GetCommonOptions() const
{
    return m_options->GetCommonOptions();
}

void wxCategoricalScatterPlot::Initialize(const wxCategoricalScatterPlotData &data)
{
    auto &datasets = data.GetData();
    for (size_t i = 0; i < datasets.size(); ++i)
    {
        Dataset::ptr newDataset(new Dataset());

        for (size_t j = 0; j < datasets[i].size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << "(" << datasets[i][j] << ")";
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic("", tooltip.str(), data.GetFillColor())
            );

            Point::ptr point(new Point(datasets[i][j], data.GetFillColor(),
                                       data.GetLineColor(), data.GetWidth(), tooltipProvider));
            newDataset->AppendPoint(point);
        }
        m_data.push_back(newDataset);
    }
}

wxDouble wxCategoricalScatterPlot::GetMinValue(const wxCategoricalScatterPlotData &data)
{
    wxDouble result = 0;
    for(const auto &vec : data.GetData())
    {
        auto it = std::min_element(vec.begin(),vec.end());
        if (it != vec.end() && *it < result)
        {
            result = *it;
        }
    }
    return result;
}

wxDouble wxCategoricalScatterPlot::GetMaxValue(const wxCategoricalScatterPlotData &data)
{
    wxDouble result = 0;
    for(const auto &vec : data.GetData())
    {
        auto it = std::max_element(vec.begin(),vec.end());
        if (it != vec.end() && *it > result)
        {
            result = *it;
        }
    }
    return result;
}

void wxCategoricalScatterPlot::DoSetSize(const wxSize &size)
{
    wxSize newSize(
        size.GetWidth() - m_options->GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options->GetPadding().GetTotalVerticalPadding()
    );
    m_grid.Resize(newSize);
}

void wxCategoricalScatterPlot::DoFit()
{
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        auto points = m_data[i]->GetPoints();
        for (size_t j = 0; j < points.size(); ++j)
        {
            points[j]->Update(m_grid.GetMapping(), i);
        }
    }
}

void wxCategoricalScatterPlot::DoDraw(wxGraphicsContext &gc,
                                      bool suppressTooltips)
{
    m_grid.Fit(gc);
    m_grid.Draw(gc);

    Fit();

    for (size_t i = 0; i < m_data.size(); ++i)
    {
        auto points = m_data[i]->GetPoints();
        for (size_t j = 0; j < points.size(); ++j)
        {
            points[j]->Draw(gc);
        }
    }

    if(!suppressTooltips)
    {
        DrawTooltips(gc);
    }

}

wxSharedPtr<wxVector<const wxChartsElement*>> wxCategoricalScatterPlot::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartsElement*>> activeElements(new wxVector<const wxChartsElement*>());
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        const wxVector<Point::ptr>& points = m_data[i]->GetPoints();
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
