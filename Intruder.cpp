#include "stdafx.h"
#include "Intruder.h"
#include "Saferelease.h"


Intruder::Intruder(ID2D1Bitmap* bitmap, ID2D1Bitmap* fliped_bitmap)
{
	jump_time = 0.0f;
	life = 3;
	time = 0.0f;
	bmp = bitmap;
	fliped_bmp = fliped_bitmap;
	width = bmp->GetSize().width / 4;
	height = bmp->GetSize().height;
	for (int i = 0; i < 4; i++) // create my frame rect
	{
		frame[i] = D2D1::RectF(
			i * width,
			0,
			(i + 1) * width,
			height
		);
	}

	frame_index = 0;
	acting = false;
	begin_moving = false;
	moving_dowm = false;
	moving_up = false;
	moving_left = false;
	moving_right = false;
	moving_enable = false;
	facing_left = true;
	dead = false;
}


Intruder::~Intruder()
{
	SafeRelease(&bmp);
	SafeRelease(&fliped_bmp);
}

void Intruder::Update(double delta)
{
	jump_time += delta / 1000;
	time += delta / 1000;
	frame_index = (int)(time * 10) % 4;
	if(target->isDead()==false&&!acting)
	{
		moving_dowm = false;
		moving_up = false;
		moving_right = false;
		moving_left = false;
		if (std::abs(target->getYPosition() - y_position) <TILE_WIDTH/3 )
		{
			if (target->getXPosition()<x_position)
			{
				moving_left = true;
			}
			else
			{
				moving_right = true;
			}
		}
		else if(target->getYPosition()<y_position)
		{
			moving_up = true;

		}
		else
		{
			moving_dowm = true;
		}
	}
	if (time - last_jump_time>jump_time_length * 5 && !acting)
	{
		jump_time = 0;
		last_jump_time = time;
		acting = true;
		begin_moving = true;
		last_y_position = y_position;
		last_x_position = x_position;
		moving_enable = true;
	}
	if (acting && moving_enable)
	{
		if (moving_dowm)
		{
			y_position = last_y_position + ((-TILE_WIDTH) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - 2 * jump_time_length));
		}
		if (moving_up)
		{
			y_position = last_y_position - ((-TILE_WIDTH) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - 2 * jump_time_length));
		}
		if (moving_left)
		{
			x_position = last_x_position - ((-TILE_WIDTH) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - 2 * jump_time_length));
			y_position = last_y_position - ((-64) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - jump_time_length));
		}
		if (moving_right)
		{
			x_position = last_x_position + ((-TILE_WIDTH) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - 2 * jump_time_length));
			y_position = last_y_position - ((-64) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - jump_time_length));
		}
		if (jump_time > jump_time_length)
		{
			if (moving_left || moving_right)
				y_position = last_y_position;
			if (moving_up)
			{
				moving_up = false;
				moving_dowm = true;
			}
			else
			{
				moving_up = true;
				moving_dowm = false;
			}
			moving_enable = false;
			acting = false;
		}
	}
	character_position_rect = D2D1::RectF(x_position - width,
		y_position - height, x_position, y_position);
}

void Intruder::OnRender(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (!dead)
	{
		if (!facing_left)
			pRenderTarget->DrawBitmap(fliped_bmp, character_position_rect,
				1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame[frame_index]
			);
		else
			pRenderTarget->DrawBitmap(bmp, character_position_rect,
				1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame[frame_index]
			);
	}
}

bool Intruder::isAboutToMove()
{
	if (begin_moving)
	{
		begin_moving = false;
		return true;
	}
	else
		return false;
}

float Intruder::getDestinationX()
{
	if (moving_right)
	{
		return x_position + TILE_WIDTH;
	}
	else if (moving_left)
	{
		return x_position - TILE_WIDTH;
	}
	else
		return x_position;
}

float Intruder::getDestinationY()
{
	if (moving_dowm)
	{
		return y_position + TILE_WIDTH;
	}
	else if (moving_up)
	{
		return y_position - TILE_WIDTH;
	}
	else
		return y_position;
}

void Intruder::beingAttacked()
{
	--life;
	if (!life)
	{
		dead = true;
	}
		
}

void Intruder::collided()
{
	moving_up = false;
	moving_dowm = false;
	moving_left = false;
	moving_right = false;
	moving_enable = false;
	acting = false;
	y_position = last_y_position;
	x_position = last_x_position;
}

void Intruder::setPosition(int x, int y)
{
	x_position = TILE_WIDTH * x;
	y_position = TILE_WIDTH * y;
	last_x_position = x_position;
	last_y_position = y_position;
}

void Intruder::setTarget(Actor* actor)
{
	target = actor;
}
