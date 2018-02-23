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

#include "wxcolumnchartoptionstests.h"
#include <wx/charts/wxcharts.h>
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"

wxColumnChartOptionsTests::wxColumnChartOptionsTests()
    : CppUnit::TestCase("wxColumnChartOptions tests")
{
}

CppUnit::Test* wxColumnChartOptionsTests::suite()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("wxColumnChartOptions tests");

    suite->addTest(new CppUnit::TestCaller<wxColumnChartOptionsTests>("testConstructor", &wxColumnChartOptionsTests::testConstructor));
    suite->addTest(new CppUnit::TestCaller<wxColumnChartOptionsTests>("testCopyConstructor", &wxColumnChartOptionsTests::testCopyConstructor));

    return suite;
}

void wxColumnChartOptionsTests::testConstructor()
{
    wxColumnChartOptions options;

    CPPUNIT_ASSERT(options.GetGridOptions().GetXAxisOptions().GetPosition() == wxCHARTAXISPOSITION_BOTTOM);
    CPPUNIT_ASSERT(options.GetGridOptions().GetXAxisOptions().GetLabelType() == wxCHARTAXISLABELTYPE_RANGE);
}

void wxColumnChartOptionsTests::testCopyConstructor()
{
    wxColumnChartOptions options;
    wxColumnChartOptions optionsCopy(options);

    CPPUNIT_ASSERT(optionsCopy.GetGridOptions().GetXAxisOptions().GetPosition() == wxCHARTAXISPOSITION_BOTTOM);
    CPPUNIT_ASSERT(optionsCopy.GetGridOptions().GetXAxisOptions().GetLabelType() == wxCHARTAXISLABELTYPE_RANGE);
}
