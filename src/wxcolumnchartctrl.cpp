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

/*
	Part of this file were copied from the Chart.js project (http://chartjs.org/)
	and translated into C++.

	The files of the Chart.js project have the following copyright and license.

	Copyright (c) 2013-2016 Nick Downie
	Released under the MIT license
	https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

#include "wxcolumnchartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <sstream>

wxColumnChartCtrl::Column::Column(wxDouble value,
								  const wxChartTooltipProvider::ptr tooltipProvider,
								  wxDouble x,
								  wxDouble y,
								  const wxColor &fillColor,
								  const wxColor &strokeColor,
								  int directions)
	: wxChartRectangle(x, y, tooltipProvider, wxChartRectangleOptions(fillColor, strokeColor, directions)),
	m_value(value)
{
}

wxDouble wxColumnChartCtrl::Column::GetValue() const
{
	return m_value;
}

wxColumnChartCtrl::Dataset::Dataset()
{
}

const wxVector<wxColumnChartCtrl::Column::ptr>& wxColumnChartCtrl::Dataset::GetColumns() const
{
	return m_columns;
}

void wxColumnChartCtrl::Dataset::AppendColumn(Column::ptr column)
{
	m_columns.push_back(column);
}

wxColumnChartCtrl::wxColumnChartCtrl(wxWindow *parent,
									 wxWindowID id,
									 const wxBarChartData &data,
									 const wxPoint &pos,
									 const wxSize &size,
									 long style)
	: wxChartCtrl(parent, id, pos, size, style), 
	m_grid(
		wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetRight()), 
		size, data.GetLabels(), GetMinValue(data.GetDatasets()),
		GetMaxValue(data.GetDatasets()), m_options.GetGridOptions()
		)
{
	const wxVector<wxBarChartDataset::ptr>& datasets = data.GetDatasets();
	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxBarChartDataset& dataset = *datasets[i];
		Dataset::ptr newDataset(new Dataset());

		const wxVector<wxDouble>& datasetData = dataset.GetData();
		for (size_t j = 0; j < datasetData.size(); ++j)
		{
			std::stringstream tooltip;
			tooltip << datasetData[j];
			wxChartTooltipProvider::ptr tooltipProvider(
				new wxChartTooltipProviderStatic(data.GetLabels()[j], tooltip.str(), dataset.GetFillColor())
				);

			newDataset->AppendColumn(Column::ptr(new Column(
				datasetData[j], tooltipProvider, 25, 50, dataset.GetFillColor(), dataset.GetStrokeColor(), wxALL
				)));
		}

		m_datasets.push_back(newDataset);
	}
}

const wxColumnChartOptions& wxColumnChartCtrl::GetOptions() const
{
	return m_options;
}

wxDouble wxColumnChartCtrl::GetMinValue(const wxVector<wxBarChartDataset::ptr>& datasets)
{
	wxDouble result = 0;
	bool foundValue = false;

	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxVector<wxDouble>& values = datasets[i]->GetData();
		for (size_t j = 0; j < values.size(); ++j)
		{
			if (!foundValue)
			{
				result = values[j];
				foundValue = true;
			}
			else if (result > values[j])
			{
				result = values[j];
			}
		}
	}

	return result;
}

wxDouble wxColumnChartCtrl::GetMaxValue(const wxVector<wxBarChartDataset::ptr>& datasets)
{
	wxDouble result = 0;
	bool foundValue = false;

	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxVector<wxDouble>& values = datasets[i]->GetData();
		for (size_t j = 0; j < values.size(); ++j)
		{
			if (!foundValue)
			{
				result = values[j];
				foundValue = true;
			}
			else if (result < values[j])
			{
				result = values[j];
			}
		}
	}

	return result;
}

void wxColumnChartCtrl::Resize(const wxSize &size)
{
	m_grid.Resize(size);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxColumnChartCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	return activeElements;
}

void wxColumnChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		for (size_t i = 0; i < m_datasets.size(); ++i)
		{
			Dataset& currentDataset = *m_datasets[i];
			for (size_t j = 0; j < currentDataset.GetColumns().size(); ++j)
			{
				Column& column = *(currentDataset.GetColumns()[j]);
				wxPoint2DDouble position = m_grid.GetMapping().GetWindowPosition(j, column.GetValue());
				column.SetPosition(position);
				column.SetSize(20, m_grid.GetMapping().GetStartPoint().m_y - position.m_y);
			}
		}

		for (size_t i = 0; i < m_datasets.size(); ++i)
		{
			Dataset& currentDataset = *m_datasets[i];
			for (size_t j = 0; j < currentDataset.GetColumns().size(); ++j)
			{	
				currentDataset.GetColumns()[j]->Draw(*gc);
			}
		}

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxColumnChartCtrl, wxChartCtrl)
	EVT_PAINT(wxColumnChartCtrl::OnPaint)
END_EVENT_TABLE()
