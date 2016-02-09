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

#ifndef _WX_CHARTS_WXBARCHARTCTRL_H_
#define _WX_CHARTS_WXBARCHARTCTRL_H_

#include "wxchartctrl.h"
#include "wxbarchartoptions.h"
#include "wxchartgrid.h"
#include "wxchartrectangle.h"
#include <wx/sharedptr.h>

/// Stores the information about a dataset to be shown on a wxBarChartCtrl.
class wxBarChartDataset
{
public:
	/// Smart pointer typedef.
	typedef wxSharedPtr<wxBarChartDataset> ptr;

	/// Constructs a wxStackedBarChartDataset instance.
	/// @param fillColor The color of the brush used to 
	/// fill the bar.
	/// @param strokeColor The color of the pen used to
	/// draw the outline of the bar.
	/// @param data The list of values.
	wxBarChartDataset(const wxColor &fillColor, const wxColor &strokeColor,
		const wxVector<wxDouble> &data);

	/// Gets the color of the brush used to fill the
	/// bar.
	/// @return The color of the brush used to fill the
	/// bar.
	const wxColor& GetFillColor() const;
	/// Gets the color of the pen used to draw the outline
	/// of the bar.
	/// @return The color of the pen used to draw the 
	/// outline of the bar.
	const wxColor& GetStrokeColor() const;
	const wxVector<wxDouble>& GetData() const;

private:
	wxColor m_fillColor;
	wxColor m_strokeColor;
	wxVector<wxDouble> m_data;
};

/// Data for the wxBarChartCtrl control.
class wxBarChartData
{
public:
	/// Constructs a wxBarChartData instance.
	/// @param labels The labels of the X axis.
	wxBarChartData(const wxVector<wxString> &labels);

	/// Adds a dataset.
	/// @param dataset The dataset to add.
	void AddDataset(wxBarChartDataset::ptr dataset);

	/// Gets the labels of the X axis.
	/// @return A vector containing the labels of the
	/// X axis.
	const wxVector<wxString>& GetLabels() const;
	const wxVector<wxBarChartDataset::ptr>& GetDatasets() const;

private:
	wxVector<wxString> m_labels;
	wxVector<wxBarChartDataset::ptr> m_datasets;
};

/// A control that displays a bar chart.
class wxBarChartCtrl : public wxChartCtrl
{
public:
	/// Constructs a wxBarChartCtrl control.
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
	wxBarChartCtrl(wxWindow *parent, wxWindowID id, const wxBarChartData &data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
		long style = 0);

	virtual const wxBarChartOptions& GetOptions() const;

	void AddData(const wxVector<wxDouble>& data);

private:
	static wxDouble GetMinValue(const wxVector<wxBarChartDataset::ptr>& datasets);
	static wxDouble GetMaxValue(const wxVector<wxBarChartDataset::ptr>& datasets);

	virtual void Resize(const wxSize &size);
	virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point);

	void OnPaint(wxPaintEvent &evt);

private:
	struct ScaleClass : public wxChartGrid
	{
		ScaleClass(const wxSize &size,
			const wxVector<wxString> &labels,
			wxDouble minValue, wxDouble maxValue,
			const wxChartGridOptions& options);

		wxDouble CalculateBarX(size_t datasetCount, size_t datasetIndex, size_t barIndex);
		wxDouble CalculateBaseWidth();
		wxDouble CalculateBarWidth(size_t datasetCount);
	};

	struct BarClass : public wxChartRectangle
	{
		BarClass(wxDouble x, wxDouble y, const wxColor &fillColor,
			const wxColor &strokeColor);
	};

	struct Dataset
	{
		typedef wxSharedPtr<Dataset> ptr;

		wxVector<BarClass> bars;
	};

private:
	wxBarChartOptions m_options;
	ScaleClass m_grid;
	wxVector<Dataset::ptr> m_datasets;

	DECLARE_EVENT_TABLE();
};

#endif
