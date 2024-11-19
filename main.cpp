#define WINDOWS_LEAN_AND_MEAN
#include "windows.h"

#include <iostream>
#include <sstream>

#include <array>

int main()
{
	std::array<wchar_t, MAX_PATH> printerName{L"Microsoft XPS Document Writer"};

	HANDLE hdl;
	::OpenPrinterW(printerName.data(), &hdl, NULL);

	int size = ::DocumentPropertiesW(NULL, hdl, printerName.data(), NULL, NULL, 0);
	auto* devmode = (DEVMODEW*)malloc(size);

	::DocumentPropertiesW(NULL, hdl, printerName.data(), devmode, NULL, DM_OUT_BUFFER);
	devmode->dmPaperSize = DMPAPER_A4;

	HDC hDC = ::CreateDCW(L"WINSPOOL", devmode->dmDeviceName, NULL, devmode);

	DOCINFOW info;
	memset(&info, 0, sizeof(info));
	info.cbSize = sizeof(info);
	info.lpszDocName = L"LineWidthTest";
	info.lpszOutput = L"LineWidthTest.oxps";

	::StartDocW(hDC, &info);
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
	auto pen05 = ::CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
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
	::EndDoc(hDC);
	::DeleteDC(hDC);
	::ClosePrinter(hdl);

	// Clean up
	::DeleteObject(pen05);
	::DeleteObject(pen10);
	::DeleteObject(pen15);
	::DeleteObject(pen20);
	::DeleteObject(pen25);
	::DeleteObject(pen30);
	::DeleteObject(pen35);

	return 0;
}
