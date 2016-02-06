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
#include "wxchartutilities.h"
#include <wx/brush.h>

wxChartMultiTooltip::wxChartMultiTooltip(const wxString &title)
	: m_title(title)
{
}

void wxChartMultiTooltip::Draw(wxGraphicsContext &gc)
{
	wxFont titleFont(m_options.GetTitleFontOptions().GetFont());
	wxFont textFont(m_options.GetTextFontOptions().GetFont());

	wxPoint2DDouble position(0, 0);
	wxVector<wxString> textItems;
	wxDouble titleWidth = 0;
	wxDouble titleHeight = 0;
	wxChartUtilities::GetTextSize(gc, titleFont, m_title, titleWidth, titleHeight);
	wxDouble tooltipWidth = titleWidth;
	wxDouble tooltipHeight = titleHeight;
	if (m_tooltipPositions.size() > 0)
	{
		for (size_t i = 0; i < m_tooltipPositions.size(); ++i)
		{
			position.m_x += m_tooltipPositions[i].m_x;
			position.m_y += m_tooltipPositions[i].m_y;

			wxString text = m_tooltipProviders[i]->GetTooltipText();
			textItems.push_back(text);

			wxDouble width = 0;
			wxDouble height = 0;
			wxChartUtilities::GetTextSize(gc, textFont, text, width, height);
			if (width > tooltipWidth)
			{
				tooltipWidth = width;
			}
		}

		position.m_x /= m_tooltipPositions.size();
		position.m_y /= m_tooltipPositions.size();
	}

	tooltipWidth += (2 * m_options.GetHorizontalPadding());
	tooltipHeight += (m_tooltipPositions.size() * m_options.GetTextFontOptions().GetSize());

	wxDouble x = position.m_x - (titleWidth / 2);

	wxGraphicsPath path = gc.CreatePath();
	path.AddRoundedRectangle(position.m_x - (tooltipWidth / 2), position.m_y - (tooltipHeight / 2),
		tooltipWidth, tooltipHeight, m_options.GetCornerRadius());
	wxBrush brush(m_options.GetBackgroundColor());
	gc.SetBrush(brush);
	gc.FillPath(path);

	gc.SetFont(titleFont, m_options.GetTitleFontOptions().GetColor());
	gc.DrawText(m_title, x, position.m_y);

	gc.SetFont(textFont, m_options.GetTextFontOptions().GetColor());
	
	wxDouble textFontSize = m_options.GetTextFontOptions().GetSize();
	wxDouble y = position.m_y + 1 + titleHeight;
	for (size_t i = 0; i < textItems.size(); ++i)
	{
		wxGraphicsPath path = gc.CreatePath();

		path.AddRoundedRectangle(x, y, textFontSize + 2, textFontSize + 2, 3);

		wxBrush brush(*wxGREEN);
		gc.SetBrush(brush);
		gc.FillPath(path);

		gc.DrawText(textItems[i], x + 20, y);
		y += textFontSize + 5;
	}



		
	
}

void wxChartMultiTooltip::AddTooltip(const wxChartTooltip &tooltip)
{
	m_tooltipPositions.push_back(tooltip.GetPosition());
	m_tooltipProviders.push_back(tooltip.GetProvider());
}
