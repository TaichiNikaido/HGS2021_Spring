//=============================================================================
//
// プレイヤー [player.cpp]
// Author : 二階堂汰一
//
//=============================================================================

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
<<<<<<< HEAD
#define TEXTURE ("Data/Texture/Player.png")
=======
#define TEXTURE ("Data/Textrue/bakuhatsu.png")
>>>>>>> 296a8f33887d24dab4338283c2379c152acb8767
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0))
#define SPEED (0.01f)
#define CAMERA_DISTANCE (500.0f)
#define GRAVITY (50.5f)
#define JUMP_POWER (150.0f)

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
	m_PositionOld = INITIAL_D3DXVECTOR3;				//過去の位置
	m_CollisionSize = INITIAL_D3DXVECTOR3;				//衝突判定用サイズ
	m_nSurvivalTime = 0;										//生存時間
	m_fCameraDistance = 0.0f;							//カメラとの距離
	m_bJump = false;									//ジャンプ
	m_State = STATE_NONE;								//状態
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
			//プレイヤーの位置を設定する
			pPlayer->SetPosition(Position);
			//プレイヤーの向きを設定する
			pPlayer->SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));
			//プレイヤーのサイズを設定する
			pPlayer->SetSize(SIZE);
			//プレイヤーの初期化処理関数呼び出し
			pPlayer->Init();
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
	//衝突判定用サイズの取得
	m_CollisionSize = GetSize();
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
	//過去の位置を保存する
	m_PositionOld = GetPosition();
	//ポリゴン3Dの更新処理関数呼び出し
	CPolygon3d::Update();
	//移動処理関数呼び出し
	Move();
	//入力処理関数呼び出し
	Input();
	//生存時間を加算する
	m_nSurvivalTime++;
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

	if (pJoystick->GetJoystickTrigger(JS_A))
	{
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_SPACE))
	{
		//もしジャンプしていなかったら
		if (m_bJump == false)
		{
			//ジャンプする
			m_Move.y += JUMP_POWER;
			//ジャンプ状態にする
			m_bJump = true;
		}
	}
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer3d::Move(void)
{
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//もし死亡状態じゃないとき
	if (m_State != STATE_DEATH)
	{
		//移動させる
		m_Move.x += m_fSpeed;
		//ジャンプしてるとき
		if (m_bJump == true)
		{
			//重力をかける
			m_Move.y -= GRAVITY;
		}
	}
	//位置更新
	Position += m_Move;
	//位置の設定
	SetPosition(Position);
	//ジャンプしてるとき
	if (m_bJump == true)
	{
		//重力をかける
		m_Move.y -= GRAVITY;
	}
	if (Position.y <= 0.0f)
	{
		m_Move.y = 0.0f;
		//ジャンプ状態にする
		m_bJump = false;
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
	if (Position.y >= SCREEN_HEIGHT)
	{
		m_Move.y = 0.0f;

	}
	return Position;
}