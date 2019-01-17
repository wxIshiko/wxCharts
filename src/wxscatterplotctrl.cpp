/*
    Copyright (c) 2016-2019 Xavier Leclercq

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

#include "wxscatterplotctrl.h"

wxScatterPlotCtrl::wxScatterPlotCtrl(wxWindow *parent,
                                     wxWindowID id,
                                     const wxScatterPlotData &data,
                                     const wxPoint &pos,
                                     const wxSize &size,
                                     long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_scatterPlot(data, size)
{
    CreateContextMenu();
}

wxScatterPlotCtrl::wxScatterPlotCtrl(wxWindow *parent,
                                     wxWindowID id,
                                     const wxScatterPlotData &data,
                                     const wxScatterPlotOptions &options,
                                     const wxPoint &pos,
                                     const wxSize &size,
                                     long style)
    : wxChartCtrl(parent, id, pos, size, style), 
    m_scatterPlot(data, options, size)
{
    CreateContextMenu();
}

wxScatterPlot& wxScatterPlotCtrl::GetChart()
{
    return m_scatterPlot;
}

void wxScatterPlotCtrl::CreateContextMenu()
{
    m_posX = 0;
    m_posY = 0;
    m_subMenu = new wxMenu;
    m_subMenu->Append(wxID_DEFAULT, wxString("Set default zoom"));
    m_subMenu->Append(wxID_UP, wxString("Zoom +"));
    m_subMenu->Append(wxID_DOWN, wxString("Zoom -"));

    m_contextMenu.AppendSubMenu(m_subMenu,wxString("Zoom"));
    Bind(wxEVT_CONTEXT_MENU,
         [this](wxContextMenuEvent& evt)
    {
        PopupMenu(&m_contextMenu, ScreenToClient(evt.GetPosition()));
    }
        );
    m_contextMenu.Bind(wxEVT_MENU,
                       [this](wxCommandEvent &)
    {
        m_contextMenu.Enable(wxID_DOWN,true);
        m_contextMenu.Enable(wxID_UP,true);
        m_scatterPlot.Scale(0);
        auto parent = this->GetParent();
        if(parent)
            parent->Layout();
    },wxID_DEFAULT);
    m_contextMenu.Bind(wxEVT_MENU,
                       [this](wxCommandEvent &)
    {

        if(!m_scatterPlot.Scale(2))
            m_contextMenu.Enable(wxID_UP,false);
        auto parent = this->GetParent();
        if(parent)
            parent->Layout();
    },wxID_UP);
    m_contextMenu.Bind(wxEVT_MENU,
                       [this](wxCommandEvent &)
    {
        if(!m_scatterPlot.Scale(-2))
            m_contextMenu.Enable(wxID_DOWN,false);
        auto parent = this->GetParent();
        if(parent)
            parent->Layout();
    },wxID_DOWN);

    this->Bind(wxEVT_LEFT_DOWN,
               [this](wxMouseEvent&  evt)
    {
        m_posX = evt.m_x;
        m_posY = evt.m_y;
        this->SetCursor(wxCURSOR_HAND);
        evt.Skip();
    });
    this->Bind(wxEVT_LEFT_UP,
               [this](wxMouseEvent&  evt)
    {
        this->SetCursor(wxCURSOR_ARROW);
        evt.Skip();
    });
    this->Bind(wxEVT_MOTION,
               [this](wxMouseEvent& evt)
    {
        evt.Skip();

        if(evt.ButtonIsDown(wxMouseButton::wxMOUSE_BTN_LEFT))
        {
            double dx = m_posX-evt.m_x;
            double dy = m_posY-evt.m_y;
            if( std::abs(dx) > 5 || std::abs(dy) > 5)
            {
                auto parent = this->GetParent();
                if(parent)
                {
                    auto Size = parent->GetSize();
                    m_scatterPlot.Shift(dx/Size.GetX(),dy/Size.GetY());
                    m_posX = evt.m_x;
                    m_posY = evt.m_y;
                    parent->Layout();
                }
            }
        }
    });
}
