#pragma once
class Character
{
private:
	float x_position;
	float y_position;
	float last_x_position;
	float last_y_position;
	float x_velocity;
	float y_velocity;
	float height;
	float width;
	float time;
	float animation_time;

	//folowing bools described the state of character
	bool moving;
	bool moving_dowm;
	bool moving_up;
	bool moving_left;
	bool moving_right;
	bool moving_enable;
	bool facing_left;


	const float jump_time_length = 0.3;
	const float camera_time_length = 0.3;

	ID2D1Bitmap* bmp;
	ID2D1Bitmap* fliped_bmp;
	D2D_RECT_F frame[4];
	int frame_index;
	D2D_RECT_F character_position_rect_left;
	D2D_RECT_F character_position_rect_right;

public:
	Character(ID2D1Bitmap* bitmap, ID2D1Bitmap* fliped_bitmap);
	void Update(double delta);
	void OnRender(ID2D1HwndRenderTarget* pRenderTarget);
	float getXPosition();
	float getYPosition();
	bool isMoving();
	~Character();
};
