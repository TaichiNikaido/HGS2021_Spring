//=============================================================================
//
// ビルボード [billboard.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CBillboard::CBillboard()
{
	m_pTexture = NULL;								//テクスチャのポインタ
	m_pVtxBuff = NULL;								//頂点バッファへのポインタ
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));		//行列計算用
	m_Position = INITIAL_D3DXVECTOR3;				//位置
	m_Rotation = INITIAL_D3DXVECTOR3;				//回転
	m_Size = INITIAL_D3DXVECTOR3;					//サイズ
	m_Move = INITIAL_D3DXVECTOR3;					//移動量
	m_Color = INITIAL_D3DXCOLOR;					//色
	memset(m_aTexture, NULL, sizeof(m_aTexture));	//テクスチャのUV座標
}

//=============================================================================
//	デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = NULL;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//テクスチャのUV座標の設定
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
void CBillboard::Uninit(void)
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
void CBillboard::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x / 2, m_Size.y / 2, +m_Size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x / 2, -m_Size.y / 2, +m_Size.z / 2);
	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//テクスチャのUV座標の設定
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	//位置を更新する
	m_Position += m_Move;
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBillboard::Draw(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRotation, mtxTrans; //行列計算用のマトリクス
	D3DMATERIAL9 matDef;
	//アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x66);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合）
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//セットテクスチャ
	pDevice->SetTexture(0, m_pTexture);
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//回転の逆行列
	pDevice->GetTransform(D3DTS_VIEW, &mtxRotation);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRotation);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;
	// 向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRotation, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotation);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Position.x,
		m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,
		&mtxTrans);
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//マテリアル情報
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient.r = m_Color.r;
	matDef.Ambient.g = m_Color.g;
	matDef.Ambient.b = m_Color.b;
	matDef.Ambient.a = m_Color.a;
	pDevice->SetMaterial(&matDef);
	// ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// テクスチャのUV座標の設定関数
//=============================================================================
void CBillboard::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
{
	//頂点数分回す
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//テクスチャのUV座標の割り当て
		m_aTexture[nCount] = aTex[nCount];
	}
}