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

#ifndef _WX_CHARTS_WXBUBBLECHARTCTRL_H_
#define _WX_CHARTS_WXBUBBLECHARTCTRL_H_

#include "wxchartctrl.h"
#include "wxbubblechartoptions.h"
#include "wxchartgrid.h"
#include "wxchartcircle.h"

class wxBubbleChartDataset
{
public:
    /// Smart pointer typedef.
    typedef wxSharedPtr<wxBubbleChartDataset> ptr;

    /// Constructs a wxBubbleChartDataset instance.
    /// @param data The list of values.
    wxBubbleChartDataset(const wxColor& fillColor, const wxColor& outlineColor,
        wxVector<wxPoint2DDouble> &data);

    const wxColor& GetFillColor() const;
    unsigned int GetOutlineWidth() const;
    const wxColor& GetOutlineColor() const;

    const wxVector<wxPoint2DDouble>& GetData() const;

private:
    wxColor m_fillColor;
    unsigned int m_outlineWidth;
    wxColor m_outlineColor;
    wxVector<wxPoint2DDouble> m_data;
};

/// Data for the wxBubbleChartCtrl control.
class wxBubbleChartData
{
public:
	/// Constructs a wxBubbleChartData instance.
	wxBubbleChartData();

    /// Adds a dataset.
    /// @param dataset The dataset to add.
    void AddDataset(wxBubbleChartDataset::ptr dataset);

    const wxVector<wxBubbleChartDataset::ptr>& GetDatasets() const;

private:
	wxVector<wxBubbleChartDataset::ptr> m_datasets;
};

/// A control that displays a bubble chart.
class wxBubbleChartCtrl : public wxChartCtrl
{
public:
	/// Constructs a wxBubbleChartCtrl control.
	/// @param parent Pointer to a parent window.
	/// @param id Control identifier. If wxID_ANY, will automatically
	/// create an identifier.
	/// @param data The data that will be used to initialize the chart.
	/// @param pos Control position. wxDefaultPosition indicates that 
	/// wxWidgets should generate a default position for the control.
	/// @param size Control size. wxDefaultSize indicates that wxWidgets
	/// should generate a default size for the window. If no suitable 
	/// size can be found, the window will be sized to 20x20 pixels 
	/// so that the window is visible but obviously not correctly sized.
	/// @param style Control style. For generic window styles, please 
	/// see wxWindow.
	wxBubbleChartCtrl(wxWindow *parent, wxWindowID id, const wxBubbleChartData &data,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
		long style = 0);

	virtual const wxBubbleChartOptions& GetOptions() const;

private:
    void Initialize(const wxBubbleChartData &data);

    static wxDouble GetMinXValue(const wxVector<wxBubbleChartDataset::ptr>& datasets);
    static wxDouble GetMaxXValue(const wxVector<wxBubbleChartDataset::ptr>& datasets);
    static wxDouble GetMinYValue(const wxVector<wxBubbleChartDataset::ptr>& datasets);
    static wxDouble GetMaxYValue(const wxVector<wxBubbleChartDataset::ptr>& datasets);

	virtual void Resize(const wxSize &size);
	virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point);

	void OnPaint(wxPaintEvent &evt);
    
private:
    class Circle : public wxChartCircle
    {
    public:
        typedef wxSharedPtr<Circle> ptr;

        Circle(wxPoint2DDouble value, wxDouble x, wxDouble y, 
            const wxChartTooltipProvider::ptr tooltipProvider,
            const wxChartCircleOptions &options);

        wxPoint2DDouble GetValue() const;

    private:
        wxPoint2DDouble m_value;
    };

    class Dataset
    {
    public:
        typedef wxSharedPtr<Dataset> ptr;

        Dataset();

        const wxVector<Circle::ptr>& GetCircles() const;
        void AppendCircle(Circle::ptr circle);

    private:
        wxVector<Circle::ptr> m_circles;
    };

private:
	wxBubbleChartOptions m_options;
	wxChartGrid m_grid;
    wxVector<Dataset::ptr> m_datasets;

	DECLARE_EVENT_TABLE();
};

#endif
