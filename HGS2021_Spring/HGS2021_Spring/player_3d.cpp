//=============================================================================
//
// プレイヤー [player.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene2d.h"
#include "mode_game.h"
#include "player_3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("")
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0))
#define SPEED (0.0f)
#define CAMERA_DISTANCE (100.0f)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer3d::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer3d::CPlayer3d(int nPriority)
{
	m_Move = INITIAL_D3DXVECTOR3;						//移動量
	m_fCameraDistance = 0.0f;							//カメラとの距離
	m_State = STATE_NONE;								//状態
	m_Input = INPUT_NONE;								//入力キー情報
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer3d::~CPlayer3d()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CPlayer3d::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE,						// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CPlayer3d::TextureUnload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをNULLにする
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPlayer3d * CPlayer3d::Create(D3DXVECTOR3 Position)
{
	//プレイヤーのポインタ
	CPlayer3d * pPlayer = NULL;
	//プレイヤーがNULLの場合
	if (pPlayer == NULL)
	{
		//プレイヤーのメモリ確保
		pPlayer = new CPlayer3d;
		//プレイヤーがNULLではない場合
		if (pPlayer != NULL)
		{
			//プレイヤーの初期化処理関数呼び出し
			pPlayer->Init();
			//プレイヤーの位置を設定する
			pPlayer->SetPosition(Position);
			//プレイヤーの向きを設定する
			pPlayer->SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));
			//プレイヤーのサイズを設定する
			pPlayer->SetSize(SIZE);
		}
	}
	//プレイヤーのポインタを返す
	return pPlayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayer3d::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//ポリゴン3Dの初期化処理関数呼び出し
	CPolygon3d::Init();
	//移動速度の初期設定
	m_fSpeed = SPEED;
	//カメラとの距離を初期設定
	m_fCameraDistance = CAMERA_DISTANCE;
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayer3d::Uninit(void)
{
	//ポリゴン3Dの終了処理関数呼び出し
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayer3d::Update(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//ポリゴン3Dの更新処理関数呼び出し
	CPolygon3d::Update();
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//移動可能範囲処理関数呼び出し
	Position = MovableRange();
	//位置更新
	Position += m_Move;
	//位置の設定
	SetPosition(Position);
	//テクスチャの設定
	SetTexture(aTexture);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayer3d::Draw(void)
{
	//ポリゴン3Dの描画処理関数呼び出し
	CPolygon3d::Draw();
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CPlayer3d::Input(void)
{
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();
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
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//プレイヤーが移動していないとき
	m_Move = INITIAL_D3DXVECTOR3;
	//上移動処理
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//入力キー情報を上にする
		m_Input = INPUT_UP;
		//移動処理関数呼び出し
		Move();
	}
	//下移動処理
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//入力キー情報を下にする
		m_Input = INPUT_DOWN;
		//移動処理関数呼び出し
		Move();
	}
	//左移動処理
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//入力キー情報を左にする
		m_Input = INPUT_LEFT;
		//移動処理関数呼び出し
		Move();
	}
	//右移動処理
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//入力キー情報を右にする
		m_Input = INPUT_RIGHT;
		//移動処理関数呼び出し
		Move();
	}
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer3d::Move(void)
{
	//もし死亡状態じゃないとき
	if (m_State != STATE_DEATH)
	{
		switch (m_Input)
		{
			//もし入力情報が上の時
		case INPUT_UP:
			//Y軸の上方向に移動量を加算
			m_Move.y = cosf(D3DX_PI) * m_fSpeed;
			break;
			//もし入力情報が下の時
		case INPUT_DOWN:
			//Y軸の下方向に移動量を加算
			m_Move.y = cosf(D3DX_PI) * -m_fSpeed;
			break;
			//もし入力情報が左の時
		case INPUT_LEFT:
			//X軸の左方向に移動量を加算
			m_Move.x = cosf(D3DX_PI) * m_fSpeed;
			break;
			//もし入力情報が右の時
		case INPUT_RIGHT:
			//X軸の右方向に移動量を加算
			m_Move.x = cosf(D3DX_PI) * -m_fSpeed;
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// 移動可能範囲処理関数
//=============================================================================
D3DXVECTOR3 CPlayer3d::MovableRange()
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//サイズを取得する
	D3DXVECTOR3 Size = GetSize();
	//もしプレイヤーが上画面外に行ったら
	if (Position.y - Size.y / 2 < 0)
	{
		//位置が画面外に移動しないように制御する
		Position.y = Size.y / 2;
	}
	//もしプレイヤーが下画面外に行ったら
	if (Position.y + Size.y / 2 > SCREEN_HEIGHT)
	{
		//位置が画面外に移動しないように制御する
		Position.y = SCREEN_HEIGHT - Size.y / 2;
	}
	//もしプレイヤーが左画面外に行ったら
	if (Position.x - Size.y / 2 < 0)
	{
		//位置が画面外に移動しないように制御する
		Position.x = Size.y / 2 + 0;
	}
	//もしプレイヤーが右画面外に行ったら
	if (Position.x + Size.y / 2 > SCREEN_WIDTH)
	{
		//位置が画面外に移動しないように制御する
		Position.x = SCREEN_WIDTH - Size.y / 2;
	}
	return Position;
}