#include "stdafx.h"
#include "Character.h"
#include "Saferelease.h"
#include "KbManager.h"


Character::Character(ID2D1Bitmap* bitmap, ID2D1Bitmap* fliped_bitmap)
{
	jump_time = 0.0f;
	time = jump_time;
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
	x_position = TILE_WIDTH * 7;
	y_position = TILE_WIDTH * 5;
	last_x_position = x_position;
	last_y_position = y_position;
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

void Character::Update(double delta)
{
	jump_time += delta / 1000;
	time += delta / 1000;
	frame_index = (int)(time * 9) % 4;

	if (KbManager::isActionKeyDown())
	{
		if (!acting)
		{
			jump_time = 0;
			acting = true;
			begin_moving = true;
			last_y_position = y_position;
			last_x_position = x_position;
		}
	}
	if (acting && !moving_enable)
	{
		if (KbManager::isZKeyDown())
			moving_dowm = true;
		else if (KbManager::isAKeyDown())
			moving_up = true;
		else if (KbManager::isLeftArrowDown())
		{
			moving_left = true;
			facing_left = true;
		}
		else if (KbManager::isRightArrowDown())
		{
			moving_right = true;
			facing_left = false;
		}
		else;
		moving_enable = true;
	}
	else { KbManager::discardMessage(); }

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
			moving_up = false;
			moving_dowm = false;
			moving_left = false;
			moving_right = false;
			moving_enable = false;
			acting = false;
		}
	}
	character_position_rect = D2D1::RectF(x_position - width,
	                                           y_position - height, x_position, y_position);
}

void Character::OnRender(ID2D1HwndRenderTarget* pRenderTarget)
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

float Character::getDestinationX()
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

float Character::getDestinationY()
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


bool Character::isAboutToMove()
{
	if (begin_moving)
	{
		begin_moving = false;
		return true;
	}
	else
		return false;
}

bool Character::isMoving()
{
	return acting;
}

void Character::collided()
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

void Character::setMovingEnable(bool b)
{
	moving_enable = b;
}

void Character::setPosition(int x, int y)
{
	x_position = TILE_WIDTH * x;
	y_position = TILE_WIDTH * y;
	last_x_position = x_position;
	last_y_position = y_position;
}

Character::~Character()
{
	SafeRelease(&bmp);
	SafeRelease(&fliped_bmp);
}
