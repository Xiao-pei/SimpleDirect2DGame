#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"

class Testlevel :public GameLevel
{
	ID2D1Bitmap* bmp;
public:
	Testlevel(ID2D1HwndRenderTarget* rt)
	{
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}
	void Load() override;
	void Unload() override;
	void OnRender() override;
	void Update() override;
};
