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

#include "wxpiechartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxPieChartOptions::wxPieChartOptions()
	: m_segmentStrokeWidth(2), m_showTooltips(true)
{
}

unsigned int wxPieChartOptions::GetSegmentStrokeWidth() const
{
	return m_segmentStrokeWidth;
}

bool wxPieChartOptions::ShowTooltips() const
{
	return m_showTooltips;
}

wxPieChartCtrl::Segment::Segment(double value,
								 const wxColor &color)
	: value(value), color(color)
{
}

wxPieChartCtrl::SegmentArc::SegmentArc(const Segment &segment, 
									   double x, 
									   double y,
									   double startAngle, 
									   double endAngle, 
									   double outerRadius,
									   unsigned int strokeWidth)
	: wxChartArc(x, y, startAngle, endAngle, outerRadius, 0, strokeWidth, segment.color),
	value(segment.value)
{
}

void wxPieChartCtrl::SegmentArc::Resize(const wxSize &size, 
										const wxPieChartOptions& options)
{
	double x = (size.GetX() / 2) - 2;
	double y = (size.GetY() / 2) - 2;
	double outerRadius = ((x < y) ? x : y) - (GetStrokeWidth() / 2);
	
	SetCenter(x, y);
	SetRadiuses(outerRadius, 0);
}

wxPieChartCtrl::wxPieChartCtrl(wxWindow *parent,
							   wxWindowID id,
							   const wxPoint &pos,
							   const wxSize &size, 
							   long style)
	: wxDoughnutAndPieChartBase(parent, id, pos, size, style), m_total(0)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(*wxWHITE);
}

void wxPieChartCtrl::AddData(const Segment &segment)
{
	AddData(segment, m_segments.size());
}

void wxPieChartCtrl::AddData(const Segment &segment, size_t index)
{
	AddData(segment, index, false);
}

void wxPieChartCtrl::AddData(const Segment &segment, size_t index, bool silent)
{
	m_total += segment.value;

	double x = (GetSize().GetX() / 2) - 2;
	double y = (GetSize().GetY() / 2) - 2;
	double outerRadius = ((x < y) ? x : y) - (m_options.GetSegmentStrokeWidth() / 2);
	
	SegmentArc::ptr newSegment = std::make_shared<SegmentArc>(segment,
		x, y, 0, 0, outerRadius, m_options.GetSegmentStrokeWidth());
	m_segments.insert(m_segments.begin() + index, newSegment);
	if (!silent){
		OnAddOrRemoveData();
	}
}

double wxPieChartCtrl::CalculateCircumference(double value)
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

void wxPieChartCtrl::OnAddOrRemoveData()
{
}

void wxPieChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);
	
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		double startAngle = 0.0;
		for (size_t i = 0; i < m_segments.size(); ++i)
		{
			SegmentArc& currentSegment = *m_segments[i];
			
			double endAngle = startAngle + CalculateCircumference(currentSegment.value);
			currentSegment.SetAngles(startAngle, endAngle);
			startAngle = endAngle;

			currentSegment.Draw(*gc);
		}

		delete gc;
	}
}

void wxPieChartCtrl::OnSize(wxSizeEvent& evt)
{
	for (size_t i = 0; i < m_segments.size(); ++i)
	{
		m_segments[i]->Resize(evt.GetSize(),m_options);
	}
	Refresh();
}

BEGIN_EVENT_TABLE(wxPieChartCtrl, wxControl)
	EVT_PAINT(wxPieChartCtrl::OnPaint)
	EVT_SIZE(wxPieChartCtrl::OnSize)
END_EVENT_TABLE()
