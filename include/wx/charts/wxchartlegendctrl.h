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

#ifndef _WX_CHARTS_WXCHARTLEGENDCTRL_H_
#define _WX_CHARTS_WXCHARTLEGENDCTRL_H_

#include "wxchartslicedata.h"
#include "wxlinechartctrl.h"
#include "wxchartlegendoptions.h"
#include "wxchartlegendline.h"
#include <wx/control.h>

/// Class that represents items of the wxChartLegendData class.
class wxChartLegendItem
{
public:
	/// Constructs a wxChartLegendItem instance.
	/// @param color The color associated with this
	/// item on the chart.
	/// @param label The text to be display in the legend.
	wxChartLegendItem(const wxColor &color, 
		const wxString &label);
	/// Constructs a wxChartLegendItem instance from a
	/// slice data.
	/// @param slice The slice of the chart this legend item
	/// corresponds to.
	wxChartLegendItem(const wxChartSliceData &slice);
	/// Constructs a wxChartLegendItem instance from a
	/// line chart dataset.
	/// @param dataset The dataset this legend item
	/// corresponds to.
	wxChartLegendItem(const wxLineChartDataset &dataset);

	/// Gets the color of the item.
	/// @return The color of the item.
	const wxColor& GetColor() const;
	/// Gets the label of the item.
	/// @return The label of the item.
	const wxString& GetLabel() const;

private:
	wxColor m_color;
	wxString m_label;
};

/// Data for the wxChartLegendCtrl control.
class wxChartLegendData
{
public:
	/// Constructs a wxChartLegendData 
	/// instance.
	wxChartLegendData();
	/// Constructs a wxChartLegendData instance from
	/// a list of slices. This can be used to build
	/// a legend for the wxPieChartCtrl and 
	/// wxDoughnutChartCtrl controls for instance.
	/// @param slices List of slices.
	wxChartLegendData(const wxVector<wxChartSliceData>& slices);
	/// Constructs a wxChartLegendData instance from
	/// a list of datasets. This can be used to build
	/// a legend for the wxLineChartCtrl control.
	/// @param datasets List of datasets.
	wxChartLegendData(const wxVector<wxLineChartDataset::ptr>& datasets);

	/// Appends an item to the legend.
	/// @param item The new item.
	void Append(const wxChartLegendItem &item);

	/// Gets the list of items in the legend.
	/// @return The list of legend items.
	const wxVector<wxChartLegendItem>& GetItems() const;

private:
	wxVector<wxChartLegendItem> m_items;
};

/// This control can be used to display a chart legend.

/// The legend is implemented as a separate control (and not
/// as part of the chart control itself) to allow for more
/// flexible layouts with the help of wxWidgets sizers.
class wxChartLegendCtrl : public wxControl
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

private:
	void OnPaint(wxPaintEvent &evt);

private:
	wxChartLegendOptions m_options;
	wxVector<wxChartLegendItem> m_items;
	wxVector<wxChartLegendLine> m_lines;

	DECLARE_EVENT_TABLE();
};

#endif
