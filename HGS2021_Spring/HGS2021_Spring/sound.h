#pragma once
//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <xaudio2.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// サウンドファイル
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_NONE = -1,
		SOUND_LABEL_BGM_TITLE,
		SOUND_LABEL_BGM_TUTORIAL,
		SOUND_LABEL_BGM_GAME,
		SOUND_LABEL_BGM_RESULT,
		SOUND_LABEL_SE_PLAYER_JUMP,
		SOUND_LABEL_SE_PLAYER_DAMAGE,
		SOUND_LABEL_SE_BUTTON,
		SOUND_LABEL_MAX
	} SOUND_LABEL;
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif