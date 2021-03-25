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
#include "billboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_POS  (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f))	//�v���C���[�̈ʒu
#define PLAYER_SIZE (D3DXVECTOR3(65.0f,65.0f,0.0f))								//�v���C���[�̃T�C�Y													
#define PLAYER_MAX_BOMB (5)														//�v���C���[�̍ő�{����
#define PLAYER_MAX_LIFE (5)														//�v���C���[�̍ő僉�C�t

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer3d :public CBillboard
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_DEATH,		//���S
		STATE_INVINCIBLE,	//���G
		STATE_MAX
	}STATE;		//���
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_UP,		//�����
		INPUT_DOWN,		//������
		INPUT_LEFT,		//������
		INPUT_RIGHT,	//�E����
		INPUT_BOMB,		//�{������
		INPUT_SHOT,		//�e����
		INPUT_MAX
	}INPUT;		//���͏��
	CPlayer3d(int nPriority = OBJTYPE_PLAYER);
	~CPlayer3d();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CPlayer3d * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Input(void);
	void Move(void);
	D3DXVECTOR3 MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_Move;						//�ړ���
	float m_fSpeed;							//����
	STATE m_State;							//���
	INPUT m_Input;							//���̓L�[���
};
#endif