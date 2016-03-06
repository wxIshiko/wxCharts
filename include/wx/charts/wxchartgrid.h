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

/// @file

#ifndef _WX_CHARTS_WXCHARTGRID_H_
#define _WX_CHARTS_WXCHARTGRID_H_

#include "wxchartelement.h"
#include "wxchartgridoptions.h"
#include "wxchartgridmapping.h"
#include "wxchartaxis.h"
#include <wx/graphics.h>

/// This class is used to display a grid.

/// It represents the grid displayed in the background
/// of some of the chart controls like for instance line and 
/// bar charts.
class wxChartGrid : public wxChartElement
{
public:
	/// Constructs a wxChartGrid element.
	/// @param position The position of the top left corner
	/// of the chart.
	/// @param size The size of the area where the grid 
	/// will be displayed.
	/// @param labels The labels of the X axis.
	/// @param minValue The minimum of the values that
	/// will be shown on the chart.
	/// @param maxValue The maximum of the values that
	/// will be shown on the chart.
	/// @param options The settings to be used for the
	/// grid.
	wxChartGrid(const wxPoint2DDouble &position, const wxSize &size,
		const wxVector<wxString> &labels,
		wxDouble minValue, wxDouble maxValue,
		const wxChartGridOptions& options);
	wxChartGrid(const wxPoint2DDouble &position, const wxSize &size,
		wxDouble minXValue, wxDouble maxXValue,
		wxDouble minYValue, wxDouble maxYValue,
		const wxChartGridOptions& options);

	virtual bool HitTest(const wxPoint &point) const;

	virtual wxPoint2DDouble GetTooltipPosition() const;

	/// Draws the grid.
	/// @param gc The graphics context.
	void Draw(wxGraphicsContext &gc);

	/// Resizes the grid.
	/// @param size The new size of the area where the grid 
	/// is displayed.
	void Resize(const wxSize &size);

	/// Gets the mapping that allows external code
	/// to correctly position points on the grid.
	/// @return The grid mapping.
	const wxChartGridMapping& GetMapping() const;

private:
    static wxChartAxis::ptr CreateNumericalAxis(wxDouble minValue, wxDouble maxValue, 
        const wxChartAxisOptions &options);
	void Fit(wxGraphicsContext &gc);
	void CalculatePadding(const wxChartAxis &xAxis,
		const wxChartAxis &yAxis, wxDouble &left, wxDouble &right);

private:
	wxChartGridOptions m_options;
	wxPoint2DDouble m_position;
	wxChartAxis::ptr m_XAxis;
	wxChartAxis::ptr m_YAxis;
	wxChartGridMapping m_mapping;
	// Whether something has changed and we
	// need to rearrange the chart
	bool m_needsFit;
};

#endif
