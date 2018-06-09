#pragma once
#include "BitmapLoader.h"
#include "GameLevel.h"
#include "Character.h"
#include "Block.h"
#include "Audio.h"
#include "SimpleCollision.h"
#include "Actor.h"
#include "Invader.h"
#include <vector>
#include "Intruder.h"
#define BLOCKS_NUMBER 20

class Testlevel : public GameLevel
{
private:
	ID2D1Bitmap* bmp = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;
	Character* main_character = NULL;
	Block* blocks = NULL;
	Audio* music = NULL;
	SimpleCollision* collision = NULL;
	Invader *enemy = NULL;
	Intruder* intruder = NULL;
	std::vector<Actor*> actors; //vector of collision and rendering

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
	int blocks_position[BLOCKS_NUMBER][3] =// destoryable, x, y
	{
		0,1,1,  //y must increase progressively
		0,1,1,
		1,2,1,
		1,1,3,
		0,2,3,
		1,3,3,
		0,4,4,
		0,6,5,
		1,6,7,
		0,10,7,
		1,18,7,
		0,19,8,
		0,10,9,
		0,12,9,
		0,19,9,
		0,19,10,
		0,19,11,
		0,20,11,
		0,20,13,
		1,20,14
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
