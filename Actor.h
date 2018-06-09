#pragma once
#include "stdafx.h"
#include "Audio.h"

class Actor
{
protected:
	float x_position;
	float y_position;
	int life;
	bool dead;
public:
	Actor() = default;
	virtual ~Actor() = default;
	virtual void Update(double delta) = 0; //update
	virtual void OnRender(ID2D1HwndRenderTarget* pRenderTarget) = 0;
	virtual bool isAboutToMove() = 0;
	virtual void beingAttacked()=0;
	//	virtual bool isMoving()=0;
	bool isDead() { return dead; }
	float getXPosition() { return x_position; }
	float getYPosition() { return y_position; }
	//	virtual void setMovingEnable(bool b);
	virtual float getDestinationX() = 0;
	virtual float getDestinationY() = 0;
	virtual void collided() = 0;
	virtual void setPosition(int x, int y) = 0;
};
