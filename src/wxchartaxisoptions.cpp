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

#include "wxchartaxisoptions.h"

wxChartAxisOptions::wxChartAxisOptions()
	: m_labelType(wxCHARTLABELTYPE_POINT),
	m_lineWidth(1), m_lineColor(0, 0, 0, 0x19),
	m_fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666)
{
}

wxChartAxisOptions::wxChartAxisOptions(wxChartLabelType labelType)
	: m_labelType(labelType),
	m_lineWidth(1), m_lineColor(0, 0, 0, 0x19),
	m_fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666)
{
}

wxChartLabelType wxChartAxisOptions::GetLabelType() const
{
	return m_labelType;
}

unsigned int wxChartAxisOptions::GetLineWidth() const
{
	return m_lineWidth;
}

const wxColor& wxChartAxisOptions::GetLineColor() const
{
	return m_lineColor;
}

const wxChartFontOptions& wxChartAxisOptions::GetFontOptions() const
{
	return m_fontOptions;
}
