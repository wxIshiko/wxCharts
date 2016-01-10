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

#include "WxBarFrame.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>

WxBarFrame::WxBarFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	// Create a top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create the data for the bar chart widget
	wxVector<wxString> labels;
	labels.push_back("January");
	labels.push_back("February");
	labels.push_back("March");
	labels.push_back("April");
	labels.push_back("May");
	labels.push_back("June");
	labels.push_back("July");
	wxBarChartData data(labels);

	// Create the bar chart widget
	wxBarChartCtrl* barChartCtrl = new wxBarChartCtrl(panel, wxID_ANY, data);
	wxVector<wxDouble> data1;
	data1.push_back(5.0);
	data1.push_back(3.0);
	barChartCtrl->AddData(data1);
	wxVector<wxDouble> data2;
	data2.push_back(7.5);
	data2.push_back(1.5);
	barChartCtrl->AddData(data2);

	// Set up the sizer for the panel
	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(barChartCtrl, 1, wxEXPAND);
	panel->SetSizer(panelSizer);

	// Set up the sizer for the frame
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);
}
