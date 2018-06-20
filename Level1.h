#pragma once
#include "GameLevel.h"


class Level1 :
	public GameLevel
{
private:
	ID2D1Bitmap * bmp_floor = NULL;
	ID2D1BitmapBrush* m_pBitmapBrush = NULL;
	Character* main_character = NULL;
	std::vector<Block*> blocks;
	SimpleCollision* collision = NULL;
	Invader *enemy = NULL;
	Invader *invader = NULL;
	Intruder* intruder = NULL;
	Intruder* intruder1 = NULL;
	FileReader *file_reader = NULL;
	std::vector<float> *beats = NULL;
	std::vector<Actor*> actors; //vector of collision and rendering

	int beats_index = 0;
	float x = 0.0f;
	float y = 0.0f;
	float time;
	//folowing variables described "camera" position
	float grid_x = 0;
	float grid_y = 0;
	std::vector<int> * blocks_position = NULL;
public:
	Level1(ID2D1HwndRenderTarget* rt)
	{
		load_next_level = false;
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}
	~Level1();
	void Load() override;
	void OnRender() override;
	void Update(double delta) override;
	GameLevel* LoadNextLevel() override;

};
