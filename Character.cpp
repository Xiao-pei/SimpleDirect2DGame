#include "stdafx.h"
#include "Character.h"
#include "Saferelease.h"
#include "KbManager.h"


Character::Character(ID2D1HwndRenderTarget* rt)
{
	jump_time = 0.0f;
	life = 3;
	time = jump_time;
	bitmap_loader = new BitmapLoader(rt);
	bmp = bitmap_loader->getBitmap(L"char1.png");
	fliped_bmp = bitmap_loader->getFlipedBitmap(L"char1.png");
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
	sound_index = 0;
	x_position = TILE_WIDTH * 7;
	y_position = TILE_WIDTH * 5;
	last_x_position = x_position;
	last_y_position = y_position;
	acting = false;
	moving = false;
	begin_moving = false;
	moving_state = STILL;
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
			acting = true;
		}
	}
	if (acting && moving_enable&&!moving)
	{
		if (KbManager::isZKeyDown())
			moving_state = DOWN;
		else if (KbManager::isAKeyDown())
			moving_state = UP;
		else if (KbManager::isLeftArrowDown())
		{
			moving_state = LEFT;
			facing_left = true;
		}
		else if (KbManager::isRightArrowDown())
		{
			moving_state = RIGHT;
			facing_left = false;
		}
		else;
		begin_moving = true;
		jump_time = 0;
		last_y_position = y_position;
		last_x_position = x_position;
		moving = true;
	}
	else { KbManager::discardMessage(); }

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
			moving = false;
			moving_enable = false;
			acting = false;
		}
	}
	if (getDestinationX() <= 0 || getDestinationY() <= 0||getDestinationX()>51*TILE_WIDTH||getDestinationY()>51*TILE_WIDTH) //character can't go outside of the map
		collidedWithBlock();

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
	if (moving_state == RIGHT)
	{
		return x_position + TILE_WIDTH/1.5;
	}
	else if (moving_state == LEFT)
	{
		return x_position - TILE_WIDTH/1.5;
	}
	else
		return x_position;
}

float Character::getDestinationY()
{
	if (moving_state==DOWN)
	{
		return y_position + TILE_WIDTH/1.5;
	}
	else if (moving_state==UP)
	{
		return y_position - TILE_WIDTH/1.5;
	}
	else
		return y_position;
}


bool Character::isAboutToMove()
{
	if (begin_moving)
	{
		if (jump_time > jump_time_length / 2)
			begin_moving = false;
		return true;
	}
	else
		return false;
}

bool Character::isMoving()
{
	return moving;
}

void Character::collidedWithActor()
{
	switch (sound_index)
	{
	case 0:
		player->PlayMusic(L"sfxsound/attack2.wav");
		sound_index = 1;
		break;
	case 1:
		player->PlayMusic(L"sfxsound/attack3.wav");
		sound_index = 0;
		break;
	}

	moving_state = STILL;
	//moving_enable = false;
	moving = false;
	y_position = last_y_position;
	x_position = last_x_position;
}

void Character::collidedWithBlock()
{
	collidedWithActor();
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

void Character::beingAttacked()
{
	life--;
	if (!life)
	{
		dead = true;
		player->PlayMusic(L"sfxsound/death.wav");
	}
}

Character::~Character()
{
	delete player;
}
