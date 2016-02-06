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

#include "wxchartlegendline.h"

wxChartLegendLine::wxChartLegendLine(const wxString &text, 
									 const wxChartLegendLineOptions& options)
	: m_options(options), m_position(0, 0), m_text(text)
{
}

bool wxChartLegendLine::HitTest(const wxPoint &point) const
{
	return false;
}

wxPoint2DDouble wxChartLegendLine::GetTooltipPosition() const
{
	return wxPoint2DDouble(0, 0);
}

void wxChartLegendLine::Draw(wxGraphicsContext &gc)
{
}

const wxPoint2DDouble& wxChartLegendLine::GetPosition() const
{
	return m_position;
}

void wxChartLegendLine::SetPosition(wxDouble x, wxDouble y)
{
	m_position.m_x = x;
	m_position.m_y = y;
}
