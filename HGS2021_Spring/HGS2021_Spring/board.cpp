//=============================================================================
//
// ボード [board.cpp]
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
#include "board.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/board.png")
#define SIZE (D3DXVECTOR3(250.0f,50.0f,0.0))
#define SPEED (0.0f)
#define CAMERA_DISTANCE (500.0f)
#define GRAVITY (50.5f)
#define JUMP_POWER (150.0f)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBoard::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBoard::CBoard(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBoard::~CBoard()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBoard::TextureLoad(void)
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
void CBoard::TextureUnload(void)
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
CBoard * CBoard::Create()
{
	//ボードのポインタ
	CBoard * pBoard = NULL;
	//プレイヤーがNULLの場合
	if (pBoard == NULL)
	{
		//プレイヤーのメモリ確保
		pBoard = new CBoard;
		//プレイヤーがNULLではない場合
		if (pBoard != NULL)
		{
			//プレイヤーの向きを設定する
			pBoard->SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));
			//プレイヤーのサイズを設定する
			pBoard->SetSize(SIZE);
			//プレイヤーの初期化処理関数呼び出し
			pBoard->Init();
		}
	}
	//プレイヤーのポインタを返す
	return pBoard;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBoard::Init(void)
{
	//プレイヤーの取得
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	//もしプレイヤーのポジションがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//プレイヤーのサイズを取得する
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
		//位置を設定する
		SetPosition(D3DXVECTOR3(PlayerPosition.x, 900.0f, PlayerPosition.z));
	}
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//ポリゴン3Dの初期化処理関数呼び出し
	CPolygon3d::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBoard::Uninit(void)
{
	//ポリゴン3Dの終了処理関数呼び出し
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBoard::Update(void)
{
	//ポリゴン3Dの更新処理関数呼び出し
	CPolygon3d::Update();
	//プレイヤーの取得
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	//もしプレイヤーのポジションがNULLじゃない場合
	if (pPlayer != NULL)
	{
		if (pPlayer->GetState() != CPlayer3d::STATE_DEATH)
		{
			//プレイヤーの位置を取得する
			D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
			//プレイヤーのサイズを取得する
			D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
			//位置を設定する
			SetPosition(D3DXVECTOR3(PlayerPosition.x, 900.0f, PlayerPosition.z));
		}
		
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBoard::Draw(void)
{
	//ポリゴン3Dの描画処理関数呼び出し
	CPolygon3d::Draw();
}
