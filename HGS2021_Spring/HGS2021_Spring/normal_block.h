//=============================================================================
// bg処理 [bg.h]
// Author : 林川紗梨夏
//=============================================================================
#ifndef _NORMAL_BLOCK_H_
#define _NORMAL_BLOCK_H_

#include "scene3d.h"
#include "block.h"

#define TEXTURE_ICE_BLOCK		"Data/TEXTURE/BLOCK/ice_block.png"
class CNormalBlock : public CBlock
{
public:
	CNormalBlock(int nPriority = 3);
	~CNormalBlock();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_ICE,
		TYPE_MAX,
	}TYPE;

	static HRESULT Load(void);
	static void Unload(void);
	static CNormalBlock *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9   m_apTexture[TYPE_MAX];
	TYPE                    m_Type;//テクスチャタイプ
	D3DXVECTOR3             m_PosOld;
	D3DXVECTOR3             m_Move;
	int                     m_nLife; //ライフ
	bool                    m_IsFall; //落下可能か
};
#endif // !_BLOCK_H_


