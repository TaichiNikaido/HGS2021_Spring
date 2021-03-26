//******************************************************************************
// リスト構造 [scene.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
#include "scene2d.h"

//******************************************************************************
// 静的メンバ変数宣言
//******************************************************************************
CScene *CScene::m_pTop[OBJTYPE_MAX] = {};
CScene *CScene::m_pCur[OBJTYPE_MAX] = {};
int CScene::m_nNext = INIT_INT;
bool CScene::m_bUpdateStop = false;

//******************************************************************************
// コンストラクタ
//******************************************************************************
CScene::CScene(int nPriority)
{
	// m_pNextをNULL
	m_pNext = NULL;

	// m_pPrevをNULL
	m_pPrev = NULL;

	//トップがNULLの時
	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;
	}
	//トップがNULLじゃないとき
	else
	{
		m_pPrev = m_pCur[nPriority];
		m_pCur[nPriority]->m_pNext = this;
	}

	// m_pNextをNULL
	m_pNext = NULL;

	// m_pCurに代入
	m_pCur[nPriority] = this;

	// オブジェクトタイプ初期化
	m_objType = OBJTYPE_NONE;

	// Priority代入
	m_nPriority = nPriority;

	// 死亡フラグをfalseに
	m_bDeath = false;
}

//******************************************************************************
// デストラクタ
//******************************************************************************
CScene::~CScene()
{

}

//******************************************************************************
// オブジェクトタイプ設定
//******************************************************************************
void CScene::SetObjType(OBJTYPE objType)
{
	// オブジェクトタイプ代入
	m_objType = objType;
}

//******************************************************************************
// シーンの取得
//******************************************************************************
CScene * CScene::GetScene(int nPriority)
{
	// pSceneにm_pTop代入
	CScene *pScene = m_pTop[nPriority];

	// m_nNextの分だけ回す
	for (int nCount = INIT_INT; nCount < m_nNext; nCount++)
	{
		// NULLチェック
		if (pScene != NULL)
		{
			// Nextの情報の保持
			CScene *pSceneNext = pScene->m_pNext;

			// Nextの情報をpSceneに入れる
			pScene = pSceneNext;
		}
	}

	// m_nNextの加算
	m_nNext++;

	// pSceneがNULLの時
	if (pScene == NULL)
	{
		m_nNext = INIT_INT;
	}
	// ポインタを返す
	return pScene;
}

//******************************************************************************
// 全破棄処理関数
//******************************************************************************
void CScene::ReleaseAll(void)
{
	// オブジェクトタイプの最大数分繰り返す
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// pSceneにm_pTopを代入
		CScene *pScene = m_pTop[nCount];

		// pSceneがNULLでない場合
		while (pScene != NULL)
		{
			// pSaveにpSceneのm_pNextを保存
			CScene *pSave = pScene->m_pNext;
			// 終了
			pScene->Release();
			// pSceneにpSaveを代入
			pScene = pSave;
		}
	}
	// オブジェクトタイプの最大数分繰り返す
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// pSceneにm_pTopを代入
		CScene *pScene = m_pTop[nCount];

		// pSceneがNULLでない場合
		while (pScene != NULL)
		{
			// pSaveにpSceneのm_pNextを代入
			CScene *pSave = pScene->m_pNext;

			// pSceneの死亡m_bDeathtrueの場合
			if (pScene->m_bDeath == true)
			{
				// pSceneのm_pPrevがNULLでない場合
				if (pScene->m_pPrev != NULL)
				{
					// pSceneのm_pPrevのm_pNextをpSceneのm_pNextにする
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}
				// pSceneのm_pNextがNULLでない場合
				if (pScene->m_pNext != NULL)
				{
					// pSceneのm_pNextのm_pPrevをpSceneのm_pPrevにする 
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}
				// m_pTopがpSceneの場合
				if (m_pTop[nCount] == pScene)
				{
					// m_pTopをpSceneのm_pNextにする
					m_pTop[nCount] = pScene->m_pNext;
				}
				// m_pCurがpSceneの場合
				if (m_pCur[nCount] == pScene)
				{
					// m_pCurをpSceneのm_pPrevにする
					m_pCur[nCount] = pScene->m_pPrev;
				}

				// オブジェクトを破棄
				delete pScene;
			}

			// pSceneに保存していたポインタを代入
			pScene = pSave;
		}
	}
}
//******************************************************************************
// 指定破棄関数
//******************************************************************************
void CScene::DesignationReleaseAll(OBJTYPE type)
{
	// オブジェクトタイプ最大数分繰り返す
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// 指定したタイプ出ない場合
		if (nCount != type)
		{
			// pSceneにm_pTopを代入
			CScene *pScene = m_pTop[nCount];

			// pSceneがNULLになるまで繰り返す
			while (pScene != NULL)
			{
				//終了処理
				CScene *pSave = pScene->m_pNext;
				pScene->Release();
				pScene = pSave;
			}
		}
	}

	// オブジェクトタイプ最大数分繰り返す
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// pSceneにm_pTopを代入
		CScene *pScene = m_pTop[nCount];

		// pSceneがNULLになるまで繰り返す
		while (pScene != NULL)
		{
			// pSceneのm_pNextを保存
			CScene *pSave = pScene->m_pNext;

			// 死亡フラグがtrueの場合
			if (pScene->m_bDeath == true)
			{
				// pSceneのm_pPrevがNULLでない場合
				if (pScene->m_pPrev != NULL)
				{
					// pSceneのm_pPrevのm_pNextをpSceneのm_pNextにする
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}
				// pSceneのm_pNextがNULLでない場合
				if (pScene->m_pNext != NULL)
				{
					// pSceneのm_pNextのm_pPrevをpSceneのm_pPrevにする
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}
				// pSceneがm_pTopだった場合
				if (m_pTop[nCount] == pScene)
				{
					// m_pTopをpSceneのm_pNextにする
					m_pTop[nCount] = pScene->m_pNext;
				}
				// pSceneがm_pCurとだった場合
				if (m_pCur[nCount] == pScene)
				{
					// m_pCurをpSceneのm_pPrevにする
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//オブジェクトを破棄
				delete pScene;
			}
			// pSceneに保存していたのを代入する
			pScene = pSave;
		}
	}
}
//******************************************************************************
// 更新停止関数
//******************************************************************************
void CScene::SetUpdateStop(bool bUpdateStop)
{
	m_bUpdateStop = bUpdateStop;
}

