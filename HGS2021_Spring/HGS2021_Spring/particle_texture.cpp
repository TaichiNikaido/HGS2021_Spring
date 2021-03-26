//***********************************************************************************
//	テクスチャ	[texture.cpp]
//	Author : 管原 司
//***********************************************************************************


//***********************************************************************************
// インクルードファイル
//***********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "particle_texture.h"
//***********************************************************************************
// マクロ定義
//***********************************************************************************
#define TEXTURE_TEXT	("data/TEXTURE/texture.txt")			// テクスチャテキスト
#define MAX_TEXT		(1024)									// 文字の最大数
//***********************************************************************************
//静的メンバ変数宣言
//***********************************************************************************
//***********************************************************************************
// コンストラクタ
//***********************************************************************************
CParticle_Texture::CParticle_Texture()
{
	m_pTexture = NULL;
	m_pLoadTexture = NULL;
	m_nNumTex = INIT_INT;
}
//***********************************************************************************
// デストラクタ
//***********************************************************************************
CParticle_Texture::~CParticle_Texture()
{
}
//***********************************************************************************
// 初期化関数
//***********************************************************************************
HRESULT CParticle_Texture::Init(void)
{
	// テクスチャ読み込み
	Load();

	return S_OK;
}
//***********************************************************************************
// 終了関数
//***********************************************************************************
void CParticle_Texture::Uninit(void)
{
	// テクスチャ破棄
	if (m_pTexture != NULL)
	{
		// 破棄
		m_pTexture->Release();

		// NULLに
		m_pTexture = NULL;
	}
	// 読み込み用テクスチャの破棄
	if (m_pLoadTexture != NULL)
	{
		// テクスチャ数分回す
		for (int nCnt = INIT_INT; nCnt < m_nNumTex; nCnt++)
		{
			// テクスチャ破棄
			m_pLoadTexture[nCnt]->Release();
		}

		// メモリ破棄
		delete[] m_pLoadTexture;

		// m_pTextureをNULLに
		m_pLoadTexture = NULL;
	}
}
//***********************************************************************************
// テクスチャ読み込み
//***********************************************************************************
void CParticle_Texture::Load(void)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// テクスチャのテキスト
	char **cTexText = NULL;

	// テクスチャカウント
	int nTexCnt = INIT_INT;

	// ファイルポインタ
	FILE *pFile = NULL;

	// NULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(TEXTURE_TEXT, "r");

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

					// cHeadTextがTEXTURE_NUMの場合 
					if (strcmp(cHeadText, "TEXTURE_NUM") == INIT_INT)
					{
						// テクスチャの数をm_nNumTexに格納
						sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nNumTex);

						// NULLの場合
						if (cTexText == NULL)
						{
							// メモリ確保
							cTexText = new char *[m_nNumTex];

							// NULLでない場合
							if (cTexText != NULL)
							{
								// テクスチャ数分回す
								for (int nCnt = INIT_INT; nCnt < m_nNumTex; nCnt++)
								{
									// メモリ確保
									cTexText[nCnt] = new char[MAX_TEXT];
								}
							}
						}
					}
					// cHeadTextがTEXTURE_FILENAMEの場合
					if (strcmp(cHeadText, "TEXTURE_FILENAME") == INIT_INT)
					{
						// テクスチャのパスをcTexTextに格納
						sscanf(cReedText, "%s %s %s", &cDie, &cDie, cTexText[nTexCnt]);

						// インクリメント
						nTexCnt++;
					}
				}
			}
			// レンダラー取得
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			// メモリ確保
			m_pLoadTexture = new LPDIRECT3DTEXTURE9[m_nNumTex];

			// テクスチャ数分回す
			for (int nCnt = INIT_INT; nCnt < m_nNumTex; nCnt++)
			{
				// テクスチャ読み込み
				D3DXCreateTextureFromFile(pDevice, cTexText[nCnt], &m_pLoadTexture[nCnt]);
			}
			// NULLでない場合
			if (cTexText != NULL)
			{
				// テクスチャ数分回す
				for (int nCnt = INIT_INT; nCnt < m_nNumTex; nCnt++)
				{
					// メモリ破棄
					delete[] cTexText[nCnt];
				}
				// メモリ破棄
				delete[] cTexText;

				// NULLに
				cTexText = NULL;
			}
			// ファイルを閉じる
			fclose(pFile);
		}
	}
}
//***********************************************************************************
// テクスチャ取得
//***********************************************************************************
LPDIRECT3DTEXTURE9 CParticle_Texture::GetTexture(int TexNum)
{
	// 代入
	m_pTexture = m_pLoadTexture[TexNum];

	// テクスチャを返す
	return m_pTexture;
}