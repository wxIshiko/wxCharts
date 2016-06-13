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

wxChartAxisOptions::wxChartAxisOptions(wxChartAxisPosition position)
	: m_position(position), m_labelType(wxCHARTAXISLABELTYPE_POINT),
    m_startMarginType(wxCHARTAXISMARGINTYPE_NONE), m_endMarginType(wxCHARTAXISMARGINTYPE_NONE),
	m_startValueMode(wxCHARTAXISVALUEMODE_AUTO), m_startValue(0),
	m_endValueMode(wxCHARTAXISVALUEMODE_AUTO), m_endValue(0),
	m_lineWidth(1), m_lineColor(0, 0, 0, 0x19), m_overhang(3),
	m_fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666)
{
}

wxChartAxisOptions::wxChartAxisOptions(wxChartAxisPosition position,
									   wxChartAxisLabelType labelType)
	: m_position(position), m_labelType(labelType),
    m_startMarginType(wxCHARTAXISMARGINTYPE_NONE), m_endMarginType(wxCHARTAXISMARGINTYPE_NONE),
	m_startValueMode(wxCHARTAXISVALUEMODE_AUTO), m_startValue(0),
	m_endValueMode(wxCHARTAXISVALUEMODE_AUTO), m_endValue(0),
	m_lineWidth(1), m_lineColor(0, 0, 0, 0x19), m_overhang(3),
	m_fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666)
{
}

wxChartAxisPosition wxChartAxisOptions::GetPosition() const
{
	return m_position;
}

wxChartAxisLabelType wxChartAxisOptions::GetLabelType() const
{
	return m_labelType;
}

wxChartAxisMarginType wxChartAxisOptions::GetStartMarginType() const
{
    return m_startMarginType;
}

void wxChartAxisOptions::SetStartMarginType(wxChartAxisMarginType type)
{
    m_startMarginType = type;
}

wxChartAxisMarginType wxChartAxisOptions::GetEndMarginType() const
{
    return m_endMarginType;
}

void wxChartAxisOptions::SetEndMarginType(wxChartAxisMarginType type)
{
    m_endMarginType = type;
}

wxChartAxisValueMode wxChartAxisOptions::GetStartValueMode() const
{
	return m_startValueMode;
}

wxDouble wxChartAxisOptions::GetStartValue() const
{
	return m_startValue;
}

void wxChartAxisOptions::SetExplicitStartValue(wxDouble startValue)
{
	m_startValueMode = wxCHARTAXISVALUEMODE_EXPLICIT;
	m_startValue = startValue;
}

wxChartAxisValueMode wxChartAxisOptions::GetEndValueMode() const
{
	return m_endValueMode;
}

wxDouble wxChartAxisOptions::GetEndValue() const
{
	return m_endValue;
}

void wxChartAxisOptions::SetExplicitEndValue(wxDouble endValue)
{
	m_endValueMode = wxCHARTAXISVALUEMODE_EXPLICIT;
	m_endValue = endValue;
}

unsigned int wxChartAxisOptions::GetLineWidth() const
{
	return m_lineWidth;
}

const wxColor& wxChartAxisOptions::GetLineColor() const
{
	return m_lineColor;
}

wxDouble wxChartAxisOptions::GetOverhang() const
{
	return m_overhang;
}

const wxChartFontOptions& wxChartAxisOptions::GetFontOptions() const
{
	return m_fontOptions;
}
