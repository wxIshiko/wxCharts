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

#include "wxchartlabelgroup.h"
#include "wxchartbackground.h"
#include "wxchartutilities.h"

wxChartLabelGroup::wxChartLabelGroup(const wxChartLabelGroupOptions &options)
    : m_options(options), m_maxWidth(0)
{
}

void wxChartLabelGroup::Draw(wxGraphicsContext &gc)
{
    if (m_options.HasBackground())
    {
        for (size_t i = 0; i < size(); ++i)
        {
            wxChartBackground background(m_options.GetBackgroundOptions());
            background.Draw((*this)[i].GetPosition(), (*this)[i].GetSize(), gc);
        }
    }

    wxFont font = m_options.GetFontOptions().GetFont();
    gc.SetFont(font, m_options.GetFontOptions().GetColor());
    for (size_t i = 0; i < size(); ++i)
    {
        (*this)[i].Draw(gc);
    }
}

void wxChartLabelGroup::UpdateSizes(wxGraphicsContext &gc)
{
    m_maxWidth = 0;

    wxFont font = m_options.GetFontOptions().GetFont();

    for (size_t i = 0; i < size(); ++i)
    {
        wxDouble labelWidth;
        wxDouble labelHeight;
        wxChartUtilities::GetTextSize(gc, font, (*this)[i].GetText(), labelWidth, labelHeight);

        (*this)[i].SetSize(labelWidth, labelHeight);
        if (labelWidth > m_maxWidth)
        {
            m_maxWidth = labelWidth;
        }
    }
}

wxDouble wxChartLabelGroup::GetMaxWidth() const
{
    return m_maxWidth;
}
