/*
    Copyright (c) 2016-2018 Xavier Leclercq and the wxCharts contributors.

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

#ifndef _WX_CHARTS_WXCHARTLEGENDCTRL_H_
#define _WX_CHARTS_WXCHARTLEGENDCTRL_H_

#include "wxchartlegendoptions.h"
#include "wxchartlegendline.h"
#include "wxchartlegenditem.h"
#include "wxchartobservers.h"
#include <wx/control.h>

/// This control can be used to display a chart legend.

/// The legend is implemented as a separate control (and not
/// as part of the chart control itself) to allow for more
/// flexible layouts with the help of wxWidgets sizers.
class wxChartLegendCtrl : public wxControl, public wxChartValueObserver<std::map<wxString, wxChartSliceData>>
{
public:
    /// Constructs a wxChartLegendCtrl control.
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
    wxChartLegendCtrl(wxWindow *parent, wxWindowID id,
        const wxChartLegendData &data,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = 0);
    wxChartLegendCtrl(wxWindow *parent, wxWindowID id,
        wxChartObservableValue<std::map<wxString, wxChartSliceData>> &data,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = 0);

private:
    void OnPaint(wxPaintEvent &evt);
    void OnUpdate(const std::map<wxString,wxChartSliceData> &data) override;

private:
    wxChartLegendOptions m_options;
    wxVector<wxChartLegendLine> m_lines;

    DECLARE_EVENT_TABLE();
};

#endif
