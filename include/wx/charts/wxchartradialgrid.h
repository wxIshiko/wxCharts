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

#ifndef _WX_CHARTS_WXCHARTRADIALGRID_H_
#define _WX_CHARTS_WXCHARTRADIALGRID_H_

#include "wxchartelement.h"
#include "wxchartradialgridoptions.h"
#include <wx/graphics.h>

// This class represents the radial grid displayed in the
// background of some of the chart controls like for instance 
// the polar area chart.
class wxChartRadialGrid : public wxChartElement
{
public:
	wxChartRadialGrid(const wxSize &size,
		const wxChartRadialGridOptions& options);

	void Draw(wxGraphicsContext &gc);

	void Resize(const wxSize &size);

private:
	static wxPoint2DDouble CalculateCenter(const wxSize& size);
	void BuildYLabels(size_t steps);

private:
	wxChartRadialGridOptions m_options;
	wxSize m_size;
	wxPoint2DDouble m_center;
	wxVector<wxString> m_yLabels;
	size_t m_steps;
};

#endif
