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

#include "wxchartslabelpanel.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dcclient.h>
#include <wx/fontdlg.h>
#include <sstream>

wxChartsLabelPanel::wxChartsLabelPanel(wxWindow* parent)
    : wxPanel(parent)
{
    m_label = new wxChartsLabel(
        "labeltext1",
        wxChartsLabelOptions(wxChartFontOptions(wxFONTFAMILY_SWISS, 12, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 0x666666), false, wxChartBackgroundOptions(*wxWHITE, 1))
    );

    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxSizer* labelSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* labelSizeLabel = new wxStaticText(this, wxID_ANY, "Size:");
    labelSizeSizer->Add(labelSizeLabel);
    wxTextCtrl* labelSizeInfo = new wxTextCtrl(this, wxID_ANY, "?");
    labelSizeInfo->Disable();
    labelSizeSizer->Add(labelSizeInfo);

    sizer->Add(labelSizeSizer);

    m_canvas = new ElementCanvasWindow(this);
    m_canvas->setElement(m_label);
    sizer->Add(m_canvas, 1, wxEXPAND);

    wxButton* button = new wxButton(this, wxID_ANY, L"Change font...");
    button->Bind(wxEVT_BUTTON, &wxChartsLabelPanel::OnFontSelection, this);
    sizer->Add(button);

    wxClientDC dc(this);
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        m_label->UpdateSize(*gc);
    }

    std::stringstream widthString;
    widthString << "(" << m_label->GetSize().GetWidth() << "," << m_label->GetSize().GetHeight() << ")";
    labelSizeInfo->SetLabel(widthString.str());

    SetSizer(sizer);
}

void wxChartsLabelPanel::OnFontSelection(wxCommandEvent &evt)
{
    wxFontDialog* fontDialog = new wxFontDialog(this);

    if (fontDialog->ShowModal() == wxID_OK)
    {
        //m_label->GetOptions().
    }

    fontDialog->Destroy();
}
