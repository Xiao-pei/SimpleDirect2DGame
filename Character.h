#pragma once
#include "Actor.h"
#include "Audio.h"

class Character : public Actor
{
private:
	float last_x_position;
	float last_y_position;
	float init_x;
	float init_y;
	float height;
	float width;
	float attack_frame_width;
	float attack_frame_height;
	float attack_time;
	float jump_time;

	//folowing bools described the state of character
	bool acting;
	bool moving;
	bool begin_moving;
	bool facing_left;

	const float jump_time_length = 0.3;

	ID2D1Bitmap* bmp_attack;
	ID2D1Bitmap* bmp_attack_right;
	ID2D1Bitmap* bmp_attack_left;
	ID2D1Bitmap* bmp_attack_down;
	ID2D1Bitmap* bmp_attack_up;
	D2D_RECT_F attack_frame[3];
	D2D_RECT_F attack_target;
	int attack_frame_index;
	int attack_direction;
	Audio* player;
	int sound_index;
	D2D_RECT_F frame[4];
	int frame_index;
	D2D_RECT_F character_position_rect;

	void RenderAttack(ID2D1HwndRenderTarget* pRenderTarget);

public:
	Character(ID2D1HwndRenderTarget* rt);
	void Update(double delta) override;
	void OnRender(ID2D1HwndRenderTarget* pRenderTarget) override;
	float getDestinationX() override;
	float getDestinationY() override;
	float getInitx() { return init_x; }
	float getInity() { return init_y; }
	bool isAboutToMove() override;
	bool isMoving();
	void collidedWithActor() override;
	void collidedWithBlock() override;
	void setMovingEnable(bool b);
	void setPosition(int x, int y) override;
	void beingAttacked() override;
	~Character();
};
