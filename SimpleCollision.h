#pragma once
#include "Character.h"
#include "Block.h"

class SimpleCollision
{
public:
	SimpleCollision();
	~SimpleCollision();
	bool AreTheyCollided(Character* character, Block* block);
	bool HandleCollision(Character* character, Block* block);//return true if a block is destroied
};
