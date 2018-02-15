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

#include "wxchartlabel.h"
#include "wxchartbackground.h"
#include "wxchartutilities.h"

wxChartLabel::wxChartLabel(const wxString &text,
                           const wxChartLabelOptions &options)
    : m_options(options), m_text(text), m_position(0, 0),
    m_size(0, 0)
{
}

wxChartLabel::wxChartLabel(const wxString &text,
                           wxDouble width,
                           wxDouble height,
                           const wxChartLabelOptions &options)
    : m_options(options), m_text(text), m_position(0, 0),
    m_size(width, height)
{
}

void wxChartLabel::Draw(wxGraphicsContext &gc) const
{
    if (m_options.HasBackground())
    {
        wxSize backgroundSize(m_size);
        backgroundSize.x += (m_padding.GetLeft() + m_padding.GetRight());
        backgroundSize.y += (m_padding.GetTop() + m_padding.GetBottom());

        wxChartBackground background(m_options.GetBackgroundOptions());
        background.Draw(m_position, backgroundSize, gc);
    }

    wxFont font = m_options.GetFontOptions().GetFont();
    gc.SetFont(font, m_options.GetFontOptions().GetColor());
    gc.DrawText(m_text, m_position.m_x, m_position.m_y);
}

bool wxChartLabel::HitTest(const wxPoint &point) const
{
    return false;
}

wxPoint2DDouble wxChartLabel::GetTooltipPosition() const
{
    return wxPoint2DDouble(0, 0);
}

const wxString& wxChartLabel::GetText() const
{
    return m_text;
}

const wxPoint2DDouble& wxChartLabel::GetPosition() const
{
    return m_position;
}

void wxChartLabel::SetPosition(const wxPoint2DDouble &position)
{
    m_position = position;
}

void wxChartLabel::SetPosition(wxDouble x,
                               wxDouble y)
{
    m_position.m_x = x;
    m_position.m_y = y;
}

const wxSize& wxChartLabel::GetSize() const
{
    return m_size;
}

void wxChartLabel::SetSize(const wxSize &size)
{
    m_size = size;
}

void wxChartLabel::SetSize(wxDouble width, wxDouble height)
{
    m_size.x = width;
    m_size.y = height;
}

void wxChartLabel::UpdateSize(wxGraphicsContext &gc)
{
    wxFont font = m_options.GetFontOptions().GetFont();
    wxDouble width = 0;
    wxDouble height = 0;
    wxChartUtilities::GetTextSize(gc, font, m_text, width, height);
    m_size.x = width;
    m_size.y = height;
}

const wxChartPadding& wxChartLabel::GetPadding() const
{
    return m_padding;
}

void wxChartLabel::SetPadding(const wxChartPadding &padding)
{
    m_padding = padding;
}
