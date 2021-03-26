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
#define INITIAL_POSITION_V (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//視点の初期値
#define INITIAL_POSITION_R (D3DXVECTOR3(0.0f,0.0f,0.0f))		//注視点の初期値
#define INITIAL_VECTOR_U (D3DXVECTOR3(0.0f,0.0f,0.0f))			//上方向ベクトル
#define INITIAL_ROTAION (D3DXVECTOR3(D3DXToRadian(0.0f),D3DXToRadian(0.0f),D3DXToRadian(0.0f)))		//回転の初期値
#define INITIAL_DISTANCE (0.0f)									//距離の初期値
#define INITIAL_PLAYER_DISTANCE (0.0f)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_PositionV = INITIAL_POSITION_V;				//視点の位置
	m_PositionR = INITIAL_POSITION_R;				//注視点の位置
	m_VectorU = INITIAL_VECTOR_U;					//上方向ベクトル
	m_Rotation = INITIAL_ROTAION;					//回転
	m_fDistance = INITIAL_DISTANCE;					//視点と注視点の距離
	m_fPlayerDistance = INITIAL_PLAYER_DISTANCE;	//プレイヤーとカメラの距離
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
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	//もしプレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を設定
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//プレイヤーとの距離を指定する
		m_fPlayerDistance = pPlayer->GetCameraDistance();
		//上方向ベクトルを指定する
		m_VectorU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_PositionV = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z + m_fPlayerDistance);
		m_PositionR = PlayerPosition;
	}
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
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	//もしプレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		if (pPlayer->GetState() != CPlayer3d::STATE_DEATH)
		{
			//プレイヤーの位置を設定
			D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
			//上方向ベクトルを指定する
			m_VectorU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_PositionV = D3DXVECTOR3(PlayerPosition.x + 550.0f, 0.0f, PlayerPosition.z + m_fPlayerDistance);
			m_PositionR = D3DXVECTOR3(PlayerPosition.x + 550.0f, 0.0f, PlayerPosition.z);
		}
	}
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
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, D3DXToRadian(-90.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProjection);
}