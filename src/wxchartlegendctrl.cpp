/*
    Copyright (c) 2016-2018 Xavier Leclercq and the wxCharts contributors.

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

#include "wxchartlegendctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxChartLegendCtrl::wxChartLegendCtrl(wxWindow *parent,
                                     wxWindowID id,
                                     const wxChartLegendData &data,
                                     const wxPoint &pos,
                                     const wxSize &size,
                                     long style)
    : wxControl(parent, id, pos, size, style)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(*wxWHITE);

    const wxVector<wxChartLegendItem>& items = data.GetItems();
    for (size_t i = 0; i < items.size(); ++i)
    {
        m_lines.push_back(
            wxChartLegendLine(items[i].GetColor(), items[i].GetLabel(),
                m_options.GetLegendLineOptions())
            );
    }
}

wxChartLegendCtrl::wxChartLegendCtrl(wxWindow *parent,
                                     wxWindowID id,
                                     wxChartObservableValue<std::map<wxString, wxChartSliceData>> &data,
                                     const wxPoint &pos,
                                     const wxSize &size,
                                     long style)
    : wxControl(parent, id, pos, size, style)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(*wxWHITE);
    OnUpdate(data.GetValue());
    data.AddObserver(this);
}

void wxChartLegendCtrl::OnUpdate(const std::map<wxString,wxChartSliceData> &data)
{
    m_lines.clear();
    auto options = m_options.GetLegendLineOptions();
    for(const auto &item : data)
    {
        auto label = item.first;
        auto color = item.second.GetColor();
        m_lines.push_back(wxChartLegendLine(color,label,options));
    }
    Update();
    Refresh();
}

void wxChartLegendCtrl::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);

    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        // Update the size of each line to reflect
        // the currently selected options and the
        // contents of each line.
        for (size_t i = 0; i < m_lines.size(); ++i)
        {
            m_lines[i].UpdateSize(*gc);
        }

        // Set the position of each line based on
        // the size of the lines that precede it.
        wxDouble y = 1;
        for (size_t i = 0; i < m_lines.size(); ++i)
        {
            m_lines[i].SetPosition(0, y);
            y += (m_lines[i].GetSize().GetHeight() + 5);
        }

        // Draw the lines
        for (size_t i = 0; i < m_lines.size(); ++i)
        {
            m_lines[i].Draw(*gc);
        }

        delete gc;
    }
}

BEGIN_EVENT_TABLE(wxChartLegendCtrl, wxControl)
    EVT_PAINT(wxChartLegendCtrl::OnPaint)
END_EVENT_TABLE()
