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

#include "wxchartgridoptions.h"
#include <wx/graphics.h>

// This class represents the grid displayed in the background
// of some of the chart controls like for instance line and 
// bar charts.
class wxChartGrid
{
public:
	wxChartGrid(const wxSize &size,
		const wxVector<wxString> &labels,
		const wxChartGridOptions& options);

	void Draw(wxGraphicsContext &gc);

	void Resize(const wxSize &size);

private:
	void Fit(size_t steps, wxGraphicsContext &gc,
		const wxFont &font);
	void BuildYLabels(size_t steps, wxGraphicsContext &gc,
		const wxFont &font);
	void CalculateXLabelRotation(wxDouble yLabelMaxWidth);
	wxDouble CalculateX(size_t index);
	wxDouble CalculateGridRange(const wxVector<wxDouble> &values);

private:
	wxChartGridOptions m_options;
	wxSize m_size;
	wxDouble m_startPoint;
	wxDouble m_endPoint;
	wxVector<wxString> m_xLabels;
	wxVector<wxString> m_yLabels;
	wxVector<wxDouble> m_yLabelWidths;
	wxVector<wxDouble> m_yLabelHeights;
	wxDouble m_yLabelMaxWidth;
	// The number of steps on the Y-axis
	size_t m_steps;
	wxDouble m_xPaddingLeft;
	// Whether something has changed and we
	// need to rearrange the chart
	bool m_needsFit;
};

#endif
