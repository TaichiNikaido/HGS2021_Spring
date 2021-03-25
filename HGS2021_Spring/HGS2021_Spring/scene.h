//*******************************************************************
// オブジェクト処理 [scene.h]
// Author : 管原司
//*******************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_
//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "main.h"
//*******************************************************************
// マクロ定義
//*******************************************************************
#define DEFAULT_PRIORITY (4)

//*******************************************************************
// オブジェクトクラス
//*******************************************************************
class CScene
{
public:
	// オブジェクトタイプ
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_DEFAULT,
		OBJTYPE_FADE,
		OBJTYPE_TUTORIAL,
		OBJTYPE_PLAYER,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_DEFAULT);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority);

	//純粋仮想関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void DesignationReleaseAll(OBJTYPE type);
	static void SetUpdateStop(bool bUpdateStop);

	static bool GetUpdateStop(void) { return m_bUpdateStop; }

protected:
	void Release(void);

private:
	OBJTYPE m_objType;					// オブジェクトの種類
	static CScene *m_pTop[OBJTYPE_MAX];	// 先頭のオブジェクトへのポインタ
	static CScene *m_pCur[OBJTYPE_MAX];	// 現在のオブジェクトへのポインタ
	CScene *m_pPrev;					// 前のオブジェクトへのポインタ
	CScene *m_pNext;					// 次のオブジェクトへのポインタ
	int m_nPriority;					// 描画順
	static int m_nNext;					// 次
	static bool m_bRelease;				// 破棄h判定
	bool m_bDeath;						// 死亡フラグ
	static bool m_bUpdateStop;			// 更新停止判定
};
#endif