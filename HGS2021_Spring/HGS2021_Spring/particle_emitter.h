//******************************************************************************
// パーティクルエミッター [particle_emitter.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class CParticle_Emitter : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BOAD,
		TYPE_MAX
	}TYPE;
	CParticle_Emitter();
	~CParticle_Emitter();
	static CParticle_Emitter *Create(D3DXVECTOR3 pos, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;			// 位置座標
	int m_nCount;				// 間隔
	int m_nCreateCount;			// 生成カウント
	char m_cText[MAX_TEXT];		// テキスト
	TYPE m_Type;				// タイプ
};
#endif