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

#ifndef _WX_CHARTS_WXCHARTTOOLTIPPROVIDER_H_
#define _WX_CHARTS_WXCHARTTOOLTIPPROVIDER_H_

#include <wx/string.h>
#include <wx/sharedptr.h>

// Interface for the classes that are able to generate
// content for tooltips
class wxChartTooltipProvider
{
public:
	typedef wxSharedPtr<wxChartTooltipProvider> ptr;

	wxChartTooltipProvider();

	virtual wxString GetTooltipText() const = 0;
};

// An implementation of the wxChartTooltipProvider
// interface where the content is a static string
// passed in at construction time.
class wxChartTooltipProviderStatic : public wxChartTooltipProvider
{
public:
	wxChartTooltipProviderStatic(const wxString &text);

	virtual wxString GetTooltipText() const;

private:
	wxString m_text;
};

#endif
