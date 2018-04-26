//FurtherStudy.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Gametry.h"
#include "Game.h"
#include "Saferelease.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
Game *app;
ID2D1Factory* pDirect2dFactory;
// 此代码模块中包含的函数的前向声明:

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL  InitInstance(HINSTANCE, int);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// TODO: 在此放置代码。
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	app->LoadLevel();
	app->Run();

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	bool wasHandled = false;
	if (app)
	{
		switch (message)
		{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				app->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;
			case WM_CLOSE:
				{
					DestroyWindow(hwnd);
				}
				result = 1;
				wasHandled = true;
				break;
		}
		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	HRESULT hr;
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.lpszClassName = L"Game";

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中
	app = new Game();
	FLOAT dpiX, dpiY;
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pDirect2dFactory);
	pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
	HWND hWnd = CreateWindow(
		L"Game",
		L"Direct2D Game",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		static_cast<UINT>(ceil(1280.f * dpiX / 96.f)),
		static_cast<UINT>(ceil(960.f * dpiY / 96.f)),
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		app
	);

	if (!hWnd)
	{
		return FALSE;
	}
	app->Init(hWnd, pDirect2dFactory);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	return TRUE;
}
	//MSG msg;
	//BOOL bDone = FALSE;
	//LONG winX, winY;
	//WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	//HRESULT hr;

	//ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	//ZeroMemory(&msg, sizeof(MSG));

	//wcex.style = CS_HREDRAW | CS_VREDRAW;
	//wcex.lpfnWndProc = Game::WndProc;
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = sizeof(LONG_PTR);
	//wcex.hInstance = HINST_THISCOMPONENT;
	//wcex.hbrBackground = NULL;
	//wcex.lpszMenuName = NULL;
	//wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	//wcex.lpszClassName = L"Game";

	//if (!RegisterClassEx(&wcex))
	//	return -2;

	//RECT rect = { 0,0,800,600 };
	//AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	// HWND hwnd = CreateWindowEx(
	//	WS_EX_OVERLAPPEDWINDOW,
	//	L"Game",
	//	L"Direct2D Game",
	//	WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT,
	//	CW_USEDEFAULT,
	//	rect.right-rect.left,
	//	rect.bottom-rect.top,
	//	NULL,
	//	NULL,
	//	HINST_THISCOMPONENT,
	//	0
	//);
	//hr = hwnd ? S_OK : E_FAIL;

	//HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	//if (SUCCEEDED(CoInitialize(NULL)))
	////{
	//
	//	game = new Game();
	//	hr = game->Init(hwnd);
	//	if(hr!=S_OK)
	//	{
	//		delete game;
	//		return -1;
	//	}
	//		
	//	if (SUCCEEDED(hr))
	//	{
	//		ShowWindow(hwnd, SW_SHOWNORMAL);
	//		UpdateWindow(hwnd);
	//	}
	//	game->Run();
	//	DestroyWindow(hwnd);

	//	return 0;
	//	CoUninitialize();
	//}

	
	/*HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			Game *app=new Game();

			if (SUCCEEDED(app->Init()))
			{
				app->Run();
			}
		}
		CoUninitialize();
	}*/




