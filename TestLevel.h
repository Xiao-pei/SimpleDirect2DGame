#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"

class Testlevel : public GameLevel
{
	ID2D1Bitmap* bmp = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;
	float tmpy = 0;
	float x=0;
	float y = 0;
	float time = 0;
	float yvelocity = 0;
	bool moving = false;
public:
	Testlevel(ID2D1HwndRenderTarget* rt)
	{
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}

	void Load() override;
	void Unload() override;
	void OnRender() override;
	void Update(double delta) override;
};
