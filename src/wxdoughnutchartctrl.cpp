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

wxDoughnutChartCtrl::SegmentArc::SegmentArc(const Segment &segment)
	: value(segment.value)
{
}

wxDoughnutChartCtrl::wxDoughnutChartCtrl(wxWindow *parent,
										 wxWindowID id,
										 const wxPoint &pos,
										 const wxSize &size, 
										 long style)
	: wxControl(parent, id, pos, size, style)
{
}

void wxDoughnutChartCtrl::AddData(const Segment &segment)
{
	AddData(segment, m_segments.size());
}

void wxDoughnutChartCtrl::AddData(const Segment &segment, size_t index)
{
	AddData(segment, index, false);
}

void wxDoughnutChartCtrl::AddData(const Segment &segment, size_t index, bool silent)
{
	m_segments.insert(
		m_segments.begin() + index,
		std::make_shared<SegmentArc>(segment)
		);
	if (!silent){
		OnAddOrRemoveData();
	}
}

void wxDoughnutChartCtrl::CalculateCircumference()
{
}

void wxDoughnutChartCtrl::CalculateTotal()
{
	m_total = 0;
}

void wxDoughnutChartCtrl::OnAddOrRemoveData()
{
	CalculateTotal();
}

void wxDoughnutChartCtrl::OnPaint(wxPaintEvent &evt)
{
}

BEGIN_EVENT_TABLE(wxDoughnutChartCtrl, wxControl)
	EVT_PAINT(wxDoughnutChartCtrl::OnPaint)
END_EVENT_TABLE()
