//=============================================================================
//
// チュートリアルモード [mode_tutorial.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "mode_tutorial.h"
#include "bg_tutorial.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorialMode::CTutorialMode()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorialMode::~CTutorialMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CTutorialMode * CTutorialMode::Create()
{
	//チュートリアルモードのポインタ
	CTutorialMode * pTutorialMode = NULL;
	//もしチュートリアルモードがNULLの場合
	if (pTutorialMode == NULL)
	{
		//チュートリアルモードのメモリ確保
		pTutorialMode = new CTutorialMode;
		//もしチュートリアルモードがNULLじゃない場合
		if (pTutorialMode != NULL)
		{
			//初期化処理関数呼び出し
			pTutorialMode->Init();
		}
	}
	//チュートリアルモードのポインタ
	return pTutorialMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTutorialMode::Init(void)
{
	//全生成処理関数呼び出し
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTutorialMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTutorialMode::Update(void)
{
	//キーボードの取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//もしENTERかAボタンを押したとき
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		//ゲームに移動
		CManager::StartFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTutorialMode::Draw(void)
{
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CTutorialMode::InitCreateAll(void)
{
	//チュートリアル画面の背景生成
	CTutorialBG::Create();
}