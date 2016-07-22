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

#include "wxlinechartctrl.h"
#include <wx/brush.h>
#include <wx/pen.h>
#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <sstream>

wxLineChartDataset::wxLineChartDataset(const wxString &label,
									   const wxColor &dotColor,
									   const wxColor &dotStrokeColor,
									   const wxColor &fillColor,
									   const wxVector<wxDouble> &data)
	: m_label(label), m_showDots(true), m_dotColor(dotColor),
	m_dotStrokeColor(dotStrokeColor), m_showLine(true),
	m_lineColor(dotColor), m_fill(true), m_fillColor(fillColor),
	m_data(data)
{
}

const wxString& wxLineChartDataset::GetLabel() const
{
	return m_label;
}

bool wxLineChartDataset::ShowDots() const
{
	return m_showDots;
}

const wxColor& wxLineChartDataset::GetDotColor() const
{
	return m_dotColor;
}

const wxColor& wxLineChartDataset::GetDotStrokeColor() const
{
	return m_dotStrokeColor;
}

bool wxLineChartDataset::ShowLine() const
{
	return m_showLine;
}

const wxColor& wxLineChartDataset::GetLineColor() const
{
	return m_lineColor;
}

bool wxLineChartDataset::Fill() const
{
	return m_fill;
}

const wxColor& wxLineChartDataset::GetFillColor() const
{
	return m_fillColor;
}

const wxVector<double>& wxLineChartDataset::GetData() const
{
	return m_data;
}

wxLineChartData::wxLineChartData(const wxVector<wxString> &labels)
	: m_labels(labels)
{
}

void wxLineChartData::AddDataset(wxLineChartDataset::ptr dataset)
{
	m_datasets.push_back(dataset);
}

const wxVector<wxString>& wxLineChartData::GetLabels() const
{
	return m_labels;
}

const wxVector<wxLineChartDataset::ptr>& wxLineChartData::GetDatasets() const
{
	return m_datasets;
}

wxLineChartCtrl::Point::Point(wxDouble value,
							  const wxChartTooltipProvider::ptr tooltipProvider,
							  wxDouble x,
							  wxDouble y,
							  wxDouble radius,
							  unsigned int strokeWidth,
							  const wxColor &strokeColor,
							  const wxColor &fillColor,
							  wxDouble hitDetectionRange)
	: wxChartPoint(x, y, radius, tooltipProvider, wxChartPointOptions(strokeWidth, strokeColor, fillColor)),
	m_value(value), m_hitDetectionRange(hitDetectionRange)
{
}

bool wxLineChartCtrl::Point::HitTest(const wxPoint &point) const
{
	wxDouble distance = (point.x - GetPosition().m_x);
	if (distance < 0)
	{
		distance = -distance;
	}
	return (distance < m_hitDetectionRange);
}

wxDouble wxLineChartCtrl::Point::GetValue() const
{
	return m_value;
}

wxLineChartCtrl::Dataset::Dataset(bool showDots,
								  bool showLine,
								  const wxColor &lineColor,
								  bool fill,
								  const wxColor &fillColor)
	: m_showDots(showDots), m_showLine(showLine),
	m_lineColor(lineColor), m_fill(fill), m_fillColor(fillColor)
{
}

bool wxLineChartCtrl::Dataset::ShowDots() const
{
	return m_showDots;
}

bool wxLineChartCtrl::Dataset::ShowLine() const
{
	return m_showLine;
}

const wxColor& wxLineChartCtrl::Dataset::GetLineColor() const
{
	return m_lineColor;
}

bool wxLineChartCtrl::Dataset::Fill() const
{
	return m_fill;
}

const wxColor& wxLineChartCtrl::Dataset::GetFillColor() const
{
	return m_fillColor;
}

const wxVector<wxLineChartCtrl::Point::ptr>& wxLineChartCtrl::Dataset::GetPoints() const
{
	return m_points;
}

void wxLineChartCtrl::Dataset::AppendPoint(Point::ptr point)
{
	m_points.push_back(point);
}

