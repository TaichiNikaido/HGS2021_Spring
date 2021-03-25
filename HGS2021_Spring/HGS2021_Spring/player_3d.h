//=============================================================================
//
// プレイヤー [player.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "billboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_POS  (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f))	//プレイヤーの位置
#define PLAYER_SIZE (D3DXVECTOR3(65.0f,65.0f,0.0f))								//プレイヤーのサイズ													
#define PLAYER_MAX_BOMB (5)														//プレイヤーの最大ボム数
#define PLAYER_MAX_LIFE (5)														//プレイヤーの最大ライフ

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer3d :public CBillboard
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_DEATH,		//死亡
		STATE_INVINCIBLE,	//無敵
		STATE_MAX
	}STATE;		//状態
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_UP,		//上方向
		INPUT_DOWN,		//下方向
		INPUT_LEFT,		//左方向
		INPUT_RIGHT,	//右方向
		INPUT_BOMB,		//ボム発射
		INPUT_SHOT,		//弾発射
		INPUT_MAX
	}INPUT;		//入力状態
	CPlayer3d(int nPriority = OBJTYPE_PLAYER);
	~CPlayer3d();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CPlayer3d * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Input(void);
	void Move(void);
	D3DXVECTOR3 MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_Move;						//移動量
	float m_fSpeed;							//速さ
	STATE m_State;							//状態
	INPUT m_Input;							//入力キー情報
};
#endif