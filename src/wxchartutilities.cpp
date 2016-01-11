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

#include "wxchartutilities.h"

size_t wxChartUtilities::GetDecimalPlaces()
{
	return 1;
}

void wxChartUtilities::CalculateGridRange(const wxVector<wxDouble> &values, 
										  wxDouble &valueRange,
										  size_t &steps)
{
	// Set a minimum step of two - a point at the top of the graph, and a point at the base
	steps = 2;

	wxDouble maxValue = 0;
	wxDouble minValue = 0;
	if (values.size() > 0)
	{
		maxValue = values[0];
		minValue = values[0];
		for (size_t i = 1; i < values.size(); ++i)
		{
			if (values[i] > maxValue)
			{
				maxValue = values[i];
			}
			if (values[i] < minValue)
			{
				minValue = values[i];
			}
		}
	}

	// We need some degree of separation here to calculate the scales if all the values are the same
	// Adding/minusing 0.5 will give us a range of 1.
	if (maxValue == minValue)
	{
		maxValue += 0.5;
		minValue -= 0.5;
	}

	valueRange = maxValue - minValue;
	if (valueRange < 0)
	{
		valueRange = -valueRange;
	}
}

void wxChartUtilities::GetTextSize(wxGraphicsContext &gc,
								   const wxFont &font, 
								   const wxString &string,
								   wxDouble &width,
								   wxDouble &height)
{
	wxDouble descent;
	wxDouble externalLeading;
	gc.SetFont(font, *wxBLACK);
	gc.GetTextExtent(string, &width, &height, &descent, &externalLeading);
}

wxDouble wxChartUtilities::GetWidestText(wxGraphicsContext &gc,
										 const wxFont &font,
										 const wxVector<wxString> &strings)
{
	wxDouble result = 0;

	for (size_t i = 0; i < strings.size(); ++i)
	{
		wxDouble width;
		wxDouble height;
		wxDouble descent;
		wxDouble externalLeading;
		gc.SetFont(font, *wxBLACK);
		gc.GetTextExtent(strings[i], &width, &height, &descent, &externalLeading);
		if (width > result)
		{
			result = width;
		}
	}

	return result;
}
