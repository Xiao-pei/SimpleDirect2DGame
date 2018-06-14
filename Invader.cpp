#include "stdafx.h"
#include "Invader.h"
#include "Saferelease.h"


Invader::Invader(ID2D1Bitmap* bitmap, ID2D1Bitmap* fliped_bitmap)
{
	time = 0.0f;
	life = 2;
	jump_time = 0.0f;
	last_jump_time = 0.0f;
	bmp = bitmap;
	fliped_bmp = fliped_bitmap;
	width = bmp->GetSize().width / 4;
	height = bmp->GetSize().height;
	player = new Audio();
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
	moving_state = UP;
	moving_enable = false;
	facing_left = true;
	dead = false;
}

Invader::~Invader()
{
	SafeRelease(&bmp);
	SafeRelease(&fliped_bmp);
	delete player;
}

void Invader::Update(double delta)
{
	time += delta / 1000;
	jump_time += delta / 1000;
	frame_index = (int)(time * 7) % 4;

	if (time - last_jump_time > jump_time_length * 2 && !moving && moving_enable)
	{
		jump_time = 0;
		last_jump_time = time;
		moving = true;
		begin_moving = true;
		last_y_position = y_position;
		last_x_position = x_position;
	}
	if (moving )
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
			if (moving_state == UP)
			{
				moving_state = DOWN;
			}
			else
			{
				moving_state = UP;
			}
			moving_enable = false;
			moving = false;
		}
	}
	character_position_rect = D2D1::RectF(x_position - width,
	                                      y_position - height, x_position, y_position);
}


void Invader::OnRender(ID2D1HwndRenderTarget* pRenderTarget)
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

void Invader::setPosition(int x, int y)
{
	x_position = TILE_WIDTH * x;
	y_position = TILE_WIDTH * y;
	last_x_position = x_position;
	last_y_position = y_position;
}

float Invader::getDestinationX()
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

float Invader::getDestinationY()
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

void Invader::collidedWithActor()
{
	moving_state = STILL;
	//moving_enable = false;
	moving = false;
	y_position = last_y_position;
	x_position = last_x_position;
}

bool Invader::isAboutToMove()
{
	if (begin_moving)
	{
		begin_moving = false;
		return true;
	}
	else
		return false;
}

void Invader::collidedWithBlock()
{
	collidedWithActor();
}

void Invader::beingAttacked()
{
	--life;
	if (!life)
	{
		dead = true;
		player->PlayMusic(L"sfxsound/death.wav");
	}
}
