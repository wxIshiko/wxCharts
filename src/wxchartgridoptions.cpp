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

#include "wxchartgridoptions.h"

wxChartGridLineOptions::wxChartGridLineOptions()
    : m_showGridLines(true),
    m_majorGridLineWidth(1), m_majorGridLineColor(0, 0, 0, 0x0C),
    m_numberOfMinorGridLinesBetweenTickMarks(0)
{
}

bool wxChartGridLineOptions::ShowGridLines() const
{
    return m_showGridLines;
}

void wxChartGridLineOptions::SetShowGridLines(bool show)
{
    m_showGridLines = show;
}

unsigned int wxChartGridLineOptions::GetMajorGridLineWidth() const
{
    return m_majorGridLineWidth;
}

void wxChartGridLineOptions::SetMajorGridLineWidth(unsigned int width)
{
    m_majorGridLineWidth = width;
}

const wxColor& wxChartGridLineOptions::GetMajorGridLineColor() const
{
    return m_majorGridLineColor;
}

void wxChartGridLineOptions::SetMajorGridLineColor(const wxColor &color)
{
    m_majorGridLineColor = color;
}

unsigned int wxChartGridLineOptions::GetNumberOfMinorGridLinesBetweenTickMarks() const
{
    return m_numberOfMinorGridLinesBetweenTickMarks;
}

void wxChartGridLineOptions::SetNumberOfMinorGridLinesBetweenTickMarks(unsigned int n)
{
    m_numberOfMinorGridLinesBetweenTickMarks = n;
}

wxChartGridOptions::wxChartGridOptions()
	: m_XAxisOptions(wxCHARTAXISPOSITION_BOTTOM), m_YAxisOptions(wxCHARTAXISPOSITION_LEFT)
{
}

wxChartGridOptions::wxChartGridOptions(const wxChartAxisOptions &xAxisOptions,
									   const wxChartAxisOptions &yAxisOptions)
	: m_XAxisOptions(xAxisOptions), m_YAxisOptions(yAxisOptions)
{
}

const wxChartAxisOptions& wxChartGridOptions::GetXAxisOptions() const
{
	return m_XAxisOptions;
}

wxChartAxisOptions& wxChartGridOptions::GetXAxisOptions()
{
	return m_XAxisOptions;
}

const wxChartAxisOptions& wxChartGridOptions::GetYAxisOptions() const
{
	return m_YAxisOptions;
}

wxChartAxisOptions& wxChartGridOptions::GetYAxisOptions()
{
	return m_YAxisOptions;
}

const wxChartGridLineOptions& wxChartGridOptions::GetHorizontalGridLineOptions() const
{
    return m_horizontalGridLineOptions;
}

wxChartGridLineOptions& wxChartGridOptions::GetHorizontalGridLineOptions()
{
    return m_horizontalGridLineOptions;
}

const wxChartGridLineOptions& wxChartGridOptions::GetVerticalGridLineOptions() const
{
    return m_verticalGridLinesOptions;
}

wxChartGridLineOptions& wxChartGridOptions::GetVerticalGridLineOptions()
{
    return m_verticalGridLinesOptions;
}
