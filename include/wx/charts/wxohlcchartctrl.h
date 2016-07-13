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

#ifndef _WX_CHARTS_WXOHLCCHARTCTRL_H_
#define _WX_CHARTS_WXOHLCCHARTCTRL_H_

#include "wxchartctrl.h"
#include "wxchartohlcdata.h"
#include "wxohlcchartoptions.h"
#include "wxchartgrid.h"

/// Data for the wxOHLCChartCtrl control.
class wxOHLCChartData
{
public:
    wxOHLCChartData(const wxVector<wxString> &labels, const wxVector<wxChartOHLCData> &data);

    /// Gets the labels of the X axis.
    /// @return A vector containing the labels of the
    /// X axis.
    const wxVector<wxString>& GetLabels() const;
    unsigned int GetLineWidth() const;
    const wxColor& GetUpLineColor() const;
    const wxColor& GetDownLineColor() const;
    unsigned int GetOpenLineLength() const;
    unsigned int GetCloseLineLength() const;
    const wxVector<wxChartOHLCData>& GetData() const;

private:
    wxVector<wxString> m_labels;
    unsigned int m_lineWidth;
    wxColor m_upLineColor;
    wxColor m_downLineColor;
    unsigned int m_openLineLength;
    unsigned int m_closeLineLength;
    wxVector<wxChartOHLCData> m_data;
};

/// A control that displays a candlestick chart.
class wxOHLCChartCtrl : public wxChartCtrl
{
public:
    /// Constructs a wxOHLCChartCtrl control.
    /// @param parent Pointer to a parent window.
    /// @param id Control identifier. If wxID_ANY, will automatically
    /// create an identifier.
    /// @param data The data that will be used to initialize the chart.
    /// @param pos Control position. wxDefaultPosition indicates that 
    /// wxWidgets should generate a default position for the control.
    /// @param size Control size. wxDefaultSize indicates that wxWidgets
    /// should generate a default size for the window. If no suitable 
    /// size can be found, the window will be sized to 20x20 pixels 
    /// so that the window is visible but obviously not correctly sized.
    /// @param style Control style. For generic window styles, please 
    /// see wxWindow.
    wxOHLCChartCtrl(wxWindow *parent, wxWindowID id, const wxOHLCChartData &data,
        const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
        long style = 0);

    virtual const wxOHLCChartOptions& GetOptions() const;

private:
    static wxDouble GetMinValue(const wxOHLCChartData &data);
    static wxDouble GetMaxValue(const wxOHLCChartData &data);

    virtual void DoDraw(wxGraphicsContext &gc) wxOVERRIDE;
    virtual void Resize(const wxSize &size) wxOVERRIDE;
    virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point) wxOVERRIDE;

    void OnPaint(wxPaintEvent &evt);

private:
    class OHLDCLines : public wxChartElement
    {
    public:
        typedef wxSharedPtr<OHLDCLines> ptr;

        OHLDCLines(const wxChartOHLCData &data, unsigned int lineWidth,
            const wxColor& upLineColor, const wxColor& downLineColor, 
            unsigned int openLineLength, unsigned int closeLineLength, 
            const wxChartTooltipProvider::ptr tooltipProvider);

        virtual bool HitTest(const wxPoint &point) const;
        virtual wxPoint2DDouble GetTooltipPosition() const;

        /// Draws the OHLDC lines.
        /// @param gc The graphics context.
        void Draw(wxGraphicsContext &gc);

        void Update(const wxChartGridMapping& mapping, size_t index);

    private:
        wxChartOHLCData m_data;
        wxPoint2DDouble m_lowPoint;
        wxPoint2DDouble m_highPoint;
        wxPoint2DDouble m_openPoint;
        wxPoint2DDouble m_closePoint;
        unsigned int m_lineWidth;
        wxColor m_upLineColor;
        wxColor m_downLineColor;
        unsigned int m_openLineLength;
        unsigned int m_closeLineLength;
    };

private:
    wxOHLCChartOptions m_options;
    wxChartGrid m_grid;
    wxVector<OHLDCLines::ptr> m_data;

    DECLARE_EVENT_TABLE();
};

#endif
