#include "stdafx.h"
#include "TestLevel.h"

void Testlevel::Load()
{
	if (bmp == NULL)
		bmp = bitmap_loader_->getBitmap(L"floor-0.png");
	if (main_character == NULL)
	{
		main_character = new Character(bitmap_loader_->
			getBitmap(L"fire_elemental1.png"));
	}
	if(blocks==NULL)
	{
		blocks = new Block[5];
		for (int i = 0; i < 5; ++i)
		{
			blocks[i].initBlock(bitmap_loader_->
				getBitmap(L"wall-2.png"));
			blocks[i].setPosition(5, i+5);
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
	main_character->OnRender(m_pRenderTarget);
	for (int i = 0; i < 5; ++i)
	{
		blocks[i].OnRender(m_pRenderTarget);
	}

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(grid_x, grid_y));
}

void Testlevel::Update(double delta)
{
	time += delta / 1000;
	for (int i = 0; i < 5; ++i)
	{
		blocks[i].Update(delta);
	}
	main_character->Update(delta);
	if(main_character->isMoving())
	{
		grid_x = (-main_character->getXPosition())+ TILE_WIDTH * 3;
		grid_y = (-main_character->getYPosition())+ TILE_WIDTH * 3;
	}
}
