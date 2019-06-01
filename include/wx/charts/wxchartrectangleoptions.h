/*
    Copyright (c) 2016-2019 Xavier Leclercq

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

#include "wxchartsbrushoptions.h"
#include <wx/colour.h>

/// The options for the wxChartRectangle element.
/**
    \ingroup elementclasses
*/
class wxChartRectangleOptions
{
public:
    /// Constructor.
    /**
        @param fillColor The color of the brush used to fill the
        rectangle.
        @param strokeColor The color of the pen used to draw the
        outline of the rectangle.
        @param borders A combination of wxTOP, wxBOTTOM, wxRIGHT
        and wxLEFT that specifies which borders need to be drawn.
    */
    wxChartRectangleOptions(const wxColor &fillColor,
        const wxColor &strokeColor, int borders);

    /// Gets the color of the brush used to fill the rectangle.
    /**
        @return The color of the brush used to fill the rectangle.
    */
    const wxColor& GetFillColor() const;

    /// Gets the color of the pen used to draw the outline of the rectangle.
    /**
        @return The color of the pen used to draw the 
        outline of the rectangle.
    */
    const wxColor& GetStrokeColor() const;

    /// Gets the flags that specify which borders need to be drawn.
    /**
        @return A combination of wxTOP, wxBOTTOM, wxRIGHT
        and wxLEFT that specifies which borders need to be drawn.
    */
    int GetBorders() const;

private:
    wxChartsBrushOptions m_brushOptions;
    wxColor m_strokeColor;
    int m_borders;
};

#endif
