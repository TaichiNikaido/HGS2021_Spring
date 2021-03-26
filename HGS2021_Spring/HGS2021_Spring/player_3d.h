//=============================================================================
//
// �v���C���[ [player.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "polygon3d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer3d :public CPolygon3d
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_DEATH,		//���S
		STATE_INVINCIBLE,	//���G
		STATE_MAX
	}STATE;		//���
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
private:
	void Input(void);
	void Move(void);
	D3DXVECTOR3 MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_PositionOld;				//�ߋ��̈ʒu
	D3DXVECTOR3 m_Move;						//�ړ���
	D3DXVECTOR3 m_CollisionSize;			//�Փ˔���p�T�C�Y
	int m_nSurvivalTime;							//��������
	float m_fSpeed;							//����
	float m_fCameraDistance;				//�J�����Ƃ̋���
	bool m_bJump;							//�W�����v�������ǂ���
	STATE m_State;							//���
};
#endif