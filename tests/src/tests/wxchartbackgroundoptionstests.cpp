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

#include "wxchartbackgroundoptionstests.h"
#include <wx/charts/wxcharts.h>
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"

wxChartBackgroundOptionsTests::wxChartBackgroundOptionsTests()
    : CppUnit::TestCase("wxChartBackgroundOptions tests")
{
}

CppUnit::Test* wxChartBackgroundOptionsTests::suite()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("wxChartBackgroundOptions tests");

    suite->addTest(new CppUnit::TestCaller<wxChartBackgroundOptionsTests>("testConstructor", &wxChartBackgroundOptionsTests::testConstructor));
    suite->addTest(new CppUnit::TestCaller<wxChartBackgroundOptionsTests>("testCopyConstructor", &wxChartBackgroundOptionsTests::testCopyConstructor));

    return suite;
}

void wxChartBackgroundOptionsTests::testConstructor()
{
    wxChartBackgroundOptions options(0x12345678, 0.2);

    CPPUNIT_ASSERT(options.GetColor() == 0x12345678);
    CPPUNIT_ASSERT(options.GetCornerRadius() == 0.2);
}

void wxChartBackgroundOptionsTests::testCopyConstructor()
{
    wxChartBackgroundOptions options(0x12345678, 0.2);
    wxChartBackgroundOptions optionsCopy(options);

    CPPUNIT_ASSERT(optionsCopy.GetColor() == 0x12345678);
    CPPUNIT_ASSERT(optionsCopy.GetCornerRadius() == 0.2);
}
