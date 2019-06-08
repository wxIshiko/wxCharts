/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "wxlinechartdatasetoptions.h"

wxLineChartDatasetOptions::wxLineChartDatasetOptions(const wxColor &dotColor,
                                                     const wxColor &dotStrokeColor)
    : m_showDots(true), m_dotColor(dotColor), m_dotStrokeColor(dotStrokeColor),
    m_dotRadius(4), m_dotStrokeWidth(1), m_lineWidth(2)
{
}

bool wxLineChartDatasetOptions::ShowDots() const
{
    return m_showDots;
}

const wxColor& wxLineChartDatasetOptions::GetDotColor() const
{
    return m_dotColor;
}

const wxColor& wxLineChartDatasetOptions::GetDotStrokeColor() const
{
    return m_dotStrokeColor;
}

wxDouble wxLineChartDatasetOptions::GetDotRadius() const
{
    return m_dotRadius;
}

unsigned int wxLineChartDatasetOptions::GetDotStrokeWidth() const
{
    return m_dotStrokeWidth;
}

unsigned int wxLineChartDatasetOptions::GetLineWidth() const
{
    return m_lineWidth;
}
