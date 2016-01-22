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

#ifndef _WX_CHARTS_WXCHARTRECTANGLEOPTIONS_H_
#define _WX_CHARTS_WXCHARTRECTANGLEOPTIONS_H_

#include <wx/colour.h>

/// The options for the wxChartRectangle element.
class wxChartRectangleOptions
{
public:
	/// Constructs a wxChartRectangleOptions instance.
	/// @param fillColor The color of the brush used to 
	/// fill the rectangle.
	/// @param strokeColor The color of the pen used to
	/// draw the outline of the rectangle.
	wxChartRectangleOptions(const wxColor &fillColor,
		const wxColor &strokeColor);

	/// Gets the color of the brush used to fill the
	/// rectangle.
	/// @return The color of the brush used to fill the
	/// rectangle.
	const wxColor& GetFillColor() const;
	/// Gets the color of the pen used to draw the outline
	/// of the rectangle.
	/// @return The color of the pen used to draw the 
	/// outline of the rectangle.
	const wxColor& GetStrokeColor() const;

private:
	wxColor m_fillColor;
	wxColor m_strokeColor;
};

#endif
