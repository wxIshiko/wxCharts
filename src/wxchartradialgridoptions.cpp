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

#include "wxchartradialgridoptions.h"

wxChartRadialGridOptions::wxChartRadialGridOptions(wxChartRadialGridStyle style)
	: m_style(style), m_lineWidth(1), m_lineColor(0, 0, 0, 0x19),
	m_showLabels(true), 
    m_fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666)
{
}

wxChartRadialGridStyle wxChartRadialGridOptions::GetStyle() const
{
	return m_style;
}

unsigned int wxChartRadialGridOptions::GetLineWidth() const
{
	return m_lineWidth;
}

const wxColor& wxChartRadialGridOptions::GetLineColor() const
{
	return m_lineColor;
}

bool wxChartRadialGridOptions::ShowLabels() const
{
	return m_showLabels;
}

const wxChartFontOptions& wxChartRadialGridOptions::GetFontOptions() const
{
    return m_fontOptions;
}
