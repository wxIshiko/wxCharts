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

#ifndef _WX_CHARTS_WXDOUGHNUTCHARTCTRL_H_
#define _WX_CHARTS_WXDOUGHNUTCHARTCTRL_H_

#include "wxchartarc.h"
#include <wx/control.h>
#include <vector>
#include <memory>

class wxDougnutChartOptions
{
public:
	wxDougnutChartOptions();

	unsigned int SegmentStrokeWidth() const;
	unsigned int PercentageInnerCutout() const;

private:
	// The width of each segment stroke, this will increase the 
	// space between the segments themselves.
	unsigned int m_segmentStrokeWidth;
	// The percentage of the chart that we cut out of the middle.
	unsigned int m_percentageInnerCutout;
};

class wxDoughnutChartCtrl : public wxControl
{
public:
	struct Segment
	{
		Segment(double value, const wxColor &color);

		double value;
		wxColor color;
	};

public:
	wxDoughnutChartCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize, long style = 0);

	void AddData(const Segment &segment);
	void AddData(const Segment &segment, size_t index);
	void AddData(const Segment &segment, size_t index, bool silent);

private:
	double CalculateCircumference(double value);
	void OnAddOrRemoveData();

	void OnPaint(wxPaintEvent &evt);
	void OnSize(wxSizeEvent& evt);

private:
	struct SegmentArc : public wxChartArc
	{
		typedef std::shared_ptr<SegmentArc> ptr;

		SegmentArc(const Segment &segment, double x, double y, 
			double startAngle, double endAngle, double outerRadius, 
			double innerRadius, unsigned int strokeWidth);

		void Resize(const wxSize &size, const wxDougnutChartOptions& options);

		double value;
	};

private:
	wxDougnutChartOptions m_options;
	std::vector<SegmentArc::ptr> m_segments;
	double m_total;

	DECLARE_EVENT_TABLE();
};

#endif
