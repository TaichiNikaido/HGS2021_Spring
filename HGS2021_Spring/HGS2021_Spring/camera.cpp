//=============================================================================
//
// カメラ [camera.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "keyboard.h"
#include "joystick.h"
#include "camera.h"
#include "player_3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_DISTANCE (0.0f)																	//距離の初期値
#define VECTOR (D3DXVECTOR3(0.0f, 1.0f, 0.0f))													//上方向ベクトル
#define ROTATION (D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)))		//回転

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_PositionV = INITIAL_D3DXVECTOR3;	//視点の位置
	m_PositionR = INITIAL_D3DXVECTOR3;	//注視点の位置
	m_VectorU = INITIAL_D3DXVECTOR3;	//上方向ベクトル
	m_Rotation = INITIAL_ROTATION;		//回転
	m_fDistance = INIT_FLOAT;			//距離
	memset(m_MtxView, NULL, sizeof(m_MtxView));
	memset(m_MtxProjection, NULL, sizeof(m_MtxProjection));
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CCamera::Init(void)
{
	//プレイヤーの取得
	CPlayer3d * pPlayer3d = CGameMode::GetPlayer3d();
	if (pPlayer3d != NULL)
	{
		//プレイヤーの位置位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer3d->GetPosition();
		//プレイヤーとの距離を設定
		float PlayerDistance = pPlayer3d->GetCameraDistance();
		//視点を設定する
		m_PositionV = D3DXVECTOR3(0.0f,0.0f,-1000.0f);
		//注視点の設定
		m_PositionR = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
	}
	//上方向ベクトルの初期設定
	m_VectorU = VECTOR;
	//回転方向の初期設定
	//m_Rotation = ROTATION;
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CCamera::Update(void)
{
	//プレイヤーの取得
	CPlayer3d * pPlayer3d = CGameMode::GetPlayer3d();
	if (pPlayer3d != NULL)
	{
		//プレイヤーの位置位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer3d->GetPosition();
		//プレイヤーとの距離を設定
		float PlayerDistance = pPlayer3d->GetCameraDistance();
		//視点を設定する
		m_PositionV = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
		//注視点の設定
		m_PositionR = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
	}
	//上方向ベクトルの初期設定
	m_VectorU = VECTOR;
	//回転方向の初期設定
	//m_Rotation = ROTATION;
}

//=============================================================================
// カメラ設定関数
//=============================================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_MtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_MtxView, &m_PositionV, &m_PositionR, &m_VectorU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);
	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_MtxProjection);
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, D3DXToRadian(90.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProjection);
}