wxLineChartCtrl::wxLineChartCtrl(wxWindow *parent,
								 wxWindowID id,
								 const wxLineChartData &data,
								 const wxPoint &pos,
								 const wxSize &size,
								 long style)
	: wxChartCtrl(parent, id, pos, size, style),
	m_grid(
		wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetTop()),
		size, data.GetLabels(), GetMinValue(data.GetDatasets()),
		GetMaxValue(data.GetDatasets()), m_options.GetGridOptions()
		)
{
	Initialize(data);
}

wxLineChartCtrl::wxLineChartCtrl(wxWindow *parent,
								 wxWindowID id,
								 const wxLineChartData &data,
								 const wxLineChartOptions &options,
								 const wxPoint &pos,
								 const wxSize &size,
								 long style)
	: wxChartCtrl(parent, id, pos, size, style), m_options(options),
	m_grid(
		wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetTop()),
		size, data.GetLabels(), GetMinValue(data.GetDatasets()),
		GetMaxValue(data.GetDatasets()), m_options.GetGridOptions()
		)
{
    Initialize(data);
}

const wxLineChartOptions& wxLineChartCtrl::GetOptions() const
{
	return m_options;
}

void wxLineChartCtrl::Initialize(const wxLineChartData &data)
{
    CreateContextMenu();

	const wxVector<wxLineChartDataset::ptr>& datasets = data.GetDatasets();
	for (size_t i = 0; i < datasets.size(); ++i)
	{
		Dataset::ptr newDataset(new Dataset(datasets[i]->ShowDots(),
			datasets[i]->ShowLine(), datasets[i]->GetLineColor(),
			datasets[i]->Fill(), datasets[i]->GetFillColor()));

		const wxVector<wxDouble>& datasetData = datasets[i]->GetData();
		for (size_t j = 0; j < datasetData.size(); ++j)
		{
			std::stringstream tooltip;
			tooltip << datasetData[j];
			wxChartTooltipProvider::ptr tooltipProvider(
				new wxChartTooltipProviderStatic(data.GetLabels()[j], tooltip.str(), datasets[i]->GetLineColor())
				);

			Point::ptr point(
				new Point(datasetData[j], tooltipProvider, 20 + j * 10, 0,
					m_options.GetDotRadius(), m_options.GetDotStrokeWidth(),
					datasets[i]->GetDotStrokeColor(), datasets[i]->GetDotColor(),
					m_options.GetHitDetectionRange())
				);

			newDataset->AppendPoint(point);
		}

		m_datasets.push_back(newDataset);
	}
}

void wxLineChartCtrl::CreateContextMenu()
{
    m_contextMenu.Append(wxID_SAVEAS, wxString("Save as"));

    Bind(wxEVT_CONTEXT_MENU, 
        [this](wxContextMenuEvent& evt) 
        {
            PopupMenu(&m_contextMenu, ScreenToClient(evt.GetPosition()));
        }
        );

    m_contextMenu.Bind(wxEVT_MENU,
        [this](wxCommandEvent &)
        {
            wxFileDialog saveFileDialog(this, _("Save file"), "", "",
                "JPEG files (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG files (*.png)|*.png",
                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
            if (saveFileDialog.ShowModal() == wxID_CANCEL)
                return;

            wxString filename = saveFileDialog.GetPath();

            wxBitmapType type = wxBitmapType::wxBITMAP_TYPE_INVALID;
            switch (saveFileDialog.GetFilterIndex())
            {
            case 0:
                type = wxBitmapType::wxBITMAP_TYPE_JPEG;
                if (wxImage::FindHandler(wxBitmapType::wxBITMAP_TYPE_JPEG) == 0)
                {
                    wxImage::AddHandler(new wxJPEGHandler());
                }
                break;

            case 1:
                type = wxBitmapType::wxBITMAP_TYPE_PNG;
                if (wxImage::FindHandler(wxBitmapType::wxBITMAP_TYPE_PNG) == 0)
                {
                    wxImage::AddHandler(new wxPNGHandler());
                }
                break;
            }
            
            Save(filename, type);
		},
        wxID_SAVEAS
        );
}

wxDouble wxLineChartCtrl::GetMinValue(const wxVector<wxLineChartDataset::ptr>& datasets)
{
	wxDouble result = 0;
	bool foundValue = false;

	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxVector<wxDouble>& values = datasets[i]->GetData();
		for (size_t j = 0; j < values.size(); ++j)
		{
			if (!foundValue)
			{
				result = values[j];
				foundValue = true;
			}
			else if (result > values[j])
			{
				result = values[j];
			}
		}
	}

	return result;
}

