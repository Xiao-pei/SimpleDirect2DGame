#include "stdafx.h"
#include "TestLevel.h"


void Testlevel::Load()
{
	if(bmp==NULL)
		bmp = bitmap_loader_->getBitmap(L"wall-1.png");
}

void Testlevel::Unload()
{
	m_pBitmapBrush->Release();
	bmp->Release();
}

void Testlevel::OnRender()
{
	D2D1_SIZE_F size = bmp->GetSize();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	//m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(90, D2D1::Point2F(size.width, size.height)));
/*	m_pRenderTarget->CreateBitmapBrush(
		bmp,
		&m_pBitmapBrush
	);
	m_pRenderTarget->FillRectangle(
		&D2D1::RectF(
		bmpx + 0,
		bmpy + 0,
		bmpx + size.width*0.8,
		bmpy + size.height*0.8),
		m_pBitmapBrush
	);*/

	m_pRenderTarget->DrawBitmap(
		bmp,
		D2D1::RectF(
			bmpx + 0,
			bmpy + 0,
			bmpx + size.width*0.8,
			bmpy + size.height*0.8)
	);
	
}

void Testlevel::Update()
{
}
