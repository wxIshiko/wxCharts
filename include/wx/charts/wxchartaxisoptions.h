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
enum wxChartLabelType
{
	/// The labels represent specific points on the 
	/// axis. Grid lines are drawn at these points.
	wxCHARTLABELTYPE_POINT = 0,
	/// The labels represent portions of the axis.
	/// The start and end of each portion are marked
	/// by the grid lines.
	wxCHARTLABELTYPE_RANGE = 1
};

/// The options for the wxChartAxis element.
class wxChartAxisOptions
{
public:
	/// Constructs a new wxChartAxisOptions
	/// instance.
	wxChartAxisOptions();
	wxChartAxisOptions(wxChartLabelType labelType);

	/// Gets the label type.
	/// @return The label type.
	wxChartLabelType GetLabelType() const;

	/// Gets the width of the line.
	/// @return The width of the line.
	unsigned int GetLineWidth() const;
	/// Gets the color of the line.
	/// @return The color of the line.
	const wxColor& GetLineColor() const;

	const wxChartFontOptions& GetFontOptions() const;

private:
	wxChartLabelType m_labelType;
	unsigned int m_lineWidth;
	wxColor m_lineColor;
	wxChartFontOptions m_fontOptions;
	
};

#endif
