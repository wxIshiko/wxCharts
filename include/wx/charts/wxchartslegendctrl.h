/*
    Copyright (c) 2016-2024 Xavier Leclercq

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

#ifndef _WX_CHARTS_WXCHARTSLEGENDCTRL_H_
#define _WX_CHARTS_WXCHARTSLEGENDCTRL_H_

#include "dlimpexp.h"
#include "wxchartslegendoptions.h"
#include "wxchartslegendline.h"
#include "wxchartslegenditem.h"
#include <wx/control.h>

/// This control can be used to display a chart legend.

/// The legend is implemented as a separate control (and not
/// as part of the chart control itself) to allow for more
/// flexible layouts with the help of wxWidgets sizers.
class WXDLLIMPEXP_ISHIKO_CHARTS wxChartsLegendCtrl : public wxControl
{
public:
    /// Constructs a wxChartsLegendCtrl control.
    /// @param parent Pointer to a parent window.
    /// @param id Control identifier. If wxID_ANY, will automatically
    /// create an identifier.
    /// @param data The initialization data for the control.
    /// @param pos Control position. wxDefaultPosition indicates that 
    /// wxWidgets should generate a default position for the control.
    /// @param size Control size. wxDefaultSize indicates that wxWidgets
    /// should generate a default size for the window. If no suitable 
    /// size can  be found, the window will be sized to 20x20 pixels 
    /// so that the window is visible but obviously not correctly sized.
    /// @param style Control style. For generic window styles, please 
    /// see wxWindow.
    wxChartsLegendCtrl(wxWindow *parent, wxWindowID id,
        const wxChartsLegendData &data,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = 0);

private:
    void OnPaint(wxPaintEvent &evt);

private:
    wxChartsLegendOptions m_options;
    wxVector<wxChartsLegendLine> m_lines;

    DECLARE_EVENT_TABLE();
};

#endif
