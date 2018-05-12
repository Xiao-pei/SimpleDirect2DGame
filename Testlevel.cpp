#include "stdafx.h"
#include "TestLevel.h"
#include "Saferelease.h"


void Testlevel::Load()
{
	if (bmp == NULL)
		bmp = bitmap_loader_->getBitmap(L"floor-0.png");
	if (test_character_bmp == NULL)
	{
		test_character_bmp = bitmap_loader_->getBitmap(L"fire_elemental1.png");
		test_height = test_character_bmp->GetSize().height/2;
		test_width = test_character_bmp->GetSize().width/4;
	}
		
	if (m_pBitmapBrush == NULL)
		m_pRenderTarget->CreateBitmapBrush(
			bmp,
			&m_pBitmapBrush
		);
	for(int i=0;i<4;i++) // create my frame rect
	{
		frame[i] = D2D1::RectF(
			i*test_width,
			0,
			(i + 1)*test_width,
			test_height
		);
	}
}

void Testlevel::Unload()
{
	m_pBitmapBrush->Release();
	SafeRelease(&m_pBitmapBrush);
	bmp->Release();
}

void Testlevel::OnRender()
{
	D2D1_SIZE_F size = bmp->GetSize();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	//m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(45, D2D1::Point2F(size.width, size.height)));

	D2D1_RECT_F rcBrushRect = D2D1::RectF(0, 0, size.width * 13, size.height * 13);
	m_pBitmapBrush->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	m_pBitmapBrush->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	m_pRenderTarget->FillRectangle(
		&rcBrushRect,
		m_pBitmapBrush
	);
	m_pRenderTarget->DrawBitmap(test_character_bmp, character_position_rect,
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame[frame_index]
	);
}

void Testlevel::Update(double delta)
{
	time += delta / 1000;
	frame_index = (int)(time * 10) % 4;

	
	const float jump_time_length = 0.2;
	if (KbManager::isSpaceDown())
	{
		if (!moving)
		{
			moving = true;
			time = 0;
			tmpy = y;
			tmpcy = character_y;
		}
	}
	
	if (moving)
	{
		y = tmpy - ((-96) / (jump_time_length * jump_time_length)) * (time * (time - 2 * jump_time_length));
		character_y = tmpcy + ((-96) / (jump_time_length * jump_time_length)) * (time * (time - 2 * jump_time_length));
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
		if ((time > jump_time_length))
			moving = false;
	}
	character_position_rect = D2D1::RectF(character_x+96 * 3, character_y + 96 * 3, character_x + test_width + 96 * 3, character_y + test_height + 96 * 3);
	
}
