#pragma once

#include "stdafx.h"
#include <wincodec.h>
#include "Saferelease.h"

//#include "Shared.h"

class BitmapLoader
{
protected:
	ID2D1Bitmap* bmp = NULL;
	ID2D1HwndRenderTarget* render_targets_ = NULL;
	IWICImagingFactory *pwicFactory = NULL;
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapFlipRotator *pFlipRotator = NULL;
	IWICBitmapScaler *pScaler = NULL;

	HRESULT createBitmap(const wchar_t* path ,const bool flip);
	
public:
	BitmapLoader(ID2D1HwndRenderTarget* render_targets); //constructor
	~BitmapLoader();
	ID2D1Bitmap* getBitmap(const wchar_t* path) // picture to D2D1Bitmap
	{
		createBitmap(path,false);
		return bmp;
	}
	ID2D1Bitmap* getFlipedBitmap(const wchar_t* path) // picture to D2D1Bitmap
	{
		bmp = NULL;
		createBitmap(path,true);
		return bmp;
	}
};
