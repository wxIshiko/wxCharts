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

#include "wxbarchartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxBarChartDataset::wxBarChartDataset(const wxVector<wxDouble> &data)
	: m_data(data)
{
}

const wxVector<wxDouble>& wxBarChartDataset::GetData() const
{
	return m_data;
}

wxBarChartData::wxBarChartData(const wxVector<wxString> &labels)
	: m_labels(labels)
{
}

void wxBarChartData::AddDataset(wxBarChartDataset::ptr dataset)
{
	m_datasets.push_back(dataset);
}

const wxVector<wxString>& wxBarChartData::GetLabels() const
{
	return m_labels;
}

const wxVector<wxBarChartDataset::ptr>& wxBarChartData::GetDatasets() const
{
	return m_datasets;
}

wxBarChartCtrl::ScaleClass::ScaleClass(const wxSize &size,
									   const wxVector<wxString> &labels,
									   wxDouble minValue, 
									   wxDouble maxValue,
									   const wxChartGridOptions& options)
	: wxChartGrid(size, labels, minValue, maxValue, options)
{
}

wxDouble wxBarChartCtrl::ScaleClass::CalculateBarX(size_t datasetCount,
												   size_t datasetIndex,
												   size_t barIndex)
{
	/*
	wxDouble xWidth = CalculateBaseWidth();
	wxDouble xAbsolute = CalculateX(barIndex) - (xWidth / 2);
	wxDouble barWidth = CalculateBarWidth(datasetCount);

	return xAbsolute + (barWidth * datasetIndex) + (datasetIndex * 1) + barWidth / 2;*/
	return 0;
}

double wxBarChartCtrl::ScaleClass::CalculateBaseWidth()
{
	return 0;// (CalculateX(1) - CalculateX(0)) - (2 * 5);
}

double wxBarChartCtrl::ScaleClass::CalculateBarWidth(size_t datasetCount)
{
	double baseWidth = CalculateBaseWidth() - ((datasetCount - 1) * 1);

	return (baseWidth / datasetCount);
}

wxBarChartCtrl::BarClass::BarClass(wxDouble x, 
								   wxDouble y,
								   const wxColor &fillColor,
								   const wxColor &strokeColor)
	: wxChartRectangle(x, y, wxChartRectangleOptions(fillColor, strokeColor))
{
}

wxBarChartCtrl::wxBarChartCtrl(wxWindow *parent,
							   wxWindowID id,
							   const wxBarChartData &data,
							   const wxPoint &pos,
							   const wxSize &size,
							   long style)
	: wxChartCtrl(parent, id, pos, size, style), 
	m_grid(size, data.GetLabels(), 0, 0, m_options.GetGridOptions())
{
}

const wxBarChartOptions& wxBarChartCtrl::GetOptions() const
{
	return m_options;
}

void wxBarChartCtrl::AddData(const wxVector<wxDouble>& data)
{
	Dataset::ptr newDataset(new Dataset());
	newDataset->bars.insert(newDataset->bars.begin(), BarClass(25, 50, wxColor(220, 220, 220), wxColor(220, 220, 220)));
	m_datasets.insert(m_datasets.end(), newDataset);
}

void wxBarChartCtrl::Resize(const wxSize &size)
{
	m_grid.Resize(size);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxBarChartCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	return activeElements;
}

void wxBarChartCtrl::OnPaint(wxPaintEvent &evt)
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
			for (size_t j = 0; j < currentDataset.bars.size(); ++j)
			{
				//currentDataset.bars[j].x = m_grid.CalculateBarX(m_datasets.size(), i, j);
				//currentDataset.bars[j].base = 50;
				currentDataset.bars[j].Draw(*gc);
			}
		}

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxBarChartCtrl, wxChartCtrl)
	EVT_PAINT(wxBarChartCtrl::OnPaint)
END_EVENT_TABLE()
