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

#include "wxchartarc.h"

wxChartArc::wxChartArc(double x,
					   double y, 
					   double startAngle,
					   double endAngle, 
					   double outerRadius,
					   double innerRadius,
					   unsigned int strokeWidth,
					   const wxColor &fillColor)
	: m_x(x), m_y(y), m_startAngle(startAngle), 
	m_endAngle(endAngle), m_outerRadius(outerRadius),
	m_innerRadius(innerRadius), m_strokeWidth(strokeWidth),
	m_fillColor(fillColor)
{
}

void wxChartArc::Draw(wxGraphicsContext &gc)
{
	wxGraphicsPath path = gc.CreatePath();

	if (m_innerRadius > 0)
	{
		path.AddArc(m_x, m_y, m_innerRadius, m_startAngle, m_endAngle, true);
		path.AddArc(m_x, m_y, m_outerRadius, m_endAngle, m_startAngle, false);
	}
	else
	{
		path.AddArc(m_x, m_y, m_outerRadius, m_endAngle, m_startAngle, false);
		path.AddLineToPoint(m_x, m_y);
	}

	path.CloseSubpath();

	wxBrush brush(m_fillColor);
	gc.SetBrush(brush);
	gc.FillPath(path);

	wxPen pen(*wxWHITE, m_strokeWidth);
	gc.SetPen(pen);
	gc.StrokePath(path);
}

void wxChartArc::SetCenter(double x, double y)
{
	m_x = x;
	m_y = y;
}

void wxChartArc::SetAngles(double startAngle, double endAngle)
{
	m_startAngle = startAngle;
	m_endAngle = endAngle;
}

void wxChartArc::SetRadiuses(double outerRadius, double innerRadius)
{
	m_outerRadius = outerRadius;
	m_innerRadius = innerRadius;
}

unsigned int wxChartArc::GetStrokeWidth() const
{
	return m_strokeWidth;
}

bool wxChartArc::HitTest(const wxPoint &point) const
{
	wxDouble distanceFromXCenter = point.x - m_x;
	wxDouble distanceFromYCenter = point.y - m_y;
	wxDouble radialDistanceFromCenter = sqrt((distanceFromXCenter * distanceFromXCenter) + (distanceFromYCenter * distanceFromYCenter));

	wxDouble angle = atan2(distanceFromYCenter, distanceFromXCenter);
	if (angle < 0)
	{
		angle += 2 * M_PI;
	}
	
	// Calculate wether the angle is between the start and the end angle
	bool betweenAngles = ((angle >= m_startAngle) && (angle <= m_endAngle));

	// Ensure within the outside of the arc centre, but inside arc outer
	bool withinRadius = ((radialDistanceFromCenter >= m_innerRadius) && (radialDistanceFromCenter <= m_outerRadius));

	return (betweenAngles && withinRadius);
}

wxPoint2DDouble wxChartArc::GetTooltipPosition() const
{
	double centreAngle = m_startAngle + (m_endAngle - m_startAngle) / 2;
	double rangeFromCentre = m_innerRadius + (m_outerRadius - m_innerRadius) / 2;
	double x = m_x + cos(centreAngle) * rangeFromCentre;
	double y = m_y + sin(centreAngle) * rangeFromCentre;
	return wxPoint2DDouble(x, y);
}
