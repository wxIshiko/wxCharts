/*
    Copyright (c) 2016-2024 Xavier Leclercq and the wxCharts contributors

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

#ifndef _WX_CHARTS_WXCHARTSELEMENT_H_
#define _WX_CHARTS_WXCHARTSELEMENT_H_

#include "dlimpexp.h"
#include "wxcharttooltipprovider.h"
#include <wx/graphics.h>
#include <wx/sharedptr.h>

/// \defgroup elementclasses

/// This is the base class for chart elements.

/// Chart elements are building blocks (arc, rectangles, labels...)
/// that can be used to build charts. These are not visible to
/// users of the charts, they are there for people implementing
/// charts.
/// \ingroup elementclasses
class WXDLLIMPEXP_ISHIKO_CHARTS wxChartsElement
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxChartsElement> ptr;

    /// Constructs a wxChartsElement instance with no
    /// tooltip.
    wxChartsElement();
    /// Constructs a wxChartsElement instance with a static
    /// tooltip.
    /// @param tooltip The tooltip text.
    wxChartsElement(const wxString &tooltip);
    /// Constructs a wxChartsElement instance.
    /// @param tooltipProvider The tooltip provider.
    wxChartsElement(const wxSharedPtr<wxChartTooltipProvider> tooltipProvider);
    virtual ~wxChartsElement();

    /// Draws the element.
    /// @param gc The graphics context.
    virtual void Draw(wxGraphicsContext &gc) const = 0;

    /// Elements can be activated with the mouse. This function
    /// checks whether the mouse is in the activation zone for 
    /// this element.
    /// @param point The position of the mouse.
    /// @return Whether the mouse is in the activation zone.
    virtual bool HitTest(const wxPoint &point) const = 0;

    /// Gets the tooltip provider.
    /// @return The tooltip provider.
    const wxSharedPtr<wxChartTooltipProvider> GetTooltipProvider() const;
    /// Gets the position of the tooltip.
    /// @return The position of the tooltip.
    virtual wxPoint2DDouble GetTooltipPosition() const = 0;

private:
    wxSharedPtr<wxChartTooltipProvider> m_tooltipProvider;
};

#endif
