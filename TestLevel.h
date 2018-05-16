#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"
#include "Character.h"
#include "Saferelease.h"

class Testlevel : public GameLevel
{
	ID2D1Bitmap* bmp = NULL;
	ID2D1Bitmap* test_character_bmp = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;

	Character* main_character=NULL;

	float tmpy = 0;
	float x;
	float y;
	float time = 0;
	bool moving = false;
public:
	Testlevel(ID2D1HwndRenderTarget* rt)
	{
		x = 0;
		y = 0;
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}

	void Load() override;
	void Unload() override;
	void OnRender() override;
	void Update(double delta) override;
};
