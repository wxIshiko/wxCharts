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

#ifndef _WX_CHARTS_WXCHARTTOOLTIPOPTIONS_H_
#define _WX_CHARTS_WXCHARTTOOLTIPOPTIONS_H_

#include <wx/colour.h>
#include <wx/font.h>

/// The options for the wxChartTooltip element.
class wxChartTooltipOptions
{
public:
	/// Constructs a wxChartTooltipOptions instance.
	wxChartTooltipOptions();

	wxFontFamily GetFontFamily() const;
	int GetFontSize() const;
	wxFontStyle GetFontStyle() const;
	const wxColor& GetFontColor() const;

	wxDouble GetHorizontalPadding() const;
	wxDouble GetVerticalPadding() const;
	const wxColor& GetBackgroundColor() const;
	wxDouble GetCornerRadius() const;

private:
	wxFontFamily m_fontFamily;
	int m_fontSize;
	wxFontStyle m_fontStyle;
	wxColor m_fontColor;
	wxDouble m_horizontalPadding;
	wxDouble m_verticalPadding;
	wxColor m_backgroundColor;
	wxDouble m_cornerRadius;
};

#endif
