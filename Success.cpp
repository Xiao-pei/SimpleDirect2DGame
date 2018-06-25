#include "stdafx.h"
#include "Success.h"


Success::~Success()
{
	SafeRelease(&bitmap_success);
	SafeRelease(&bitmap_overlay);
}

void Success::OnRender()
{
	m_pRenderTarget->DrawBitmap(bitmap_success, D2D1::RectF(0, 0,
		bitmap_success->GetSize().width, bitmap_success->GetSize().height),
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0,
			bitmap_success->GetSize().width,
			bitmap_success->GetSize().height));
	m_pRenderTarget->DrawBitmap(bitmap_overlay,
		D2D1::RectF(0, 0, bitmap_overlay->GetSize().width, bitmap_overlay->GetSize().height),
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0, 0, bitmap_overlay->GetSize().width, bitmap_overlay->GetSize().height));
}

void Success::Update(double delta)
{
	time += delta / 1000;
}

void Success::Load()
{
	if(bitmap_success==NULL)
		bitmap_success = bitmap_loader_->getBitmap(L"win.png");
	if(bitmap_overlay==NULL)
		bitmap_overlay= bitmap_loader_->getBitmap(L"cover.png");
}

GameLevel* Success::LoadNextLevel()
{
	if (load_next_level)
	{
		return new StartScreen(m_pRenderTarget);
	}
	else
		return this;
}
