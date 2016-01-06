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

#ifndef _WX_CHARTS_WXDOUGHNUTANDPIECHARTBASE_H_
#define _WX_CHARTS_WXDOUGHNUTANDPIECHARTBASE_H_

#include "wxchartarc.h"
#include <wx/control.h>
#include <vector>
#include <memory>

class ChartSlice
{
public:
	ChartSlice(double value, const wxColor &color);

	double GetValue() const;
	const wxColor& GetColor() const;

private:
	double m_value;
	wxColor m_color;
};

class wxDoughnutAndPieChartOptionsBase
{
public:
	wxDoughnutAndPieChartOptionsBase(unsigned int percentageInnerCutout);

	unsigned int GetSegmentStrokeWidth() const;
	unsigned int GetPercentageInnerCutout() const;
	bool ShowTooltips() const;

private:
	// The width of each segment stroke, this will increase the 
	// space between the segments themselves.
	unsigned int m_segmentStrokeWidth;
	// The percentage of the chart that we cut out of the middle.
	unsigned int m_percentageInnerCutout;
	bool m_showTooltips;
};

// The doughnut and pie chart are very similar so we use
// a common base class. It would actually be possible to
// only have the doughnut classes but I usually favor
// ease of use over ease of implementation.
class wxDoughnutAndPieChartBase : public wxControl
{
public:
	wxDoughnutAndPieChartBase(wxWindow *parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize, long style = 0);

	void Add(const ChartSlice &slice);
	void Add(const ChartSlice &slice, size_t index);
	void Add(const ChartSlice &slice, size_t index, bool silent);

private:
	double CalculateCircumference(double value);
	void GetSegmentsAtEvent(const wxPoint &point);

	void OnPaint(wxPaintEvent &evt);
	void OnSize(wxSizeEvent& evt);
	void OnMouseEnter(wxMouseEvent& evt);
	void OnMouseOver(wxMouseEvent& evt);
	void OnMouseExit(wxMouseEvent& evt);

private:
	virtual const wxDoughnutAndPieChartOptionsBase& GetOptions() const = 0;

private:
	struct SliceArc : public wxChartArc
	{
		typedef std::shared_ptr<SliceArc> ptr;

		SliceArc(const ChartSlice &slice, double x, double y,
			double startAngle, double endAngle, double outerRadius,
			double innerRadius, unsigned int strokeWidth);

		void Resize(const wxSize &size, const wxDoughnutAndPieChartOptionsBase& options);

		double value;
	};

private:
	std::vector<SliceArc::ptr> m_slices;
	double m_total;
	bool m_mouseInWindow;
	std::vector<SliceArc::ptr> m_activeSlices;

	DECLARE_EVENT_TABLE();
};

#endif
