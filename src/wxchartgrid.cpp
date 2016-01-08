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

#include "wxchartgrid.h"

wxChartGrid::wxChartGrid(const std::vector<std::string> &labels,
						 unsigned int gridLineWidth, 
						 const wxColor &gridLineColor)
	: m_xLabels(labels), m_gridLineWidth(gridLineWidth),
	m_gridLineColor(gridLineColor)
{
}

void wxChartGrid::Draw(wxGraphicsContext &gc)
{
	for (size_t i = 0; i < m_yLabels.size(); ++i)
	{
		wxGraphicsPath path = gc.CreatePath();

		path.MoveToPoint(10, 10);
		path.AddLineToPoint(100, 10);
		path.CloseSubpath();

		wxPen pen(m_gridLineColor, m_gridLineWidth);
		gc.SetPen(pen);
		gc.StrokePath(path);
	}

	for (size_t i = 0; i < m_xLabels.size(); ++i)
	{
		wxGraphicsPath path = gc.CreatePath();

		double xPos = CalculateX(i);
		path.MoveToPoint(xPos, 10);
		path.AddLineToPoint(xPos, 100);
		path.CloseSubpath();

		wxPen pen(m_gridLineColor, m_gridLineWidth);
		gc.SetPen(pen);
		gc.StrokePath(path);
	}
}

double wxChartGrid::CalculateX(size_t index)
{
	double innerWidth = 100;
	double valueWidth = innerWidth / m_xLabels.size();
	double valueOffset = (valueWidth * index);

	return valueOffset;
}
