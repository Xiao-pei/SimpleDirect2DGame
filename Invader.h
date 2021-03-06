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
	D2D_RECT_F heart_frame[5];
	int heart_frame_index;
	D2D_RECT_F* heart_position;
	ID2D1Bitmap* heart_full;
	ID2D1Bitmap* heart_empty;

	float last_x_position;
	float last_y_position;
	float height;
	float width;
	float heart_width;
	float heart_height;
	float last_jump_time;
	float health_dispaly_timer;

	bool begin_moving;
	bool facing_left;
	bool display_health;
	Audio* sound_player;
	D2D_RECT_F character_position_rect;
public:
	Invader(ID2D1HwndRenderTarget* rt);
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
