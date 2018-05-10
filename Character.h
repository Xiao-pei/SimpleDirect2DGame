#pragma once
class Character
{
private:
	float x_position;
	float y_position;
	float x_velocity;
	float y_velocity;
	float time;
	ID2D1Bitmap* bmp = NULL;

public:
	Character();
	~Character();
};

