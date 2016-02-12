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

#ifndef _WX_CHARTS_WXCHARTAXISOPTIONS_H_
#define _WX_CHARTS_WXCHARTAXISOPTIONS_H_

#include "wxchartfontoptions.h"

/// The position of the axis in relation to the chart.

/// The position is used to know where to draw the labels
/// and markers.
enum wxChartAxisPosition
{
	/// The axis is on the left of the chart. Markers
	/// and labels should be drawn on the left of the axis.
	wxCHARTAXISPOSITION_LEFT = 0,
	/// The axis is on the right of the chart. Markers
	/// and labels should be drawn on the right of the axis.
	wxCHARTAXISPOSITION_RIGHT = 1,
	/// The axis is at the top of the chart. Markers
	/// and labels should be drawn above the axis.
	wxCHARTAXISPOSITION_BOTTOM = 2,
	/// The axis is at the bottom of the chart. Markers
	/// and labels should be drawn below the axis.
	wxCHARTAXISPOSITION_TOP = 3
};

/// Label types for the wxChartAxis class.

/// Labels on an axis can represent 2 things. 
/// - A specific value or point, in which case 
/// the labels should be centered on the grid
/// lines.
/// - A range, in which case the labels should
/// be positioned in between grid lines.
///
/// Note that the wxChartAxis class can be used
/// for many things so the above description may
/// not make sense for a particular type of data
/// shown on the axis.
///
/// This terminology was chosen because the type of 
/// label may affect more than just where they are
/// positioned so something like 'centered' would
/// have its own issues.
enum wxChartAxisLabelType
{
	/// The labels represent specific points on the 
	/// axis. Grid lines are drawn at these points.
	wxCHARTAXISLABELTYPE_POINT = 0,
	/// The labels represent portions of the axis.
	/// The start and end of each portion are marked
	/// by the grid lines.
	wxCHARTAXISLABELTYPE_RANGE = 1
};

enum wxChartAxisValueMode
{
	wxCHARTAXISVALUEMODE_AUTO = 0,
	wxCHARTAXISVALUEMODE_EXPLICIT = 1
};

/// The options for the wxChartAxis element.
class wxChartAxisOptions
{
public:
	/// Constructs a new wxChartAxisOptions
	/// instance.
	wxChartAxisOptions(wxChartAxisPosition position);
	wxChartAxisOptions(wxChartAxisPosition position, wxChartAxisLabelType labelType);

	wxChartAxisPosition GetPosition() const;

	/// Gets the label type.
	/// @return The label type.
	wxChartAxisLabelType GetLabelType() const;

	wxChartAxisValueMode GetStartValueMode() const;
	wxDouble GetStartValue() const;
	void SetExplicitStartValue(wxDouble startValue);
	wxChartAxisValueMode GetEndValueMode() const;
	wxDouble GetEndValue() const;
	void SetExplicitEndValue(wxDouble endValue);

	/// Gets the width of the line.
	/// @return The width of the line.
	unsigned int GetLineWidth() const;
	/// Gets the color of the line.
	/// @return The color of the line.
	const wxColor& GetLineColor() const;

	const wxChartFontOptions& GetFontOptions() const;

private:
	wxChartAxisPosition m_position;
	wxChartAxisLabelType m_labelType;
	wxChartAxisValueMode m_startValueMode;
	wxDouble m_startValue;
	wxChartAxisValueMode m_endValueMode;
	wxDouble m_endValue;
	unsigned int m_lineWidth;
	wxColor m_lineColor;
	wxChartFontOptions m_fontOptions;
	
};

#endif
