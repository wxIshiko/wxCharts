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

#include "wxchartmultitooltip.h"

wxChartMultiTooltip::wxChartMultiTooltip(const wxString &title)
	: m_title(title)
{
}

void wxChartMultiTooltip::Draw(wxGraphicsContext &gc)
{
	wxPoint2DDouble position(0, 0);
	if (m_tooltipPositions.size() > 0)
	{
		for (size_t i = 0; i < m_tooltipPositions.size(); ++i)
		{
			position.m_x += m_tooltipPositions[i].m_x;
			position.m_y += m_tooltipPositions[i].m_y;
		}

		position.m_x /= m_tooltipPositions.size();
		position.m_y /= m_tooltipPositions.size();
	}

	wxFont font(m_options.GetTitleFontOptions().GetFont());
	gc.SetFont(font, m_options.GetTitleFontOptions().GetColor());

	gc.DrawText(m_title, position.m_x, position.m_y);
}

void wxChartMultiTooltip::AddTooltip(const wxChartTooltip &tooltip)
{
	m_tooltipPositions.push_back(tooltip.GetPosition());
	m_tooltipProviders.push_back(tooltip.GetProvider());
}
