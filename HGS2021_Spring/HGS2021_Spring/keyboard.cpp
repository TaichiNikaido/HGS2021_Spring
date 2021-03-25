//=============================================================================
//
// キーボード処理 [keyboard.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "keyboard.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CKeyboard::CKeyboard()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
}

//=============================================================================
// デストラクタ
//=============================================================================
CKeyboard::~CKeyboard()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pDinput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	int nCntKey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//g_aKeyState[nCntKey] = aKeyState[nCntKey]; //キープレス情報保存
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

bool CKeyboard::GetKeyboardPress(int nKey)
{
	return m_aKeyState[nKey] & 0x80 ? true : false;
}

bool CKeyboard::GetKeyboardTrigger(int nKey)
{
	return m_aKeyStateTrigger[nKey] & 0x80 ? true : false;
}

bool CKeyboard::GetKeyboardRelease(int nKey)
{
	return m_aKeyStateRelease[nKey] & 0x80 ? true : false;
}
