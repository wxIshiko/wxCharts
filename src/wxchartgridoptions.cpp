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

wxChartGridOptions::wxChartGridOptions()
	: m_XAxisOptions(wxCHARTAXISPOSITION_BOTTOM), m_YAxisOptions(wxCHARTAXISPOSITION_LEFT),
	m_showHorizontalGridLines(true), m_numberOfHorizontalMinorGridLinesBetweenTickMarks(0),
    m_showVerticalGridLines(true), m_numberOfVerticalMinorGridLinesBetweenTickMarks(0),
    m_gridLineWidth(1), m_gridLineColor(0, 0, 0, 0x0C)
{
}

wxChartGridOptions::wxChartGridOptions(const wxChartAxisOptions &xAxisOptions,
									   const wxChartAxisOptions &yAxisOptions)
	: m_XAxisOptions(xAxisOptions), m_YAxisOptions(yAxisOptions),
	m_showHorizontalGridLines(true), m_numberOfHorizontalMinorGridLinesBetweenTickMarks(0),
    m_showVerticalGridLines(true), m_numberOfVerticalMinorGridLinesBetweenTickMarks(0),
    m_gridLineWidth(1), m_gridLineColor(0, 0, 0, 0x0C)
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

bool wxChartGridOptions::ShowHorizontalGridLines() const
{
	return m_showHorizontalGridLines;
}

unsigned int wxChartGridOptions::GetNumberOfHorizontalMinorGridLinesBetweenTickMarks() const
{
    return m_numberOfHorizontalMinorGridLinesBetweenTickMarks;
}

void wxChartGridOptions::SetNumberOfHorizontalMinorGridLinesBetweenTickMarks(unsigned int n)
{
    m_numberOfHorizontalMinorGridLinesBetweenTickMarks = n;
}

bool wxChartGridOptions::ShowVerticalGridLines() const
{
	return m_showVerticalGridLines;
}

unsigned int wxChartGridOptions::GetNumberOfVerticalMinorGridLinesBetweenTickMarks() const
{
    return m_numberOfVerticalMinorGridLinesBetweenTickMarks;
}

void wxChartGridOptions::SetNumberOfVerticalMinorGridLinesBetweenTickMarks(unsigned int n)
{
    m_numberOfVerticalMinorGridLinesBetweenTickMarks = n;
}

unsigned int wxChartGridOptions::GetGridLineWidth() const
{
	return m_gridLineWidth;
}

void wxChartGridOptions::SetGridLineWidth(unsigned int width)
{
    m_gridLineWidth = width;
}

const wxColor& wxChartGridOptions::GetGridLineColor() const
{
	return m_gridLineColor;
}

void wxChartGridOptions::SetGridLineColor(const wxColor &color)
{
    m_gridLineColor = color;
}
