/*
    Copyright (c) 2018 Xavier Leclercq

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

#include "wxchartfontoptionstests.h"
#include <wx/charts/wxcharts.h>
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"

wxChartFontOptionsTests::wxChartFontOptionsTests()
    : CppUnit::TestCase("wxChartFontOptions tests")
{
}

CppUnit::Test* wxChartFontOptionsTests::suite()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("wxChartFontOptions tests");

    suite->addTest(new CppUnit::TestCaller<wxChartFontOptionsTests>("testConstructor", &wxChartFontOptionsTests::testConstructor));
    suite->addTest(new CppUnit::TestCaller<wxChartFontOptionsTests>("testCopyConstructor", &wxChartFontOptionsTests::testCopyConstructor));

    return suite;
}

void wxChartFontOptionsTests::testConstructor()
{
    wxChartFontOptions options(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666);

    CPPUNIT_ASSERT(options.GetFamily() == wxFONTFAMILY_SWISS);
    CPPUNIT_ASSERT(options.GetSize() == 12);
    CPPUNIT_ASSERT(options.GetStyle() == wxFONTSTYLE_NORMAL);
    CPPUNIT_ASSERT(options.GetWeight() == wxFONTWEIGHT_NORMAL);
    CPPUNIT_ASSERT(options.GetColor() == 0x666666);
}

void wxChartFontOptionsTests::testCopyConstructor()
{
    wxChartFontOptions options(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666);
    wxChartFontOptions optionsCopy(options);

    CPPUNIT_ASSERT(optionsCopy.GetFamily() == wxFONTFAMILY_SWISS);
    CPPUNIT_ASSERT(optionsCopy.GetSize() == 12);
    CPPUNIT_ASSERT(optionsCopy.GetStyle() == wxFONTSTYLE_NORMAL);
    CPPUNIT_ASSERT(optionsCopy.GetWeight() == wxFONTWEIGHT_NORMAL);
    CPPUNIT_ASSERT(optionsCopy.GetColor() == 0x666666);
}
