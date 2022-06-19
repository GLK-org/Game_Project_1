 #include "Engine.h"
#include "CoreAudio.h"


AudioController::AudioController() {
    pXAudio2 = nullptr;
    pSourceVoice = nullptr;
    pMasterVoice = nullptr;
  //  pCallback = {};
    wfx = { 0 };
    buffer = { 0 };
};


HRESULT AudioController::Initialize()
{

	HRESULT hr;
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
		return hr;



	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		return hr;

	
	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
		return hr;



	return S_OK;

}

HRESULT AudioController::LoadFromFile(PCSTR uri, XAUDIO2_BUFFER& buffer)
{
    // Open the file
    HANDLE hFile = CreateFile(
        uri,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (INVALID_HANDLE_VALUE == hFile)
        return HRESULT_FROM_WIN32(GetLastError());

    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkSize;
    DWORD dwChunkPosition;
    //check the file type, should be fourccWAVE or 'XWMA'
    FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
    DWORD filetype;
    ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
    if (filetype != fourccWAVE)
        return S_FALSE;

    FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
    ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

    FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
    BYTE* pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);


    buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
    buffer.pAudioData = pDataBuffer;  //buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM;


    return S_OK;
}
HRESULT AudioController::LoadFromFile(PCSTR uri)
{
    // Open the file
    HANDLE hFile = CreateFile(
        uri,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (INVALID_HANDLE_VALUE == hFile)
        return HRESULT_FROM_WIN32(GetLastError());

    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkSize;
    DWORD dwChunkPosition;
    //check the file type, should be fourccWAVE or 'XWMA'
    FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
    DWORD filetype;
    ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
    if (filetype != fourccWAVE)
        return S_FALSE;

    FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
    ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

    FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
    BYTE* pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);


    buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
    buffer.pAudioData = pDataBuffer;  //buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM;


    return S_OK;
}

HRESULT AudioController::LoadFromRes(

    LPCWSTR modulename,
    int resourceName,
    LPCWSTR resourceType) {
    FILE* in;
    HRSRC audioResHandle = NULL;
    HGLOBAL audioResDataHandle = NULL;
    void* pImageFile = NULL;
    
    DWORD imageFileSize = 0;
    IWIN pStream;

    DWORD dwChunkSize;
    DWORD dwChunkPosition;

    HMODULE e = GetModuleHandleW(modulename);

    // Locate the resource.
    audioResHandle = FindResourceW(e, MAKEINTRESOURCEW(resourceName), resourceType);

    HRESULT hr = audioResHandle ? S_OK :  E_FAIL;
    GetLastError();
        if (SUCCEEDED(hr))
        {
        // Load the resource.
        audioResDataHandle = LoadResource(e, audioResHandle);

        hr = audioResDataHandle ? S_OK :  E_FAIL;
        }
        else {
            return hr;
        }
        if (SUCCEEDED(hr))
        {
            // Lock it to get a system memory pointer.
            pImageFile = LockResource(audioResDataHandle);

            hr = pImageFile ? S_OK :  E_FAIL;
        }
        else {
            return hr;
        }
        if (SUCCEEDED(hr))
        {
            // Calculate the size.
            imageFileSize = SizeofResource(e, audioResHandle);

            hr = imageFileSize ? S_OK :  E_FAIL;

        }
        else {
            return hr;
        }
        if (SUCCEEDED(hr))
        {
            // Create a WIC stream to map onto the memory.
          //  hr = pIWICFactory->CreateStream(&pStream);
        }

       

    //check the file type, should be fourccWAVE or 'XWMA'
    FindChunk(audioResDataHandle, fourccRIFF, dwChunkSize, dwChunkPosition);
    DWORD filetype;
    ReadChunkData(audioResDataHandle, &filetype, sizeof(DWORD), dwChunkPosition);
    if (filetype != fourccWAVE)
        return S_FALSE;

    FindChunk(audioResDataHandle, fourccFMT, dwChunkSize, dwChunkPosition);
    ReadChunkData(audioResDataHandle, &wfx, dwChunkSize, dwChunkPosition);

    FindChunk(audioResDataHandle, fourccDATA, dwChunkSize, dwChunkPosition);
    BYTE* pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(audioResDataHandle, pDataBuffer, dwChunkSize, dwChunkPosition);


    buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
    buffer.pAudioData = pDataBuffer;  //buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM;


    return S_OK;
};

HRESULT AudioController::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    HRESULT hr = S_OK;
 //   if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
 //       return HRESULT_FROM_WIN32(GetLastError());



    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    return S_OK;

}
/*
HRESULT AudioController::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    return S_OK;

}*/

HRESULT AudioController::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
    HRESULT hr = S_OK;
    DWORD dwRead;
    if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return hr;
}

HRESULT AudioController::Init_Source(XAUDIO2_BUFFER& buff, VoiceCallback& ref, IXAudio2SourceVoice** pSourceV)
{
    HRESULT hr;
    if (FAILED(hr = pXAudio2->CreateSourceVoice(pSourceV, (WAVEFORMATEX*)&wfx), 0, XAUDIO2_DEFAULT_FREQ_RATIO, ref, NULL, NULL))
        return hr;
    if (FAILED(hr = (* pSourceV)->SubmitSourceBuffer(&buff)))
        return hr;
 //  WaitForCallback(ref);
    return hr;
}

HRESULT AudioController::Init_Source()
{
    HRESULT hr;
    if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx), 0, XAUDIO2_DEFAULT_FREQ_RATIO, &pCallback, NULL, NULL))
        return hr;
    if (FAILED(hr = pSourceVoice->SubmitSourceBuffer(&buffer)))
        return hr;
 //  WaitForCallback();
    return hr;
}

HRESULT AudioController::PlayAudio()
{

    HRESULT hr;
    Init_Source();
    if (FAILED(hr = pSourceVoice->Start(0)))
        return hr;

}

HRESULT AudioController::PlayAudio(IXAudio2SourceVoice* pSourceV)
{
    HRESULT hr;

    if (FAILED(hr = pSourceV->Start(0)))
        return hr;
}

HRESULT AudioController::StopAudio()
{
    HRESULT hr;
    if (FAILED(hr = pSourceVoice->Stop(0)))
        return hr;
    pSourceVoice->FlushSourceBuffers();

    return S_OK;
}
HRESULT AudioController::Release()
{

    pXAudio2->Release();
    return S_OK;
}

XAUDIO2_BUFFER& AudioController::GetBuffer()
{

    return buffer;
    // // O: tu wstawiæ instrukcjê return
}

VoiceCallback AudioController::GetCallback()
{

    return pCallback;
}

void AudioController::WaitForCallback()
{
    WaitForSingleObjectEx(pCallback.hBufferEnd, 1000, TRUE);
}

void AudioController::WaitForCallback(VoiceCallback pCb)
{
   WaitForSingleObjectEx(pCb.hBufferEnd, 1000, TRUE);
}

void AudioController::PlaySimple(
    LPCSTR modulename,
    int resourceName
    )
{
    PlaySoundA(MAKEINTRESOURCEA(resourceName), GetModuleHandle(modulename),SND_RESOURCE |SND_LOOP| SND_ASYNC);

}
