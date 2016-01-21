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

#ifndef _WX_CHARTS_WXDOUGHNUTCHARTCTRL_H_
#define _WX_CHARTS_WXDOUGHNUTCHARTCTRL_H_

#include "wxdoughnutandpiechartbase.h"
#include "wxdoughnutchartoptions.h"

/// Data for the wxDoughnutChartCtrl.
class wxDoughnutChartData
{
public:
	wxDoughnutChartData();

	void AppendSlice(const wxChartSliceData &slice);

	const wxVector<wxChartSliceData>& GetSlices() const;

private:
	wxVector<wxChartSliceData> m_slices;
};

/// A control that displays a doughnut chart.
class wxDoughnutChartCtrl : public wxDoughnutAndPieChartBase
{
public:
	wxDoughnutChartCtrl(wxWindow *parent, wxWindowID id, const wxDoughnutChartData &data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
		long style = 0);
	wxDoughnutChartCtrl(wxWindow *parent, wxWindowID id, const wxDoughnutChartData &data,
		const wxDougnutChartOptions &options, const wxPoint &pos = wxDefaultPosition, 
		const wxSize &size = wxDefaultSize, long style = 0);

private:
	virtual const wxDoughnutAndPieChartOptionsBase& GetOptions() const;
	void Initialize(const wxDoughnutChartData &data);

private:
	wxDougnutChartOptions m_options;
};

#endif
