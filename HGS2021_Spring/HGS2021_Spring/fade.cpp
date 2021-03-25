//=============================================================================
//
// フェード [fade.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode_game.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))		//位置
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))					//サイズ
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))								//色

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;					//頂点バッファ
	m_Position = INITIAL_D3DXVECTOR3;	//位置
	m_Size = INITIAL_D3DXVECTOR3;		//サイズ
	m_fade = FADE_NONE;					//フェード
	m_ModeNext = CManager::MODE_NONE;	//次のモード
	m_Color = COLOR;			//フェードの色
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CFade * CFade::Create(CManager::MODE mode)
{
	//フェードのポインタ
	CFade * pFade = NULL;
	//もしフェードのポインタがNULLの場合
	if (pFade == NULL)
	{
		//フェードのメモリ確保
		pFade = new CFade;
		//もしフェードのポインタがNULLじゃない場合
		if (pFade != NULL)
		{
			//初期化処理関数呼び出し
			pFade->Init(mode);
		}
	}
	//フェードのポインタを返す
	return pFade;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CFade::Init(CManager::MODE mode)
{
	//レンダラーの取得
	CRenderer * pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_2D *pVtx;
	//位置の初期設定
	m_Position = POSITION;
	//サイズの初期設定
	m_Size = SIZE;
	//次のモード
	m_ModeNext = mode;
	m_fade = FADE_IN;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定 
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CFade::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CFade::Update(void)
{
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//モード
	m_ModeNext = CManager::GetMode();
	//更新
	if (m_fade != FADE_NONE)
	{
		//フェードイン
		if (m_fade == FADE_IN)
		{
			//a値を加算
			m_Color.a += FADE_RATE;
			//画面が黒くなったら
			if (m_Color.a >= 1.0f)
			{
				//タイトルに遷移
				CManager::SetMode(m_ModeNext);
				//フェード終了処理
				m_Color.a = 1.0f;
				m_fade = FADE_OUT;
			}
		}
		//フェードアウト
		if (m_fade == FADE_OUT)
		{
			//α値を減算
			m_Color.a -= FADE_RATE;
			//画面の透過
			if (m_Color.a <= 0.0f)
			{
				//フェード処理切り替え
				m_Color.a = 0.0f;
				//モード設定
				m_fade = FADE_IN;
				CManager::StopFade();
			}
		}
		//頂点バッファをロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定 
		pVtx[0].col = m_Color;
		pVtx[1].col = m_Color;
		pVtx[2].col = m_Color;
		pVtx[3].col = m_Color;
		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CFade::Draw(void)
{
	//描画
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, NULL);
	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}
