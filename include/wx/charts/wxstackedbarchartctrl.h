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

#ifndef _WX_CHARTS_WXSTACKEDBARCHARTCTRL_H_
#define _WX_CHARTS_WXSTACKEDBARCHARTCTRL_H_

#include "wxchartctrl.h"
#include "wxbarchartdata.h"
#include "wxstackedbarchartoptions.h"
#include "wxchartgrid.h"
#include "wxchartrectangle.h"

/// A control that displays a stacked bar chart.
class wxStackedBarChartCtrl : public wxChartCtrl
{
public:
	/// Constructs a wxStackedBarChartCtrl control.
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
	wxStackedBarChartCtrl(wxWindow *parent, wxWindowID id, const wxBarChartData &data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
		long style = 0);
	wxStackedBarChartCtrl(wxWindow *parent, wxWindowID id, const wxBarChartData &data,
		const wxStackedBarChartOptions &options, const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize, long style = 0);

	virtual const wxStackedBarChartOptions& GetOptions() const;

private:
	static wxDouble GetCumulativeMinValue(const wxVector<wxBarChartDataset::ptr>& datasets);
	static wxDouble GetCumulativeMaxValue(const wxVector<wxBarChartDataset::ptr>& datasets);

    virtual void DoFit() wxOVERRIDE;
    virtual void DoDraw(wxGraphicsContext &gc) wxOVERRIDE;
	virtual void Resize(const wxSize &size) wxOVERRIDE;
	virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point) wxOVERRIDE;

private:
	class Bar : public wxChartRectangle
	{
	public:
		typedef wxSharedPtr<Bar> ptr;

		Bar(wxDouble value,
			const wxChartTooltipProvider::ptr tooltipProvider,
			wxDouble x, wxDouble y,
			const wxColor &fillColor, const wxColor &strokeColor,
			int directions);

		virtual bool HitTest(const wxPoint &point) const;

		wxDouble GetValue() const;

	private:
		wxDouble m_value;
	};

	class Dataset
	{
	public:
		typedef wxSharedPtr<Dataset> ptr;

		Dataset();

		const wxVector<Bar::ptr>& GetBars() const;
		void AppendBar(Bar::ptr bar);

	private:
		wxVector<Bar::ptr> m_bars;
	};

private:
	wxStackedBarChartOptions m_options;
	wxChartGrid m_grid;
	wxVector<Dataset::ptr> m_datasets;
};

#endif
