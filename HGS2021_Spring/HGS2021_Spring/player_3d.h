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
#include "polygon3d.h"
#include "block.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer3d :public CPolygon3d
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_DEATH,		//死亡
		STATE_INVINCIBLE,	//無敵
		STATE_MAX
	}STATE;		//状態
	CPlayer3d(int nPriority = OBJTYPE_PLAYER);
	~CPlayer3d();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CPlayer3d * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	float GetCameraDistance(void) { return m_fCameraDistance; }
	D3DXVECTOR3 GetPositionOld(void) { return m_PositionOld; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	D3DXVECTOR3 GetMove(void) { return m_Move; };
	void SetMove(D3DXVECTOR3 Move);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize);
	void SetState(STATE state);
	STATE GetState(void) { return m_State; };
	void Death(D3DXVECTOR3 HitPos);
	CBlock::IS_COLLISION GetIsCollision(void) { return m_bIsCollision; };

	void SetIsCollision(CBlock::IS_COLLISION isCollision);
private:
	void Input(void);
	void Move(void);
	D3DXVECTOR3 MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_PositionOld;				//過去の位置
	D3DXVECTOR3 m_Move;						//移動量
	D3DXVECTOR3 m_CollisionSize;			//衝突判定用サイズ
	int m_nSurvivalTime;					//生存時間
	float m_fSpeed;							//速さ
	float m_fCameraDistance;				//カメラとの距離
	bool m_bJump;							//ジャンプしたかどうか
	STATE m_State;							//状態
	CBlock::IS_COLLISION m_bIsCollision;	//どの面に当たってるか
	int m_nPattarnAnim;						//アニメーションカウンタ
	int m_nCounterAnim;						//フレームカウンタ
	int m_nCreateCount;
	float m_fAddSpeed;
	bool m_bSyagami;
};
#endif