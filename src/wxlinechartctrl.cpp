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

wxLineChartDataset::wxLineChartDataset(const wxString &label,
									   const wxColor &dotColor,
									   const wxColor &dotStrokeColor,
									   const wxColor &fillColor,
									   const wxVector<wxDouble> &data)
	: m_label(label), m_showDots(true), m_dotColor(dotColor), 
	m_dotStrokeColor(dotStrokeColor), m_showLine(true), 
	m_lineColor(dotColor), m_fill(true), m_fillColor(fillColor), 
	m_data(data)
{
}

const wxString& wxLineChartDataset::GetLabel() const
{
	return m_label;
}

bool wxLineChartDataset::ShowDots() const
{
	return m_showDots;
}

const wxColor& wxLineChartDataset::GetDotColor() const
{
	return m_dotColor;
}

const wxColor& wxLineChartDataset::GetDotStrokeColor() const
{
	return m_dotStrokeColor;
}

bool wxLineChartDataset::ShowLine() const
{
	return m_showLine;
}

const wxColor& wxLineChartDataset::GetLineColor() const
{
	return m_lineColor;
}

bool wxLineChartDataset::Fill() const
{
	return m_fill;
}

const wxColor& wxLineChartDataset::GetFillColor() const
{
	return m_fillColor;
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
										const wxColor &fillColor,
										wxDouble hitDetectionRange)
	: wxChartPoint(x, y, radius, strokeWidth, strokeColor, fillColor),
	m_value(value), m_hitDetectionRange(hitDetectionRange)
{
}

bool wxLineChartCtrl::PointClass::HitTest(const wxPoint &point) const
{
	wxDouble distance = (point.x - GetPosition().m_x);
	if (distance < 0)
	{
		distance = -distance;
	}
	return (distance < m_hitDetectionRange);
}

wxDouble wxLineChartCtrl::PointClass::GetValue() const
{
	return m_value;
}

wxLineChartCtrl::Dataset::Dataset(bool showDots,
								  bool showLine,
								  const wxColor &lineColor,
								  bool fill, 
								  const wxColor &fillColor)
	: m_showDots(showDots), m_showLine(showLine), 
	m_lineColor(lineColor), m_fill(fill), m_fillColor(fillColor)
{
}

bool wxLineChartCtrl::Dataset::ShowDots() const
{
	return m_showDots;
}

bool wxLineChartCtrl::Dataset::ShowLine() const
{
	return m_showLine;
}

const wxColor& wxLineChartCtrl::Dataset::GetLineColor() const
{
	return m_lineColor;
}

bool wxLineChartCtrl::Dataset::Fill() const
{
	return m_fill;
}

const wxColor& wxLineChartCtrl::Dataset::GetFillColor() const
{
	return m_fillColor;
}

const wxVector<wxLineChartCtrl::PointClass::ptr>& wxLineChartCtrl::Dataset::GetPoints() const
{
	return m_points;
}

void wxLineChartCtrl::Dataset::AppendPoint(PointClass::ptr point)
{
	m_points.push_back(point);
}

wxLineChartCtrl::wxLineChartCtrl(wxWindow *parent,
								 wxWindowID id,
								 const wxLineChartData &data,
								 const wxPoint &pos,
								 const wxSize &size,
								 long style)
	: wxChartCtrl(parent, id, pos, size, style), 
	m_grid(size, data.GetLabels(), GetMinValue(data.GetDatasets()),
	GetMaxValue(data.GetDatasets()), m_options.GetGridOptions())
{
	Initialize(data);
}

wxLineChartCtrl::wxLineChartCtrl(wxWindow *parent,
								 wxWindowID id,
								 const wxLineChartData &data,
								 const wxLineChartOptions &options,
								 const wxPoint &pos,
								 const wxSize &size, 
								 long style)
	: wxChartCtrl(parent, id, pos, size, style), m_options(options),
	m_grid(size, data.GetLabels(), GetMinValue(data.GetDatasets()),
	GetMaxValue(data.GetDatasets()), m_options.GetGridOptions())
{
	Initialize(data);
}

void wxLineChartCtrl::Initialize(const wxLineChartData &data)
{
	const wxVector<wxLineChartDataset::ptr>& datasets = data.GetDatasets();
	for (size_t i = 0; i < datasets.size(); ++i)
	{
		Dataset::ptr newDataset(new Dataset(datasets[i]->ShowDots(),
			datasets[i]->ShowLine(), datasets[i]->GetLineColor(),
			datasets[i]->Fill(), datasets[i]->GetFillColor()));
		
		const wxVector<wxDouble>& data = datasets[i]->GetData();
		for (size_t j = 0; j < data.size(); ++j)
		{
			newDataset->AppendPoint(PointClass::ptr(new PointClass(data[j], 20 + j * 10, 0,
				m_options.GetDotRadius(), m_options.GetDotStrokeWidth(),
				datasets[i]->GetDotStrokeColor(), datasets[i]->GetDotColor(),
				m_options.GetHitDetectionRange())));
		}

		m_datasets.push_back(newDataset);
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

wxSharedPtr<wxVector<const wxChartElement*> > wxLineChartCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	for (size_t i = 0; i < m_datasets.size(); ++i)
	{
		const wxVector<PointClass::ptr>& points = m_datasets[i]->GetPoints();
		for (size_t j = 0; j < points.size(); ++j)
		{
			if (points[j]->HitTest(point))
			{
				activeElements->push_back(points[j].get());
			}
		}
	}
	return activeElements;
}

void wxLineChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		for (size_t i = 0; i < m_datasets.size(); ++i)
		{
			const wxVector<PointClass::ptr>& points = m_datasets[i]->GetPoints();

			wxGraphicsPath path = gc->CreatePath();

			if (points.size() > 0)
			{
				const PointClass::ptr& point = points[0];
				wxPoint2DDouble firstPosition = m_grid.GetMapping().GetPointPosition(0, point->GetValue());
				path.MoveToPoint(firstPosition);

				wxPoint2DDouble lastPosition;
				for (size_t j = 1; j < points.size(); ++j)
				{
					const PointClass::ptr& point = points[j];
					lastPosition = m_grid.GetMapping().GetPointPosition(j, point->GetValue());
					path.AddLineToPoint(lastPosition);
				}

				if (m_datasets[i]->ShowLine())
				{
					wxPen pen(m_datasets[i]->GetLineColor(), m_options.GetLineWidth());
					gc->SetPen(pen);
				}
				else
				{
					// TODO : transparent pen
				}

				gc->StrokePath(path);

				path.AddLineToPoint(lastPosition.m_x, m_grid.GetMapping().GetEndPoint());
				path.AddLineToPoint(firstPosition.m_x, m_grid.GetMapping().GetEndPoint());
				path.CloseSubpath();

				wxBrush brush(m_datasets[i]->GetFillColor());
				gc->SetBrush(brush);
				gc->FillPath(path);
			}

			if (m_datasets[i]->ShowDots())
			{
				for (size_t j = 0; j < points.size(); ++j)
				{
					const PointClass::ptr& point = points[j];
					point->SetPosition(m_grid.GetMapping().GetPointPosition(j, point->GetValue()));
					point->Draw(*gc);
				}
			}
		}

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxLineChartCtrl, wxChartCtrl)
	EVT_PAINT(wxLineChartCtrl::OnPaint)
END_EVENT_TABLE()
