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

#ifndef _WX_CHARTS_WXDOUGHNUTANDPIECHARTOPTIONSBASE_H_
#define _WX_CHARTS_WXDOUGHNUTANDPIECHARTOPTIONSBASE_H_

class wxDoughnutAndPieChartOptionsBase
{
public:
	wxDoughnutAndPieChartOptionsBase(unsigned int percentageInnerCutout);

	unsigned int GetSliceStrokeWidth() const;
	unsigned int GetPercentageInnerCutout() const;
	bool ShowTooltips() const;

protected:
	void SetSliceStrokeWidth(unsigned int strokeWidth);
	void SetPercentageInnerCutout(unsigned int cutout);
	void SetShowTooltips(bool show);

private:
	// The width of each slice stroke, this will increase the 
	// space between the slices themselves.
	unsigned int m_sliceStrokeWidth;
	// The percentage of the chart that we cut out of the middle.
	unsigned int m_percentageInnerCutout;
	bool m_showTooltips;
};

#endif
