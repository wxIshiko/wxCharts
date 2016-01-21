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

#ifndef _WX_CHARTS_WXDOUGHNUTANDPIECHARTBASE_H_
#define _WX_CHARTS_WXDOUGHNUTANDPIECHARTBASE_H_

#include "wxchartctrl.h"
#include "wxchartslicedata.h"
#include "wxdoughnutandpiechartoptionsbase.h"
#include "wxchartarc.h"
#include <wx/control.h>
#include <wx/sharedptr.h>

/// Common base class for the wxDoughnutChartCtrl and wxPieChartCtrl controls.

/// The doughnut and pie charts are very similar so we use
/// a common base class. It would actually be possible to
/// only have the doughnut classes but I usually favor
/// ease of use over ease of implementation.
class wxDoughnutAndPieChartBase : public wxChartCtrl
{
public:
	/// Constructs a wxDoughnutAndPieChartBase control.
	/// @param parent Pointer to a parent window.
	/// @param id Control identifier. If wxID_ANY, will automatically
	/// create an identifier.
	/// @param pos Control position. wxDefaultPosition indicates that 
	/// wxWidgets should generate a default position for the control.
	/// @param size Control size. wxDefaultSize indicates that wxWidgets
	/// should generate a default size for the window. If no suitable 
	/// size can  be found, the window will be sized to 20x20 pixels 
	/// so that the window is visible but obviously not correctly sized.
	/// @param style Control style. For generic window styles, please 
	/// see wxWindow.
	wxDoughnutAndPieChartBase(wxWindow *parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize, long style = 0);

protected:
	void Add(const wxChartSliceData &slice);
	void Add(const wxChartSliceData &slice, size_t index);
	void Add(const wxChartSliceData &slice, size_t index, bool silent);

private:
	virtual void Resize(const wxSize &size);

	wxDouble CalculateCircumference(double value);
	void GetSegmentsAtEvent(const wxPoint &point);

	void OnPaint(wxPaintEvent &evt);
	void OnMouseEnter(wxMouseEvent& evt);
	void OnMouseOver(wxMouseEvent& evt);
	void OnMouseExit(wxMouseEvent& evt);

private:
	virtual const wxDoughnutAndPieChartOptionsBase& GetOptions() const = 0;

private:
	class SliceArc : public wxChartArc
	{
	public:
		typedef wxSharedPtr<SliceArc> ptr;

		SliceArc(const wxChartSliceData &slice, wxDouble x, wxDouble y,
			wxDouble startAngle, wxDouble endAngle, wxDouble outerRadius,
			wxDouble innerRadius, unsigned int strokeWidth);

		void Resize(const wxSize &size, const wxDoughnutAndPieChartOptionsBase& options);

		wxDouble GetValue() const;
		const wxString& GetTooltip() const;

	private:
		wxDouble m_value;
		wxString m_tooltip;
	};

private:
	wxVector<SliceArc::ptr> m_slices;
	double m_total;
	bool m_mouseInWindow;
	wxVector<SliceArc::ptr> m_activeSlices;

	DECLARE_EVENT_TABLE();
};

#endif
