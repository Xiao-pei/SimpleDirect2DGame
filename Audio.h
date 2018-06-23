#pragma once
#include "stdafx.h"
#include <string>
//Macros copied from MSDN, Xiao-pei is aware that this game 
//will not run on Xbox platform.
#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

class Audio
{
private:
	IXAudio2* pXAudio2 = NULL;
	IXAudio2MasteringVoice* pMasterVoice = NULL;
	IXAudio2SourceVoice* pSourceVoice = NULL;
	WAVEFORMATEXTENSIBLE wfx = {0};
	XAUDIO2_BUFFER buffer = {0};

public:
	Audio();
	HRESULT Init();
	HRESULT FindChunk(HANDLE hFile, DWORD fourcc,
	                  DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* buffer,
	                      DWORD buffersize, DWORD bufferoffset);
	HRESULT PlayMusic(const wchar_t* path);
	~Audio();
};
