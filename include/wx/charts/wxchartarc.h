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

#ifndef _WX_CHARTS_WXCHARTARC_H_
#define _WX_CHARTS_WXCHARTARC_H_

#include "wxchartelement.h"
#include <wx/graphics.h>

/// This class is used to draw one of the segments of a circular chart e.g. a pie chart or a doughnut chart.
class wxChartArc : public wxChartElement
{
public:
	/// Constructs a wxChartArc element. The arc is defined by the 
	/// coordinates of its centre (x, y), its inner radius and its 
	/// outer radius. The arc goes from the starting angle startAngle
	/// to endAngle clockwise. The angles are measured in radians but,
	/// contrary to the usual mathematical convention, are always 
	/// clockwise from the horizontal axis.
	/// @param x The x coordinate of the center of the arc.
	/// @param y The y coordinate of the center of the arc.
	/// @param startAngle The angle (in radians) at which the arc starts.
	/// @param endAngle The angle (in radians) at which the arc ends.
	/// @param outerRadius The outer radius of the arc.
	/// @param innerRadius The inner radius of the arc. This can be 0.
	/// @param strokeWidth The width of the pen used to draw the contour
	/// of the arc.
	/// @param fillColor The color of the brush used to fill the arc.
	wxChartArc(wxDouble x, wxDouble y, wxDouble startAngle,
		wxDouble endAngle, wxDouble outerRadius, wxDouble innerRadius,
		unsigned int strokeWidth, const wxColor &fillColor);

	virtual bool HitTest(const wxPoint &point) const;

	void Draw(wxGraphicsContext &gc);

	void SetCenter(wxDouble x, wxDouble y);
	void SetAngles(wxDouble startAngle, wxDouble endAngle);
	void SetRadiuses(wxDouble outerRadius, wxDouble innerRadius);

	unsigned int GetStrokeWidth() const;

	wxPoint2DDouble GetTooltipPosition() const;

private:
	wxDouble m_x;
	wxDouble m_y;
	wxDouble m_startAngle;
	wxDouble m_endAngle;
	wxDouble m_outerRadius;
	wxDouble m_innerRadius;
	unsigned int m_strokeWidth;
	wxColor m_fillColor;
};

#endif
