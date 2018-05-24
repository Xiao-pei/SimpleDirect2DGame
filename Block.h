#pragma once
#include "Saferelease.h"

class Block
{
private:
	float x_position = 0;
	float y_position = 0;
	float width;
	float height;
	float time = 0;
	bool destoryable;
	bool destoried;
	bool is_above; //if the block's position is above the character
	//it will be draw after the character

	ID2D1Bitmap* bmp;
	D2D_RECT_F position_rect;
	D2D_RECT_F source_rect;
public:
	Block();
	~Block();
	void initBlock(ID2D1Bitmap* bitmap);
	void initDestroyableBlock(ID2D1Bitmap* bitmap);
	void Update(double delta);
	void OnRender(ID2D1HwndRenderTarget* pRenderTarget);
	float getXPosition();
	float getYPosition();
	bool isAboveCharacter(float y);
	bool getIsAbove();
	void setPosition(float, float);
	void setIsAbove(bool);
};
