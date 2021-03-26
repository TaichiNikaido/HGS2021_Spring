//=============================================================================
//
// ブロックの処理 [block.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "block.h"
#include "player_3d.h"
#include "mode_game.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBlock::m_apTexture[1] = {};
//=============================================================================
// コンストラクタ
//=============================================================================
CBlock::CBlock(int nPriority)
{
	m_nPatternAnim = 2;
	m_nCountAnim = 0;
	m_nBreakIces = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBlock::~CBlock()
{

}
//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CBlock::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK, &m_apTexture[0]);
	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CBlock::Unload(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBlock::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CPolygon3d::Init();

	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//向きを設定
	SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));

	BindTexture(m_apTexture[0]);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBlock::Uninit(void)
{
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBlock::Update(void)
{
	CPolygon3d::Update();
	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);
	/*Collisaon();*/
}

//=============================================================================
// 描画処理
//=============================================================================
void CBlock::Draw(void)
{
	CPolygon3d::Draw();
}

CBlock::IS_COLLISION CBlock::Collision(void)
{
	IS_COLLISION bCollision;

	D3DXVECTOR3 Move;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	D3DXVECTOR3 PosOld;
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	if (pPlayer != nullptr)
	{
		Pos = pPlayer->GetPosition();
		Size = pPlayer->GetSize();
		Size = pPlayer->GetSize();
		PosOld = pPlayer->GetPositionOld();
		/*bCollision.bIsTop = pCharactor->GetIsCollision().bIsTop;
		bCollision.bIsBottom = pCharactor->GetIsCollision().bIsBottom;
		bCollision.bIsRight = pCharactor->GetIsCollision().bIsRight;
		bCollision.bIsLeft = pCharactor->GetIsCollision().bIsLeft;
		bCollision.bIsFront = pCharactor->GetIsCollision().bIsFront;
		bCollision.bIsBack = pCharactor->GetIsCollision().bIsBack;*/
		bool bIsTop = false;
		bool bIsBottom = false;
		bool bIsRight = false;
		bool bIsLeft = false;
		bool bIsFront = false;
		bool bIsBack = false;

		D3DXVECTOR3 box1Max = D3DXVECTOR3(Size.x / 2, Size.y / 2, Size.z / 2) + Pos;
		D3DXVECTOR3 box1Min = D3DXVECTOR3(-Size.x / 2, -Size.y / 2, -Size.z / 2) + Pos;
		D3DXVECTOR3 box2Max = D3DXVECTOR3((GetSize().x / 2), (GetSize().y / 2), (GetSize().z / 2));
		D3DXVECTOR3 box2Min = D3DXVECTOR3((-GetSize().x / 2), (-GetSize().y / 2), (-GetSize().z / 2));

		if (
			box1Max.y >= box2Min.y && //縦上
			box1Min.y <= box2Max.y && //縦下
			box1Max.x >= box2Min.x && //横左
			box1Min.x <= box2Max.x //横右
			)
		{
			if (box1Max.y >= box2Min.y && PosOld.y <= box2Min.y)//縦下
			{
				Pos.y = box2Min.y - Size.y / 2;
				bIsBottom = true;
			}

			else if (box1Min.y <= box2Max.y && PosOld.y >= box2Max.y)//縦上
			{
				Pos.y = box2Max.y + Size.y / 2;
				bIsTop = true;
			}

			else if (box1Max.x >= box2Min.x && PosOld.x <= box2Min.x)//右から
			{
				Pos.x = box2Min.x - Size.x / 2;
				bIsRight = true;
			}

			else if (box1Min.x <= box2Max.x && PosOld.x >= box2Max.x)//左から
			{
				Pos.x = box2Max.x + Size.x / 2;
				bIsLeft = true;
			}
		}
	}

	pPlayer->SetPosition(Pos);
	return bCollision;
}