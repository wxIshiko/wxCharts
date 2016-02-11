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

/// @file

#ifndef _WX_CHARTS_WXCHARTGRIDOPTIONS_H_
#define _WX_CHARTS_WXCHARTGRIDOPTIONS_H_

#include "wxchartaxisoptions.h"
#include <wx/colour.h>

/// The options for the wxChartGrid element.
class wxChartGridOptions
{
public:
	/// Constructs a wxChartGridOptions instance with
	/// default options for the X and Y axes.
	wxChartGridOptions();
	/// Constructs a wxChartGridOptions instance with
	/// the options for the X and Y axes passed in as
	/// arguments.
	/// @param xAxisOptions The options for the X axis.
	/// @param yAxisOptions The options for the Y axis.
	wxChartGridOptions(const wxChartAxisOptions &xAxisOptions,
		const wxChartAxisOptions &yAxisOptions);

	/// Gets the options for the X axis.
	/// @return The options for the X axis.
	const wxChartAxisOptions& GetXAxisOptions() const;
	/// Gets the options for the X axis.
	/// @return The options for the X axis.
	wxChartAxisOptions& GetXAxisOptions();
	/// Gets the options for the Y axis.
	/// @return The options for the Y axis.
	const wxChartAxisOptions& GetYAxisOptions() const;
	wxChartAxisOptions& GetYAxisOptions();

	/// Whether to show horizontal grid lines. This doesn't affect
	/// the visibility of the X axis.
	/// @retval true Show horizontal grid lines.
	/// @retval false Don't show horizontal grid lines.
	bool ShowHorizontalLines() const;
	/// Whether to show vertical grid lines. This doesn't affect
	/// the visibility of the Y axis.
	/// @retval true Show vertical grid lines.
	/// @retval false Don't show vertical grid lines.
	bool ShowVerticalLines() const;
	/// Gets the width of the grid lines. This doesn't affect
	/// the width of the axes.
	/// @return The width of the grid lines.
	unsigned int GetGridLineWidth() const;
	/// Gets the color of the grid lines. This doesn't affect
	/// the color of the axes.
	/// @return The color of the grid lines.
	const wxColor& GetGridLineColor() const;

private:
	wxChartAxisOptions m_XAxisOptions;
	wxChartAxisOptions m_YAxisOptions;
	// Whether to show horizontal lines (the X-axis is always shown)
	bool m_showHorizontalLines;
	// Whether to show vertical lines (the Y-axis is always shown)
	bool m_showVerticalLines;
	unsigned int m_gridLineWidth;
	wxColor m_gridLineColor;
};

#endif
