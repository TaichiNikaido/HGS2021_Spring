//=============================================================================
//
// マネージャー [manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CSound;
class CKeyboard;
class CJoystick;
class CTitleMode;
class CGameMode;
class CResultMode;
class CFade;
class CParticle_Texture;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void StartFade(MODE mode);
	static void StopFade(void);
	static void SetMode(MODE Mode);
	static MODE GetMode(void) { return m_Mode; }
	static CRenderer * GetRenderer(void) { return m_pRenderer; }
	static CSound * GetSound(void) { return m_pSound; }
	static CKeyboard * GetKeyboard(void) { return m_pKeyboard; }
	static CJoystick * GetJoystick(void) { return m_pJoystick; }
	static CGameMode * GetGameMode(void) { return m_pGameMode; }
	static CResultMode * GetResultMode(void) { return m_pResultMode; }
	static CFade * GetFade(void) { return m_pFade; }
	static CParticle_Texture *GetParticle_Texture(void) { return m_pParticle_Texture; }
private:
	void LoadAll(void);
	void UnloadAll(void);
	void DeleteAll(void);
	static CRenderer * m_pRenderer;
	static CSound * m_pSound;
	static CKeyboard * m_pKeyboard;
	static CJoystick * m_pJoystick;
	static CGameMode * m_pGameMode;
	static CResultMode * m_pResultMode;
	static CFade * m_pFade;
	static MODE m_Mode;
	static CParticle_Texture *m_pParticle_Texture;
	static bool m_bUseFade;
};
#endif