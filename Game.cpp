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

void Game::LoadLevel() //load level and reset timer
{
	timer->Reset();
	currentLevel = new StartScreen(m_pRenderTarget);
	currentLevel->Load();
}

void Game::OnRender()
{
	currentLevel->OnRender();
	timer->Update();
}

void Game::Update(double delta)
{
	currentLevel->Update(delta);
	if (currentLevel->isLoadingNextLevel())
	{
		GameLevel* pre = currentLevel;
		currentLevel = currentLevel->LoadNextLevel();
		delete pre;
		currentLevel->Load();
		currentLevel->Update(delta);
	}
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

Game::~Game() //relaease resources
{
	delete currentLevel;
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pDirect2dFactory);
}

bool Game::Init(HWND hwnd, ID2D1Factory* id2d1factory)
{
	m_hwnd = hwnd;
	m_pDirect2dFactory = id2d1factory;
	if (m_pDirect2dFactory != NULL)
	{
		CreateDeviceResources();
		timer = new Timer();
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
			Update(timer->getDeltaTime());
			BeginDraw();
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
