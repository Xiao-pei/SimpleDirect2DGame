#include "stdafx.h"
#include "TestLevel.h"


void Testlevel::Load()
{
	bmp = bitmap_loader_->getBitmap(L"B.jpg");
}

void Testlevel::Unload()
{
}

void Testlevel::OnRender()
{
	D2D1_SIZE_F size = bmp->GetSize();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	m_pRenderTarget->DrawBitmap(
		bmp,
		D2D1::RectF(
			0,
			0,
			size.width,
			size.height)
	);
}

void Testlevel::Update()
{
}
