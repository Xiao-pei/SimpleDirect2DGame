#include "stdafx.h"
#include "Character.h"
#include "Saferelease.h"
#include "KbManager.h"


Character::Character(ID2D1Bitmap* bitmap)
{
	time = 0.0f;
	bmp = bitmap;
	width = bmp->GetSize().width/4;
	height = bmp->GetSize().height/2;
	for (int i = 0; i<4; i++) // create my frame rect
	{
		frame[i] = D2D1::RectF(
			i*width,
			0,
			(i + 1)*width,
			height
		);
	}
	frame_index = 0;
	x_position = 96 * 3;
	y_position = 96 * 3;
	last_x_position = x_position;
	last_y_position = y_position;
	x_velocity = 0;
	y_velocity = 0;
	moving = false;
}

void Character::Update(double delta)
{
	time += delta/1000;
	const float jump_time_length = 0.3;

	frame_index = (int)(time * 10) % 4;
	if (KbManager::isZKeyDown())
	{
		if (!moving)
		{
			time = 0;
			moving = true;
			last_y_position = y_position;
			last_x_position = x_position;
		}
	}
	if(moving)
	{
		y_position = last_y_position + ((-96) / (jump_time_length * jump_time_length)) * (time * (time - 2 * jump_time_length));
		if ((time > jump_time_length))
			moving = false;
	}
	character_position_rect = D2D1::RectF(x_position , y_position, x_position + 96 , y_position + 96);
}

void Character::OnRender(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->DrawBitmap(bmp, character_position_rect,
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame[frame_index]
	);
}

float Character::getXPosition()
{
	return x_position;
}

float Character::getYPosition()
{
	return y_position;
}

bool Character::isMoving()
{
	return moving;
}


Character::~Character()
{
	SafeRelease(&bmp);
}
