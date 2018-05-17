#include "stdafx.h"
#include "Character.h"
#include "Saferelease.h"
#include "KbManager.h"


Character::Character(ID2D1Bitmap* bitmap)
{
	time = 0.0f;
	bmp = bitmap;
	width = bmp->GetSize().width / 4;
	height = bmp->GetSize().height / 2;
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
	x_position = TILE_WIDTH * 3;
	y_position = TILE_WIDTH * 3;
	last_x_position = x_position;
	last_y_position = y_position;
	x_velocity = 0;
	y_velocity = 0;
	moving = false;
	moving_dowm = false;
	moving_up = false;
	moving_left = false;
	moving_right = false;
	moving_enable = false;
	grid_x = 0;
	grid_y = 0;
}

void Character::Update(double delta)
{
	time += delta / 1000;

	frame_index = (int)(time * 10) % 4;

	if (KbManager::isActionKeyDown())
	{
		if (!moving)
		{
			time = 0;
			moving = true;
			last_y_position = y_position;
			last_x_position = x_position;
			last_grid_x = grid_x;
			last_grid_y = grid_y;
		}
	}
	if (moving && !moving_enable)
	{
		if (KbManager::isZKeyDown())
			moving_dowm = true;
		else if (KbManager::isAKeyDown())
			moving_up = true;
		else if (KbManager::isLeftArrowDown())
			moving_left = true;
		else if (KbManager::isRightArrowDown())
			moving_right = true;
		else;
		moving_enable = true;
	}
	else { KbManager::discardMessage(); }

	if (moving && moving_enable)
	{
		if (moving_dowm)
		{
			y_position = last_y_position + ((-TILE_WIDTH) / (jump_time_length * jump_time_length)) * (time * (time - 2 *
				jump_time_length));
			grid_y = last_grid_y - ((-TILE_WIDTH) / (camera_time_length * camera_time_length)) * (time * (time - 2 *
				camera_time_length));
		}
		if (moving_up)
		{
			y_position = last_y_position - ((-TILE_WIDTH) / (jump_time_length * jump_time_length)) * (time * (time - 2 *
				jump_time_length));
			grid_y = last_grid_y + ((-TILE_WIDTH) / (camera_time_length * camera_time_length)) * (time * (time - 2 *
				camera_time_length));
		}
		if (moving_left)
		{
			x_position = last_x_position - ((-TILE_WIDTH) / (jump_time_length * jump_time_length)) * (time * (time - 2 *
				jump_time_length));
			grid_x = last_grid_x + ((-TILE_WIDTH) / (camera_time_length * camera_time_length)) * (time * (time - 2 *
				camera_time_length));
		}
		if (moving_right)
		{
			x_position = last_x_position + ((-TILE_WIDTH) / (jump_time_length * jump_time_length)) * (time * (time - 2 *
				jump_time_length));
			grid_x = last_grid_x - ((-TILE_WIDTH) / (camera_time_length * camera_time_length)) * (time * (time - 2 *
				camera_time_length));
		}
		if (time > jump_time_length)
		{
			moving_up = false;
			moving_dowm = false;
			moving_left = false;
			moving_right = false;
			moving_enable = false;
			moving = false;
		}
	}
	character_position_rect = D2D1::RectF(x_position, y_position, x_position + TILE_WIDTH, y_position + TILE_WIDTH);
}

void Character::OnRender(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(grid_x, grid_y));
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
