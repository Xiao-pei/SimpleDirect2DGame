#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"

class Testlevel :public GameLevel
{
	ID2D1Bitmap* bmp=NULL;
	ID2D1BitmapBrush *m_pBitmapBrush;
	float bmpx=0;
	float bmpy=0;
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
