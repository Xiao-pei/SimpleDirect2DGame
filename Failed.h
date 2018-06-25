#pragma once
#include "GameLevel.h"
class Failed :
	public GameLevel
{
private:
	ID2D1Bitmap * bitmap_failed = NULL;
	ID2D1Bitmap* bitmap_overlay = NULL;
	double time = 0.0f;
public:
	Failed(ID2D1HwndRenderTarget* rt)
	{
		load_next_level = false;
		m_pRenderTarget = rt;
		bitmap_loader_ = new BitmapLoader(m_pRenderTarget);
	}
	~Failed();
	void OnRender() override;
	void Update(double delta) override;
	void Load() override;
	GameLevel* LoadNextLevel() override;
};