wxDouble wxLineChartCtrl::GetMaxValue(const wxVector<wxLineChartDataset::ptr>& datasets)
{
	wxDouble result = 0;
	bool foundValue = false;

	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxVector<wxDouble>& values = datasets[i]->GetData();
		for (size_t j = 0; j < values.size(); ++j)
		{
			if (!foundValue)
			{
				result = values[j];
				foundValue = true;
			}
			else if (result < values[j])
			{
				result = values[j];
			}
		}
	}

	return result;
}

void wxLineChartCtrl::DoFit()
{
}

void wxLineChartCtrl::DoDraw(wxGraphicsContext &gc)
{
    m_grid.Draw(gc);

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        const wxVector<Point::ptr>& points = m_datasets[i]->GetPoints();

        wxGraphicsPath path = gc.CreatePath();

        if (points.size() > 0)
        {
            const Point::ptr& point = points[0];
            wxPoint2DDouble firstPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(0, point->GetValue());
            path.MoveToPoint(firstPosition);

            wxPoint2DDouble lastPosition;
            for (size_t j = 1; j < points.size(); ++j)
            {
                const Point::ptr& point = points[j];
                lastPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(j, point->GetValue());
                path.AddLineToPoint(lastPosition);
            }

            if (m_datasets[i]->ShowLine())
            {
                wxPen pen(m_datasets[i]->GetLineColor(), m_options.GetLineWidth());
                gc.SetPen(pen);
            }
            else
            {
                // TODO : transparent pen
            }

            gc.StrokePath(path);

            wxPoint2DDouble yPos = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(0);

            path.AddLineToPoint(lastPosition.m_x, yPos.m_y);
            path.AddLineToPoint(firstPosition.m_x, yPos.m_y);
            path.CloseSubpath();

            wxBrush brush(m_datasets[i]->GetFillColor());
            gc.SetBrush(brush);
            gc.FillPath(path);
        }

        if (m_datasets[i]->ShowDots())
        {
            for (size_t j = 0; j < points.size(); ++j)
            {
                const Point::ptr& point = points[j];
                point->SetPosition(m_grid.GetMapping().GetWindowPositionAtTickMark(j, point->GetValue()));
                point->Draw(gc);
            }
        }
    }
}

void wxLineChartCtrl::Resize(const wxSize &size)
{
	wxSize newSize(
		size.GetWidth() - m_options.GetPadding().GetTotalHorizontalPadding(),
		size.GetHeight() - m_options.GetPadding().GetTotalVerticalPadding()
		);
	m_grid.Resize(newSize);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxLineChartCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	for (size_t i = 0; i < m_datasets.size(); ++i)
	{
		const wxVector<Point::ptr>& points = m_datasets[i]->GetPoints();
		for (size_t j = 0; j < points.size(); ++j)
		{
			if (points[j]->HitTest(point))
			{
				activeElements->push_back(points[j].get());
			}
		}
	}
	return activeElements;
}

void wxLineChartCtrl::Save(const wxString &filename, const wxBitmapType &type)
{
    int w,h;
    GetSize(&w, &h);
    wxBitmap bmp(w, h);
    wxMemoryDC mdc(bmp);
    mdc.Clear();
    wxGraphicsContext* gc = wxGraphicsContext::Create(mdc);
    if (gc)
    {
        DoDraw(*gc);
        bmp.SaveFile(filename, type);
        delete gc;
    }
}
