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

#ifndef _WX_CHARTS_WXCHARTAXIS_H_
#define _WX_CHARTS_WXCHARTAXIS_H_

#include "wxchartelement.h"
#include "wxchartaxisoptions.h"
#include "wxchartlabel.h"

/// This class represents an axis.
class wxChartAxis : public wxChartElement
{
public:
	/// Construcs a wxChartAxis
	/// element.
	wxChartAxis();
	/// Constructs a wxChartAxis element.
	/// @param labels The labels to display along the axis.
	wxChartAxis(const wxVector<wxString> &labels);

	virtual bool HitTest(const wxPoint &point) const;

	/// Draws the axis.
	/// @param gc The graphics context.
	void Draw(wxGraphicsContext &gc);

	void UpdateLabelSizes(wxGraphicsContext &gc);
	void Fit(wxDouble leftPadding, wxDouble length);
	void BuildYLabels(wxDouble minValue, size_t steps,
		wxDouble stepValue);
	void UpdateLabelPositions(wxDouble startPoint, 
		wxDouble endPoint);
	void UpdateLabelPosition(size_t index, wxDouble x,
		wxDouble y);

	const wxVector<wxChartLabel>& GetLabels();
	wxDouble GetLabelMaxWidth() const;

	wxDouble CalculateLabelPosition(size_t index);

private:
	wxChartAxisOptions m_options;
	wxDouble m_leftPadding;
	wxDouble m_length;
	wxVector<wxChartLabel> m_labels;
	wxDouble m_labelMaxWidth;
};

#endif
