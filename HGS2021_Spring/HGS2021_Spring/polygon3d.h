//=============================================================================
//
// 3Dポリゴン管理 [polygon3d.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPolygon3d :public CScene3d
{
public:
	CPolygon3d(int nPriority = DEFAULT_PRIORITY);
	~CPolygon3d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX]);
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetScale(float fScale) { m_fScale = fScale; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	D3DXCOLOR GetColor(void) { return m_Color; };
	float GetScale(void) { return m_fScale; };
private:
	D3DXMATRIX m_mtxWorld;							//ワールドマトリクス
	LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	D3DXVECTOR2				m_aTex[NUM_VERTEX];		//テクスチャのUV座標
	D3DXCOLOR	 			m_Color;				//頂点カラー
	float					m_fScale;				//縮尺
	float					m_fAngle;				//角度
	float					m_fLength;				//長さ
};
#endif