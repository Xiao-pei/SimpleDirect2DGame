#include "stdafx.h"
#include "Level1.h"

Level1::~Level1()
{
	SafeRelease(&bmp_floor);
	SafeRelease(&bmp_vertical_wall);
	SafeRelease(&bmp_vertical_wall_top);
	SafeRelease(&bmp_transverse_wall);
	SafeRelease(&bmp_full_life_bar);
	SafeRelease(&bmp_empty_life_bar);
	SafeRelease(&m_pBitmapBrushForFloor);
	SafeRelease(&m_pBitmapBrushForVerticalWall);
	SafeRelease(&m_pBitmapBrushForTransverseWall);
	if (enemy)
		delete enemy;
	if (intruder)
		delete intruder;
	if (file_reader)
		delete file_reader;
}

void Level1::Load()
{
	if (bmp_floor == NULL)
		bmp_floor = bitmap_loader_->getBitmap(L"floor-3.png");
	if (bmp_vertical_wall == NULL)
		bmp_vertical_wall = bitmap_loader_->getBitmap(L"wall-2-mid.png");
	if (bmp_vertical_wall_top == NULL)
		bmp_vertical_wall_top = bitmap_loader_->getBitmap(L"wall-2-up.png");
	if (bmp_transverse_wall == NULL)
		bmp_transverse_wall = bitmap_loader_->getBitmap(L"wall-2.png");
	if (bmp_full_life_bar == NULL)
		bmp_full_life_bar = bitmap_loader_->getBitmap(L"life-full.png");
	if (bmp_empty_life_bar == NULL)
		bmp_empty_life_bar = bitmap_loader_->getBitmap(L"life-empty.png");

	if (file_reader == NULL)
		file_reader = new FileReader();
	if (beats == NULL)
		beats = file_reader->getBeats(L"MOON.txt");
	if(blocks_position==NULL)
	{
		blocks_position = file_reader->getMap(L"a.txt");
	}
	if (blocks.size()==0)
	{
		for (int i = 0; i < blocks_position->size(); i+=3)
		{
			Block* block = new Block();
			if (blocks_position->at(i) == 0)
				block->initBlock(bitmap_loader_->
					getBitmap(L"wall-2.png"));
			else
				block->initDestroyableBlock(bitmap_loader_->
					getBitmap(L"wall-1.png"));
			block->setPosition(blocks_position->at(i+1), blocks_position->at(i+2));
			blocks.push_back(block);
		}
	}
	if (main_character == NULL)
	{
		main_character = new Character(m_pRenderTarget);
		full_life_num = main_character->getLife();
		life_bar_position = new D2D_RECT_F[full_life_num];
		actors.push_back(main_character);
	}
	if (enemy == NULL)
	{
		enemy = new Invader(m_pRenderTarget);
		enemy->setPosition(2, 2);
		actors.push_back(enemy);
	}
	if(invader==NULL)
	{
		invader = new Invader(m_pRenderTarget);
		invader->setPosition(10, 10);
		actors.push_back(invader);
	}
	if (intruder == NULL)
	{
		intruder = new Intruder(m_pRenderTarget);
		intruder->setPosition(8, 8);
		intruder->setTarget(main_character);
		actors.push_back(intruder);
	}
	if(intruder1==NULL)
	{
		intruder1 = new Intruder(m_pRenderTarget);
		intruder1->setPosition(10, 9);
		intruder1->setTarget(main_character);
		actors.push_back(intruder1);
	}
	if (music == NULL)
	{
		music = new Audio();
		music->PlayMusic(L"MOON.wav");
		time = 0;
	}

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


void Level1::OnRender()
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
	//draw the map boundary
	D2D1_RECT_F rcBrushRectWallTransverseTop = D2D1::RectF(-bmp_transverse_wall->GetSize().width, -bmp_transverse_wall->GetSize().height,
		bmp_transverse_wall->GetSize().width * 50, 0);
	D2D1_RECT_F rcBrushRectWallTransverseButton = D2D1::RectF(-TILE_WIDTH, 50 * TILE_WIDTH,
		TILE_WIDTH * 51, 50 * TILE_WIDTH + bmp_transverse_wall->GetSize().height);
	m_pBitmapBrushForTransverseWall->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	m_pBitmapBrushForTransverseWall->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	m_pRenderTarget->FillRectangle(
		&rcBrushRectWallTransverseTop,
		m_pBitmapBrushForTransverseWall
	);	//draw the top boundary


	D2D1_SIZE_F top_size = bmp_vertical_wall_top->GetSize();
	m_pRenderTarget->DrawBitmap(bmp_vertical_wall_top,
		D2D1::RectF(-top_size.width, -top_size.height,
			0, 0),						//target rect
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0, 0,
			top_size.width, top_size.height)//source rect
	);
	m_pRenderTarget->DrawBitmap(bmp_vertical_wall_top,
		D2D1::RectF(50 * top_size.width, -top_size.height,
			51 * top_size.width, 0),		//target rect
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0, 0,
			top_size.width, top_size.height)//source rect
	);

	D2D1_RECT_F rcBrushRectWallVerticalLeft = D2D1::RectF(-bmp_vertical_wall->GetSize().width, 0,
		0, bmp_vertical_wall->GetSize().height * 50);
	D2D1_RECT_F rcBrushRectWallVerticalRight = D2D1::RectF(50 * bmp_vertical_wall->GetSize().width, 0,
		51 * bmp_vertical_wall->GetSize().width, bmp_vertical_wall->GetSize().height * 50);
	m_pBitmapBrushForVerticalWall->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	m_pBitmapBrushForVerticalWall->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	m_pRenderTarget->FillRectangle(
		&rcBrushRectWallVerticalLeft,
		m_pBitmapBrushForVerticalWall);//draw the left bundary
	m_pRenderTarget->FillRectangle(
		&rcBrushRectWallVerticalRight,
		m_pBitmapBrushForVerticalWall);//draw the right bundary

	m_pRenderTarget->FillRectangle(
		&rcBrushRectWallTransverseButton,
		m_pBitmapBrushForTransverseWall
	);	//draw the button boundary

	std::vector<Actor*>::iterator iterator = actors.begin();
	for (int i = 0; i < blocks.size();)
	{
		if (iterator != actors.end() && blocks[i]->isAboveCharacter((*iterator)->getYPosition()))
			//blocks above character render first
		{
			blocks[i++]->OnRender(m_pRenderTarget);
		}
		else
		{
			if (iterator != actors.end())
			{
				(*iterator)->OnRender(m_pRenderTarget);
				++iterator;
			}
			else
				blocks[i++]->OnRender(m_pRenderTarget);
		}
	}
	while (iterator != actors.end()) //draw the rest character
		(*iterator++)->OnRender(m_pRenderTarget);

	D2D1_RECT_F life_bar_source = D2D1::RectF(0, 0, bmp_full_life_bar->GetSize().width, bmp_full_life_bar->GetSize().height);
	for (int i = 0; i<full_life_num; i++)
	{
		if (i < current_life_num)
			m_pRenderTarget->DrawBitmap(bmp_full_life_bar, life_bar_position[i],
				1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				life_bar_source);
		else
			m_pRenderTarget->DrawBitmap(bmp_empty_life_bar, life_bar_position[i],
				1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				life_bar_source);
	}// draw health bar

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(grid_x, grid_y));

}

