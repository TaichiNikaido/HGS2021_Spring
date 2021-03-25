//=============================================================================
//
// 2Dシーン管理処理 [scene2d.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_SCALE (1.0f)
#define INITIAL_ANGLE (0.0f)
#define INITIAL_LENGTH (0.0f)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;										//テクスチャへのポインタ
	m_pVtxBuff = NULL;										//頂点バッファへのポインタ
	m_Position = INITIAL_D3DXVECTOR3;						//座標
	m_Size = INITIAL_D3DXVECTOR3;							//サイズ
	m_Color = INITIAL_D3DXCOLOR;							//カラー
	m_Rotation = INITIAL_ROTATION;							//回転
	memset(m_aVtxPosition, NULL, sizeof(m_aVtxPosition));	//頂点座標
	memset(m_aTexture, NULL, sizeof(m_aTexture));			//テクスチャのUV座標
	m_fScale = INITIAL_SCALE;								//縮尺
	m_fAngle = INITIAL_ANGLE;								//角度
	m_fLength = INITIAL_LENGTH;								//長さ
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CScene2d::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//長さの設定
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//角度の設定
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));
	//頂点座標の設定
	pVtx[0].pos.x = m_Position.x - cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Position.y - sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Position.x + cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Position.y - sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Position.x - cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Position.y + sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Position.x + cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Position.y + sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//除算数の設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//テクスチャ座標の設定
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CScene2d::Uninit(void)
{
	//もし頂点バッファのポインタがNULLじゃない場合
	if (m_pVtxBuff != NULL)
	{
		//頂点バッファの破棄
		m_pVtxBuff->Release();
		//頂点バッファのポインタをNULLにする
		m_pVtxBuff = NULL;
	}
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CScene2d::Update(void)
{
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//長さの設定
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//角度の設定
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));
	//頂点座標の設定
	pVtx[0].pos.x = m_Position.x - cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Position.y - sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Position.x + cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Position.y - sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Position.x - cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Position.y + sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Position.x + cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Position.y + sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//除算数の設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//テクスチャ座標の設定
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CScene2d::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点座標設定関数
//=============================================================================
void CScene2d::SetVertexPosition(D3DXVECTOR3 VtxPos[NUM_VERTEX])
{
	//頂点数分回す
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//テクスチャのUV座標割り当て
		m_aVtxPosition[nCount] = VtxPos[nCount];
	}
}

//=============================================================================
// テクスチャのUV座標設定関数
//=============================================================================
void CScene2d::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
{
	//頂点数分回す
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//テクスチャのUV座標の割り当て
		m_aTexture[nCount] = aTex[nCount];
	}
}