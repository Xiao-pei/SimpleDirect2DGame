#pragma once
#include "GameLevel.h"


class Testlevel : public GameLevel
{
private:
	ID2D1Bitmap* bmp_floor = NULL;
	ID2D1Bitmap* bmp_vertical_wall = NULL;
	ID2D1Bitmap* bmp_vertical_wall_top = NULL;
	ID2D1Bitmap* bmp_transverse_wall = NULL;
	ID2D1Bitmap* bmp_full_life_bar = NULL;
	ID2D1Bitmap* bmp_empty_life_bar = NULL;
	ID2D1BitmapBrush* m_pBitmapBrushForFloor = NULL;
	ID2D1BitmapBrush* m_pBitmapBrushForVerticalWall = NULL;
	ID2D1BitmapBrush* m_pBitmapBrushForTransverseWall = NULL;
	SimpleCollision* collision = NULL;
	std::vector<Block*> blocks;
	Invader* enemy = NULL;
	Intruder* intruder = NULL;
	FileReader* file_reader = NULL;
	std::vector<float>* beats = NULL;
	std::vector<Actor*> actors; //vector of collision and rendering
	D2D_RECT_F *life_bar_position;

	int beats_index = 0;
	float x = 0.0f;
	float y = 0.0f;
	float time = 0;
	//bool load_next_level = false;
	//folowing variables described "camera" position
	float grid_x = 0;
	float grid_y = 0;
	int full_life_num=0;
	int current_life_num = 0;
	std::vector<int>* blocks_position = NULL;

public:
	Testlevel(ID2D1HwndRenderTarget* rt)
	{
		load_next_level = false;
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}

	~Testlevel();
	void Load() override;
	void OnRender() override;
	void Update(double delta) override;
	GameLevel* LoadNextLevel() override;
};
