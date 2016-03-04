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

/// @file

#ifndef _WX_CHARTS_WXSCATTERPLOTCTRL_H_
#define _WX_CHARTS_WXSCATTERPLOTCTRL_H_

#include "wxchartctrl.h"
#include "wxscatterplotoptions.h"
#include "wxchartgrid.h"
#include "wxchartpoint.h"

class wxScatterPlotDataset
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxScatterPlotDataset> ptr;

    /// Constructs a wxScatterPlotDataset instance.
    /// @param data The list of values.
    wxScatterPlotDataset(const wxColor& fillColor, const wxColor& strokeColor,
        wxVector<wxPoint2DDouble> &data);

    const wxColor& GetFillColor() const;
    const wxColor& GetStrokeColor() const;

    const wxVector<wxPoint2DDouble>& GetData() const;

private:
    wxColor m_fillColor;
    wxColor m_strokeColor;
    wxVector<wxPoint2DDouble> m_data;
};

/// Data for the wxScatterPlotCtrl control.
class wxScatterPlotData
{
public:
    /// Constructs a wxScatterPlotData instance.
    wxScatterPlotData();

    /// Adds a dataset.
    /// @param dataset The dataset to add.
    void AddDataset(wxScatterPlotDataset::ptr dataset);

    const wxVector<wxScatterPlotDataset::ptr>& GetDatasets() const;

private:
    wxVector<wxScatterPlotDataset::ptr> m_datasets;
};

/// A control that displays a scatter plot.
class wxScatterPlotCtrl : public wxChartCtrl
{
public:
	/// Constructs a wxScatterPlotCtrl control.
	/// @param parent Pointer to a parent window.
	/// @param id Control identifier. If wxID_ANY, will automatically
	/// create an identifier.
    /// @param data The data that will be used to initialize the chart.
	/// @param pos Control position. wxDefaultPosition indicates that 
	/// wxWidgets should generate a default position for the control.
	/// @param size Control size. wxDefaultSize indicates that wxWidgets
	/// should generate a default size for the window. If no suitable 
	/// size can  be found, the window will be sized to 20x20 pixels 
	/// so that the window is visible but obviously not correctly sized.
	/// @param style Control style. For generic window styles, please 
	/// see wxWindow.
	wxScatterPlotCtrl(wxWindow *parent, wxWindowID id, const wxScatterPlotData &data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
		long style = 0);

	virtual const wxScatterPlotOptions& GetOptions() const;

private:
    static wxDouble GetMinXValue(const wxVector<wxScatterPlotDataset::ptr>& datasets);
    static wxDouble GetMaxXValue(const wxVector<wxScatterPlotDataset::ptr>& datasets);
    static wxDouble GetMinYValue(const wxVector<wxScatterPlotDataset::ptr>& datasets);
    static wxDouble GetMaxYValue(const wxVector<wxScatterPlotDataset::ptr>& datasets);

	virtual void Resize(const wxSize &size);
	virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point);

	void OnPaint(wxPaintEvent &evt);

private:
    class Point : public wxChartPoint
    {
    public:
        typedef wxSharedPtr<Point> ptr;

        Point(wxPoint2DDouble value,
            const wxChartTooltipProvider::ptr tooltipProvider,
            wxDouble x, wxDouble y, 
            const wxChartPointOptions &options);

        wxPoint2DDouble GetValue() const;

    private:
        wxPoint2DDouble m_value;
    };

    class Dataset
    {
    public:
        typedef wxSharedPtr<Dataset> ptr;

        Dataset();

        const wxVector<Point::ptr>& GetPoints() const;
        void AppendPoint(Point::ptr point);

    private:
        wxVector<Point::ptr> m_points;
    };

private:
	wxScatterPlotOptions m_options;
	wxChartGrid m_grid;
    wxVector<Dataset::ptr> m_datasets;

	DECLARE_EVENT_TABLE();
};

#endif
