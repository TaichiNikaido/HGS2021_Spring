//******************************************************************************
// パーティクルエミッター [particle_emitter.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
#include "particle_effect.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_TEXT	(1024)								// テキストの最大数
#define DATA_TEXT	("data/Effect/Explosion_Data.txt")	// テキスト
#define REMAINDER	(0)									// 余り0
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle_Effect::CParticle_Effect()
{
	m_pos					= INITIAL_D3DXVECTOR3;
	m_nCreate_TotalCount	= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle_Effect::~CParticle_Effect()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle_Effect * CParticle_Effect::Create(D3DXVECTOR3 pos)
{
	// CParticle_Effectのポインタ
	CParticle_Effect *pParticle_Effect;

	// メモリ確保
	pParticle_Effect = new CParticle_Effect;

	// 位置代入
	pParticle_Effect->m_pos = pos;

	// テキストファイル読み込み
	pParticle_Effect->Load(DATA_TEXT);

	// 初期化
	pParticle_Effect->Init();

	// ポインタを返す
	return pParticle_Effect;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CParticle_Effect::Init(void)
{
	// 生成
	CParticle::CreateEffect(m_pos, m_nCreate_TotalCount, DATA_TEXT);

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CParticle_Effect::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CParticle_Effect::Update(void)
{
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CParticle_Effect::Draw(void)
{
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void CParticle_Effect::Load(const char * cText)
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
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == INIT_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreate_TotalCount);
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