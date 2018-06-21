#include "stdafx.h"
#include "Intruder.h"
#include "Saferelease.h"


Intruder::Intruder(ID2D1HwndRenderTarget* rt)
{
	jump_time = 0.0f;
	collide_count = 0;
	life = 3;
	time = 0.0f;
	bitmap_loader = new BitmapLoader(rt);
	bmp = bitmap_loader->getBitmap(L"char3.png");
	fliped_bmp = bitmap_loader->getFlipedBitmap(L"char3.png");
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
	moving = false;
	begin_moving = false;
	moving_state = STILL;
	moving_enable = false;
	continue_moving = false;
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
	frame_index = (int)(time * 8) % 4;
	if (target->isDead() == false && !moving) //decide the moing direction of the Intruder
	{
		moving_state = STILL;
		if (collide_count > 1)
		{
			continue_moving = true;
			if (collided_direction == UP || collided_direction == DOWN)
			{
				if (target->getXPosition() < x_position)
					moving_state = LEFT;
				else
					moving_state = RIGHT;
			}
			else
			{
				if (target->getYPosition() < y_position)
					moving_state = UP;
				else
					moving_state = DOWN;
			}
		}
		else if (std::abs(target->getYPosition() - y_position) < TILE_WIDTH / 3)
		{
			if (target->getXPosition() < x_position)
				moving_state = LEFT;
			else
				moving_state = RIGHT;
		}
		else if (target->getYPosition() < y_position)
			moving_state = UP;
		else
			moving_state = DOWN;

		if (continue_moving && !collide_count)
		{
			moving_state = collided_direction;
		}
	}

	if (time - last_jump_time > jump_time_length * 4 && !moving &&moving_enable)
	{
		jump_time = 0;
		last_jump_time = time;
		moving = true;
		begin_moving = true;
		last_y_position = y_position;
		last_x_position = x_position;
	}

	if (moving)
	{
		if (moving_state == DOWN)
		{
			y_position = last_y_position + ((-TILE_WIDTH) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - 2 * jump_time_length));
		}
		if (moving_state == UP)
		{
			y_position = last_y_position - ((-TILE_WIDTH) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - 2 * jump_time_length));
		}
		if (moving_state == LEFT)
		{
			x_position = last_x_position - ((-TILE_WIDTH) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - 2 * jump_time_length));
			y_position = last_y_position - ((-64) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - jump_time_length));
		}
		if (moving_state == RIGHT)
		{
			x_position = last_x_position + ((-TILE_WIDTH) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - 2 * jump_time_length));
			y_position = last_y_position - ((-64) / (jump_time_length * jump_time_length))
				* (jump_time * (jump_time - jump_time_length));
		}
		if (jump_time > jump_time_length)
		{
			if (moving_state == LEFT || moving_state == RIGHT)
				y_position = last_y_position;
			moving_state = STILL;
			moving_enable = false;
			moving = false;
			if (collide_count == 0)
				continue_moving = false;
			collide_count = 0;
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
	if (moving_state == RIGHT)
	{
		return x_position + TILE_WIDTH;
	}
	else if (moving_state == LEFT)
	{
		return x_position - TILE_WIDTH;
	}
	else
		return x_position;
}

float Intruder::getDestinationY()
{
	if (moving_state == DOWN)
	{
		return y_position + TILE_WIDTH;
	}
	else if (moving_state == UP)
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

void Intruder::collidedWithActor()
{
	moving_state = STILL;
	moving_enable = false;
	moving = false;
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

void Intruder::collidedWithBlock()
{
	collide_count++;
	collided_direction = moving_state;
	collidedWithActor();
}

void Intruder::setTarget(Actor* actor)
{
	target = actor;
}
