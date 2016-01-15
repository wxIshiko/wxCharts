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

#ifndef _WX_CHARTS_WXCHARTLEGENDCTRL_H_
#define _WX_CHARTS_WXCHARTLEGENDCTRL_H_

#include "wxchartslicedata.h"
#include "wxchartlegendoptions.h"
#include <wx/control.h>

class wxChartLegendItem
{
public:
	wxChartLegendItem(const wxColor &color, 
		const wxString &label);
	wxChartLegendItem(const wxChartSliceData &slice);

	const wxColor& GetColor() const;
	const wxString& GetLabel() const;

private:
	wxColor m_color;
	wxString m_label;
};

class wxChartLegendData
{
public:
	wxChartLegendData();
	wxChartLegendData(const wxVector<wxChartSliceData>& slices);

	void Append(const wxChartLegendItem &item);

	const wxVector<wxChartLegendItem>& GetItems() const;

private:
	wxVector<wxChartLegendItem> m_items;
};

class wxChartLegendCtrl : public wxControl
{
public:
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

	DECLARE_EVENT_TABLE();
};

#endif
