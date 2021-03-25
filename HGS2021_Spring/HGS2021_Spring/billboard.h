//=============================================================================
//
// ビルボード [billboard.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

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

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBillboard :public CScene
{
public:
	CBillboard();
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	void SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX]);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; };
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; };
	D3DXVECTOR3 GetSize(void) { return m_Size; };
	D3DXCOLOR GetColor(void) { return m_Color; };
private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファ
	D3DXMATRIX m_mtxWorld;					//行列計算用
	D3DXVECTOR3 m_Position;					//位置
	D3DXVECTOR3 m_Rotation;					//回転
	D3DXVECTOR3 m_Size;						//サイズ
	D3DXCOLOR m_Color;						//カラー
	D3DXVECTOR3 m_Move;						//移動量
	D3DXVECTOR2	m_aTexture[NUM_VERTEX];		//テクスチャのUV座標
};
#endif