#pragma once
#include "GameLevel.h"
#include"StartScreen.h"

class Success :
	public GameLevel
{
private:
	ID2D1Bitmap* bitmap_success = NULL;
	ID2D1Bitmap* bitmap_overlay = NULL;
	double time = 0;
public:
	Success(ID2D1HwndRenderTarget* rt)
	{
		load_next_level = false;
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}

	~Success();
	void OnRender() override;
	void Update(double delta) override;
	void Load() override;
	GameLevel* LoadNextLevel() override;
};
