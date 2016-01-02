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
#include <wx/dcclient.h>
#include <wx/graphics.h>

wxDoughnutChartCtrl::Segment::Segment(double value,
									  const wxColor &color)
	: value(value), color(color)
{
}

wxDoughnutChartCtrl::SegmentArc::SegmentArc(const Segment &segment)
	: wxChartArc(segment.color), value(segment.value)
{
}

wxDoughnutChartCtrl::wxDoughnutChartCtrl(wxWindow *parent,
										 wxWindowID id,
										 const wxPoint &pos,
										 const wxSize &size, 
										 long style)
	: wxControl(parent, id, pos, size, style), m_total(0)
{
	SetBackgroundColour(*wxWHITE);
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
	m_total += segment.value;
	m_segments.insert(
		m_segments.begin() + index,
		std::make_shared<SegmentArc>(segment)
		);
	if (!silent){
		OnAddOrRemoveData();
	}
}

double wxDoughnutChartCtrl::CalculateCircumference(double value)
{
	if (m_total > 0) 
	{
		return (value * 2 * M_PI / m_total);
	}
	else
	{
		return 0;
	}
}

void wxDoughnutChartCtrl::OnAddOrRemoveData()
{
}

void wxDoughnutChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxPaintDC dc(this);
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		for (size_t i = 0; i < m_segments.size(); ++i)
		{
			SegmentArc& currentSegment = *m_segments[i];
			if (i == 0)
			{
				currentSegment.startAngle = 0;
			}
			currentSegment.endAngle = currentSegment.startAngle + CalculateCircumference(currentSegment.value);
			currentSegment.draw(*gc);
			// Check to see if it's the last segment, if not get the next and update the start angle
			if (i < (m_segments.size() - 1))
			{
				m_segments[i + 1]->startAngle = currentSegment.endAngle;
			}
		}

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxDoughnutChartCtrl, wxControl)
	EVT_PAINT(wxDoughnutChartCtrl::OnPaint)
END_EVENT_TABLE()
