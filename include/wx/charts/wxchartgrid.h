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

#ifndef _WX_CHARTS_WXCHARTGRID_H_
#define _WX_CHARTS_WXCHARTGRID_H_

#include <wx/graphics.h>
#include <vector>

// Class holding the options for the wxChartGrid
// element
class wxChartGridOptions
{
};

// This class represents the grid displayed in the background
// of some of the chart controls like for instance line and 
// bar charts.
class wxChartGrid
{
public:
	wxChartGrid(const std::vector<std::string> &labels, 
		unsigned int gridLineWidth, const wxColor &gridLineColor);

	void Draw(wxGraphicsContext &gc);

private:
	double CalculateX(size_t index);

private:
	std::vector<std::string> m_xLabels;
	std::vector<std::string> m_yLabels;
	unsigned int m_gridLineWidth;
	wxColor m_gridLineColor;
};

#endif
