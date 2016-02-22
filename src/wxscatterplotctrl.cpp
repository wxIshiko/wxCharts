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

#include "wxscatterplotctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxScatterPlotDataset::wxScatterPlotDataset(wxVector<wxPoint2DDouble> &data)
    : m_data(data)
{
}

wxScatterPlotData::wxScatterPlotData()
{
}

void wxScatterPlotData::AddDataset(wxScatterPlotDataset::ptr dataset)
{
    m_datasets.push_back(dataset);
}

wxScatterPlotCtrl::wxScatterPlotCtrl(wxWindow *parent,
									 wxWindowID id,
                                     const wxScatterPlotData &data,
									 const wxPoint &pos,
									 const wxSize &size,
									 long style)
	: wxChartCtrl(parent, id, pos, size, style),
	m_grid(
		wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetRight()),
		size, -10, 30, 0,
		20, m_options.GetGridOptions()
		)
{
}

const wxScatterPlotOptions& wxScatterPlotCtrl::GetOptions() const
{
	return m_options;
}

void wxScatterPlotCtrl::Resize(const wxSize &size)
{
	wxSize newSize(
		size.GetWidth() - m_options.GetPadding().GetTotalHorizontalPadding(),
		size.GetHeight() - m_options.GetPadding().GetTotalVerticalPadding()
		);
	m_grid.Resize(newSize);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxScatterPlotCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	return activeElements;
}

void wxScatterPlotCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxScatterPlotCtrl, wxChartCtrl)
	EVT_PAINT(wxScatterPlotCtrl::OnPaint)
END_EVENT_TABLE()
