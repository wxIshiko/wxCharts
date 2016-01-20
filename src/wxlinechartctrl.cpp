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

#include "wxlinechartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxLineChartDataset::wxLineChartDataset(const wxColor &dotColor,
									   const wxColor &dotStrokeColor,
									   const wxVector<wxDouble> &data)
	: m_dotColor(dotColor), m_dotStrokeColor(dotStrokeColor), 
	m_showLines(true), m_data(data)
{
}

const wxColor& wxLineChartDataset::GetDotColor() const
{
	return m_dotColor;
}

const wxColor& wxLineChartDataset::GetDotStrokeColor() const
{
	return m_dotStrokeColor;
}

bool wxLineChartDataset::ShowLines() const
{
	return m_showLines;
}

const wxVector<double>& wxLineChartDataset::GetData() const
{
	return m_data;
}

wxLineChartData::wxLineChartData(const wxVector<wxString> &labels)
	: m_labels(labels)
{
}

void wxLineChartData::AddDataset(wxLineChartDataset::ptr dataset)
{
	m_datasets.push_back(dataset);
}

const wxVector<wxString>& wxLineChartData::GetLabels() const
{
	return m_labels;
}

const wxVector<wxLineChartDataset::ptr>& wxLineChartData::GetDatasets() const
{
	return m_datasets;
}

wxLineChartCtrl::PointClass::PointClass(wxDouble value, 
										wxDouble x,
										wxDouble y, 
										wxDouble radius,
										unsigned int strokeWidth,
										const wxColor &strokeColor,
										const wxColor &fillColor)
	: wxChartPoint(x, y, radius, strokeWidth, strokeColor, fillColor),
	m_value(value)
{
}

wxDouble wxLineChartCtrl::PointClass::GetValue() const
{
	return m_value;
}

wxLineChartCtrl::wxLineChartCtrl(wxWindow *parent,
								 wxWindowID id,
								 const wxLineChartData &data,
								 const wxPoint &pos,
								 const wxSize &size,
								 long style)
	: wxChart(parent, id, pos, size, style), 
	m_grid(size, data.GetLabels(), GetMinValue(data.GetDatasets()),
	GetMaxValue(data.GetDatasets()), m_options.GetGridOptions())
{
	const wxVector<wxLineChartDataset::ptr>& datasets = data.GetDatasets();
	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxVector<double>& data = datasets[i]->GetData();
		for (size_t j = 0; j < data.size(); ++j)
		{
			m_points.push_back(PointClass::ptr(new PointClass(data[j], 20 + j * 10, 0,
				m_options.GetDotRadius(), m_options.GetDotStrokeWidth(),
				datasets[i]->GetDotStrokeColor(), datasets[i]->GetDotColor())));
		}
	}
}

wxLineChartCtrl::wxLineChartCtrl(wxWindow *parent,
								 wxWindowID id,
								 const wxLineChartData &data,
								 const wxLineChartOptions &options,
								 const wxPoint &pos,
								 const wxSize &size, 
								 long style)
	: wxChart(parent, id, pos, size, style), m_options(options),
	m_grid(size, data.GetLabels(), GetMinValue(data.GetDatasets()),
	GetMaxValue(data.GetDatasets()), m_options.GetGridOptions())
{
	const wxVector<wxLineChartDataset::ptr>& datasets = data.GetDatasets();
	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxVector<double>& data = datasets[i]->GetData();
		for (size_t j = 0; j < data.size(); ++j)
		{
			m_points.push_back(PointClass::ptr(new PointClass(data[j], 20 + j * 10, 0,
				m_options.GetDotRadius(), m_options.GetDotStrokeWidth(),
				datasets[i]->GetDotStrokeColor(), datasets[i]->GetDotColor())));
		}
	}
}

wxDouble wxLineChartCtrl::GetMinValue(const wxVector<wxLineChartDataset::ptr>& datasets)
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

wxDouble wxLineChartCtrl::GetMaxValue(const wxVector<wxLineChartDataset::ptr>& datasets)
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


void wxLineChartCtrl::Resize(const wxSize &size)
{
	m_grid.Resize(size);
}

void wxLineChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		if (true) // TODO : check if dataset ShowLines())
		{
			if (m_points.size() > 0)
			{
				wxGraphicsPath path = gc->CreatePath();

				const PointClass::ptr& point = m_points[0];
				wxPoint2DDouble position = m_grid.GetMapping().GetPointPosition(0, point->GetValue());
				path.MoveToPoint(position);

				for (size_t i = 1; i < m_points.size(); ++i)
				{
					const PointClass::ptr& point = m_points[i];
					wxPoint2DDouble position = m_grid.GetMapping().GetPointPosition(i, point->GetValue());
					path.AddLineToPoint(position);
				}

				//path.CloseSubpath();

				//wxBrush brush(m_fillColor);
				//gc.SetBrush(brush);
				//gc.FillPath(path);

				wxPen pen(*wxBLUE, 2);
				gc->SetPen(pen);
				gc->StrokePath(path);
			}
		}

		for (size_t i = 0; i < m_points.size(); ++i)
		{
			const PointClass::ptr& point = m_points[i];
			point->SetPosition(m_grid.GetMapping().GetPointPosition(i, point->GetValue()));
			point->Draw(*gc);
		}

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxLineChartCtrl, wxChart)
	EVT_PAINT(wxLineChartCtrl::OnPaint)
END_EVENT_TABLE()
