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

/*
	Part of this file were copied from the Chart.js project (http://chartjs.org/)
	and translated into C++.

	The files of the Chart.js project have the following copyright and license.

	Copyright (c) 2013-2016 Nick Downie
	Released under the MIT license
	https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

#include "wxchartgridmapping.h"

wxChartGridMapping::wxChartGridMapping(const wxSize &size,
									   unsigned int numberOfVerticalLines)
	: m_size(size), 
	m_leftPadding(0), m_rightPadding(0),
	m_minValue(0), m_maxValue(0),
	m_startPoint(0, 0), m_endPoint(0, 0),
	m_numberOfVerticalLines(numberOfVerticalLines)
{
}

void wxChartGridMapping::Fit(wxDouble leftPadding, 
							 wxDouble rightPadding,
							 wxPoint2DDouble startPoint,
							 wxPoint2DDouble endPoint)
{
	m_leftPadding = leftPadding;
	m_rightPadding = rightPadding;
	m_startPoint = startPoint;
	m_endPoint = endPoint;
}

void wxChartGridMapping::SetPadding(wxDouble leftPadding,
									wxDouble rightPadding)
{
	m_leftPadding = leftPadding;
	m_rightPadding = rightPadding;
}

const wxSize& wxChartGridMapping::GetSize() const
{
	return m_size;
}

void wxChartGridMapping::SetSize(const wxSize &size)
{
	m_size = size;
}

wxDouble wxChartGridMapping::GetLeftPadding() const
{
	return m_leftPadding;
}

wxDouble wxChartGridMapping::GetRightPadding() const
{
	return m_rightPadding;
}

wxDouble wxChartGridMapping::GetMinValue() const
{
	return m_minValue;
}

void wxChartGridMapping::SetMinValue(wxDouble minValue)
{
	m_minValue = minValue;
}

wxDouble wxChartGridMapping::GetMaxValue() const
{
	return m_maxValue;
}

void wxChartGridMapping::SetMaxValue(wxDouble maxValue)
{
	m_maxValue = maxValue;
}

wxPoint2DDouble wxChartGridMapping::GetStartPoint() const
{
	return m_startPoint;
}

wxPoint2DDouble wxChartGridMapping::GetEndPoint() const
{
	return m_endPoint;
}

wxPoint2DDouble wxChartGridMapping::GetWindowPosition(size_t index,
													  wxDouble value) const
{
	wxDouble innerWidth = m_size.GetWidth() - m_leftPadding - m_rightPadding;
	wxDouble valueWidth = innerWidth / m_numberOfVerticalLines;
	wxDouble x = m_leftPadding + (valueWidth * index);

	wxDouble scalingFactor = ((m_startPoint.m_y - m_endPoint.m_y) / (m_maxValue - m_minValue));
	wxDouble y  = m_startPoint.m_y - (scalingFactor * (value - m_minValue));

	return wxPoint2DDouble(x, y);
}

wxPoint2DDouble wxChartGridMapping::GetWindowPositionOfPointOnXAxis(size_t index) const
{
	wxDouble innerWidth = m_size.GetWidth() - m_leftPadding - m_rightPadding;
	wxDouble valueWidth = innerWidth / m_numberOfVerticalLines;
	wxDouble x = m_leftPadding + (valueWidth * index);

	wxDouble scalingFactor = ((m_startPoint.m_y - m_endPoint.m_y) / (m_maxValue - m_minValue));

	return wxPoint2DDouble(x, m_startPoint.m_y);
}
