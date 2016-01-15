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

#ifndef _WX_CHARTS_WXCHARTGRIDOPTIONS_H_
#define _WX_CHARTS_WXCHARTGRIDOPTIONS_H_

#include <wx/colour.h>
#include <wx/font.h>

// Class holding the options for the wxChartGrid
// element
class wxChartGridOptions
{
public:
	wxChartGridOptions();

	void SetFontSize(int size);

	unsigned int GetAxisLineWidth() const;
	const wxColor& GetAxisLineColor() const;

	bool ShowHorizontalLines() const;
	bool ShowVerticalLines() const;
	unsigned int GetGridLineWidth() const;
	const wxColor& GetGridLineColor() const;

	wxFontFamily GetFontFamily() const;
	int GetFontSize() const;
	wxFontStyle GetFontStyle() const;
	const wxColor& GetFontColor() const;

private:
	unsigned int m_axisLineWidth;
	wxColor m_axisLineColor;
	// Whether to show horizontal lines (the X-axis is always shown)
	bool m_showHorizontalLines;
	// Whether to show vertical lines (the Y-axis is always shown)
	bool m_showVerticalLines;
	unsigned int m_gridLineWidth;
	wxColor m_gridLineColor;
	wxFontFamily m_fontFamily;
	int m_fontSize;
	wxFontStyle m_fontStyle;
	wxColor m_fontColor;
};

#endif