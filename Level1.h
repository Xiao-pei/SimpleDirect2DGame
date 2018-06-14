#pragma once
#include "GameLevel.h"


class Level1 :
	public GameLevel
{
private:
	ID2D1Bitmap * bmp = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;
	Character* main_character = NULL;
	Block* blocks = NULL;
	SimpleCollision* collision = NULL;
	Invader *enemy = NULL;
	Intruder* intruder = NULL;
	BeatsReader *beats_reader = NULL;
	std::vector<float> *beats = NULL;
	std::vector<Actor*> actors; //vector of collision and rendering

	int beats_index = 0;
	float x = 0.0f;
	float y = 0.0f;
	float time;
	//folowing variables described "camera" position
	float grid_x = 0;
	float grid_y = 0;
	int blocks_position[2][3] =
	{
		1,1,3,
		0,2,3,
	};
public:
	Level1(ID2D1HwndRenderTarget* rt)
	{
		load_next_level = false;
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}
	void Load() override;
	void Unload() override;
	void OnRender() override;
	void Update(double delta) override;
	GameLevel* LoadNextLevel() override;
};
