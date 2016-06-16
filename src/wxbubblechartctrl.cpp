/*
	Copyright (c) 2016 Xavier Leclercq

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

#include "wxbubblechartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <sstream>

wxBubbleChartDataset::wxBubbleChartDataset(const wxColor& fillColor,
                                           const wxColor& outlineColor,
                                           wxVector<wxPoint2DDouble> &data)
    : m_fillColor(fillColor), m_outlineWidth(1), 
    m_outlineColor(outlineColor), m_data(data)
{
}

const wxColor& wxBubbleChartDataset::GetFillColor() const
{
    return m_fillColor;
}

unsigned int wxBubbleChartDataset::GetOutlineWidth() const
{
    return m_outlineWidth;
}

const wxColor& wxBubbleChartDataset::GetOutlineColor() const
{
    return m_outlineColor;
}

const wxVector<wxPoint2DDouble>& wxBubbleChartDataset::GetData() const
{
    return m_data;
}

wxBubbleChartData::wxBubbleChartData()
{
}

void wxBubbleChartData::AddDataset(wxBubbleChartDataset::ptr dataset)
{
    m_datasets.push_back(dataset);
}

const wxVector<wxBubbleChartDataset::ptr>& wxBubbleChartData::GetDatasets() const
{
    return m_datasets;
}

wxBubbleChartCtrl::Circle::Circle(wxPoint2DDouble value, 
                                  wxDouble x,
                                  wxDouble y,
                                  const wxChartTooltipProvider::ptr tooltipProvider,
                                  const wxChartCircleOptions &options)
    : wxChartCircle(x, y, tooltipProvider, options), m_value(value)
{
}

wxPoint2DDouble wxBubbleChartCtrl::Circle::GetValue() const
{
    return m_value;
}

wxBubbleChartCtrl::Dataset::Dataset()
{
}

const wxVector<wxBubbleChartCtrl::Circle::ptr>& wxBubbleChartCtrl::Dataset::GetCircles() const
{
    return m_circles;
}

void wxBubbleChartCtrl::Dataset::AppendCircle(Circle::ptr circle)
{
    m_circles.push_back(circle);
}

wxBubbleChartCtrl::wxBubbleChartCtrl(wxWindow *parent,
									 wxWindowID id,
									 const wxBubbleChartData &data,
									 const wxPoint &pos,
									 const wxSize &size,
									 long style)
	: wxChartCtrl(parent, id, pos, size, style),
    m_grid(
        wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetRight()),
        size,
        GetMinXValue(data.GetDatasets()), GetMaxXValue(data.GetDatasets()),
        GetMinYValue(data.GetDatasets()), GetMaxYValue(data.GetDatasets()),
        m_options.GetGridOptions()
        )
{
    Initialize(data);
}

const wxBubbleChartOptions& wxBubbleChartCtrl::GetOptions() const
{
	return m_options;
}

void wxBubbleChartCtrl::Initialize(const wxBubbleChartData &data)
{
    const wxVector<wxBubbleChartDataset::ptr>& datasets = data.GetDatasets();
    for (size_t i = 0; i < datasets.size(); ++i)
    {
        Dataset::ptr newDataset(new Dataset());

        const wxVector<wxPoint2DDouble>& datasetData = datasets[i]->GetData();
        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << "(" << datasetData[j].m_x << "," << datasetData[j].m_y << ")";
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic("", tooltip.str(), datasets[i]->GetFillColor())
                );

            Circle::ptr circle(
                new Circle(datasetData[j], 0, 0, tooltipProvider,
                    wxChartCircleOptions(datasets[i]->GetOutlineWidth(),
                        datasets[i]->GetOutlineColor(), datasets[i]->GetFillColor()))
                );

            newDataset->AppendCircle(circle);
        }

        m_datasets.push_back(newDataset);
    }
}

wxDouble wxBubbleChartCtrl::GetMinXValue(const wxVector<wxBubbleChartDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxPoint2DDouble>& values = datasets[i]->GetData();
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j].m_x;
                foundValue = true;
            }
            else if (result > values[j].m_x)
            {
                result = values[j].m_x;
            }
        }
    }

    return result;
}

wxDouble wxBubbleChartCtrl::GetMaxXValue(const wxVector<wxBubbleChartDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxPoint2DDouble>& values = datasets[i]->GetData();
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j].m_x;
                foundValue = true;
            }
            else if (result < values[j].m_x)
            {
                result = values[j].m_x;
            }
        }
    }

    return result;
}

wxDouble wxBubbleChartCtrl::GetMinYValue(const wxVector<wxBubbleChartDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxPoint2DDouble>& values = datasets[i]->GetData();
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j].m_y;
                foundValue = true;
            }
            else if (result > values[j].m_y)
            {
                result = values[j].m_y;
            }
        }
    }

    return result;
}

wxDouble wxBubbleChartCtrl::GetMaxYValue(const wxVector<wxBubbleChartDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxPoint2DDouble>& values = datasets[i]->GetData();
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j].m_y;
                foundValue = true;
            }
            else if (result < values[j].m_y)
            {
                result = values[j].m_y;
            }
        }
    }

    return result;
}

void wxBubbleChartCtrl::Resize(const wxSize &size)
{
	m_grid.Resize(size);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxBubbleChartCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	return activeElements;
}

void wxBubbleChartCtrl::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);

    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        m_grid.Draw(*gc);

        for (size_t i = 0; i < m_datasets.size(); ++i)
        {
            const wxVector<Circle::ptr>& circles = m_datasets[i]->GetCircles();
            for (size_t j = 0; j < circles.size(); ++j)
            {
                const Circle::ptr& circle = circles[j];
                circle->SetCenter(m_grid.GetMapping().GetWindowPosition(circle->GetValue().m_x, circle->GetValue().m_y));
                circle->Draw(*gc);
            }
        }

        DrawTooltips(*gc);

        delete gc;
    }
}

BEGIN_EVENT_TABLE(wxBubbleChartCtrl, wxChartCtrl)
	EVT_PAINT(wxBubbleChartCtrl::OnPaint)
END_EVENT_TABLE()
