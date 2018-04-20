#include "stdafx.h"
#include "Game.h"
#include "Saferelease.h"
#include "BitmapLoader.h"

HRESULT Game::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;
	return hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
}

void Game::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
}

void Game::LoadLevel()
{
	currentLevel = new Testlevel(m_pRenderTarget);
}

HRESULT Game::OnRender()
{
	HRESULT hr = CreateDeviceResources();
	if(SUCCEEDED(hr))
	{
		/*BitmapLoader* bitmap_loader = new BitmapLoader(m_pRenderTarget);
		ID2D1Bitmap* bmp=bitmap_loader->getBitmap(L"B.jpg");
		
		D2D1_SIZE_F size = bmp->GetSize();*/
		// Draw bitmap
		LoadLevel();
		currentLevel->Load();
		m_pRenderTarget->BeginDraw();
		currentLevel->OnRender();
		hr = m_pRenderTarget->EndDraw();
	}
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}

	return E_NOTIMPL;
}

LRESULT Game::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		Game *pGame = (Game *)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			PtrToUlong(pGame)
		);

		result = 1;
	}
	else
	{
		Game *pGame = reinterpret_cast<Game *>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
			)));

		bool wasHandled = false;

		if (pGame)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pGame->OnResize(width, height);
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

			case WM_PAINT:
			{
				pGame->OnRender();
				ValidateRect(hwnd, NULL);
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
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;


}

HRESULT Game::CreateDeviceResources()
{
	RECT rc;
	GetClientRect(m_hwnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top
	);

	HRESULT hr = m_pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hwnd, size),
		&m_pRenderTarget
	);

	return hr;
}
Game::Game()
{
	
}

Game::~Game()
{
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);

}

HRESULT Game::Init()
{
	HRESULT hr;
	hr = CreateDeviceIndependentResources();
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Game::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.lpszClassName = L"Game";

	RegisterClassEx(&wcex);

	FLOAT dpiX, dpiY;
	m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

	m_hwnd = CreateWindow(
		L"Game",
		L"Direct2D Game",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
		static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
	);
	hr = m_hwnd ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		UpdateWindow(m_hwnd);
	}
	return hr;

}

void Game::Run()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) //PeekMessage(&msg, m_hwnd, NULL, 0, 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

void Game::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}

}


