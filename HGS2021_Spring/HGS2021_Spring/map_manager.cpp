//=============================================================================
//
// スコア管理処理 [score.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include <stdio.h>
#include "manager.h"
#include "scene.h"
#include "map_manager.h"
#include <cmath>
#include "block.h"
#include "normal_block.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMap::CMap(int nPriority) : CScene(nPriority)
{
	memset(m_aMapIndex, 0, sizeof(m_aMapIndex));
	memset(m_apBlock, NULL, sizeof(m_apBlock));
}

//=============================================================================
// デストラクタ
//=============================================================================
CMap::~CMap()
{
}
//=============================================================================
// 生成処理
//=============================================================================
CMap * CMap::Create(void)
{
	CMap *pMap = NULL;

	if (pMap == NULL)
	{
		pMap = new CMap;
		pMap->Init();
	}

	return pMap;
}
//=============================================================================
// マップロード処理
//=============================================================================
void CMap::MapLoad(void)
{
	FILE * pfile = fopen("Data/Text/maptest.csv", "r");

	//csv読み取り処理
	char str[2048];
	int nRowIndex = 0; //行
	int nColIndex = 0; //列
	if (pfile != NULL)
	{
		//一行取得
		while (fgets(str, 2048, pfile) != NULL)
		{
			char * cTokStr;
			cTokStr = strtok(str, ",");
			while (cTokStr != NULL)
			{
				//#が含まれていれば抜かす
				char cSearchStr = '#';//対象文字
				strchr(cTokStr, cSearchStr);
				//含まれていなかったら出力
				if (strchr(cTokStr, cSearchStr) == NULL)
				{
					//行列にブロックのタイプを格納
					m_aMapIndex[nRowIndex][nColIndex] = (TYPE)atoi(cTokStr);
					//次の列へ
					nColIndex++;
				}
				cTokStr = strtok(NULL, ",");//NULLを入れる
			}

			nRowIndex++;
			nColIndex = 0;
		}
		fclose(pfile);
	}
	else
	{

	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMap::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	//マップロード
	MapLoad();

	for (int nCountRow = 0; nCountRow < MAX_ROW; nCountRow++)
	{
		for (int nCountCol = 0; nCountCol < MAX_COL; nCountCol++)
		{
			switch (m_aMapIndex[nCountRow][nCountCol])
			{
			case TYPE_AIR://空気
				//生成しない
				break;
			case TYPE_BLOCK://天井
				CNormalBlock::Create(D3DXVECTOR3(nCountCol * BLOCK_SIZE, nCountRow * BLOCK_SIZE, 0.0f), D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, 0.0f));
				break;
			default:
				break;
			}
		}
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CMap::Uninit(void)
{
	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CMap::Update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void CMap::Draw(void)
{
}