#include "stdafx.h"
#include "Failed.h"
#include "StartScreen.h"


Failed::~Failed()
{
	SafeRelease(&bitmap_failed);
	SafeRelease(&bitmap_overlay);
}

void Failed::OnRender()
{
	m_pRenderTarget->DrawBitmap(bitmap_failed, D2D1::RectF(0, 0,
		bitmap_failed->GetSize().width, bitmap_failed->GetSize().height),
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0,
			bitmap_failed->GetSize().width,
			bitmap_failed->GetSize().height));
	m_pRenderTarget->DrawBitmap(bitmap_overlay,
		D2D1::RectF(0, 0, bitmap_overlay->GetSize().width, bitmap_overlay->GetSize().height),
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0, 0, bitmap_overlay->GetSize().width, bitmap_overlay->GetSize().height));
}

void Failed::Update(double delta)
{
	time += delta / 1000;
}

void Failed::Load()
{
	if (bitmap_failed == NULL)
		bitmap_failed = bitmap_loader_->getBitmap(L"failed.png");
	if (bitmap_overlay == NULL)
		bitmap_overlay = bitmap_loader_->getBitmap(L"cover.png");
}

GameLevel* Failed::LoadNextLevel()
{
	if (load_next_level)
	{
		return new StartScreen(m_pRenderTarget);
	}
	else
		return this;
}