void Level1::Update(double delta)
{
	std::sort(actors.begin(), actors.end(), com);
	time += delta / 1000;
	for (int i = 0; i < blocks.size(); ++i)
	{
		blocks[i]->Update(delta);
	}
	for (int i = 0; i < actors.size(); i++)
	{
		if (abs(beats->at(beats_index) - time) < 0.13)
			actors[i]->setMovingEnable(true);
		else { actors[i]->setMovingEnable(false); }
		actors[i]->Update(delta);
	}
	current_life_num = main_character->getLife();
	if (abs(beats->at(beats_index) - time) < 0.17)
		main_character->setMovingEnable(true);//special benefit for character
	if (beats->at(beats_index) + 0.18 < time)
		if (beats_index + 1<beats->size())
			beats_index++;

	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i]->isDead())
			actors.erase(actors.begin() + i);
		else if (actors[i]->isAboutToMove()) //if character is about to move, begin to detect collision
		{
			for (int j = 0; j < blocks.size(); j++)
			{
				if (collision->AreTheyCollided(actors[i], blocks[j]))
				{
					collision->HandleCollision(actors[i], blocks[j]);
					break;
				}
			}
			for (int j = 0; j < actors.size(); j++)
			{
				if (j != i)
					if (collision->AreTheyCollided(actors[i], actors[j]))
					{
						collision->HandleCollision(actors[i], actors[j]);
					}
			}
		}
	}
	if (main_character->isMoving())
	{
		grid_x = (-main_character->getXPosition()) + TILE_WIDTH * 7;
		grid_y = (-main_character->getYPosition()) + TILE_WIDTH * 5;
	}

	life_bar_position[0] = D2D1::RectF(-grid_x + TILE_WIDTH, -(int)grid_y + TILE_WIDTH * 8,
		-grid_x + TILE_WIDTH + bmp_full_life_bar->GetSize().width,
		-(int)grid_y + TILE_WIDTH * 8 + bmp_full_life_bar->GetSize().height);
	for (int i = 1; i<full_life_num; i++)
	{
		life_bar_position[i] = D2D1::RectF(life_bar_position[i - 1].right, life_bar_position[i - 1].top,
			life_bar_position[i - 1].right + bmp_full_life_bar->GetSize().width,
			life_bar_position[i - 1].top + bmp_full_life_bar->GetSize().height);
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
