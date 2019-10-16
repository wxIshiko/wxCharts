/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#include <wx/charts/wxcharts.h>
#include <catch.hpp>

TEST_CASE("wxChartsLabelOptions constructor")
{
	wxChartFontOptions fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666);
	wxChartBackgroundOptions backgroundOptions(0x12345678, 0.2);
	wxChartsLabelOptions options(fontOptions, true, backgroundOptions);

	REQUIRE(options.GetFontOptions().GetFamily() == wxFONTFAMILY_SWISS);
	REQUIRE(options.GetFontOptions().GetSize() == 12);
	REQUIRE(options.GetFontOptions().GetStyle() == wxFONTSTYLE_NORMAL);
	REQUIRE(options.GetFontOptions().GetWeight() == wxFONTWEIGHT_NORMAL);
	REQUIRE(options.GetFontOptions().GetColor() == 0x666666);
	REQUIRE(options.HasBackground() == true);
	REQUIRE(options.GetBackgroundOptions().GetColor() == 0x12345678);
	REQUIRE(options.GetBackgroundOptions().GetCornerRadius() == 0.2);
}

TEST_CASE("wxChartsLabelOptions copy constructor")
{
	wxChartFontOptions fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666);
	wxChartBackgroundOptions backgroundOptions(0x12345678, 0.2);
	wxChartsLabelOptions options(fontOptions, true, backgroundOptions);
	wxChartsLabelOptions optionsCopy(options);

	REQUIRE(optionsCopy.GetFontOptions().GetFamily() == wxFONTFAMILY_SWISS);
	REQUIRE(optionsCopy.GetFontOptions().GetSize() == 12);
	REQUIRE(optionsCopy.GetFontOptions().GetStyle() == wxFONTSTYLE_NORMAL);
	REQUIRE(optionsCopy.GetFontOptions().GetWeight() == wxFONTWEIGHT_NORMAL);
	REQUIRE(optionsCopy.GetFontOptions().GetColor() == 0x666666);
	REQUIRE(optionsCopy.HasBackground() == true);
	REQUIRE(optionsCopy.GetBackgroundOptions().GetColor() == 0x12345678);
	REQUIRE(optionsCopy.GetBackgroundOptions().GetCornerRadius() == 0.2);
}
