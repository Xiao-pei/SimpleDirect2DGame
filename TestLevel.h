#pragma once
#include "GameLevel.h"

#define BLOCKS_NUMBER 20

class Testlevel : public GameLevel
{
private:
	ID2D1Bitmap* bmp_floor = NULL;
	ID2D1Bitmap* bmp_vertical_wall = NULL;
	ID2D1Bitmap* bmp_vertical_wall_top = NULL;
	ID2D1Bitmap* bmp_transverse_wall = NULL;
	ID2D1BitmapBrush* m_pBitmapBrushForFloor = NULL;
	ID2D1BitmapBrush* m_pBitmapBrushForVerticalWall = NULL;
	ID2D1BitmapBrush* m_pBitmapBrushForTransverseWall = NULL;
	SimpleCollision* collision = NULL;
	Invader *enemy = NULL;
	Intruder* intruder = NULL;
	FileReader *beats_reader = NULL;
	std::vector<float> *beats = NULL;
	std::vector<Actor*> actors; //vector of collision and rendering

	int beats_index=0;
	float x = 0.0f;
	float y = 0.0f;
	float time = 0;
	//bool load_next_level = false;
	//folowing variables described "camera" position
	float grid_x=0;
	float grid_y=0;
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
