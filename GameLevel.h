#pragma once
#include "BitmapLoader.h"

class GameLevel
{
public:
	ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
	BitmapLoader* bitmap_loader_=NULL;
	virtual ~GameLevel() = default;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void OnRender() = 0;
};
