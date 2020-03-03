#include"Helper.h"
#pragma comment(lib,"d2d1")
#include <d2d1.h>
float dpiX, dpiY;
ID2D1Factory* pD2D1Factory = NULL;
ID2D1HwndRenderTarget* pRT = NULL;
ID2D1SolidColorBrush *pBrush = NULL;
float pixelToDipX(float x)
{
  return (x * 96.0f) / dpiX;
}
float pixelToDipY(float y)
{
  return (y * 96.0f) / dpiY;
}
LRESULT CALLBACK MainWinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)

{
  switch (msg)
  {
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);
    pRT->BeginDraw();
    pRT->Clear(D2D1::ColorF(0.141f,0.321f, 0.541f));

    pRT->FillRectangle(D2D1::RectF(pixelToDipX(10.0f), pixelToDipY(10.0f), pixelToDipX(110.0f), pixelToDipY(110.0f)), pBrush);

    pRT->EndDraw();
    EndPaint(hwnd, &ps);
  }
  return 0;
  case WM_DESTROY:
  {
    if (pD2D1Factory) {
      pD2D1Factory->Release();
      pD2D1Factory = NULL;
    }
    if (pRT) {
      pRT->Release();
      pRT = NULL;
    }
    if (pBrush)
    {
      pBrush->Release();
      pBrush = NULL;
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
  WNDCLASSEX wc;
  HWND hwnd;
  MSG msg;
  if (!SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2D1Factory)))
    return EXIT_FAILURE;
  pD2D1Factory->GetDesktopDpi(&dpiX, &dpiY);
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
  wc.lpfnWndProc = MainWinProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hinstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "TimerClass";
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wc.hInstance = hInstance;
  wc.lpfnWndProc(HWND hwnd, UINT uMsg, WPARAM wParam,LPARAM lParam)->LRESULT
  {
    switch(uMsg){
      case WM_DESTROY:{
        hbutton=CreateWindow(30,30,);
        return 0;
      };
    }
  if (!RegisterClassEx(&windowsclass))
    return 0;
  hwnd = CreateWindowA(NULL, "TimerClass", "Timer", WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE, 0, 0, 600, 500, NULL, NULL, hinstance, NULL);
  HRESULT hr = pD2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(600, 500)), &pRT);
  if (!SUCCEEDED(hr))
  {
    return EXIT_FAILURE;
  }

  pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SlateGray), &pBrush);
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}
