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

#ifndef _WX_CHARTS_WXBARCHARTCTRL_H_
#define _WX_CHARTS_WXBARCHARTCTRL_H_

#include "wxchart.h"
#include "wxbarchartoptions.h"
#include "wxchartgrid.h"
#include "wxchartrectangle.h"
#include <wx/sharedptr.h>

class wxBarChartData
{
public:
	wxBarChartData(const wxVector<wxString> &labels);

	const wxVector<wxString>& GetLabels() const;

private:
	wxVector<wxString> m_labels;
};

class wxBarChartCtrl : public wxChart
{
public:
	wxBarChartCtrl(wxWindow *parent, wxWindowID id, const wxBarChartData &data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
		long style = 0);

	void AddData(const wxVector<wxDouble>& data);

private:
	virtual void Resize(const wxSize &size);

	void OnPaint(wxPaintEvent &evt);

private:
	struct ScaleClass : public wxChartGrid
	{
		ScaleClass(const wxSize &size,
			const wxVector<wxString> &labels,
			const wxChartGridOptions& options);

		double CalculateBarX(size_t datasetCount, size_t datasetIndex, size_t barIndex);
		double CalculateBaseWidth();
		double CalculateBarWidth(size_t datasetCount);
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
