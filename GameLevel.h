#pragma once
#include "BitmapLoader.h"
#include "KbManager.h"
#include "Actor.h"
#include "Character.h"
#include "Block.h"
#include "Audio.h"
#include "SimpleCollision.h"
#include "Actor.h"
#include "Invader.h"
#include "Intruder.h"
#include "FileReader.h"

class GameLevel
{
protected:
	bool load_next_level;
	ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
	BitmapLoader* bitmap_loader_ = NULL;
	Audio* music = NULL;
	Character* main_character = NULL;
public:

	static bool com(Actor* a, Actor* b)
	{
		if (abs(a->getYPosition() - b->getYPosition()) < 1)
			return a->getXPosition() < b->getXPosition();
		else
			return a->getYPosition() < b->getYPosition();
	}

	virtual void Load() = 0; //load resources
	virtual void Update(double delta) = 0; //update
	virtual void OnRender() = 0; //render
	virtual GameLevel* LoadNextLevel() = 0; //load next level
	bool isLoadingNextLevel() { return load_next_level; }

	virtual ~GameLevel()
	{
		if(music)
			delete music;
		if(main_character)
			delete main_character;
	}
};
