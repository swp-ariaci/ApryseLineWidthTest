#include <iostream>
#include <sstream>

#include <PDF/PDFNet.h>
#include <PDF/PDFDC.h>
#include <PDF/PDFDCEX.h>

#include "license.h"

#include <array>

using namespace pdftron;
using namespace PDF;

int main()
{
	struct PDFNetInitializer final
	{
		PDFNetInitializer()
		{
			PDFNet::Initialize(APRYSE_LICENSE_KEY);
		}
		~PDFNetInitializer()
		{
			PDFNet::Terminate();
		}
	} pdfNetInitializer;

	try  
	{	
		PDFDoc pdfdoc;
		PDFDCEX pdfDcEx;

		const PDF::Point paperDimensions(8.27, 11.69);	// A4 paper size in inches
		auto hDC = pdfDcEx.Begin(pdfdoc, paperDimensions);

		::StartPage(hDC);

		::SetMapMode(hDC, MM_ANISOTROPIC);
		::SetWindowExtEx(hDC, 1000, 1000, NULL);
		::SetViewportExtEx(hDC, 
			(::GetDeviceCaps(hDC, LOGPIXELSX) * 100 + 127) / 254,
			(::GetDeviceCaps(hDC, LOGPIXELSY) * 100 + 127) / 254, nullptr);
		::SetBkColor(hDC, RGB(255, 255, 255));

		XFORM Xform;
		::GetWorldTransform(hDC, &Xform);

		// 0.05mm line width
		auto pen05 = ::CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		::SelectObject(hDC, pen05);
		::SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		::Polyline(hDC, std::array<POINT, 2>{POINT{3658, 9157}, {3658, 13157}}.data(), 2);

		// 0.10mm line width
		auto pen10 = ::CreatePen(PS_SOLID, 8, RGB(0, 0, 0));
		::SelectObject(hDC, pen10);
		::SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		::Polyline(hDC, std::array<POINT, 2>{POINT{5658, 9157}, {5658, 13157}}.data(), 2);

		// 0.15mm line width
		auto pen15 = ::CreatePen(PS_SOLID, 17, RGB(0, 0, 0));
		::SelectObject(hDC, pen15);
		::SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		::Polyline(hDC, std::array<POINT, 2>{POINT{7658, 9157}, {7658, 13157}}.data(), 2);

		// 0.20mm line width
		auto pen20 = ::CreatePen(PS_SOLID, 21, RGB(0, 0, 0));
		::SelectObject(hDC, pen15);
		::SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		::Polyline(hDC, std::array<POINT, 2>{POINT{9658, 9157}, {9658, 13157}}.data(), 2);

		// 0.25mm line width
		auto pen25 = ::CreatePen(PS_SOLID, 25, RGB(0, 0, 0));
		::SelectObject(hDC, pen25);
		::SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		::Polyline(hDC, std::array<POINT, 2>{POINT{11658, 9157}, {11658, 13157}}.data(), 2);

		// 0.30mm line width
		auto pen30 = ::CreatePen(PS_SOLID, 30, RGB(0, 0, 0));
		::SelectObject(hDC, pen30);
		::SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		::Polyline(hDC, std::array<POINT, 2>{POINT{13658, 9157}, {13658, 13157}}.data(), 2);

		// 0.35mm line width
		auto pen35 = ::CreatePen(PS_SOLID, 34, RGB(0, 0, 0));
		::SelectObject(hDC, pen35);
		::SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		::Polyline(hDC, std::array<POINT, 2>{POINT{15658, 9157}, {15658, 13157}}.data(), 2);

		::EndPage(hDC);

		// Complete the translation
		pdfDcEx.End();

		// Save the PDF document
		pdfdoc.Save("LineWidthTest.pdf", SDF::SDFDoc::e_remove_unused, NULL);
		std::cout << "Saved LineWidthTest.pdf\nDone.\n";

		// Clean up
		::DeleteObject(pen05);
		::DeleteObject(pen10);
		::DeleteObject(pen15);
		::DeleteObject(pen20);
		::DeleteObject(pen25);
		::DeleteObject(pen30);
		::DeleteObject(pen35);
	}
	catch(Common::Exception& e)
	{
		std::cout << e << std::endl;
		return 1;
	}
	catch(...)
	{
		std::cout << "Unknown Exception" << std::endl;
		return 1;
	}

	return 0;
}
