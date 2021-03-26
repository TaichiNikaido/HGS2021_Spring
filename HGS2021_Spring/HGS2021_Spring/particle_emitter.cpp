//******************************************************************************
// パーティクルエミッター [particle_emitter.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
#include "particle_emitter.h"
#include "mode_game.h"
#include "player_3d.h"

//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_TEXT	(1024)							// テキストの最大数
#define BOAD_EFFECT_TEXT	("data/Effect/BoadEffect_Data.txt")	// テキスト
#define REMAINDER	(0)								// 余り0
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle_Emitter::CParticle_Emitter()
{
	m_pos			= INITIAL_D3DXVECTOR3;
	m_nCount		= INIT_INT;
	m_nCreateCount  = INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle_Emitter::~CParticle_Emitter()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle_Emitter * CParticle_Emitter::Create(D3DXVECTOR3 pos, TYPE type)
{
	// CParticle_Emitterのポインタ
	CParticle_Emitter *pParticle_Emitter;

	// メモリ確保
	pParticle_Emitter = new CParticle_Emitter;

	// 位置代入
	pParticle_Emitter->m_pos = pos;

	// 位置代入
	pParticle_Emitter->m_Type = type;

	// 初期化
	pParticle_Emitter->Init();

	// ポインタを返す
	return pParticle_Emitter;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CParticle_Emitter::Init(void)
{
	// タイプ
	switch (m_Type)
	{
	case TYPE_BOAD:
		// テキストファイル読み込み
		sprintf(m_cText, BOAD_EFFECT_TEXT);
		break;
	}

	// 読み込み
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CParticle_Emitter::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CParticle_Emitter::Update(void)
{
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	// インクリメント
	m_nCount++;
	if (pPlayer != NULL)
	{
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		m_pos = PlayerPosition;
		// 余りが0の場合
		//if (m_nCount % m_nCreateCount == REMAINDER)
		//{
			CParticle::Create(PlayerPosition, m_cText);
		//}
	}


}
//******************************************************************************
// 描画関数
//******************************************************************************
void CParticle_Emitter::Draw(void)
{
}
//******************************************************************************
// 破棄関数
//******************************************************************************
void CParticle_Emitter::Release(void)
{
	// 終了
	Uninit();
	return;
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void CParticle_Emitter::Load(const char * cText)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// ファイルポインタ
	FILE *pFile = NULL;

	// NULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(cText, "r");

		// NULLでない場合
		if (pFile != NULL)
		{
			// SCRIPTの文字が見つかるまで
			while (strcmp(cHeadText, "SCRIPT") != INIT_INT)
			{
				// テキストからcReedText分文字を読み込む
				fgets(cReedText, sizeof(cReedText), pFile);

				// 読み込んだ文字ををcHeadTextに格納
				sscanf(cReedText, "%s", &cHeadText);
			}
			// cHeadTextがSCRIPTだったら
			if (strcmp(cHeadText, "SCRIPT") == INIT_INT)
			{
				// END_SCRIPTの文字が見つかるまで
				while (strcmp(cHeadText, "END_SCRIPT") != INIT_INT)
				{
					// テキストからcReedText分文字を読み込む
					fgets(cReedText, sizeof(cReedText), pFile);

					// 読み込んだ文字ををcHeadTextに格納
					sscanf(cReedText, "%s", &cHeadText);

					// cHeadTextがMOTIONSETだったら
					if (strcmp(cHeadText, "SETTINGS") == INIT_INT)
					{
						// END_MOTIONSETの文字が見つかるまで
						while (strcmp(cHeadText, "END_SETTINGS") != INIT_INT)
						{
							// テキストからcReedText分文字を読み込む
							fgets(cReedText, sizeof(cReedText), pFile);

							// 読み込んだ文字ををcHeadTextに格納
							sscanf(cReedText, "%s", &cHeadText);

							// cHeadTextがALPHA_BLENDの場合
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount);
							}
						}
					}
				}
				// ファイルを閉じる
				fclose(pFile);
			}
			// 開けなかったら
			else
			{
				printf("ファイルを開く事が出来ませんでした。\n");
			}
		}
	}
}