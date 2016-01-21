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

#ifndef _WX_CHARTS_WXCHARTLABEL_H_
#define _WX_CHARTS_WXCHARTLABEL_H_

#include "wxchartelement.h"
#include <wx/graphics.h>
#include <wx/string.h>

/// This class is used to display text on a chart.

/// In addition to the text this class stores
/// the width and height of the label. However
/// this class itself is unable to compute them
/// as that requires a graphics context. The code
/// that uses this class needs to set and update 
/// the width and height.
class wxChartLabel : public wxChartElement
{
public:
	/// Constructs a wxChartLabel element. The width
	/// and height are set to 0.
	/// @param text The text to display.
	wxChartLabel(const wxString &text);
	/// Constructs a wxChartLabel element.
	/// @param text The text to display.
	/// @param width The width of the label.
	/// @param height The height of the label.
	wxChartLabel(const wxString &text, wxDouble width,
		wxDouble height);

	virtual bool HitTest(const wxPoint &point) const;

	void Draw(wxDouble x, wxDouble y, 
		wxGraphicsContext &gc);

	const wxString& GetText() const;
	const wxSize& GetSize() const;
	void SetSize(const wxSize &size);
	void SetSize(wxDouble width, wxDouble height);

private:
	wxString m_text;
	wxSize m_size;
};

#endif
