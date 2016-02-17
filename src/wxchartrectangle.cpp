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

#include "wxchartrectangle.h"
#include <wx/pen.h>
#include <wx/brush.h>

wxChartRectangle::wxChartRectangle(wxDouble x,
								   wxDouble y,
								   const wxChartTooltipProvider::ptr tooltipProvider,
								   const wxChartRectangleOptions &options)
	: wxChartElement(tooltipProvider), 
	m_position(x, y), m_width(0), m_height(0), m_options(options)
{
}

bool wxChartRectangle::HitTest(const wxPoint &point) const
{
	return false;
}

wxPoint2DDouble wxChartRectangle::GetTooltipPosition() const
{
	return wxPoint2DDouble(m_position.m_x + (m_width / 2),
		m_position.m_y + (m_height / 2));
}

void wxChartRectangle::Draw(wxGraphicsContext &gc) const
{
	wxGraphicsPath path = gc.CreatePath();

	path.AddRectangle(m_position.m_x, m_position.m_y, m_width, m_height);

	wxBrush brush(m_options.GetFillColor());
	gc.SetBrush(brush);
	gc.FillPath(path);

	if (m_options.GetDirections() == wxALL)
	{
		wxPen pen(m_options.GetStrokeColor(), 2);
		gc.SetPen(pen);
		gc.StrokePath(path);
	}
	else
	{
		wxPen pen(m_options.GetStrokeColor(), 2);
		gc.SetPen(pen);

		if (m_options.GetDirections() & wxTOP)
		{
			gc.StrokeLine(m_position.m_x, m_position.m_y, 
				m_position.m_x + m_width, m_position.m_y);
		}
		if (m_options.GetDirections() & wxRIGHT)
		{
			gc.StrokeLine(m_position.m_x + m_width, m_position.m_y, 
				m_position.m_x + m_width, m_position.m_y + m_height);
		}
		if (m_options.GetDirections() & wxBOTTOM)
		{
			gc.StrokeLine(m_position.m_x, m_position.m_y + m_height,
				m_position.m_x + m_width, m_position.m_y + m_height);
		}
		if (m_options.GetDirections() & wxLEFT)
		{
			gc.StrokeLine(m_position.m_x, m_position.m_y,
				m_position.m_x, m_position.m_y + m_height);
		}
	}
}

const wxPoint2DDouble& wxChartRectangle::GetPosition() const
{
	return m_position;
}

void wxChartRectangle::SetPosition(wxDouble x, wxDouble y)
{
	m_position.m_x = x;
	m_position.m_y = y;
}

void wxChartRectangle::SetPosition(wxPoint2DDouble position)
{
	m_position = position;
}

wxDouble wxChartRectangle::GetWidth() const
{
	return m_width;
}

wxDouble wxChartRectangle::GetHeight() const
{
	return m_height;
}

void wxChartRectangle::SetSize(wxDouble width, wxDouble height)
{
	m_width = width;
	m_height = height;
}
