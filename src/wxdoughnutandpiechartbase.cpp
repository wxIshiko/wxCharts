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

ChartSlice::ChartSlice(double value,
					   const wxColor &color)
	: m_value(value), m_color(color)
{
}

double ChartSlice::GetValue() const
{
	return m_value;
}

const wxColor& ChartSlice::GetColor() const
{
	return m_color;
}

wxDoughnutAndPieChartOptionsBase::wxDoughnutAndPieChartOptionsBase(unsigned int percentageInnerCutout)
	: m_segmentStrokeWidth(2), m_percentageInnerCutout(percentageInnerCutout), m_showTooltips(true)
{
}

unsigned int wxDoughnutAndPieChartOptionsBase::GetSegmentStrokeWidth() const
{
	return m_segmentStrokeWidth;
}

unsigned int wxDoughnutAndPieChartOptionsBase::GetPercentageInnerCutout() const
{
	return m_percentageInnerCutout;
}

bool wxDoughnutAndPieChartOptionsBase::ShowTooltips() const
{
	return m_showTooltips;
}

wxDoughnutAndPieChartBase::SliceArc::SliceArc(const ChartSlice &slice,
											  double x,
											  double y,
											  double startAngle,
											  double endAngle,
											  double outerRadius,
											  double innerRadius,
											  unsigned int strokeWidth)
	: wxChartArc(x, y, startAngle, endAngle, outerRadius, innerRadius, strokeWidth, slice.GetColor()),
	value(slice.GetValue())
{
}

void wxDoughnutAndPieChartBase::SliceArc::Resize(const wxSize &size,
												 const wxDoughnutAndPieChartOptionsBase& options)
{
	double x = (size.GetX() / 2) - 2;
	double y = (size.GetY() / 2) - 2;
	double outerRadius = ((x < y) ? x : y) - (GetStrokeWidth() / 2);
	double innerRadius = outerRadius * ((double)options.GetPercentageInnerCutout()) / 100;

	SetCenter(x, y);
	SetRadiuses(outerRadius, innerRadius);
}

wxDoughnutAndPieChartBase::wxDoughnutAndPieChartBase(wxWindow *parent,
													 wxWindowID id,
													 const wxPoint &pos,
													 const wxSize &size,
													 long style)
	: wxControl(parent, id, pos, size, style), m_total(0),
	m_mouseInWindow(false)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(*wxWHITE);
}

void wxDoughnutAndPieChartBase::Add(const ChartSlice &slice)
{
	Add(slice, m_slices.size());
}

void wxDoughnutAndPieChartBase::Add(const ChartSlice &slice, size_t index)
{
	Add(slice, index, false);
}

void wxDoughnutAndPieChartBase::Add(const ChartSlice &slice, size_t index, bool silent)
{
	m_total += slice.GetValue();

	double x = (GetSize().GetX() / 2) - 2;
	double y = (GetSize().GetY() / 2) - 2;
	double outerRadius = ((x < y) ? x : y) - (GetOptions().GetSegmentStrokeWidth() / 2);
	double innerRadius = outerRadius * ((double)GetOptions().GetPercentageInnerCutout()) / 100;

	SliceArc::ptr newSlice = std::make_shared<SliceArc>(slice,
		x, y, 0, 0, outerRadius, innerRadius, GetOptions().GetSegmentStrokeWidth());
	m_slices.insert(m_slices.begin() + index, newSlice);
	if (!silent)
	{
	}
}

double wxDoughnutAndPieChartBase::CalculateCircumference(double value)
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
	if (point.x > 100)
	{
		m_activeSlices.push_back(m_slices[0]);
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

			double endAngle = startAngle + CalculateCircumference(currentSlice.value);
			currentSlice.SetAngles(startAngle, endAngle);
			startAngle = endAngle;

			currentSlice.Draw(*gc);
		}

		if (m_activeSlices.size() > 0)
		{
			wxChartTooltip tooltip(m_activeSlices[0]->GetTooltipPosition());
			tooltip.Draw(*gc);
		}

		delete gc;
	}
}

void wxDoughnutAndPieChartBase::OnSize(wxSizeEvent& evt)
{
	for (size_t i = 0; i < m_slices.size(); ++i)
	{
		m_slices[i]->Resize(evt.GetSize(), GetOptions());
	}
	Refresh();
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

BEGIN_EVENT_TABLE(wxDoughnutAndPieChartBase, wxControl)
	EVT_PAINT(wxDoughnutAndPieChartBase::OnPaint)
	EVT_SIZE(wxDoughnutAndPieChartBase::OnSize)
	EVT_ENTER_WINDOW(wxDoughnutAndPieChartBase::OnMouseEnter)
	EVT_MOTION(wxDoughnutAndPieChartBase::OnMouseOver)
	EVT_LEAVE_WINDOW(wxDoughnutAndPieChartBase::OnMouseExit)
END_EVENT_TABLE()
