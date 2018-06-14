#include "stdafx.h"
#include "Level1.h"
#define BLOCKS_NUMBER 2

void Level1::Load()
{
	if (bmp == NULL)
		bmp = bitmap_loader_->getBitmap(L"floor-3.png");
	if (main_character == NULL)
	{
		main_character = new Character(bitmap_loader_->
			getBitmap(L"char1.png"),
			bitmap_loader_->getFlipedBitmap(L"char1.png"));
		actors.push_back(main_character);
	}
	if (blocks == NULL)
	{
		blocks = new Block[BLOCKS_NUMBER];
		for (int i = 0; i < BLOCKS_NUMBER; ++i)
		{
			if (blocks_position[i][0] == 0)
				blocks[i].initBlock(bitmap_loader_->
					getBitmap(L"wall-2.png"));
			else
				blocks[i].initDestroyableBlock(bitmap_loader_->
					getBitmap(L"wall-1.png"));
			blocks[i].setPosition(blocks_position[i][1], blocks_position[i][2]);
		}
	}
	if (enemy == NULL)
	{
		enemy = new Invader(bitmap_loader_->
			getBitmap(L"char2.png"),
			bitmap_loader_->getFlipedBitmap(L"char2.png"));
		enemy->setPosition(2, 2);
		actors.push_back(enemy);
	}
	if (intruder == NULL)
	{
		intruder = new Intruder(bitmap_loader_->
			getBitmap(L"char1.png"),
			bitmap_loader_->getFlipedBitmap(L"char1.png"));
		intruder->setPosition(8, 8);
		intruder->setTarget(main_character);
		actors.push_back(intruder);
	}
	if (music == NULL)
	{
		music = new Audio();
		music->PlayMusic(L"Tutorial.wav");
		time = 0;
	}
	if (beats_reader == NULL)
		beats_reader = new BeatsReader();
	if (beats == NULL)
		beats = beats_reader->getBeats(L"Tutorial.txt");

	if (m_pBitmapBrush == NULL)
		m_pRenderTarget->CreateBitmapBrush(
			bmp,
			&m_pBitmapBrush
		);
}

void Level1::Unload()
{
	SafeRelease(&m_pBitmapBrush);
	delete main_character;
	SafeRelease(&bmp);
	delete collision;
	delete music;
	delete enemy;
	delete beats_reader;
	delete intruder;
	delete beats;
}

void Level1::OnRender()
{
	D2D1_SIZE_F size = bmp->GetSize();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	//m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(45, D2D1::Point2F(size.width, size.height)));

	D2D1_RECT_F rcBrushRect = D2D1::RectF(0, 0, size.width * 50, size.height * 50);
	m_pBitmapBrush->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	m_pBitmapBrush->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	m_pRenderTarget->FillRectangle(
		&rcBrushRect,
		m_pBitmapBrush
	);

	std::vector<Actor*>::iterator iterator = actors.begin();
	for (int i = 0; i < BLOCKS_NUMBER;)
	{
		if (iterator != actors.end() && blocks[i].isAboveCharacter((*iterator)->getYPosition()))
			//blocks above character render first
		{
			blocks[i++].OnRender(m_pRenderTarget);
		}
		else
		{
			if (iterator != actors.end())
			{
				(*iterator)->OnRender(m_pRenderTarget);
				++iterator;
			}
			else
				blocks[i++].OnRender(m_pRenderTarget);
		}
	}
	while (iterator != actors.end()) //draw the rest character
		(*iterator++)->OnRender(m_pRenderTarget);

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(grid_x, grid_y));

}

void Level1::Update(double delta)
{
	std::sort(actors.begin(), actors.end(), com);
	time += delta / 1000;
	for (int i = 0; i < BLOCKS_NUMBER; ++i)
	{
		blocks[i].Update(delta);
	}
	for (int i = 0; i < actors.size(); i++)
	{
		if (abs(beats->at(beats_index) - time) < 0.2)
			actors[i]->setMovingEnable(true);
		else { actors[i]->setMovingEnable(false); }
		actors[i]->Update(delta);
	}
	if (beats->at(beats_index) + 0.19 < time)
		beats_index++;
	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i]->isDead())
			actors.erase(actors.begin() + i);
		else if (actors[i]->isAboutToMove()) //if character is about to move, begin to detect collision
		{
			for (int j = 0; j < BLOCKS_NUMBER; j++)
			{
				if (collision->AreTheyCollided(actors[i], &blocks[j]))
				{
					collision->HandleCollision(actors[i], &blocks[j]);
					break;
				}
			}
			for (int j = 0; j < actors.size(); j++)
			{
				if (j != i)
					if (collision->AreTheyCollided(actors[i], actors[j]))
					{
						collision->HandleCollision(actors[i], actors[j]);
						break;
					}
			}
		}
	}
	if (main_character->isMoving())
	{
		grid_x = (-main_character->getXPosition()) + TILE_WIDTH * 7;
		grid_y = (-main_character->getYPosition()) + TILE_WIDTH * 5;
	}

	if (actors.size() == 1 && actors[0] == main_character)
		load_next_level = true; //if level was clean, load next level
}

GameLevel * Level1::LoadNextLevel()
{
	if (load_next_level)
	{
		return nullptr;
	}
	else
		return this;
}
