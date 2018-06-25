#pragma once
#include "Character.h"
#include "Block.h"

class SimpleCollision
{
public:
	SimpleCollision();
	~SimpleCollision() = default;
	bool AreTheyCollided(Actor* character, Block* block);
	bool AreTheyCollided(Actor* attacker, Actor* attackee);
	bool HandleCollision(Actor* character, Block* block);//return true if a block is destroied
	bool HandleCollision(Actor* attacker, Actor* attackee);
};
