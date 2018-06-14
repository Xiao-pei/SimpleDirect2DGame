#pragma once
#include "Actor.h"

class Intruder :
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

	int collide_count;
	int collided_direction;
	bool begin_moving;
	bool facing_left;
	bool continue_moving;
//	ID2D1Bitmap* bmp;
//	ID2D1Bitmap* fliped_bmp;
	D2D_RECT_F character_position_rect;
	Actor* target; //use target position to update
public:
	Intruder(ID2D1Bitmap* bitmap, ID2D1Bitmap* fliped_bitmap);
	~Intruder();
	void Update(double delta) override;
	void OnRender(ID2D1HwndRenderTarget* pRenderTarget) override;
	bool isAboutToMove() override;
	float getDestinationX() override;
	float getDestinationY() override;
	void beingAttacked() override;
	void collidedWithActor() override;
	void setPosition(int x, int y) override;
	void collidedWithBlock() override;
	void setTarget(Actor*);
};
