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

wxStackedBarChartCtrl::wxStackedBarChartCtrl(wxWindow *parent,
											 wxWindowID id,
											 const wxStackedBarChartData &data,
											 const wxPoint &pos,
											 const wxSize &size,
											 long style)
	: wxChartCtrl(parent, id, pos, size, style)
{
}

const wxStackedBarChartOptions& wxStackedBarChartCtrl::GetOptions() const
{
	return m_options;
}

void wxStackedBarChartCtrl::Resize(const wxSize &size)
{
}

wxSharedPtr<wxVector<const wxChartElement*> > wxStackedBarChartCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	return activeElements;
}
