#include "stdafx.h"
#include "Invader.h"
#include "Saferelease.h"


Invader::Invader(ID2D1HwndRenderTarget* rt)
{
	time = 0.0f;
	health = 2;
	jump_time = 0.0f;
	last_jump_time = 0.0f;
	health_dispaly_timer = 0.0f;
	bitmap_loader = new BitmapLoader(rt);
	bmp = bitmap_loader->getBitmap(L"char2.png");
	fliped_bmp = bitmap_loader->getFlipedBitmap(L"char2.png");
	heart_full = bitmap_loader->getBitmap(L"heart-full.png");
	heart_empty = bitmap_loader->getBitmap(L"heart-empty.png");
	width = bmp->GetSize().width / 4;
	height = bmp->GetSize().height;
	sound_player = new Audio();
	for (int i = 0; i < 4; i++) // create actor's frame rect
	{
		frame[i] = D2D1::RectF(
			i * width,
			0,
			(i + 1) * width,
			height
		);
	}
	frame_index = 0;
	heart_width = heart_full->GetSize().width / 5;
	heart_height = heart_full->GetSize().height;
	heart_frame_index = 0;
	for (int i = 0; i < 5; i++) // create frame rect for heart
	{
		heart_frame[i] = D2D1::RectF(
			i * heart_width,
			0,
			(i + 1) * heart_width,
			heart_height
		);
	}
	heart_position = new D2D_RECT_F[health];


	moving = false;
	display_health = false;
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
	SafeRelease(&heart_full);
	SafeRelease(&heart_empty);
	if (sound_player)
		delete sound_player;
}

void Invader::Update(double delta)
{
	time += delta / 1000;
	jump_time += delta / 1000;
	frame_index = (int)(time * 7) % 4;
	heart_frame_index = (int)(time * 10) % 5;
	if (display_health)
		health_dispaly_timer += delta / 1000;
	if (health_dispaly_timer > 4)
	{
		display_health = false;
		health_dispaly_timer = 0.0f;
	}

	if (time - last_jump_time > jump_time_length * 2 && !moving && moving_enable)
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
	heart_position[0] = D2D1::RectF(
		x_position - width / 2 - heart_width,
		y_position - height - heart_height,
		x_position - width / 2,
		y_position - height
	);
	heart_position[1] = D2D1::RectF(
		x_position - width / 2,
		y_position - height - heart_height,
		x_position - width / 2 + heart_width,
		y_position - height
	);
	// create target rect for heart
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

		if (display_health)
			for (int i = 0; i < 2; i++)
			{
				if (i < health)
					pRenderTarget->DrawBitmap(heart_full, heart_position[i],
					                          1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, heart_frame[heart_frame_index]
					);
				else
					pRenderTarget->DrawBitmap(heart_empty, heart_position[i],
					                          1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, heart_frame[heart_frame_index]
					);
			}
	}
}

void Invader::setPosition(int x, int y)
{
	x_position = TILE_WIDTH * x - 1;
	y_position = TILE_WIDTH * y - 2;
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
	moving = false;
	y_position = last_y_position;
	x_position = last_x_position;
	sound_player->PlayMusic(L"sfxsound/chop.wav");
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
	moving_state = STILL;
	moving = false;
	y_position = last_y_position;
	x_position = last_x_position;
}

void Invader::beingAttacked()
{
	--health;
	display_health = true;
	if (!health)
	{
		dead = true;
		sound_player->PlayMusic(L"sfxsound/death.wav");
	}
}
