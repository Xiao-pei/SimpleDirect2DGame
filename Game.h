#pragma once
#include "stdafx.h"
#include "GameLevel.h"
#include "TestLevel.h"
#include "resource.h"
#include "Timer.h"

class Game//ÓÎÏ·Ö÷Àà
{
private:
	GameLevel* currentLevel;
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	void OnRender();
	void Update(double delta);

public:
	HWND m_hwnd = NULL;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
	Timer *timer=NULL;

	Game();
	~Game();
	bool Init(HWND hwnd, ID2D1Factory* id2d1factory);
	int Run();
	void LoadLevel();
	void BeginDraw();
	void EndDraw();
	void OnResize(
		UINT width,
		UINT height
	);
};
