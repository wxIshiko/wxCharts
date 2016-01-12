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

#include "wxdoughnutandpiechartbase.h"
#include "wxcharttooltip.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxDoughnutAndPieChartBase::SliceArc::SliceArc(const ChartSliceData &slice,
											  wxDouble x,
											  wxDouble y,
											  wxDouble startAngle,
											  wxDouble endAngle,
											  wxDouble outerRadius,
											  wxDouble innerRadius,
											  unsigned int strokeWidth)
	: wxChartArc(x, y, startAngle, endAngle, outerRadius, innerRadius, strokeWidth, slice.GetColor()),
	m_value(slice.GetValue()), m_tooltip(slice.GetLabel())
{
}

void wxDoughnutAndPieChartBase::SliceArc::Resize(const wxSize &size,
												 const wxDoughnutAndPieChartOptionsBase& options)
{
	wxDouble x = (size.GetX() / 2) - 2;
	wxDouble y = (size.GetY() / 2) - 2;
	wxDouble outerRadius = ((x < y) ? x : y) - (GetStrokeWidth() / 2);
	wxDouble innerRadius = outerRadius * ((wxDouble)options.GetPercentageInnerCutout()) / 100;

	SetCenter(x, y);
	SetRadiuses(outerRadius, innerRadius);
}

wxDouble wxDoughnutAndPieChartBase::SliceArc::GetValue() const
{
	return m_value;
}

const wxString& wxDoughnutAndPieChartBase::SliceArc::GetTooltip() const
{
	return m_tooltip;
}

wxDoughnutAndPieChartBase::wxDoughnutAndPieChartBase(wxWindow *parent,
													 wxWindowID id,
													 const wxPoint &pos,
													 const wxSize &size,
													 long style)
	: wxChart(parent, id, pos, size, style), m_total(0),
	m_mouseInWindow(false)
{
}

void wxDoughnutAndPieChartBase::Add(const ChartSliceData &slice)
{
	Add(slice, m_slices.size());
}

void wxDoughnutAndPieChartBase::Add(const ChartSliceData &slice, size_t index)
{
	Add(slice, index, false);
}

void wxDoughnutAndPieChartBase::Add(const ChartSliceData &slice, size_t index, bool silent)
{
	m_total += slice.GetValue();

	wxDouble x = (GetSize().GetX() / 2) - 2;
	wxDouble y = (GetSize().GetY() / 2) - 2;
	wxDouble outerRadius = ((x < y) ? x : y) - (GetOptions().GetSliceStrokeWidth() / 2);
	wxDouble innerRadius = outerRadius * ((wxDouble)GetOptions().GetPercentageInnerCutout()) / 100;

	SliceArc::ptr newSlice = SliceArc::ptr(new SliceArc(slice,
		x, y, 0, 0, outerRadius, innerRadius, GetOptions().GetSliceStrokeWidth()));
	m_slices.insert(m_slices.begin() + index, newSlice);
	if (!silent)
	{
	}
}

void wxDoughnutAndPieChartBase::Resize(const wxSize &size)
{
	for (size_t i = 0; i < m_slices.size(); ++i)
	{
		m_slices[i]->Resize(size, GetOptions());
	}
}

double wxDoughnutAndPieChartBase::CalculateCircumference(wxDouble value)
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

void wxDoughnutAndPieChartBase::GetSegmentsAtEvent(const wxPoint &point)
{
	m_activeSlices.clear();
	for (size_t i = 0; i < m_slices.size(); ++i)
	{
		if (m_slices[i]->HitTest(point))
		{
			m_activeSlices.push_back(m_slices[i]);
		}
	}
}

void wxDoughnutAndPieChartBase::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		double startAngle = 0.0;
		for (size_t i = 0; i < m_slices.size(); ++i)
		{
			SliceArc& currentSlice = *m_slices[i];

			double endAngle = startAngle + CalculateCircumference(currentSlice.GetValue());
			currentSlice.SetAngles(startAngle, endAngle);
			startAngle = endAngle;

			currentSlice.Draw(*gc);
		}

		for (size_t j = 0; j < m_activeSlices.size(); ++j)
		{
			wxChartTooltip tooltip(m_activeSlices[j]->GetTooltipPosition(), m_activeSlices[j]->GetTooltip());
			tooltip.Draw(*gc);
		}

		delete gc;
	}
}

void wxDoughnutAndPieChartBase::OnMouseEnter(wxMouseEvent& evt)
{
	if (GetOptions().ShowTooltips())
	{
		m_mouseInWindow = true;
		Refresh();
	}
}

void wxDoughnutAndPieChartBase::OnMouseOver(wxMouseEvent& evt)
{
	if (GetOptions().ShowTooltips())
	{
		GetSegmentsAtEvent(evt.GetPosition());
		Refresh();
	}
}

void wxDoughnutAndPieChartBase::OnMouseExit(wxMouseEvent& evt)
{
	if (GetOptions().ShowTooltips())
	{
		m_mouseInWindow = false;
		Refresh();
	}
}

BEGIN_EVENT_TABLE(wxDoughnutAndPieChartBase, wxChart)
	EVT_PAINT(wxDoughnutAndPieChartBase::OnPaint)
	EVT_ENTER_WINDOW(wxDoughnutAndPieChartBase::OnMouseEnter)
	EVT_MOTION(wxDoughnutAndPieChartBase::OnMouseOver)
	EVT_LEAVE_WINDOW(wxDoughnutAndPieChartBase::OnMouseExit)
END_EVENT_TABLE()
