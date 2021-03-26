//******************************************************************************
// パーティクル [ particle.h]
// Author : 管原 司
//******************************************************************************
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "billboard.h"
//******************************************************************************
// クラス
//******************************************************************************
class CParticle : public CBillboard
{
public:
	CParticle();
	~CParticle();
	static CParticle *Create(D3DXVECTOR3 pos, const char *cText);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadParticle(const char *cText);
	void SetTexNum(int nTexNum);
	static void CreateEffect(D3DXVECTOR3 pos, int nCreateNum, const char *cText);
private:
	bool m_bAlpha_Blend;		// 加算合成を行うか
	bool m_bLife;				// ライフを使用するか
	bool m_bRandomPos;			// 位置をランダムにするか
	bool m_bRandomSize;			// ランダムサイズ
	bool m_bAddScale;			// 拡大率を加算するか
	bool m_bSubColor;			// 色減算を行うか
	bool m_bRotRandom;			// 向きランダム
	bool m_bTexRandom;			// テクスチャランダム
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_Random_pos;	// 位置ランダム
	D3DXVECTOR3 m_size;			// サイズ
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_Angle;		// 角度
	D3DXVECTOR3 m_AddAngle;		// xyzの角度加算
	D3DXCOLOR m_color;			// 色
	D3DXCOLOR m_SubColor;		// 色減算量
	int m_nAlpha;				// 描画する透明度
	int m_nLife;				// ライフ数
	int m_nTexNum;				// テクスチャナンバー
	int m_nMinTex_RandomNum;	// テクスチャナンバー
	int m_nMaxTex_RandomNum;	// テクスチャナンバー
	float m_fAngle;				// 角度
	float m_fAddAngle;			// 角度の加算量
	float m_fRandom_Min_Size;	// ランダムサイズの最小値
	float m_fRandom_Max_Size;	// ランダムサイズの最大値
	float m_fAddScale;			// 拡大率の加算量
};
#endif