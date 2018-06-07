#pragma once
#include "Actor.h"

class Character:public Actor
{
private:

	float last_x_position;
	float last_y_position;
	float height;
	float width;
	float jump_time;
	float time;

	//folowing bools described the state of character
	bool acting;
	bool begin_moving;
	bool moving_dowm;
	bool moving_up;
	bool moving_left;
	bool moving_right;
	bool moving_enable;
	bool facing_left;
	bool dead;

	const float jump_time_length = 0.3;

	ID2D1Bitmap* bmp;
	ID2D1Bitmap* fliped_bmp;
	D2D_RECT_F frame[4];
	int frame_index;
	D2D_RECT_F character_position_rect;

public:
	Character(ID2D1Bitmap* bitmap, ID2D1Bitmap* fliped_bitmap);
	void Update(double delta) override;
	void OnRender(ID2D1HwndRenderTarget* pRenderTarget) override;
	float getDestinationX() override;
	float getDestinationY() override;
	bool isAboutToMove() override;
	bool isMoving();
	void collided() override;
	void setMovingEnable(bool b);
	void setPosition(int x, int y) override;
	~Character();
};
