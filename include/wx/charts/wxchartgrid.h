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

#ifndef _WX_CHARTS_WXCHARTGRID_H_
#define _WX_CHARTS_WXCHARTGRID_H_

#include "wxchartelement.h"
#include "wxchartgridoptions.h"
#include "wxchartgridmapping.h"
#include "wxchartlabel.h"
#include <wx/graphics.h>

// This class represents the grid displayed in the background
// of some of the chart controls like for instance line and 
// bar charts.
class wxChartGrid : public wxChartElement
{
public:
	wxChartGrid(const wxSize &size,
		const wxVector<wxString> &labels,
		wxDouble minValue, wxDouble maxValue,
		const wxChartGridOptions& options);

	void Draw(wxGraphicsContext &gc);

	void Resize(const wxSize &size);

	const wxChartGridMapping& GetMapping() const;

private:
	void Fit(wxDouble minValue, size_t steps, 
		wxGraphicsContext &gc, const wxFont &font);
	void BuildYLabels(wxDouble minValue, size_t steps, 
		wxGraphicsContext &gc, const wxFont &font);
	void CalculateXLabelRotation(const wxVector<wxChartLabel> &xLabels, 
		wxDouble yLabelMaxWidth, wxGraphicsContext &gc, 
		const wxFont &font);
	wxDouble CalculateLabelPosition(size_t index);

private:
	wxChartGridOptions m_options;
	wxChartGridMapping m_mapping;
	wxVector<wxChartLabel> m_xLabels;
	wxVector<wxDouble> m_xLabelsWidths;
	wxVector<wxString> m_yLabels;
	wxVector<wxDouble> m_yLabelWidths;
	wxVector<wxDouble> m_yLabelHeights;
	wxDouble m_yLabelMaxWidth;
	wxDouble m_startYValue;
	// The number of steps on the Y-axis
	size_t m_steps;
	wxDouble m_stepValue;
	// Whether something has changed and we
	// need to rearrange the chart
	bool m_needsFit;
};

#endif
