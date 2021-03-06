#include "stdafx.h"
#include "Character.h"
#include "Saferelease.h"
#include "KbManager.h"


void Character::RenderAttack(ID2D1HwndRenderTarget* pRenderTarget)
{
	switch (attack_direction)
	{
	case UP:
		bmp_attack = bmp_attack_up;
		attack_target = D2D1::RectF(x_position - width / 2 - attack_frame_width / 2,
		                            y_position - height - attack_frame_height,
		                            x_position - width / 2 + attack_frame_width / 2,
		                            y_position - height);
		break;
	case DOWN:
		bmp_attack = bmp_attack_down;
		attack_target = D2D1::RectF(x_position - width / 2 - attack_frame_width / 2,
		                            y_position,
		                            x_position - width / 2 + attack_frame_width / 2,
		                            y_position + attack_frame_height);
		break;
	case LEFT:
		bmp_attack = bmp_attack_left;
		attack_target = D2D1::RectF(x_position - width - attack_frame_width,
		                            y_position - attack_frame_height,
		                            x_position - width,
		                            y_position);
		break;
	case RIGHT:
		bmp_attack = bmp_attack_right;
		attack_target = D2D1::RectF(x_position,
		                            y_position - attack_frame_height,
		                            x_position + attack_frame_width,
		                            y_position);
		break;
	}
	pRenderTarget->DrawBitmap(bmp_attack, attack_target,
	                          1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, attack_frame[attack_frame_index]);
	if (attack_frame_index >= 3)
	{
		is_attacking = false;
		attack_frame_index = 0;
	}
}

Character::Character(ID2D1HwndRenderTarget* rt)
{
	jump_time = 0.0f;
	health = 3;
	time = 0.0f;
	attack_time = 0.0;
	bitmap_loader = new BitmapLoader(rt);
	bmp = bitmap_loader->getBitmap(L"char1.png");
	fliped_bmp = bitmap_loader->getFlipedBitmap(L"char1.png");
	bmp_attack_down = bitmap_loader->getBitmap(L"swipe-d.png");
	bmp_attack_up = bitmap_loader->getBitmap(L"swipe-u.png");
	bmp_attack_right = bitmap_loader->getBitmap(L"swipe-r.png");
	bmp_attack_left = bitmap_loader->getBitmap(L"swipe-l.png");
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
	attack_frame_height = bmp_attack_down->GetSize().height;
	attack_frame_width = bmp_attack_down->GetSize().width / 3;
	for (int i = 0; i < 3; i++)
	{
		attack_frame[i] = D2D1::RectF(
			i * attack_frame_width,
			0,
			(i + 1) * attack_frame_width,
			attack_frame_height
		);
	}

	frame_index = 0;
	sound_index = 0;
	attack_frame_index = 0;

	x_position = TILE_WIDTH * 7;
	y_position = TILE_WIDTH * 5;
	last_x_position = x_position;
	last_y_position = y_position;
	acting = false;
	moving = false;
	begin_moving = false;
	moving_state = STILL;
	attack_direction = STILL;
	moving_enable = false;
	is_attacking = false;
	facing_left = true;
	dead = false;
}

void Character::Update(double delta)
{
	jump_time += delta / 1000;
	time += delta / 1000;
	frame_index = (int)(time * 9) % 4;
	if (is_attacking)
	{
		attack_time += delta / 1000;
		if (attack_time > 0.06)
		{
			++attack_frame_index;
			attack_time = 0;
		}
	}

	if (KbManager::isActionKeyDown())
	{
		if (!acting)
		{
			acting = true;
		}
	}
	if (acting && moving_enable && !moving)
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
	else
	{
		KbManager::discardMessage();
		acting = false;
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
			moving = false;
			acting = false;
		}
	}
	if (getDestinationX() <= 0 || getDestinationY() <= 0 || getDestinationX() > 51 * TILE_WIDTH || getDestinationY() > 51 *
		TILE_WIDTH) //character can't go outside of the map
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
		if (is_attacking)
			RenderAttack(pRenderTarget);
	}
}

float Character::getDestinationX()
{
	if (moving_state == RIGHT)
	{
		return x_position + TILE_WIDTH / 1.5;
	}
	else if (moving_state == LEFT)
	{
		return x_position - TILE_WIDTH / 1.5;
	}
	else
		return x_position;
}

float Character::getDestinationY()
{
	if (moving_state == DOWN)
	{
		return y_position + TILE_WIDTH / 1.5;
	}
	else if (moving_state == UP)
	{
		return y_position - TILE_WIDTH / 1.5;
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
		player->PlayMusic(L"sfxsound/kick.wav");
		sound_index = 0;
		break;
	}
	attack_direction = moving_state;
	moving_state = STILL;
	moving = false;
	is_attacking = true;
	y_position = last_y_position;
	x_position = last_x_position;
}

void Character::collidedWithBlock()
{
	player->PlayMusic(L"sfxsound/attack3.wav");
	moving_state = STILL;
	moving = false;
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
	init_x = x_position;
	init_y = y_position;
	last_x_position = x_position;
	last_y_position = y_position;
}

void Character::beingAttacked()
{
	health--;
	if (!health)
	{
		dead = true;
		player->PlayMusic(L"sfxsound/death.wav");
	}
}

Character::~Character()
{
	delete player;
}
