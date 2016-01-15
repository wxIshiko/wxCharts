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

#include "wxdoughnutchartctrl.h"

wxDoughnutChartData::wxDoughnutChartData()
{
}

void wxDoughnutChartData::AppendSlice(const wxChartSliceData &slice)
{
	m_slices.push_back(slice);
}

const wxVector<wxChartSliceData>& wxDoughnutChartData::GetSlices() const
{
	return m_slices;
}

wxDoughnutChartCtrl::wxDoughnutChartCtrl(wxWindow *parent,
										 wxWindowID id,
										 const wxDoughnutChartData &data,
										 const wxPoint &pos,
										 const wxSize &size, 
										 long style)
	: wxDoughnutAndPieChartBase(parent, id, pos, size, style)
{
	Initialize(data);
}

wxDoughnutChartCtrl::wxDoughnutChartCtrl(wxWindow *parent, 
										 wxWindowID id, 
										 const wxDoughnutChartData &data,
										 const wxDougnutChartOptions &options,
										 const wxPoint &pos,
										 const wxSize &size, 
										 long style)
	: wxDoughnutAndPieChartBase(parent, id, pos, size, style),
	m_options(options)
{
	Initialize(data);
}

const wxDoughnutAndPieChartOptionsBase& wxDoughnutChartCtrl::GetOptions() const
{
	return m_options;
}

void wxDoughnutChartCtrl::Initialize(const wxDoughnutChartData &data)
{
	const wxVector<wxChartSliceData>& slices = data.GetSlices();
	for (size_t i = 0; i < slices.size(); ++i)
	{
		Add(slices[i]);
	}
}
