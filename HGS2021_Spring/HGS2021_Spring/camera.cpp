//=============================================================================
//
// �J���� [camera.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "keyboard.h"
#include "joystick.h"
#include "camera.h"
#include "player_3d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_DISTANCE (0.0f)																	//�����̏����l
#define VECTOR (D3DXVECTOR3(0.0f, 1.0f, 0.0f))													//������x�N�g��
#define ROTATION (D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)))		//��]

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_PositionV = INITIAL_D3DXVECTOR3;	//���_�̈ʒu
	m_PositionR = INITIAL_D3DXVECTOR3;	//�����_�̈ʒu
	m_VectorU = INITIAL_D3DXVECTOR3;	//������x�N�g��
	m_Rotation = INITIAL_ROTATION;		//��]
	m_fDistance = INIT_FLOAT;			//����
	memset(m_MtxView, NULL, sizeof(m_MtxView));
	memset(m_MtxProjection, NULL, sizeof(m_MtxProjection));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CCamera::Init(void)
{
	//�v���C���[�̎擾
	CPlayer3d * pPlayer3d = CGameMode::GetPlayer3d();
	if (pPlayer3d != NULL)
	{
		//�v���C���[�̈ʒu�ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer3d->GetPosition();
		//�v���C���[�Ƃ̋�����ݒ�
		float PlayerDistance = pPlayer3d->GetCameraDistance();
		//���_��ݒ肷��
		m_PositionV = D3DXVECTOR3(0.0f,0.0f,-1000.0f);
		//�����_�̐ݒ�
		m_PositionR = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
	}
	//������x�N�g���̏����ݒ�
	m_VectorU = VECTOR;
	//��]�����̏����ݒ�
	//m_Rotation = ROTATION;
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CCamera::Update(void)
{
	//�v���C���[�̎擾
	CPlayer3d * pPlayer3d = CGameMode::GetPlayer3d();
	if (pPlayer3d != NULL)
	{
		//�v���C���[�̈ʒu�ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer3d->GetPosition();
		//�v���C���[�Ƃ̋�����ݒ�
		float PlayerDistance = pPlayer3d->GetCameraDistance();
		//���_��ݒ肷��
		m_PositionV = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
		//�����_�̐ݒ�
		m_PositionR = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
	}
	//������x�N�g���̏����ݒ�
	m_VectorU = VECTOR;
	//��]�����̏����ݒ�
	//m_Rotation = ROTATION;
}

//=============================================================================
// �J�����ݒ�֐�
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_MtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_MtxView, &m_PositionV, &m_PositionR, &m_VectorU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_MtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, D3DXToRadian(90.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProjection);
}