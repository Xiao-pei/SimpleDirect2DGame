#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"
#include "Character.h"
#include "Saferelease.h"
#include "Block.h"
#define BLOCKS_NUMBER 5

class Testlevel : public GameLevel
{
	ID2D1Bitmap* bmp = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;
	Character* main_character = NULL;
	Block* blocks = NULL;

	float tmpy = 0;
	float x=0.0f;
	float y=0.0f;
	float time = 0;
	bool moving = false;
	int blocks_position[BLOCKS_NUMBER][2] = 
	{
		4,8,
		9,8,
		7,6,
		3,3,
		5,2
	};
	//folowing variables described "camera" position
	float grid_x;
	float grid_y;
	float last_grid_x;
	float last_grid_y;

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
	GameLevel* LoadNextLevel() override;
};
