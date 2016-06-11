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

wxOHLCChartData::wxOHLCChartData(const wxVector<wxString> &labels, 
                                 const wxVector<wxChartOHLCData> &data)
    : m_labels(labels), m_lineWidth(5), m_lineColor(131, 167, 185), m_data(data)
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

const wxVector<wxChartOHLCData>& wxOHLCChartData::GetData() const
{
    return m_data;
}

wxOHLCChartCtrl::OHLDCLines::OHLDCLines(const wxChartOHLCData &data, 
                                        unsigned int lineWidth,
                                        const wxColor& lineColor)
    : m_data(data), m_bottom(0, 0), m_top(0, 0), 
    m_lineWidth(lineWidth), m_lineColor(lineColor)
{
}

bool wxOHLCChartCtrl::OHLDCLines::HitTest(const wxPoint &point) const
{
    return false;
}

wxPoint2DDouble wxOHLCChartCtrl::OHLDCLines::GetTooltipPosition() const
{
    return wxPoint2DDouble(0, 0);
}

void wxOHLCChartCtrl::OHLDCLines::Draw(wxGraphicsContext &gc)
{
    wxGraphicsPath path = gc.CreatePath();
    path.MoveToPoint(m_top);
    path.AddLineToPoint(m_bottom);
    path.CloseSubpath();

    wxPen pen(m_lineColor, m_lineWidth);
    gc.SetPen(pen);
    gc.StrokePath(path);
}

void wxOHLCChartCtrl::OHLDCLines::Update(const wxChartGridMapping& mapping,
                                         size_t index)
{
    m_bottom = mapping.GetWindowPositionAtTickMark(index, m_data.low());
    m_top = mapping.GetWindowPositionAtTickMark(index, m_data.high());
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
        OHLDCLines::ptr newOHLCLines(new OHLDCLines(data.GetData()[i], data.GetLineWidth(), data.GetLineColor()));
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
