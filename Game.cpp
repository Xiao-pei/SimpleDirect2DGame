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

void Game::OnRender()
{
		currentLevel->Load();
		currentLevel->OnRender();
}

void Game::Update()
{
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
	currentLevel->Unload();
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pDirect2dFactory);

}

bool Game::Init(HWND hwnd, ID2D1Factory* id2d1factory)
{
	m_hwnd = hwnd;
	m_pDirect2dFactory = id2d1factory;
	if(m_pDirect2dFactory!=NULL)
	{
		CreateDeviceResources();
		return true;
	}
	else { return false; }

}

int Game::Run()
{
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			BeginDraw();
			//currentLevel->Update();
			OnRender();
			EndDraw();
		}
	}
	return 0;
}

void Game::BeginDraw()
{
	m_pRenderTarget->BeginDraw();
}

void Game::EndDraw()
{
	m_pRenderTarget->EndDraw();
}

void Game::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}
