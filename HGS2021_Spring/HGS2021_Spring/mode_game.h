//=============================================================================
//
// ゲームモード [mode_game.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODE_GAME_H_
#define _MODE_GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLight;
class CCamera;
class CPlayer2d;
class CPlayer3d;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGameMode : CScene
{
public:
	CGameMode();
	~CGameMode();
	static CGameMode * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCamera * GetCamera(void) { return m_pCamera; }
	static CPlayer2d * GetPlayer2d(void) { return m_pPlayer2d; }
	static CPlayer3d * GetPlayer3d(void) { return m_pPlayer3d; }
private:
	void InitCreateAll(void);
	void UpdateCreateAll(void);
	static CCamera * m_pCamera;			//カメラのポインタ
	static CPlayer2d * m_pPlayer2d;		//プレイヤー2Dのポインタ
	static CPlayer3d * m_pPlayer3d;		//プレイヤー3Dのポインタ
	CLight * m_pLight;				//ライトのポインタ
};
#endif
