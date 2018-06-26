#include "stdafx.h"
#include "StartScreen.h"
#include "TestLevel.h"
#include"KbManager.h"
#include "Level1.h"


StartScreen::~StartScreen()
{
	SafeRelease(&bitmap);
	SafeRelease(&bitmap_start);
	SafeRelease(&bitmap_overlay);
}

void StartScreen::OnRender()
{
	m_pRenderTarget->DrawBitmap(bitmap, D2D1::RectF(0, 0,
	                                                bitmap->GetSize().width, bitmap->GetSize().height),
	                            1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0,
	                                                                                    bitmap->GetSize().width,
	                                                                                    bitmap->GetSize().height));
	if (dispaly_start)
		m_pRenderTarget->DrawBitmap(bitmap_start, D2D1::RectF(399, 595,
		                                                      399 + bitmap_start->GetSize().width,
		                                                      595 + bitmap_start->GetSize().height),
		                            1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0,
		                                                                                    bitmap_start->GetSize().width,
		                                                                                    bitmap_start->GetSize().height));
	m_pRenderTarget->DrawBitmap(bitmap_overlay,
	                            D2D1::RectF(0, 0, bitmap_overlay->GetSize().width, bitmap_overlay->GetSize().height),
	                            1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	                            D2D1::RectF(0, 0, bitmap_overlay->GetSize().width, bitmap_overlay->GetSize().height));
}

void StartScreen::Update(double delta)
{
	time += delta / 1000;
	if ((int)(time * 2) % 2 == 1)
		dispaly_start = true;
	else { dispaly_start = false; }

	if (KbManager::isSpaceDown())
		load_next_level = true;
}

void StartScreen::Load()
{
	if (bitmap == NULL)
		bitmap = bitmap_loader_->getBitmap(L"mainmenudemo.png");
	if (bitmap_start == NULL)
		bitmap_start = bitmap_loader_->getBitmap(L"start.png");
	if (bitmap_overlay == NULL)
		bitmap_overlay = bitmap_loader_->getBitmap(L"cover.png");
	if (music == NULL)
	{
		music = new Audio();
		music->PlayMusic(L"Nightcrawler.wav");
		time = 0;
	}
}

GameLevel* StartScreen::LoadNextLevel()
{
	if (load_next_level)
	{
		return new Testlevel(m_pRenderTarget);
	}
	else
		return this;
}
