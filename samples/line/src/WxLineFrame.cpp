/*
	Copyright (c) 2015-2016 Xavier Leclercq

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

#include "WxLineFrame.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>

WxLineFrame::WxLineFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	// Create a top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create the data for the line chart widget
	wxVector<wxString> labels;
	labels.push_back("January");
	labels.push_back("February");
	labels.push_back("March");
	labels.push_back("April");
	labels.push_back("May");
	labels.push_back("June");
	labels.push_back("July");
	wxLineChartData data(labels);
	
	// Add the first dataset
	wxVector<wxDouble> points;
	points.push_back(3);
	points.push_back(-2.5);
	points.push_back(-1.2);
	points.push_back(3);
	points.push_back(6);
	points.push_back(5);
	points.push_back(1);
	wxLineChartDataset::ptr dataset(new wxLineChartDataset(
		wxColor(220, 220, 220), wxColor(255, 255, 255), points));  
	data.AddDataset(dataset);

	// Create the bar chart widget from the constructed data
	wxLineChartCtrl* lineChartCtrl = new wxLineChartCtrl(panel, wxID_ANY, data);

	// Set up the sizer for the panel
	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(lineChartCtrl, 1, wxEXPAND);
	panel->SetSizer(panelSizer);

	// Set up the sizer for the frame
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);
}
