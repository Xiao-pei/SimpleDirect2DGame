#include "stdafx.h"
#include "StartScreen.h"
#include "TestLevel.h"


StartScreen::~StartScreen()
{
	SafeRelease(&bitmap);
}

void StartScreen::OnRender()
{
	m_pRenderTarget->DrawBitmap(bitmap, D2D1::RectF(0, 0,
		bitmap->GetSize().width, bitmap->GetSize().height),
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0,
			bitmap->GetSize().width, bitmap->GetSize().height) );
}

void StartScreen::Update(double delta)
{
	time += delta/1000;
	if (time > 10)
		load_next_level = true;
}

void StartScreen::Load()
{
	if (bitmap == NULL)
		bitmap = bitmap_loader_->getBitmap(L"B.jpg");
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
