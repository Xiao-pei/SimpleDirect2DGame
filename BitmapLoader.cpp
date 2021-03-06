#include "stdafx.h"
#include "BitmapLoader.h"
#include "Saferelease.h"
#include "resource.h"

BitmapLoader::BitmapLoader(ID2D1HwndRenderTarget* render_targets)
{
	render_targets_ = render_targets;
	CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pwicFactory
	);
}

HRESULT BitmapLoader::createBitmap(const wchar_t* path, const bool flip)
{
	HRESULT hr;
	//Create Decoder
	hr = pwicFactory->CreateDecoderFromFilename(
		path,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&pDecoder);

	if (SUCCEEDED(hr))
		hr = pDecoder->GetFrame(0, &pSource);

	if (SUCCEEDED(hr))
		hr = pwicFactory->CreateFormatConverter(&pConverter);

	if (SUCCEEDED(hr) && flip)
	{
		hr = pwicFactory->CreateBitmapFlipRotator(&pFlipRotator);
		if (SUCCEEDED(hr))
		{
			hr = pFlipRotator->Initialize(
				pSource, // Bitmap source to flip.
				WICBitmapTransformFlipHorizontal);
		}
		pConverter->Initialize(
			pFlipRotator,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	else if (SUCCEEDED(hr))
	{
		pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	hr = render_targets_->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&bmp
	);
	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}
