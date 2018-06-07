#pragma once
#include "Character.h"
#include "Block.h"

class SimpleCollision
{
public:
	SimpleCollision();
	~SimpleCollision();
	bool AreTheyCollided(Actor* character, Block* block);
	bool HandleCollision(Actor* character, Block* block);//return true if a block is destroied
};
