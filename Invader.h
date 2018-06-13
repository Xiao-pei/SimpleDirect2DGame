#pragma once
#include "Actor.h"
class Invader :
	public Actor
{
private:
	int frame_index;
	double jump_time;
	const float jump_time_length = 0.3;
	D2D_RECT_F frame[4];

	float last_x_position;
	float last_y_position;
	float height;
	float width;
	float time;
	float last_jump_time;

	bool begin_moving;
	bool facing_left;
	Audio* player;
	ID2D1Bitmap* bmp;
	ID2D1Bitmap* fliped_bmp;
	D2D_RECT_F character_position_rect;
public:
	Invader(ID2D1Bitmap* bitmap, ID2D1Bitmap* fliped_bitmap);
	~Invader();
	void Update(double delta) override;
	void OnRender(ID2D1HwndRenderTarget* pRenderTarget) override;
	void setPosition(int x, int y) override;
	float getDestinationX() override;
	float getDestinationY() override;
	void collidedWithActor() override;
	bool isAboutToMove() override;
	void collidedWithBlock() override;
	void beingAttacked() override;
};

