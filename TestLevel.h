#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"

class Testlevel : public GameLevel
{
	ID2D1Bitmap* bmp = NULL;
	ID2D1Bitmap* test_character_bmp = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;
	D2D_RECT_F frame[4];
	D2D_RECT_F character_position_rect;
	int frame_index=0;
	float character_x=0;
	float character_y=0;
	float tmpcy = 0;
	float tmpy = 0;
	float x;
	float y;
	float time = 0;
	float yvelocity = 0;
	float test_height = 0;
	float test_width = 0;
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
