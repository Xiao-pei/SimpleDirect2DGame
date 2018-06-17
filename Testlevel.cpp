#include "stdafx.h"
#include "TestLevel.h"
#include "Saferelease.h"
#include "Level1.h"


Testlevel::~Testlevel()
{
	//Testlevel::Unload();
	SafeRelease(&bmp_floor);
	SafeRelease(&bmp_vertical_wall);
	delete blocks;
	if (enemy)
		delete enemy;
	if (intruder)
		delete intruder;
	if (beats_reader)
		delete beats_reader;
	SafeRelease(&m_pBitmapBrushForFloor);
	SafeRelease(&m_pBitmapBrushForVerticalWall);
}

void Testlevel::Load()
{
	//bitmaps for the floor and the boundary
	if (bmp_floor == NULL)
		bmp_floor = bitmap_loader_->getBitmap(L"floor-3.png");
	if (bmp_vertical_wall == NULL)
		bmp_vertical_wall = bitmap_loader_->getBitmap(L"wall-2-mid.png");
	if (bmp_vertical_wall_top == NULL)
		bmp_vertical_wall_top = bitmap_loader_->getBitmap(L"wall-2-up.png");
	if (bmp_transverse_wall == NULL)
		bmp_transverse_wall = bitmap_loader_->getBitmap(L"wall-2.png");

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
		enemy->setPosition(6, 6);
		actors.push_back(enemy);
	}
	if(intruder==NULL)
	{
		intruder=new Intruder(bitmap_loader_->
			getBitmap(L"char3.png"),
			bitmap_loader_->getFlipedBitmap(L"char3.png"));
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

	if (m_pBitmapBrushForFloor == NULL)
		m_pRenderTarget->CreateBitmapBrush(
			bmp_floor,
			&m_pBitmapBrushForFloor
		);
	if (m_pBitmapBrushForVerticalWall == NULL)
		m_pRenderTarget->CreateBitmapBrush(
			bmp_vertical_wall,
			&m_pBitmapBrushForVerticalWall
		);
	if (m_pBitmapBrushForTransverseWall == NULL)
		m_pRenderTarget->CreateBitmapBrush(
			bmp_transverse_wall,
			&m_pBitmapBrushForTransverseWall
		);
}

void Testlevel::Unload()
{
	if(main_character)
		delete main_character;
	if(blocks)
		delete blocks;
	if(enemy)
		delete enemy;
	if(intruder)
		delete intruder;
	if (music)
		delete music;
	if(beats_reader)
		delete beats_reader;
	
}

void Testlevel::OnRender()
{
	D2D1_SIZE_F floor_size = bmp_floor->GetSize();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_RECT_F rcBrushRect = D2D1::RectF(-floor_size.width * 6, -floor_size.height * 5, floor_size.width * 50, floor_size.height * 50);
	m_pBitmapBrushForFloor->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	m_pBitmapBrushForFloor->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	m_pRenderTarget->FillRectangle(
		&rcBrushRect,
		m_pBitmapBrushForFloor
	);	//draw the floor
	D2D1_RECT_F rcBrushRectWallTransverse = D2D1::RectF(-bmp_transverse_wall->GetSize().width, -bmp_transverse_wall->GetSize().height,
		bmp_transverse_wall->GetSize().width*50, 0);
	m_pBitmapBrushForTransverseWall->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	m_pBitmapBrushForTransverseWall->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	m_pRenderTarget->FillRectangle(
		&rcBrushRectWallTransverse,
		m_pBitmapBrushForTransverseWall
	);	//draw the top boundary
	D2D1_SIZE_F top_size = bmp_vertical_wall_top->GetSize();
	m_pRenderTarget->DrawBitmap(bmp_vertical_wall_top,
		D2D1::RectF(-top_size.width,-top_size.height,
			0, 0),									//target rect
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0, 0,
			top_size.width,top_size.height)//source rect
	);

	D2D1_RECT_F rcBrushRectWallVertical = D2D1::RectF(-bmp_vertical_wall->GetSize().width, 0,
		0, bmp_vertical_wall->GetSize().height * 50);
	m_pBitmapBrushForVerticalWall->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	m_pBitmapBrushForVerticalWall->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	
	m_pRenderTarget->FillRectangle(
		&rcBrushRectWallVertical,
		m_pBitmapBrushForVerticalWall);
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


void Testlevel::Update(double delta)
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
		if(beats_index+1<beats->size())
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
						//break;
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

GameLevel* Testlevel::LoadNextLevel()
{
	if(load_next_level)
	{
		return new Level1(m_pRenderTarget);
	}	
	else
		return this;
}
