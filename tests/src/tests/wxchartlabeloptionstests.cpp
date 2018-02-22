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

#include "wxchartlabeloptionstests.h"
#include <wx/charts/wxcharts.h>
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"

wxChartLabelOptionsTests::wxChartLabelOptionsTests()
    : CppUnit::TestCase("wxChartLabelOptions tests")
{
}

CppUnit::Test* wxChartLabelOptionsTests::suite()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("wxChartLabelOptions tests");

    suite->addTest(new CppUnit::TestCaller<wxChartLabelOptionsTests>("testConstructor", &wxChartLabelOptionsTests::testConstructor));
    suite->addTest(new CppUnit::TestCaller<wxChartLabelOptionsTests>("testCopyConstructor", &wxChartLabelOptionsTests::testCopyConstructor));

    return suite;
}

void wxChartLabelOptionsTests::testConstructor()
{
    wxChartFontOptions fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666);
    wxChartBackgroundOptions backgroundOptions(0x12345678, 0.2);
    wxChartLabelOptions options(fontOptions, true, backgroundOptions);

    CPPUNIT_ASSERT(options.GetFontOptions().GetFamily() == wxFONTFAMILY_SWISS);
    CPPUNIT_ASSERT(options.GetFontOptions().GetSize() == 12);
    CPPUNIT_ASSERT(options.GetFontOptions().GetStyle() == wxFONTSTYLE_NORMAL);
    CPPUNIT_ASSERT(options.GetFontOptions().GetWeight() == wxFONTWEIGHT_NORMAL);
    CPPUNIT_ASSERT(options.GetFontOptions().GetColor() == 0x666666);
    CPPUNIT_ASSERT(options.HasBackground() == true);
    CPPUNIT_ASSERT(options.GetBackgroundOptions().GetColor() == 0x12345678);
    CPPUNIT_ASSERT(options.GetBackgroundOptions().GetCornerRadius() == 0.2);
}

void wxChartLabelOptionsTests::testCopyConstructor()
{
    wxChartFontOptions fontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666);
    wxChartBackgroundOptions backgroundOptions(0x12345678, 0.2);
    wxChartLabelOptions options(fontOptions, true, backgroundOptions);
    wxChartLabelOptions optionsCopy(options);

    CPPUNIT_ASSERT(optionsCopy.GetFontOptions().GetFamily() == wxFONTFAMILY_SWISS);
    CPPUNIT_ASSERT(optionsCopy.GetFontOptions().GetSize() == 12);
    CPPUNIT_ASSERT(optionsCopy.GetFontOptions().GetStyle() == wxFONTSTYLE_NORMAL);
    CPPUNIT_ASSERT(optionsCopy.GetFontOptions().GetWeight() == wxFONTWEIGHT_NORMAL);
    CPPUNIT_ASSERT(optionsCopy.GetFontOptions().GetColor() == 0x666666);
    CPPUNIT_ASSERT(optionsCopy.HasBackground() == true);
    CPPUNIT_ASSERT(optionsCopy.GetBackgroundOptions().GetColor() == 0x12345678);
    CPPUNIT_ASSERT(optionsCopy.GetBackgroundOptions().GetCornerRadius() == 0.2);
}
