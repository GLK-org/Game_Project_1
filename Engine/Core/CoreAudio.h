#pragma once
#include "../pch/Engine.h"
#include <xaudio2.h>
#include <string>
#include <stdio.h>
#include "E:\VS_projects\Game_engine_1\resources\resource.h"
using namespace std;
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


class IWIN : public IStream {

public:
	IWIN() : IStream() {};
	HRESULT Clone(
		 IStream** ppstm
	)override {
		return S_OK;
	};
	HRESULT Commit(
		 DWORD grfCommitFlags
	)override {
		return S_OK;
	};
	HRESULT CopyTo(
		  IStream* pstm,
		  ULARGE_INTEGER cb,
		ULARGE_INTEGER* pcbRead,
		 ULARGE_INTEGER* pcbWritten
	)override {
		return S_OK;
	};
	HRESULT LockRegion(
		 ULARGE_INTEGER libOffset,
		 ULARGE_INTEGER cb,
		 DWORD          dwLockType
	)override {
		return S_OK;
	};
	HRESULT Revert()override {
		return S_OK;
	};
	HRESULT Seek(
		  LARGE_INTEGER  dlibMove,
		  DWORD          dwOrigin,
		 ULARGE_INTEGER* plibNewPosition
	)override {
		return S_OK;
	};
	HRESULT SetSize(
		 ULARGE_INTEGER libNewSize
	)override {
		return S_OK;
	};
	HRESULT Stat(
		 STATSTG* pstatstg,
		 DWORD   grfStatFlag
	)override {
		return S_OK;
	};
	HRESULT UnlockRegion(
		ULARGE_INTEGER libOffset,
		ULARGE_INTEGER cb,
		DWORD          dwLockType
	) override {
		return S_OK;
	};
	HRESULT Read(
		 void* pv,
		 ULONG cb,
		 ULONG* pcbRead
	) override {
		return S_OK;
	};
	HRESULT Write(
		  const void* pv,
		  ULONG      cb,
		  ULONG* pcbWritten
	) override {
		return S_OK;
	};
	ULONG AddRef() override {
		return 0U;
	};
	HRESULT QueryInterface(
		REFIID riid,
		void** ppvObject
	) override {
		return S_OK;
	};
	ULONG Release() override {
		return 0U;
	};
};


class VoiceCallback : public IXAudio2VoiceCallback {
public:
	HANDLE hBufferEndEvent; HANDLE hBufferEnd;
	VoiceCallback() : hBufferEnd(CreateEvent(NULL, FALSE, FALSE, NULL)) {}
	~VoiceCallback() {
		//CloseHandle(hBufferEnd);
		 }

	//Called when the voice has just finished playing a contiguous audio stream.
	void OnStreamEnd() override { SetEvent(hBufferEnd); }

	//Unused methods are stubs
	void OnVoiceProcessingPassEnd() override { SetEvent(hBufferEnd); }
	void OnVoiceProcessingPassStart(UINT32 SamplesRequired) override { SetEvent(hBufferEnd); }
	void OnBufferEnd(void* pBufferContext)override { SetEvent(hBufferEnd); }
	void OnBufferStart(void* pBufferContext) override { SetEvent(hBufferEnd); }
	void OnLoopEnd(void* pBufferContext) override {
		SetEvent(hBufferEnd);
	}
	void OnVoiceError(void* pBufferContext, HRESULT Error) override { SetEvent(hBufferEnd); }
};

class ENGINE_API AudioController {

	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;
	WAVEFORMATEXTENSIBLE wfx;
	VoiceCallback pCallback;
	IXAudio2SourceVoice* pSourceVoice;
	XAUDIO2_BUFFER buffer;
	static XAUDIO2_VOICE_STATE state;
public:
	AudioController();
	HRESULT Initialize();

	HRESULT LoadFromFile(PCSTR uri, XAUDIO2_BUFFER& buffer);
	HRESULT LoadFromFile(PCSTR uri);
	HRESULT LoadFromRes(
		LPCWSTR modulename,
		int resourceName,
		LPCWSTR resourceType );
	//Get to load and play a file, just that will do for now

	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);
	HRESULT Init_Source(XAUDIO2_BUFFER& buffer, VoiceCallback& ref , IXAudio2SourceVoice** pSourceVoice );
	HRESULT Init_Source();
	HRESULT PlayAudio();
	HRESULT PlayAudio(IXAudio2SourceVoice* pSourceVoice );

	HRESULT StopAudio();
	HRESULT Release();
	XAUDIO2_BUFFER& GetBuffer();
	VoiceCallback GetCallback();
	void WaitForCallback();
	void WaitForCallback(VoiceCallback pCb);

	void PlaySimple(
		LPCSTR modulename,
		int resourceName
		);
};

