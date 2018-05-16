#include "stdafx.h"
#include "TestLevel.h"

void Testlevel::Load()
{
	if (bmp == NULL)
		bmp = bitmap_loader_->getBitmap(L"floor-0.png");
	if (main_character == NULL)
	{
		main_character = new Character(bitmap_loader_->getBitmap(L"fire_elemental1.png"));
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
	main_character->OnRender(m_pRenderTarget);
}

void Testlevel::Update(double delta)
{
	time += delta / 1000;

	main_character->Update(delta);

	const float jump_time_length = 0.15;
	if (main_character->isMoving())
	{
		time = 0;
		tmpy = y;
		moving = true;
	}
	
	if (moving)
	{
		y = tmpy - ((-96) / (jump_time_length * jump_time_length)) * (time * (time - 2 * jump_time_length));
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
		if ((time > jump_time_length))
			moving = false;
	}
	
}
