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
#include "logo_over.h"
#include "logo_clear.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Player.png")
#define SIZE (D3DXVECTOR3(180.0f,180.0f,0.0))
#define SPEED (15.0f)
#define CAMERA_DISTANCE (1500.0f)
#define GRAVITY (-4.5f)
#define JUMP_POWER (80.0f)
#define FLOOR (900.0f)
#define COLLISION_SIZE (D3DXVECTOR3(100.0f,300.0f,0.0f))
#define KNOCKBACK_VALUE (10.0f) //ノックバック移動量(横)
#define KNOCKBACK_VALUE_UP (-60.0f) //ノックバック移動量(上方向)
#define DEATH_ADD_ROT (0.3f)//死んだ時の回転量
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
	memset(&m_bIsCollision, 0, sizeof(m_bIsCollision));//当たったか
	m_nCounterAnim = 0;
	m_nPattarnAnim = 0;
	m_nCreateCount = 0;
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
	aTexture[0] = D3DXVECTOR2(m_nPattarnAnim * 0.2f, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_nPattarnAnim * 0.2f + 0.2f, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_nPattarnAnim * 0.2f, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_nPattarnAnim * 0.2f + 0.2f, 1.0f);
	//ポリゴン3Dの初期化処理関数呼び出し
	CPolygon3d::Init();
	//衝突判定用サイズの取得
	m_CollisionSize = COLLISION_SIZE;
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
	m_nCounterAnim++;
	//アニメーションカウンタ
	if (m_nCounterAnim % 5 == 0)
	{
		m_nPattarnAnim++;
	}
	if (m_nPattarnAnim > 5)
	{
		m_nCounterAnim = 0;
		m_nPattarnAnim = 0;
	}
	if (m_State == STATE_DEATH)//死んだときくるくるさせる
	{
		D3DXVECTOR3 Rot = GetRotation();

		Rot.z += DEATH_ADD_ROT;
		SetRotation(Rot);
	}
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_nPattarnAnim * 0.2f, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_nPattarnAnim * 0.2f + 0.2f, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_nPattarnAnim * 0.2f, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_nPattarnAnim * 0.2f + 0.2f, 1.0f);
	//ポリゴン3Dの更新処理関数呼び出し
	CPolygon3d::Update();
	//テクスチャの設定
	SetTexture(aTexture);
	//位置の設定
	SetPosition(GetPosition() + m_Move);
	//移動処理関数呼び出し
	Move();
	//入力処理関数呼び出し
	Input();
	//生存時間を加算する
	m_nSurvivalTime++;
	if (m_nSurvivalTime >= 7200)
	{
		if (m_nCreateCount == 0)
		{
			CClearLogo::Create();
			m_nCreateCount++;
		}
	}
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
// 移動量セット
//=============================================================================
void CPlayer3d::SetMove(D3DXVECTOR3 Move)
{
	m_Move = Move;
}

//=============================================================================
// 当たり判定セット
//=============================================================================
void CPlayer3d::SetCollisionSize(D3DXVECTOR3 CollisionSize)
{
	m_CollisionSize = CollisionSize;
}

//=============================================================================
// 状態
//=============================================================================
void CPlayer3d::SetState(STATE state)
{
	m_State = state;
}

//=============================================================================
// 死亡処理
//=============================================================================
void CPlayer3d::Death(D3DXVECTOR3 HitPos)
{
	CSound * pSound = CManager::GetSound();
	float fKnockBackRot = 0.0f; //ノックバック方向
	D3DXVECTOR3 distance; //プレイヤーと敵の距離
	if (m_State != STATE_DEATH)
	{
		m_State = STATE_DEATH;
		if (pSound != NULL)
		{
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);
		}

		distance = GetPosition() - HitPos;

		fKnockBackRot = atan2f((HitPos.x - GetPosition().x), (HitPos.y - GetPosition().y));	//プレイヤーから見た当たった敵のいる向きを計算
		//その逆方向にぶっ飛ばす
		SetMove(D3DXVECTOR3(sinf(fKnockBackRot - D3DXToRadian(180))*KNOCKBACK_VALUE, KNOCKBACK_VALUE_UP, cosf(fKnockBackRot - D3DXToRadian(180))*KNOCKBACK_VALUE));
		COverLogo::Create();
	}
}

void CPlayer3d::SetIsCollision(CBlock::IS_COLLISION isCollision)
{
	m_bIsCollision = isCollision;
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

	if (m_State != STATE_DEATH)
	{
		if (pKeyboard->GetKeyboardPress(DIK_LSHIFT) ||pKeyboard->GetKeyboardPress(DIK_RSHIFT) || pJoystick->GetJoystickPress(JS_A))
		{
			m_CollisionSize.y = 50;
		}
		else
		{
			m_CollisionSize = COLLISION_SIZE;
		}
		if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || pJoystick->GetJoystickTrigger(JS_X))
		{
			//もしジャンプしていなかったら
			if (m_bJump == false)
			{
				m_bIsCollision.bIsTop = false;
				//ジャンプす
				m_Move.y -= JUMP_POWER;
				//ジャンプ状態にする
				m_bJump = true;
			}
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
		m_Move.x = m_fSpeed;
		////ジャンプしてるとき
		//if (m_bJump == true)
		//{
		//	//重力をかける
		//	m_Move.y -= GRAVITY;
		//}
	}
	if (Position.y >= FLOOR - GetSize().y / 2 && m_State != STATE_DEATH)
	{
		m_Move.y = 0.0f;
		SetPosition(D3DXVECTOR3(GetPosition().x, FLOOR - GetSize().y / 2, 0.0f));
		//ジャンプ状態にする
		m_bJump = false;
	}
	else
	{
		m_Move.y -= GRAVITY;
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