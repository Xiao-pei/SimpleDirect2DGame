#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"
#include "Character.h"
#include "Block.h"
#include "Audio.h"
#include "SimpleCollision.h"
#define BLOCKS_NUMBER 20

class Testlevel : public GameLevel
{
	ID2D1Bitmap* bmp = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;
	Character* main_character = NULL;
	Block* blocks = NULL;
	Audio* music = NULL;
	SimpleCollision* collision = NULL;

	float tmpy = 0;
	float x = 0.0f;
	float y = 0.0f;
	float time = 0;
	bool moving = false;
	//folowing variables described "camera" position
	float grid_x;
	float grid_y;
	float last_grid_x;
	float last_grid_y;
	int blocks_position[BLOCKS_NUMBER][3] =
	{
		0,1,9, // destoryable, x, y 
		0,1,10,
		1,2,10,
		1,2,13,
		0,2,16,
		1,3,13,
		0,4,4,
		1,14,5,
		1,18,10,
		0,18,19,
		1,18,14,
		0,19,8,
		0,19,9,
		0,19,14,
		0,19,16,
		0,19,17,
		0,19,19,
		0,20,11,
		0,20,12,
		1,20,18
	};

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