//******************************************************************************
// 全更新処理
//******************************************************************************
void CScene::UpdateAll(void)
{
	// 更新停止変数がfalseの場合
	if (m_bUpdateStop == false)
	{
		// オブジェクトタイプの最大数分繰り返す
		for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
		{
			// pSceneにm_pTopを代入
			CScene *pScene = m_pTop[nCount];

			// pSceneがNULLになるまで繰り返す
			while (pScene != NULL)
			{
				// pSceneのm_pNextを保存
				CScene *pSave = pScene->m_pNext;

				// 死亡フラグがfalseの場合
				if (pScene->m_bDeath == false)
				{
					//更新処理
					pScene->Update();
				}
				// 保存していたものを代入
				pScene = pSave;
			}
		}
	}
	else
	{
		// pSceneにm_pTopを代入
		CScene *pScene = m_pTop[OBJTYPE_TUTORIAL];

		// pSceneがNULLになるまで繰り返す
		while (pScene != NULL)
		{
			// pSceneのm_pNextを保存
			CScene *pSave = pScene->m_pNext;

			// 死亡フラグがfalseの場合
			if (pScene->m_bDeath == false)
			{
				//更新処理
				pScene->Update();
			}
			// 保存していたものを代入
			pScene = pSave;
		}
	}
	// オブジェクトタイプの最大数分繰り返す
	for (int nCount = INIT_INT; nCount < OBJTYPE_MAX; nCount++)
	{
		// pSceneにm_pTopを代入
		CScene *pScene = m_pTop[nCount];

		// pSceneがNULLになるまで繰り返す
		while (pScene != NULL)
		{
			// pSceneのm_pNextを保存
			CScene *pSave = pScene->m_pNext;

			// 死亡フラグがtrueの場合
			if (pScene->m_bDeath == true)
			{
				// pSceneのm_pPrevがNULLでない場合
				if (pScene->m_pPrev != NULL)
				{
					// pSceneのm_pPrevのm_pNextをpSceneのm_pNextにする
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}
				// pSceneのm_pNextがNULLでない場合
				if (pScene->m_pNext != NULL)
				{
					// pSceneのm_pNextのm_pPrevをpSceneのm_pPrevにする
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}
				// pSceneがm_pTopだった場合
				if (m_pTop[nCount] == pScene)
				{
					// m_pTopをpSceneのm_pNextにする
					m_pTop[nCount] = pScene->m_pNext;
				}
				// pSceneがm_pCurとだった場合
				if (m_pCur[nCount] == pScene)
				{
					// m_pCurをpSceneのm_pPrevにする
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//オブジェクトを破棄
				delete pScene;
			}
			// 保存をしていたものを代入
			pScene = pSave;
		}
	}
}

//******************************************************************************
// 全描画関数
//******************************************************************************
void CScene::DrawAll(void)
{
	// オブジェクトタイプの最大数分繰り返す
	for (int nCountpriority = INIT_INT; nCountpriority < OBJTYPE_MAX; nCountpriority++)
	{
		// pSceneにm_pTopを代入
		CScene*pScene = m_pTop[nCountpriority];
		CScene*pSceneNext = NULL;

		// pSceneがNULLになるまで繰り返す
		while (pScene != NULL)
		{
			// pSceneNextにpSceneのm_pNextを代入
			pSceneNext = pScene->m_pNext;

			// 描画
			pScene->Draw();

			// pSceneにpSceneNextを代入
			pScene = pSceneNext;
		}
	}
}

//******************************************************************************
// 死亡フラグを立てる関数
//******************************************************************************
void CScene::Release(void)
{
	//死亡フラグを立てる
	m_bDeath = true;
}