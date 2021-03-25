//=============================================================================
//
// 2Dシーン管理 [scene2d.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene2d :public CScene
{
public:
	CScene2d(int nPriority = DEFAULT_PRIORITY);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetScale(float fScale) { m_fScale = fScale; }
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetVertexPosition(D3DXVECTOR3 aVertexPosition[NUM_VERTEX]);
	void SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX]);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXCOLOR GetColor(void) { return m_Color; }
	float GetScale(void) { return m_fScale; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;					//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//頂点バッファへのポインタ
	D3DXVECTOR3				m_Position;					//座標
	D3DXVECTOR3				m_Size;						//サイズ
	D3DXVECTOR3				m_Rotation;					//回転
	D3DXVECTOR3				m_aVtxPosition[NUM_VERTEX];	//頂点座標
	D3DXVECTOR2				m_aTexture[NUM_VERTEX];		//テクスチャのUV座標
	D3DXCOLOR	 			m_Color;					//カラー
	float					m_fScale;					//拡縮
	float					m_fAngle;					//角度
	float					m_fLength;					//長さ
};
#endif