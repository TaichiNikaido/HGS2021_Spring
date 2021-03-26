//=============================================================================
//
// ゲームモード [mode_game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_game.h"
#include "camera.h"
#include "player_2d.h"
#include "player_3d.h"
#include "background.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CCamera * CGameMode::m_pCamera = NULL;			//カメラのポインタ
CPlayer2d * CGameMode::m_pPlayer2d = NULL;		//プレイヤー2Dのポインタ
CPlayer3d * CGameMode::m_pPlayer3d = NULL;		//プレイヤー3Dのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_pLight = NULL;	//ライト
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameMode::~CGameMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CGameMode * CGameMode::Create()
{
	//ゲームモードのポインタ
	CGameMode * pGameMode = NULL;
	//もしゲームモードのポインタをNULLだった場合
	if (pGameMode == NULL)
	{
		//ゲームモードのメモリ確保
		pGameMode = new CGameMode;
		//もしゲームモードのポインタをNULLじゃない場合
		if (pGameMode != NULL)
		{
			//ゲームモードの初期化関数呼び出し
			pGameMode->Init();
		}
	}
	//ゲームモードのポインタを返す
	return pGameMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLじゃない場合
	if (pSound != NULL)
	{
		//タイトルBGMの再生
		//pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_GAME);
	}
	//全初期生成処理関数呼び出し
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameMode::Uninit(void)
{
	//もしカメラのポインタがNULLじゃない場合
	if (m_pCamera != NULL)
	{
		//カメラの初期化処理関数呼び出し
		m_pCamera->Uninit();
		//カメラのメモリ破棄
		delete m_pCamera;
		//カメラのポインタをNULLにする
		m_pCamera = NULL;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameMode::Update(void)
{
	//全更新生成処理関数呼び出し
	UpdateCreateAll();
	//もしカメラのポインタがNULLじゃない場合
	if (m_pCamera != NULL)
	{
		//カメラを設定する
		m_pCamera->SetCamera();
		//カメラの更新処理関数呼び出し
		m_pCamera->Update();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// 全初期生成処理関数
//=============================================================================
void CGameMode::InitCreateAll(void)
{
	//もしプレイヤー3DのポインタがNULLの場合
	if (m_pPlayer3d == NULL)
	{
		//プレイヤー3Dを生成する
		m_pPlayer3d = CPlayer3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	//CBackground::Create();
	//もしカメラのポインタがNULLの場合
	if (m_pCamera == NULL)
	{
		//カメラのメモリ確保
		m_pCamera = new CCamera;
		//もしカメラのポインタがNULLじゃない場合
		if (m_pCamera != NULL)
		{
			//カメラの初期化処理関数呼び出し
			m_pCamera->Init();
		}
	}
}

//=============================================================================
// 全更新生成処理関数
//=============================================================================
void CGameMode::UpdateCreateAll(void)
{
}