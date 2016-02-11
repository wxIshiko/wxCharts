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

#include "wxstackedbarchartctrl.h"
#include <wx/dcbuffer.h>

wxStackedBarChartDataset::wxStackedBarChartDataset(const wxColor &fillColor, 
												   const wxColor &strokeColor,
												   const wxVector<wxDouble> &data)
	: m_fillColor(fillColor), m_strokeColor(strokeColor), m_data(data)
{
}

const wxColor& wxStackedBarChartDataset::GetFillColor() const
{
	return m_fillColor;
}

const wxColor& wxStackedBarChartDataset::GetStrokeColor() const
{
	return m_strokeColor;
}

const wxVector<wxDouble>& wxStackedBarChartDataset::GetData() const
{
	return m_data;
}

wxStackedBarChartData::wxStackedBarChartData(const wxVector<wxString> &labels)
	: m_labels(labels)
{
}

void wxStackedBarChartData::AddDataset(wxStackedBarChartDataset::ptr dataset)
{
	m_datasets.push_back(dataset);
}

const wxVector<wxString>& wxStackedBarChartData::GetLabels() const
{
	return m_labels;
}

const wxVector<wxStackedBarChartDataset::ptr>& wxStackedBarChartData::GetDatasets() const
{
	return m_datasets;
}

wxStackedBarChartCtrl::Bar::Bar(wxDouble value,
								wxDouble x,
								wxDouble y,
								const wxColor &fillColor,
								const wxColor &strokeColor)
	: wxChartRectangle(x, y, wxChartRectangleOptions(fillColor, strokeColor)),
	m_value(value)
{
}

wxDouble wxStackedBarChartCtrl::Bar::GetValue() const
{
	return m_value;
}

wxStackedBarChartCtrl::Dataset::Dataset()
{
}

const wxVector<wxStackedBarChartCtrl::Bar::ptr>& wxStackedBarChartCtrl::Dataset::GetBars() const
{
	return m_bars;
}

void wxStackedBarChartCtrl::Dataset::AppendBar(Bar::ptr bar)
{
	m_bars.push_back(bar);
}

wxStackedBarChartCtrl::wxStackedBarChartCtrl(wxWindow *parent,
											 wxWindowID id,
											 const wxStackedBarChartData &data,
											 const wxPoint &pos,
											 const wxSize &size,
											 long style)
	: wxChartCtrl(parent, id, pos, size, style), 
	m_grid(size, data.GetLabels(), GetCumulativeMinValue(data.GetDatasets()),
		GetCumulativeMaxValue(data.GetDatasets()), m_options.GetGridOptions())
{
	const wxVector<wxStackedBarChartDataset::ptr>& datasets = data.GetDatasets();
	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxStackedBarChartDataset& dataset = *datasets[i];
		Dataset::ptr newDataset(new Dataset());

		const wxVector<wxDouble>& data = dataset.GetData();
		for (size_t j = 0; j < data.size(); ++j)
		{
			newDataset->AppendBar(Bar::ptr(new Bar(data[j], 25, 50, dataset.GetFillColor(), dataset.GetStrokeColor())));
		}

		m_datasets.push_back(newDataset);
	}
}

const wxStackedBarChartOptions& wxStackedBarChartCtrl::GetOptions() const
{
	return m_options;
}

wxDouble wxStackedBarChartCtrl::GetCumulativeMinValue(const wxVector<wxStackedBarChartDataset::ptr>& datasets)
{
	wxDouble result = 0;
	
	size_t i = 0;
	while (true)
	{
		wxDouble sum = 0;
		bool stop = true;
		for (size_t j = 0; j < datasets.size(); ++j)
		{
			const wxStackedBarChartDataset& dataset = *datasets[j];
			if (i < dataset.GetData().size())
			{
				sum += dataset.GetData()[i];
				stop = false;
			}
		}
		if (sum < result)
		{
			result = sum;
		}
		if (stop)
		{
			break;
		}
		++i;
	}

	return result;
}

wxDouble wxStackedBarChartCtrl::GetCumulativeMaxValue(const wxVector<wxStackedBarChartDataset::ptr>& datasets)
{
	wxDouble result = 0;
	
	size_t i = 0;
	while (true)
	{
		wxDouble sum = 0;
		bool stop = true;
		for (size_t j = 0; j < datasets.size(); ++j)
		{
			const wxStackedBarChartDataset& dataset = *datasets[j];
			if (i < dataset.GetData().size())
			{
				sum += dataset.GetData()[i];
				stop = false;
			}
		}
		if (sum > result)
		{
			result = sum;
		}
		if (stop)
		{
			break;
		}
		++i;
	}

	return result;
}

void wxStackedBarChartCtrl::Resize(const wxSize &size)
{
	m_grid.Resize(size);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxStackedBarChartCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	return activeElements;
}

void wxStackedBarChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		for (size_t i = 0; i < m_datasets.size(); ++i)
		{
			for (size_t i = 0; i < m_datasets.size(); ++i)
			{
				Dataset& currentDataset = *m_datasets[i];
				for (size_t j = 0; j < currentDataset.GetBars().size(); ++j)
				{
					Bar& bar = *(currentDataset.GetBars()[j]);

					wxPoint2DDouble upperLeftCornerPosition = m_grid.GetMapping().GetWindowPosition(j, bar.GetValue());
					upperLeftCornerPosition.m_x += m_options.GetBarSpacing();
					wxPoint2DDouble upperRightCornerPosition = m_grid.GetMapping().GetWindowPosition(j + 1, bar.GetValue());
					upperRightCornerPosition.m_x -= m_options.GetBarSpacing();

					bar.SetPosition(upperLeftCornerPosition);
					bar.SetSize(upperRightCornerPosition.m_x - upperLeftCornerPosition.m_x, 
						m_grid.GetMapping().GetEndPoint() - upperLeftCornerPosition.m_y);
				}
			}

			for (size_t i = 0; i < m_datasets.size(); ++i)
			{
				Dataset& currentDataset = *m_datasets[i];
				for (size_t j = 0; j < currentDataset.GetBars().size(); ++j)
				{
					currentDataset.GetBars()[j]->Draw(*gc);
				}
			}
		}

		DrawTooltips(*gc);

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxStackedBarChartCtrl, wxChartCtrl)
	EVT_PAINT(wxStackedBarChartCtrl::OnPaint)
END_EVENT_TABLE()
