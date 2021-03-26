//******************************************************************************
// ビルボード[billboard.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "billboard.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define NOR				(D3DXVECTOR3(1, 1, -1))	// 法線
#define SCALE_VALUE		(1.0f)					// 拡大率
#define DEVIDE_VALUE	(2)						// 割る数
#define TEX_UV_MAX		(1.0f)					// UVの最大値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBillboard::CBillboard(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos		= INITIAL_D3DXVECTOR3;
	m_rot		= INITIAL_D3DXVECTOR3;
	m_size		= INITIAL_D3DXVECTOR3;
	m_col		= INITIAL_D3DXCOLOR;
	m_fScale	= INIT_FLOAT;
	m_fTexX		= INIT_FLOAT;
	m_fTexX2	= TEX_UV_MAX;
	m_fTexY		= INIT_FLOAT;
	m_fTexY2	= TEX_UV_MAX;
	m_nAlpha	= INIT_INT;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}
//******************************************************************************
//　デストラクタ
//******************************************************************************
CBillboard::~CBillboard()
{
}
//******************************************************************************
//　初期化
//******************************************************************************
HRESULT CBillboard::Init(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_3D *pVtx;

	// スケール1.0f
	m_fScale = SCALE_VALUE;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 場所の設定
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[1].pos = D3DXVECTOR3((+m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[3].pos = D3DXVECTOR3((+m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;

	// 法線の設定
	pVtx[0].nor = NOR;
	pVtx[1].nor = NOR;
	pVtx[2].nor = NOR;
	pVtx[3].nor = NOR;

	// カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//******************************************************************************
//　終了
//******************************************************************************
void CBillboard::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
//　更新
//******************************************************************************
void CBillboard::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 場所の設定
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[1].pos = D3DXVECTOR3((+m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[3].pos = D3DXVECTOR3((+m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;

	// 法線の設定
	pVtx[0].nor = NOR;
	pVtx[1].nor = NOR;
	pVtx[2].nor = NOR;
	pVtx[3].nor = NOR;

	// カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//******************************************************************************
//　描画
//******************************************************************************
void CBillboard::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //行列計算用のマトリクス

	//ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlpha);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// セットテクスチャ
	pDevice->SetTexture(0, m_pTexture);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転の逆行列
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// 向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x,
		m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,
		&mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライト有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//******************************************************************************
//　位置座標設定
//******************************************************************************
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	//代入
	m_pos = pos;
}
//******************************************************************************
//　向き設定
//******************************************************************************
void CBillboard::SetRotation(D3DXVECTOR3 rot)
{
	//代入
	m_rot = rot;
}
//******************************************************************************
//　サイズ設定
//******************************************************************************
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	//代入
	m_size = size;
}
//******************************************************************************
//　カラー設定
//******************************************************************************
void CBillboard::SetColor(D3DXCOLOR col)
{
	//代入
	m_col = col;
}
//******************************************************************************
//　テクスチャ設定
//******************************************************************************
void CBillboard::SetTexture(float fTexX, float fTexY, float fTexX2, float fTexY2)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexX2 = fTexX2;
	m_fTexY2 = fTexY2;
}
//******************************************************************************
//　拡大率設定
//******************************************************************************
void CBillboard::SetScale(float fScale)
{
	//代入
	m_fScale = fScale;
}
//******************************************************************************
//　テクスチャ受け渡し
//******************************************************************************
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//代入
	m_pTexture = pTexture;
}
//******************************************************************************
// アルファテストの数値設定
//******************************************************************************
void CBillboard::SetAlpha(int nAlpha)
{
	m_nAlpha = nAlpha;
}