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

/// @file

#ifndef _WX_CHARTS_WXDOUGHNUTANDPIECHARTBASE_H_
#define _WX_CHARTS_WXDOUGHNUTANDPIECHARTBASE_H_

#include "wxchart.h"
#include "wxchartslicedata.h"
#include "wxdoughnutandpiechartoptionsbase.h"
#include "wxchartarc.h"
#include <wx/control.h>
#include <wx/sharedptr.h>

/// Common base class for the wxDoughnutChart and wxPieChart charts.

/// The doughnut and pie charts are very similar so we use
/// a common base class. It would actually be possible to
/// only have the doughnut classes but I usually favor
/// ease of use over ease of implementation.
class wxDoughnutAndPieChartBase : public wxChart
{
public:
	/// Constructs a wxDoughnutAndPieChartBase
    /// instance.
	wxDoughnutAndPieChartBase();

protected:
	void Add(const wxChartSliceData &slice, const wxSize &size);
	void Add(const wxChartSliceData &slice, size_t index,
        const wxSize &size);
	
private:
    virtual void DoSetSize(const wxSize &size) wxOVERRIDE;
    virtual void DoFit() wxOVERRIDE;
    virtual void DoDraw(wxGraphicsContext &gc) wxOVERRIDE;
    virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point) wxOVERRIDE;
    
	wxDouble CalculateCircumference(double value);
	
private:
	virtual const wxDoughnutAndPieChartOptionsBase& GetOptions() const = 0;

private:
	class SliceArc : public wxChartArc
	{
	public:
		typedef wxSharedPtr<SliceArc> ptr;

		SliceArc(const wxChartSliceData &slice, wxDouble x, wxDouble y,
			wxDouble startAngle, wxDouble endAngle, wxDouble outerRadius,
			wxDouble innerRadius, unsigned int strokeWidth);

		void Resize(const wxSize &size, const wxDoughnutAndPieChartOptionsBase& options);

		wxDouble GetValue() const;

	private:
		wxDouble m_value;
	};

private:
    wxSize m_size;
	wxVector<SliceArc::ptr> m_slices;
	wxDouble m_total;
};

#endif
