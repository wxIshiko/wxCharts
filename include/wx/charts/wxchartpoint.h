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

#ifndef _WX_CHARTS_WXCHARTPOINT_H_
#define _WX_CHARTS_WXCHARTPOINT_H_

#include "wxchartelement.h"
#include <wx/graphics.h>

/// This class is used to display a point on a chart.
class wxChartPoint : public wxChartElement
{
public:
	/// Constructs a wxChartPoint element.
	/// @param x The X coordinate of the center of the point.
	/// @param y The Y coordinate of the center of the point.
	/// @param radius The radius of the circle used to represent
	/// the point.
	/// @param strokeWidth The size of the pen used to draw the 
	/// outline of the circle.
	/// @param strokeColor The color of the pen used to draw the
	/// outline of the circle.
	/// @param fillColor The color of the point.
	/// @param tooltipProvider The tooltip provider.
	wxChartPoint(wxDouble x, wxDouble y, wxDouble radius,
		unsigned int strokeWidth, const wxColor &strokeColor, 
		const wxColor &fillColor, const wxChartTooltipProvider::ptr tooltipProvider);

	virtual bool HitTest(const wxPoint &point) const;

	virtual wxPoint2DDouble GetTooltipPosition() const;

	/// Draws the point.
	/// @param gc The graphics context.
	void Draw(wxGraphicsContext &gc);

	/// Gets the position of the point.
	/// @return The position of the point.
	const wxPoint2DDouble& GetPosition() const;
	/// Sets the position of the point.
	/// @param x The new X coordinate of the point.
	/// @param y The new Y coordinate of the point.
	void SetPosition(wxDouble x, wxDouble y);
	/// Sets the position of the point.
	/// @param position The new position of the point.
	void SetPosition(wxPoint2DDouble position);

private:
	wxPoint2DDouble m_position;
	wxDouble m_radius;
	unsigned int m_strokeWidth;
	wxColor m_strokeColor;
	wxColor m_fillColor;
};

#endif
