#pragma once
#include "stdafx.h"
#include "GameLevel.h"
#include "TestLevel.h"
#include "resource.h"

class Game //ÓÎÏ·Ö÷Àà
{
private:
	GameLevel * currentLevel;

	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	void LoadLevel();
	HRESULT OnRender();
	static LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

public:
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory = NULL;
	ID2D1HwndRenderTarget* m_pRenderTarget = NULL;

	Game();
	~Game();
	HRESULT Init();
	void Run();
	void OnResize(
		UINT width,
		UINT height
	);
};
