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

#include "wxlinechartctrl.h"
#include <wx/dcclient.h>
#include <wx/graphics.h>

wxLineChartOptions::wxLineChartOptions()
	: m_gridLineWidth(1), m_gridLineColor(0, 0, 0, 0x20),
	m_showDots(true), m_dotRadius(4), m_dotStrokeWidth(1)
{
}

unsigned int wxLineChartOptions::GetGridLineWidth() const
{
	return m_gridLineWidth;
}

const wxColor& wxLineChartOptions::GetGridLineColor() const
{
	return m_gridLineColor;
}

bool wxLineChartOptions::ShowDots() const
{
	return m_showDots;
}

double wxLineChartOptions::GetDotRadius() const
{
	return m_dotRadius;
}

unsigned int wxLineChartOptions::GetDotStrokeWidth() const
{
	return m_dotStrokeWidth;
}

wxLineChartDataset::wxLineChartDataset(const wxColor &dotColor,
									   const wxColor &dotStrokeColor,
									   const std::vector<double> &data)
	: m_dotColor(dotColor), m_dotStrokeColor(dotStrokeColor), m_data(data)
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

const std::vector<double>& wxLineChartDataset::data() const
{
	return m_data;
}

wxLineChartData::wxLineChartData(const std::vector<std::string> &labels)
	: m_labels(labels)
{
}

void wxLineChartData::AddDataset(wxLineChartDataset::ptr dataset)
{
	m_datasets.push_back(dataset);
}

const std::vector<std::string>& wxLineChartData::GetLabels() const
{
	return m_labels;
}

const std::vector<wxLineChartDataset::ptr>& wxLineChartData::GetDatasets() const
{
	return m_datasets;
}

double wxLineChartData::GetMinValue() const
{
	double result = 0;
	bool foundAtLeastOneValue = false;

	for (size_t i = 0; i < m_datasets.size(); ++i)
	{
	}

	return result;
}

double wxLineChartData::GetMaxValue() const
{
	double result = 0;
	bool foundAtLeastOneValue = false;

	for (size_t i = 0; i < m_datasets.size(); ++i)
	{
	}

	return result;
}

wxLineChartCtrl::PointClass::PointClass(double x, 
										double y, 
										double radius,
										unsigned int strokeWidth,
										const wxColor &strokeColor,
										const wxColor &fillColor)
	: wxChartPoint(x, y, radius, strokeWidth, strokeColor, fillColor)
{
}

wxLineChartCtrl::wxLineChartCtrl(wxWindow *parent,
								 wxWindowID id,
								 const wxLineChartData& data,
								 const wxPoint &pos,
								 const wxSize &size,
								 long style)
	: wxControl(parent, id, pos, size, style), 
	m_grid(data.GetLabels(), m_options.GetGridLineWidth(),m_options.GetGridLineColor()),
	m_minValue(data.GetMinValue()), m_maxValue(data.GetMaxValue())
{
	SetBackgroundColour(*wxWHITE);

	const std::vector<wxLineChartDataset::ptr>& datasets = data.GetDatasets();
	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const std::vector<double>& data = datasets[i]->data();
		for (size_t j = 0; j < data.size(); ++j)
		{
			m_points.push_back(std::make_shared<PointClass>(20+j*10, 50+data[j],
				m_options.GetDotRadius(), m_options.GetDotStrokeWidth(),
				datasets[i]->GetDotStrokeColor(), datasets[i]->GetDotColor()));
		}
	}
}

double wxLineChartCtrl::GetMinValue() const
{
	return m_minValue;
}

double wxLineChartCtrl::GetMaxValue() const
{
	return m_maxValue;
}

void wxLineChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxPaintDC dc(this);
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		for (size_t i = 0; i < m_points.size(); ++i)
		{
			m_points[i]->Draw(*gc);
		}

		delete gc;
	}
}

void wxLineChartCtrl::OnSize(wxSizeEvent& evt)
{
	Refresh();
}

BEGIN_EVENT_TABLE(wxLineChartCtrl, wxControl)
	EVT_PAINT(wxLineChartCtrl::OnPaint)
	EVT_SIZE(wxLineChartCtrl::OnSize)
END_EVENT_TABLE()
