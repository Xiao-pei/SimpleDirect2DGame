#include "stdafx.h"
#include "SimpleCollision.h"
#include <complex>


SimpleCollision::SimpleCollision()
{
}



bool SimpleCollision::AreTheyCollided(Actor* character, Block* block)
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

bool SimpleCollision::AreTheyCollided(Actor * attacker, Actor * attackee)
{
	float const difference_between_x = attacker->getDestinationX() - attackee->getXPosition();
	float const difference_between_y = attacker->getDestinationY() - attackee->getYPosition();
	if (std::abs(difference_between_x) < (TILE_WIDTH / 2) &&
		std::abs(difference_between_y) < (TILE_WIDTH / 2)) //simple law of "collision"
	{
		return true;
	}
	else return false;
}


bool SimpleCollision::HandleCollision(Actor* character, Block* block)
{
	if(!block->isDestoryable()||!block->isDestroied())
		character->collidedWithBlock();
	return block->blockDestoried();
}

bool SimpleCollision::HandleCollision(Actor * attacker, Actor * attackee)
{
	attacker->collidedWithActor();
	attackee->beingAttacked();
	return attackee->isDead();
}
