#include "stdafx.h"
#include "Block.h"


Block::Block()
{
	destoryable = false;
	destoried = false;
	is_above = false;
	bmp = NULL;
}

Block::~Block()
{
	SafeRelease(&bmp);
}

void Block::initBlock(ID2D1Bitmap* bitmap)
{
	bmp = bitmap;
	width = bitmap->GetSize().width;
	height = bitmap->GetSize().height;
	source_rect = D2D1::RectF(0, 0, width, height);
}

void Block::initDestroyableBlock(struct ID2D1Bitmap* bitmap)
{
	bmp = bitmap;
	destoryable = true;
	width = bitmap->GetSize().width;
	height = bitmap->GetSize().height;
	source_rect = D2D1::RectF(0, 0, width, height);
}

void Block::Update(double delta)
{
	time += delta / 1000;
	position_rect = D2D1::RectF(x_position - width, y_position - height, x_position, y_position);
}

void Block::OnRender(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (!destoryable || !destoried)
		pRenderTarget->DrawBitmap(bmp, position_rect,
		                          1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, source_rect
		);
}

float Block::getXPosition()
{
	return x_position;
}

float Block::getYPosition()
{
	return y_position;
}

bool Block::isAboveCharacter(float y)
{
	if (y_position >= y)
		return false;
	else
		return true;
}

bool Block::getIsAbove()
{
	return is_above;
}

bool Block::isDestroied()
{
	return destoried;
}

bool Block::isDestoryable()
{
	return destoryable;
}

void Block::setPosition(float x, float y)
{
	x_position = x * TILE_WIDTH;
	y_position = y * TILE_WIDTH;
}

void Block::setIsAbove(bool above)
{
	is_above = above;
}

bool Block::blockDestoried()
{
	if (destoryable&&!destoried)
	{
		destoried = true;
		return true;
	}
	else { return false; }
		
}
