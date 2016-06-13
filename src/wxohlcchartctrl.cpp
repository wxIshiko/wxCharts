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

#include "wxohlcchartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <sstream>

wxOHLCChartData::wxOHLCChartData(const wxVector<wxString> &labels, 
                                 const wxVector<wxChartOHLCData> &data)
    : m_labels(labels), m_lineWidth(3), m_lineColor(91, 127, 125), 
    m_openLineLength(10), m_closeLineLength(10), m_data(data)
{
}

const wxVector<wxString>& wxOHLCChartData::GetLabels() const
{
    return m_labels;
}

unsigned int wxOHLCChartData::GetLineWidth() const
{
    return m_lineWidth;
}

const wxColor& wxOHLCChartData::GetLineColor() const
{
    return m_lineColor;
}

unsigned int wxOHLCChartData::GetOpenLineLength() const
{
    return m_openLineLength;
}

unsigned int wxOHLCChartData::GetCloseLineLength() const
{
    return m_closeLineLength;
}

const wxVector<wxChartOHLCData>& wxOHLCChartData::GetData() const
{
    return m_data;
}

wxOHLCChartCtrl::OHLDCLines::OHLDCLines(const wxChartOHLCData &data, 
                                        unsigned int lineWidth,
                                        const wxColor& lineColor,
                                        unsigned int openLineLength,
                                        unsigned int closeLineLength,
                                        const wxChartTooltipProvider::ptr tooltipProvider)
    : wxChartElement(tooltipProvider), m_data(data), m_lowPoint(0, 0), m_highPoint(0, 0),
    m_openPoint(0, 0), m_closePoint(0, 0), m_lineWidth(lineWidth), m_lineColor(lineColor),
    m_openLineLength(openLineLength), m_closeLineLength(closeLineLength)
{
}

bool wxOHLCChartCtrl::OHLDCLines::HitTest(const wxPoint &point) const
{
    return ((point.y <= m_lowPoint.m_y) && (point.y >= m_highPoint.m_y) &&
        (point.x >= (m_lowPoint.m_x - m_openLineLength)) && 
        (point.x <= (m_lowPoint.m_x + m_closeLineLength)));
}

wxPoint2DDouble wxOHLCChartCtrl::OHLDCLines::GetTooltipPosition() const
{
    return wxPoint2DDouble(m_lowPoint.m_x, m_highPoint.m_y + (m_lowPoint.m_y - m_highPoint.m_y) / 2);
}

void wxOHLCChartCtrl::OHLDCLines::Draw(wxGraphicsContext &gc)
{
    wxGraphicsPath path = gc.CreatePath();
    path.MoveToPoint(m_highPoint);
    path.AddLineToPoint(m_lowPoint);
    
    path.MoveToPoint(wxPoint2DDouble(m_openPoint.m_x - m_openLineLength, m_openPoint.m_y));
    path.AddLineToPoint(m_openPoint);

    path.MoveToPoint(m_closePoint);
    path.AddLineToPoint(wxPoint2DDouble(m_closePoint.m_x + m_closeLineLength, m_closePoint.m_y));

    wxPen pen(m_lineColor, m_lineWidth);
    gc.SetPen(pen);
    gc.StrokePath(path);
}

void wxOHLCChartCtrl::OHLDCLines::Update(const wxChartGridMapping& mapping,
                                         size_t index)
{
    m_lowPoint = mapping.GetWindowPositionAtTickMark(index, m_data.low());
    m_highPoint = mapping.GetWindowPositionAtTickMark(index, m_data.high());
    m_openPoint = mapping.GetWindowPositionAtTickMark(index, m_data.open());
    m_closePoint = mapping.GetWindowPositionAtTickMark(index, m_data.close());
}

wxOHLCChartCtrl::wxOHLCChartCtrl(wxWindow *parent,
                                 wxWindowID id,
                                 const wxOHLCChartData &data,
                                 const wxPoint &pos,
                                 const wxSize &size,
                                 long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_grid(
        wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetTop()),
        size, data.GetLabels(), GetMinValue(data), GetMaxValue(data), m_options.GetGridOptions()
        )
{
    for (size_t i = 0; i < data.GetData().size(); ++i)
    {
        std::stringstream tooltip;
        tooltip << "O: " << data.GetData()[i].open() 
            << "\r\nH: " << data.GetData()[i].high()
            << "\r\nL: " << data.GetData()[i].low()
            << "\r\nC: " << data.GetData()[i].close();
        wxChartTooltipProvider::ptr tooltipProvider(
            new wxChartTooltipProviderStatic(data.GetLabels()[i], tooltip.str(), *wxWHITE)
            );

        OHLDCLines::ptr newOHLCLines(new OHLDCLines(
            data.GetData()[i], 
            data.GetLineWidth(), 
            data.GetLineColor(),
            data.GetOpenLineLength(),
            data.GetCloseLineLength(),
            tooltipProvider
            ));
        m_data.push_back(newOHLCLines);
    }
}

const wxOHLCChartOptions& wxOHLCChartCtrl::GetOptions() const
{
    return m_options;
}

wxDouble wxOHLCChartCtrl::GetMinValue(const wxOHLCChartData &data)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < data.GetData().size(); ++i)
    {
        if (!foundValue)
        {
            result = data.GetData()[i].low();
            foundValue = true;
        }
        else if (result > data.GetData()[i].low())
        {
            result = data.GetData()[i].low();
        }
    }

    return result;
}

wxDouble wxOHLCChartCtrl::GetMaxValue(const wxOHLCChartData &data)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < data.GetData().size(); ++i)
    {
        if (!foundValue)
        {
            result = data.GetData()[i].high();
            foundValue = true;
        }
        else if (result < data.GetData()[i].high())
        {
            result = data.GetData()[i].high();
        }
    }

    return result;
}

void wxOHLCChartCtrl::Resize(const wxSize &size)
{
    wxSize newSize(
        size.GetWidth() - m_options.GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options.GetPadding().GetTotalVerticalPadding()
        );
    m_grid.Resize(newSize);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxOHLCChartCtrl::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        if (m_data[i]->HitTest(point))
        {
            activeElements->push_back(m_data[i].get());
        }
    }
    return activeElements;
}

void wxOHLCChartCtrl::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);

    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        m_grid.Draw(*gc);

        for (size_t i = 0; i < m_data.size(); ++i)
        {
            m_data[i]->Update(m_grid.GetMapping(), i);
        }

        for (size_t i = 0; i < m_data.size(); ++i)
        {
            m_data[i]->Draw(*gc);
        }

        DrawTooltips(*gc);

        delete gc;
    }
}

BEGIN_EVENT_TABLE(wxOHLCChartCtrl, wxChartCtrl)
	EVT_PAINT(wxOHLCChartCtrl::OnPaint)
END_EVENT_TABLE()
