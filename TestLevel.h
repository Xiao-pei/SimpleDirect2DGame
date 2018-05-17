#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"
#include "Character.h"
#include "Saferelease.h"
#include "Block.h"

class Testlevel : public GameLevel
{
	ID2D1Bitmap* bmp = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;
	Character* main_character = NULL;
	Block* blocks = NULL;

	float tmpy = 0;
	float x;
	float y;
	float time = 0;
	bool moving = false;
	//folowing variables described "camera" position
	float grid_x;
	float grid_y;
	float last_grid_x;
	float last_grid_y;

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
	GameLevel* LoadNextLevel() override;
};
