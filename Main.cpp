#include"Helper.h"
#pragma comment(lib,"d2d1")
#pragma comment(lib,"dwrite")
#include <d2d1.h>
#include "d2dfunc.h"
#include "UiDraw.h"
#include <windowsx.h>
#include <dwrite.h>
#include <string>
HWND hwnd;
extern float dpiX, dpiY;
extern int AppWidth, AppHeight;
ID2D1Factory* pD2D1Factory = NULL;
ID2D1SolidColorBrush *pSolidBrush = NULL;
IDWriteFactory* pDWriteFactory = NULL;
ID2D1DCRenderTarget* pDCRT = NULL;
IDWriteTextFormat* pTextFormat = NULL;
HDC hWindowDC;
RECT WindowRect;
Buttons TButtons;
LRESULT CALLBACK MainWinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_PAINT:
	case WM_DISPLAYCHANGE:
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		hWindowDC = ps.hdc;
		pDCRT->BindDC(hWindowDC, &WindowRect);
		pDCRT->BeginDraw();
		pDCRT->Clear(D2D1::ColorF(0.078431f, 0.050980f, 0.129412f));
		DrawWindowFrame();
		DrawWindowTitleBar();
		pDCRT->EndDraw();
		EndPaint(hwnd, &ps);
	}
	return 0;
	case WM_CREATE:
	{
	if (!CreateUiControls(hwnd))
			SendMessage(hwnd, WM_DESTROY, 0, 0);
		GetClientRect(hwnd, &WindowRect);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		ReleaseCapture();
		SendMessage(hwnd, WM_SYSCOMMAND, 61458, 0);
	}
	break;
	case WM_DRAWITEM:
	{
		DrawUiButtons(wparam, reinterpret_cast<PDRAWITEMSTRUCT>(lparam));
	}
	break;
	case WM_COMMAND:
	{
		UiClick(LOWORD(wparam),hwnd);
	}
	break;
	case WM_NCCALCSIZE:
	{

		if (wparam == TRUE)
			SetWindowLong(hwnd, 0, 0);
		return TRUE;
		return FALSE;
	}
	break;

	case WM_NCHITTEST:
	{
		SetWindowLong(hwnd, DWL_MSGRESULT, HTCAPTION);
		return 1;
	}
	break;
	case WM_NCCREATE:
	{
		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lparam;

		lpcs->style &= ~WS_CAPTION;
		SetWindowLong(hwnd, GWL_STYLE, lpcs->style);
	}
	return 1;
	case WM_DESTROY:
	{
		if (pD2D1Factory) {
			pD2D1Factory->Release();
			pD2D1Factory = NULL;
		}
		if (pDCRT) {
			pDCRT->Release();
			pDCRT = NULL;
		}
		if (pSolidBrush)
		{
			pSolidBrush->Release();
			pSolidBrush = NULL;
		}
		PostQuitMessage(0);
		return(0);
	}
	break;
	}
	return(DefWindowProc(hwnd, msg, wparam, lparam));
}
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpCmdLine, int nCmdShow)
{

	HRESULT hr = CoInitialize(NULL);
	if (!SUCCEEDED(hr))
		return false;
	WNDCLASSEX windowsclass;
	MSG msg;
	windowsclass.cbSize = sizeof(WNDCLASSEX);
	windowsclass.style = CS_VREDRAW | CS_HREDRAW ;
	windowsclass.lpfnWndProc = MainWinProc;
	windowsclass.cbClsExtra = 0;
	windowsclass.cbWndExtra = 0;
	windowsclass.hInstance = hinstance;
	windowsclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowsclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowsclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowsclass.lpszMenuName = NULL;
	windowsclass.lpszClassName = "TimerClass";
	windowsclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&windowsclass))
		return 0;
	if (!(hwnd = CreateWindowEx(NULL, "TimerClass", "Timer", WS_CAPTION | WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) - AppWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - AppHeight) / 2, AppWidth, AppHeight, NULL, NULL, hinstance, NULL)))
		return(0);

	if (d2dUnit(&pD2D1Factory, &pDCRT, &pSolidBrush) == EXIT_FAILURE)
		return EXIT_FAILURE;

	 hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (!SUCCEEDED(hr))
		return EXIT_FAILURE;
	pDWriteFactory->CreateTextFormat(
		L"Roboto",
		nullptr,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		24.0f,
		L"",
		&pTextFormat
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
