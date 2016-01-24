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

#ifndef _WX_CHARTS_WXCHARTAXISOPTIONS_H_
#define _WX_CHARTS_WXCHARTAXISOPTIONS_H_

#include <wx/colour.h>
#include <wx/font.h>

enum wxChartLabelAlignment
{
	wxCHARTLABELALIGNMENT_ON_LINES = 0,
	wxCHARTLABELALIGNMENT_BETWEEN_LINES = 1
};

/// The options for the wxChartAxis element.
class wxChartAxisOptions
{
public:
	/// Constructs a new wxChartAxisOptions
	/// instance.
	wxChartAxisOptions();
	wxChartAxisOptions(wxChartLabelAlignment labelAlignment);

	wxChartLabelAlignment GetLabelAlignment() const;

	unsigned int GetLineWidth() const;
	const wxColor& GetLineColor() const;

	/// Gets the font family to be used for 
	/// the labels.
	/// @return The font family.
	wxFontFamily GetFontFamily() const;
	/// Gets the font size to be used for 
	/// the labels.
	/// @return The font size in pixels.
	int GetFontSize() const;
	/// Gets the font style to be used for 
	/// the labels.
	/// @return The font style.
	wxFontStyle GetFontStyle() const;
	/// Gets the font color to be used for 
	/// the labels.
	/// @return The font color.
	const wxColor& GetFontColor() const;

private:
	wxChartLabelAlignment m_labelAlignment;
	unsigned int m_lineWidth;
	wxColor m_lineColor;
	wxFontFamily m_fontFamily;
	int m_fontSize;
	wxFontStyle m_fontStyle;
	wxColor m_fontColor;
};

#endif
