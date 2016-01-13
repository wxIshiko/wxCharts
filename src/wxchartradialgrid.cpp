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

#include "wxchartradialgrid.h"
#include "wxchartutilities.h"

wxChartRadialGrid::wxChartRadialGrid(const wxSize &size,
									 const wxChartRadialGridOptions& options)
	: m_options(options), m_size(size), m_center(CalculateCenter(size))
{
	wxVector<wxDouble> dummy;
	wxDouble valueRange = 0;
	wxChartUtilities::CalculateGridRange(dummy, valueRange, m_steps);
	BuildYLabels(m_steps);
}

void wxChartRadialGrid::Draw(wxGraphicsContext &gc)
{
	// Don't draw a centre value so start from 1
	for (size_t i = 1; i < m_yLabels.size(); ++i)
	{
		wxDouble yCenterOffset = i * 50;

		wxGraphicsPath path = gc.CreatePath();
		path.AddArc(m_center.m_x, m_center.m_y, 25, 0, 2 * M_PI, true);
		path.CloseSubpath();

		wxPen pen(m_options.GetLineColor(), m_options.GetLineWidth());
		gc.SetPen(pen);
		gc.StrokePath(path);
	}
}

void wxChartRadialGrid::Resize(const wxSize &size)
{
	m_size = size;
	m_center = CalculateCenter(size);
}

wxPoint2DDouble wxChartRadialGrid::CalculateCenter(const wxSize& size)
{
	return wxPoint2DDouble(size.GetWidth() / 2, size.GetHeight() / 2);
}

void wxChartRadialGrid::BuildYLabels(size_t steps)
{
	m_yLabels.clear();

	for (size_t i = 0; i <= steps; ++i)
	{
		m_yLabels.push_back("10");
	}
}
