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

/*
	Part of this file were copied from the Chart.js project (http://chartjs.org/)
	and translated into C++.

	The files of the Chart.js project have the following copyright and license.

	Copyright (c) 2013-2016 Nick Downie
	Released under the MIT license
	https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

/// @file

#ifndef _WX_CHARTS_WXPOLARAREACHARTCTRL_H_
#define _WX_CHARTS_WXPOLARAREACHARTCTRL_H_

#include "wxchartctrl.h"
#include "wxchartslicedata.h"
#include "wxpolarareachartoptions.h"
#include "wxchartradialgrid.h"
#include "wxchartarc.h"

/// Data for the wxPolarAreaChartCtrl control.
class wxPolarAreaChartData
{
public:
	wxPolarAreaChartData();

	void AppendSlice(const wxChartSliceData &slice);

	const wxVector<wxChartSliceData>& GetSlices() const;

private:
	wxVector<wxChartSliceData> m_slices;
};

/// A control that displays a polar area chart.
class wxPolarAreaChartCtrl : public wxChartCtrl
{
public:
	/// Constructs a wxPolarAreaChartCtrl control.
	/// @param parent Pointer to a parent window.
	/// @param id Control identifier. If wxID_ANY, will automatically
	/// create an identifier.
	/// @param data The data that will be used to initialize the chart.
	/// @param pos Control position. wxDefaultPosition indicates that 
	/// wxWidgets should generate a default position for the control.
	/// @param size Control size. wxDefaultSize indicates that wxWidgets
	/// should generate a default size for the window. If no suitable 
	/// size can  be found, the window will be sized to 20x20 pixels 
	/// so that the window is visible but obviously not correctly sized.
	/// @param style Control style. For generic window styles, please 
	/// see wxWindow.
	wxPolarAreaChartCtrl(wxWindow *parent, wxWindowID id, const wxPolarAreaChartData &data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
		long style = 0);
    wxPolarAreaChartCtrl(wxWindow *parent, wxWindowID id, const wxPolarAreaChartData &data,
        const wxPolarAreaChartOptions &options, const wxPoint &pos = wxDefaultPosition, 
        const wxSize &size = wxDefaultSize, long style = 0);

	virtual const wxPolarAreaChartOptions& GetOptions() const;

private:
	void Add(const wxChartSliceData &slice);
	void Add(const wxChartSliceData &slice, size_t index);
	
	static wxDouble GetMinValue(const wxVector<wxChartSliceData> &slices);
	static wxDouble GetMaxValue(const wxVector<wxChartSliceData> &slices);

    virtual void DoFit() wxOVERRIDE;
    virtual void DoDraw(wxGraphicsContext &gc) wxOVERRIDE;
	virtual void Resize(const wxSize &size) wxOVERRIDE;
	virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point) wxOVERRIDE;

private:
    class SliceArc : public wxChartArc
    {
    public:
        typedef wxSharedPtr<SliceArc> ptr;

        SliceArc(const wxChartSliceData &slice, wxDouble x, wxDouble y,
            wxDouble startAngle, wxDouble endAngle, wxDouble radius);

        void Resize(const wxSize &size);

        wxDouble GetValue() const;

    private:
        wxDouble m_value;
    };

private:
	wxPolarAreaChartOptions m_options;
	wxChartRadialGrid m_grid;
	wxVector<SliceArc::ptr> m_slices;
};

#endif
