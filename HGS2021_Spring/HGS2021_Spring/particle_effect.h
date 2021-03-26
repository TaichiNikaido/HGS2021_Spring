//******************************************************************************
// パーティクルエフェクト [particle_effect.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PARTICLE_EFFECT_H_
#define _PARTICLE_EFFECT_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class CParticle_Effect : public CScene
{
public:
	CParticle_Effect();
	~CParticle_Effect();
	static CParticle_Effect *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Load(const char *cText);
	D3DXVECTOR3 m_pos;				// 位置座標
	int m_nCreate_TotalCount;		// 生成の総数
};
#endif