#pragma once
#include "stdafx.h"
#include "Audio.h"
#include "Saferelease.h"

class Actor
{
protected:
	enum state { STILL, UP, DOWN, RIGHT, LEFT };
	float x_position;
	float y_position;
	int life;
	int moving_state;
	bool dead;
	bool moving;
	bool moving_enable;
	ID2D1Bitmap* bmp;
	ID2D1Bitmap* fliped_bmp;
public:
	Actor() = default;
	virtual ~Actor()
	{
		SafeRelease(&bmp);
		SafeRelease(&fliped_bmp);
	}
	virtual void Update(double delta) = 0; //update
	virtual void OnRender(ID2D1HwndRenderTarget* pRenderTarget) = 0;
	virtual bool isAboutToMove() = 0;
	virtual void beingAttacked()=0;
	//	virtual bool isMoving()=0;
	bool isDead() { return dead; }
	float getXPosition() { return x_position; }
	float getYPosition() { return y_position; }
	virtual void setMovingEnable(bool e) { moving_enable = e; }
	//	virtual void setMovingEnable(bool b);
	virtual float getDestinationX() = 0;
	virtual float getDestinationY() = 0;
	virtual void collidedWithActor() = 0;
	virtual void collidedWithBlock() = 0;
	virtual void setPosition(int x, int y) = 0;
};
