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

#ifndef _WX_CHARTS_WXCHARTARC_H_
#define _WX_CHARTS_WXCHARTARC_H_

#include "wxchartelement.h"
#include <wx/graphics.h>

// This class is used to draw one of the segments of a circular chart
// e.g. a pie chart or a doughnut chart.
class wxChartArc : public wxChartElement
{
public:
	wxChartArc(double x, double y, double startAngle,
		double endAngle, double outerRadius, double innerRadius,
		unsigned int strokeWidth, const wxColor &fillColor);

	void Draw(wxGraphicsContext &gc);

	void SetCenter(double x, double y);
	void SetAngles(double startAngle, double endAngle);
	void SetRadiuses(double outerRadius, double innerRadius);

	unsigned int GetStrokeWidth() const;

	bool HitTest(const wxPoint &point) const;
	wxPoint2DDouble GetTooltipPosition() const;

private:
	double m_x;
	double m_y;
	double m_startAngle;
	double m_endAngle;
	double m_outerRadius;
	double m_innerRadius;
	unsigned int m_strokeWidth;
	wxColor m_fillColor;
};

#endif
