//=============================================================================
// bg処理 [bg.h]
// Author : 林川紗梨夏
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "polygon3d.h"

#define TEXTURE_BLOCK "Data/Textrue/ookamitex.png"
#define BLOCK_SIZE (100.0f)
#define ICE_LIFE 3
#define HARD_ICE_LIFE 6

class CBlock : public CPolygon3d
{
public:
	CBlock(int nPriority = 3);
	~CBlock();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BLOCK_001,
		TYPE_MAX,
	}TYPE;
	typedef struct
	{
		bool bIsTop;
		bool bIsBottom;
		bool bIsRight;
		bool bIsLeft;
		bool bIsFront;
		bool bIsBack;
	}IS_COLLISION;
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	IS_COLLISION Collision(void);
	void AddBreakIces(int nBreakIce) { m_nBreakIces += nBreakIce; }
	int GetBreakIces(void) { return m_nBreakIces; }
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[1];//テクスチャのポインタ
	int                     m_nPatternAnim; //アニメーションパターン
	int                     m_nCountAnim; //アニメーションパターン
	int m_nBreakIces;

};
#endif // !_BLOCK_H_