#include "stdafx.h"
#include "TestLevel.h"
#include "Saferelease.h"


void Testlevel::Load()
{
	if(bmp==NULL)
		bmp = bitmap_loader_->getBitmap(L"floor-0.png");
	if(m_pBitmapBrush==NULL)
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

	D2D1_RECT_F rcBrushRect = D2D1::RectF(0, 0, size.width*13, size.height*13);
	m_pBitmapBrush->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	m_pBitmapBrush->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	m_pRenderTarget->FillRectangle(
		&rcBrushRect,
		m_pBitmapBrush
	);

//	m_pRenderTarget->DrawBitmap(
//		bmp,
//		D2D1::RectF(
//		bmpx + 0,
//			bmpy + 0,
//			bmpx + size.width*0.8,
//		bmpy + size.height*0.8)
//	);
}

void Testlevel::Update()
{
	if(KbManager::isSpaceDown())
	{
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
		y -= 50;
	}
		
	
}
