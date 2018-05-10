#pragma once
#include "BitmapLoader.h"
#include "KbManager.h"

class GameLevel
{
public:
	ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
	BitmapLoader* bitmap_loader_ = NULL;
	virtual ~GameLevel() = default;
	virtual void Load() = 0; //load resources
	virtual void Unload() = 0; //unload all resources
	virtual void Update(double delta) = 0; //update
	virtual void OnRender() = 0; //render
};
