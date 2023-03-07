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

#include "WxScatterPlotFrame.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>

WxScatterPlotFrame::WxScatterPlotFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	// Create a top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create the data for the scatter plot widget
    wxScatterPlotData chartData;

    // Add the first dataset
    wxVector<wxPoint2DDouble> points1;
    points1.push_back(wxPoint2DDouble(-0.2, 3.5));
    points1.push_back(wxPoint2DDouble(0.5, 2.5));
    points1.push_back(wxPoint2DDouble(1.2, 0.1));
    points1.push_back(wxPoint2DDouble(1.5, 1.6));
    points1.push_back(wxPoint2DDouble(2, 1.8));
    points1.push_back(wxPoint2DDouble(2.2, 2.1));
    points1.push_back(wxPoint2DDouble(2.7, 2));
    wxScatterPlotDataset::ptr dataset1(
        new wxScatterPlotDataset(
            wxColor(250, 20, 20, 0x78),
            wxColor(250, 20, 20, 0xB8),
            points1)
        );
    chartData.AddDataset(dataset1);

    // Add the second dataset
    wxVector<wxPoint2DDouble> points2;
    points2.push_back(wxPoint2DDouble(-0.3, 6.5));
    points2.push_back(wxPoint2DDouble(0.2, -1.5));
    points2.push_back(wxPoint2DDouble(1.6, 0.7));
    points2.push_back(wxPoint2DDouble(1.5, 4.1));
    points2.push_back(wxPoint2DDouble(1.8, 2.7));
    points2.push_back(wxPoint2DDouble(2.1, 2));
    points2.push_back(wxPoint2DDouble(2.3, 6));
    wxScatterPlotDataset::ptr dataset2(
        new wxScatterPlotDataset(
            wxColor(20, 20, 20, 0x78),
            wxColor(20, 20, 20, 0xB8),
            points2)
        );
    chartData.AddDataset(dataset2);

	// Create the scatter plot widget
	wxScatterPlotCtrl* scatterPlotCtrl = new wxScatterPlotCtrl(panel, wxID_ANY, chartData);

	// Set up the sizer for the panel
	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(scatterPlotCtrl, 1, wxEXPAND);
	panel->SetSizer(panelSizer);
}
