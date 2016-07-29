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

#ifndef _WX_CHARTS_WXCHART_H_
#define _WX_CHARTS_WXCHART_H_

#include "wxchartoptions.h"
#include "wxchartelement.h"
#include <wx/sharedptr.h>

class wxChart
{
public:
    wxChart();

    /// Gets the options for the chart. Derived classes
    /// would typically change the signature of this method
    /// to return a class derived from wxChartOptions.
    /// @return The options.
    virtual const wxChartOptions& GetOptions() const = 0;

    void SetSize(const wxSize &size);
    void Draw(wxGraphicsContext &gc);
    void ActivateElementsAt(const wxPoint &point);

protected:
    void Fit();
    void DrawTooltips(wxGraphicsContext &gc);

private:
    virtual void DoSetSize(const wxSize &size) = 0;
    virtual void DoFit() = 0;
    virtual void DoDraw(wxGraphicsContext &gc) = 0;
    virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point) = 0;

private:
    bool m_needsFit;
    wxSharedPtr<wxVector<const wxChartElement*> > m_activeElements;
};

#endif
