#pragma once
#include "GameLevel.h"
class StartScreen :
	public GameLevel
{
private:
	ID2D1Bitmap * bitmap = NULL;
	ID2D1Bitmap* bitmap_start = NULL;
	ID2D1Bitmap* bitmap_overlay = NULL;
	bool dispaly_start = false;
	double time=0;
public:
	StartScreen(ID2D1HwndRenderTarget* rt)
	{
		load_next_level = false;
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}
	~StartScreen();
	void OnRender() override;
	void Update(double delta) override;
	void Load() override;
	GameLevel* LoadNextLevel() override;
};

