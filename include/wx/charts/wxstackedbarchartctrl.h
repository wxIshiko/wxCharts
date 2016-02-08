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
#include "wxstackedbarchartoptions.h"
#include "wxchartgrid.h"

/// Stores the information about a dataset to be shown on a wxStackedBarChartCtrl.
class wxStackedBarChartDataset
{
public:
	/// Smart pointer typedef.
	typedef wxSharedPtr<wxStackedBarChartDataset> ptr;

	/// Constructs a wxStackedBarChartDataset instance.
	/// @param data The list of values.
	wxStackedBarChartDataset(const wxVector<wxDouble> &data);

	const wxVector<wxDouble>& GetData() const;

private:
	wxVector<wxDouble> m_data;
};

/// Data for the wxStackedBarChartCtrl control.
class wxStackedBarChartData
{
public:
	/// Constructs a wxStackedBarChartData instance.
	/// @param labels The labels of the X axis.
	wxStackedBarChartData(const wxVector<wxString> &labels);

	/// Adds a dataset.
	/// @param dataset The dataset to add.
	void AddDataset(wxStackedBarChartDataset::ptr dataset);

	/// Gets the labels of the X axis.
	/// @return A vector containing the labels of the
	/// X axis.
	const wxVector<wxString>& GetLabels() const;
	const wxVector<wxStackedBarChartDataset::ptr>& GetDatasets() const;
	
private:
	wxVector<wxString> m_labels;
	wxVector<wxStackedBarChartDataset::ptr> m_datasets;
};

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
	wxStackedBarChartCtrl(wxWindow *parent, wxWindowID id, const wxStackedBarChartData &data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
		long style = 0);

	virtual const wxStackedBarChartOptions& GetOptions() const;

private:
	virtual void Resize(const wxSize &size);
	virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point);

	void OnPaint(wxPaintEvent &evt);

private:
	wxStackedBarChartOptions m_options;
	wxChartGrid m_grid;

	DECLARE_EVENT_TABLE();
};

#endif
