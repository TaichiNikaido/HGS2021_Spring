//=============================================================================
//
// 3Dポリゴン管理 [polygon3d.cpp]
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
#include "scene3d.h"
#include "polygon3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_SCALE (1.0f)	//拡縮の初期値
#define INITIAL_ANGLE (0.0f)	//角度の初期値
#define INITIAL_LENGTH (0.0f)	//長さの初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygon3d::CPolygon3d(int nPriority) : CScene3d(nPriority)
{
	m_pTexture = NULL;	//テクスチャへのポインタ
	m_pVtxBuff = NULL;	//頂点バッファへのポインタ
						//テクスチャ座標
	m_aTex[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_aTex[1] = D3DXVECTOR2(1.0f, 0.0f);
	m_aTex[2] = D3DXVECTOR2(0.0f, 1.0f);
	m_aTex[3] = D3DXVECTOR2(1.0f, 1.0f);
	m_Color = INITIAL_D3DXCOLOR;					//頂点カラー
	m_fScale = INITIAL_SCALE;						//縮尺
	m_fAngle = INITIAL_ANGLE;						//角度
	m_fLength = INITIAL_LENGTH;						//長さ
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));	//ワールドマトリクス
}

//=============================================================================
// デストラクタ
//=============================================================================
CPolygon3d::~CPolygon3d()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPolygon3d::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点情報を設定
	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//長さの設定
	m_fLength = sqrtf((float)(((GetSize().x / 2) * (GetSize().x / 2)) + ((GetSize().y / 2) * (GetSize().y / 2))));
	//角度の設定
	m_fAngle = atan2f((GetSize().y / 2), (GetSize().x / 2));
	//頂点座標の設定
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//テクスチャ座標の設定
	pVtx[0].tex = m_aTex[0];
	pVtx[1].tex = m_aTex[1];
	pVtx[2].tex = m_aTex[2];
	pVtx[3].tex = m_aTex[3];
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPolygon3d::Uninit(void)
{
	//もし頂点バッファのポインタがNULLじゃない場合
	if (m_pVtxBuff != NULL)
	{
		//頂点バッファを破棄する
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
void CPolygon3d::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx;
	//長さの設定
	m_fLength = sqrtf((float)(((GetSize().x / 2) * (GetSize().x / 2)) + ((GetSize().y / 2) * (GetSize().y / 2))));
	//角度の設定
	m_fAngle = atan2f((GetSize().y / 2), (GetSize().x / 2));
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength  * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//テクスチャ座標の設定
	pVtx[0].tex = m_aTex[0];
	pVtx[1].tex = m_aTex[1];
	pVtx[2].tex = m_aTex[2];
	pVtx[3].tex = m_aTex[3];
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPolygon3d::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	pDevice->SetRenderState(D3DRS_LIGHTING,false);
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRotation().y, GetRotation().x, GetRotation().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->SetTexture(0, m_pTexture);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

//=============================================================================
// テクスチャのUV座標設定関数
//=============================================================================
void CPolygon3d::SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//テクスチャのUV座標の割り当て
		m_aTex[nCount] = aTexture[nCount];
	}
}