#include "stdafx.h"
#include "TestLevel.h"

void Testlevel::Load()
{
	if (bmp == NULL)
		bmp = bitmap_loader_->getBitmap(L"floor-0.png");
	if (main_character == NULL)
	{
		main_character = new Character(bitmap_loader_->
		                               getBitmap(L"char1.png"), bitmap_loader_->getFlipedBitmap(L"char1.png"));
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

	if (m_pBitmapBrush == NULL)
		m_pRenderTarget->CreateBitmapBrush(
			bmp,
			&m_pBitmapBrush
		);
}

void Testlevel::Unload()
{
	m_pBitmapBrush->Release();
	SafeRelease(&m_pBitmapBrush);
	delete main_character;
	delete blocks;
	bmp->Release();
}

void Testlevel::OnRender()
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

	for (int i = 0; i < BLOCKS_NUMBER; ++i)
	{
		if (blocks[i].getIsAbove()) //blocks above character render first
			blocks[i].OnRender(m_pRenderTarget);
	}

	main_character->OnRender(m_pRenderTarget);

	for (int i = 0; i < BLOCKS_NUMBER; ++i)
	{
		if (!blocks[i].getIsAbove())
			blocks[i].OnRender(m_pRenderTarget);
	}

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(grid_x, grid_y));
}

void Testlevel::Update(double delta)
{
	time += delta / 1000;
	for (int i = 0; i < BLOCKS_NUMBER; ++i)
	{
		blocks[i].Update(delta);
	}
	main_character->Update(delta);
	if (main_character->isMoving())
	{
		grid_x = (-main_character->getXPosition()) + TILE_WIDTH * 7;
		grid_y = (-main_character->getYPosition()) + TILE_WIDTH * 5;
	}
	for (int i = 0; i < BLOCKS_NUMBER; i++)
	{
		if (blocks[i].isAboveCharacter(main_character->getYPosition()))
			blocks[i].setIsAbove(true);
		else { blocks[i].setIsAbove(false); }
	}
}

GameLevel* Testlevel::LoadNextLevel()
{
	return nullptr;
}
