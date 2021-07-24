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

#include "wxchartcommonoptions.h"

wxChartCommonOptions::wxChartCommonOptions()
    : m_titleOptions(wxChartFontOptions(wxFONTFAMILY_SWISS, 12,
        wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666), false,
        wxChartBackgroundOptions(*wxWHITE, 0)),
    m_responsive(true), m_showTooltips(true)
{
}

const wxChartsLabelOptions& wxChartCommonOptions::GetTitleOptions() const
{
    return m_titleOptions;
}

bool wxChartCommonOptions::IsResponsive() const
{
    return m_responsive;
}

bool wxChartCommonOptions::ShowTooltips() const
{
    return m_showTooltips;
}

void wxChartCommonOptions::SetShowTooltips(bool show)
{
    m_showTooltips = show;
}

const wxChartMultiTooltipOptions& wxChartCommonOptions::GetMultiTooltipOptions() const
{
    return m_multiTooltipOptions;
}

wxChartMultiTooltipOptions& wxChartCommonOptions::GetMultiTooltipOptions()
{
    return m_multiTooltipOptions;
}
