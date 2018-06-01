#include "stdafx.h"
#include "SimpleCollision.h"
#include <complex>


SimpleCollision::SimpleCollision()
{
}


SimpleCollision::~SimpleCollision()
{
}

bool SimpleCollision::AreTheyCollided(Character* character, Block* block)
{
	float const difference_between_x = character->getDestinationX() - block->getXPosition();
	float const difference_between_y = character->getDestinationY() - block->getYPosition();
	if (std::abs(difference_between_x) < (TILE_WIDTH / 2) &&
		std::abs(difference_between_y) < (TILE_WIDTH / 2)) //simple law of "collision"
	{
		return true;
	}
	else return false;
}

bool SimpleCollision::HandleCollision(Character* character, Block* block)
{
	if(!block->isDestoryable()||!block->isDestroied())
		character->collided();
	return block->blockDestoried();
}
