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

#ifndef _WX_CHARTS_WXLINECHARTCTRL_H_
#define _WX_CHARTS_WXLINECHARTCTRL_H_

#include "wxchartgrid.h"
#include "wxchartpoint.h"
#include <wx/control.h>
#include <vector>
#include <memory>

class wxLineChartOptions
{
public:
	wxLineChartOptions();

	unsigned int GetGridLineWidth() const;
	const wxColor& GetGridLineColor() const;
	bool ShowDots() const;
	double GetDotRadius() const;
	unsigned int GetDotStrokeWidth() const;

private:
	unsigned int m_gridLineWidth;
	wxColor m_gridLineColor;
	bool m_showDots;
	double m_dotRadius;
	unsigned int m_dotStrokeWidth;
};

class wxLineChartDataset
{
public:
	typedef std::shared_ptr<wxLineChartDataset> ptr;

	wxLineChartDataset(const wxColor &dotColor,
		const wxColor &dotStrokeColor, const std::vector<double> &data);

	const wxColor& GetDotColor() const;
	const wxColor& GetDotStrokeColor() const;
	const std::vector<double>& data() const;

private:
	wxColor m_dotColor;
	wxColor m_dotStrokeColor;
	std::vector<double> m_data;
};

class wxLineChartData
{
public:
	wxLineChartData(const std::vector<std::string> &labels);

	void AddDataset(wxLineChartDataset::ptr dataset);

	const std::vector<std::string>& GetLabels() const;
	const std::vector<wxLineChartDataset::ptr>& GetDatasets() const;

	double GetMinValue() const;
	double GetMaxValue() const;

private:
	std::vector<std::string> m_labels;
	std::vector<wxLineChartDataset::ptr> m_datasets;
};

class wxLineChartCtrl : public wxControl
{
public:
	wxLineChartCtrl(wxWindow *parent, wxWindowID id, const wxLineChartData& data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, 
		long style = 0);

	double GetMinValue() const;
	double GetMaxValue() const;

private:
	void OnPaint(wxPaintEvent &evt);
	void OnSize(wxSizeEvent& evt);

private:
	struct PointClass : public wxChartPoint
	{
		typedef std::shared_ptr<PointClass> ptr;

		PointClass(double x, double y, double radius,
			unsigned int strokeWidth, const wxColor &strokeColor,
			const wxColor &fillColor);
	};

private:
	wxLineChartOptions m_options;
	wxChartGrid m_grid;
	std::vector<PointClass::ptr> m_points;
	double m_minValue;
	double m_maxValue;

	DECLARE_EVENT_TABLE();
};

#endif
