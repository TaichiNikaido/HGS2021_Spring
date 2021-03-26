//=============================================================================
//
// �v���C���[ [player.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene2d.h"
#include "mode_game.h"
#include "player_3d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
<<<<<<< HEAD
#define TEXTURE ("Data/Texture/Player.png")
=======
#define TEXTURE ("Data/Textrue/bakuhatsu.png")
>>>>>>> 296a8f33887d24dab4338283c2379c152acb8767
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0))
#define SPEED (0.01f)
#define CAMERA_DISTANCE (500.0f)
#define GRAVITY (50.5f)
#define JUMP_POWER (150.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer3d::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer3d::CPlayer3d(int nPriority)
{
	m_Move = INITIAL_D3DXVECTOR3;						//�ړ���
	m_PositionOld = INITIAL_D3DXVECTOR3;				//�ߋ��̈ʒu
	m_CollisionSize = INITIAL_D3DXVECTOR3;				//�Փ˔���p�T�C�Y
	m_nSurvivalTime = 0;										//��������
	m_fCameraDistance = 0.0f;							//�J�����Ƃ̋���
	m_bJump = false;									//�W�����v
	m_State = STATE_NONE;								//���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer3d::~CPlayer3d()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CPlayer3d::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE,						// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CPlayer3d::TextureUnload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayer3d * CPlayer3d::Create(D3DXVECTOR3 Position)
{
	//�v���C���[�̃|�C���^
	CPlayer3d * pPlayer = NULL;
	//�v���C���[��NULL�̏ꍇ
	if (pPlayer == NULL)
	{
		//�v���C���[�̃������m��
		pPlayer = new CPlayer3d;
		//�v���C���[��NULL�ł͂Ȃ��ꍇ
		if (pPlayer != NULL)
		{
			//�v���C���[�̈ʒu��ݒ肷��
			pPlayer->SetPosition(Position);
			//�v���C���[�̌�����ݒ肷��
			pPlayer->SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));
			//�v���C���[�̃T�C�Y��ݒ肷��
			pPlayer->SetSize(SIZE);
			//�v���C���[�̏����������֐��Ăяo��
			pPlayer->Init();
		}
	}
	//�v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayer3d::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�|���S��3D�̏����������֐��Ăяo��
	CPolygon3d::Init();
	//�Փ˔���p�T�C�Y�̎擾
	m_CollisionSize = GetSize();
	//�ړ����x�̏����ݒ�
	m_fSpeed = SPEED;
	//�J�����Ƃ̋����������ݒ�
	m_fCameraDistance = CAMERA_DISTANCE;
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayer3d::Uninit(void)
{
	//�|���S��3D�̏I�������֐��Ăяo��
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer3d::Update(void)
{
	//�ߋ��̈ʒu��ۑ�����
	m_PositionOld = GetPosition();
	//�|���S��3D�̍X�V�����֐��Ăяo��
	CPolygon3d::Update();
	//�ړ������֐��Ăяo��
	Move();
	//���͏����֐��Ăяo��
	Input();
	//�������Ԃ����Z����
	m_nSurvivalTime++;
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayer3d::Draw(void)
{
	//�|���S��3D�̕`�揈���֐��Ăяo��
	CPolygon3d::Draw();
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPlayer3d::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();

	if (pJoystick->GetJoystickTrigger(JS_A))
	{
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_SPACE))
	{
		//�����W�����v���Ă��Ȃ�������
		if (m_bJump == false)
		{
			//�W�����v����
			m_Move.y += JUMP_POWER;
			//�W�����v��Ԃɂ���
			m_bJump = true;
		}
	}
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer3d::Move(void)
{
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�������S��Ԃ���Ȃ��Ƃ�
	if (m_State != STATE_DEATH)
	{
		//�ړ�������
		m_Move.x += m_fSpeed;
		//�W�����v���Ă�Ƃ�
		if (m_bJump == true)
		{
			//�d�͂�������
			m_Move.y -= GRAVITY;
		}
	}
	//�ʒu�X�V
	Position += m_Move;
	//�ʒu�̐ݒ�
	SetPosition(Position);
	//�W�����v���Ă�Ƃ�
	if (m_bJump == true)
	{
		//�d�͂�������
		m_Move.y -= GRAVITY;
	}
	if (Position.y <= 0.0f)
	{
		m_Move.y = 0.0f;
		//�W�����v��Ԃɂ���
		m_bJump = false;
	}
}

//=============================================================================
// �ړ��\�͈͏����֐�
//=============================================================================
D3DXVECTOR3 CPlayer3d::MovableRange()
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y���擾����
	D3DXVECTOR3 Size = GetSize();
	if (Position.y >= SCREEN_HEIGHT)
	{
		m_Move.y = 0.0f;

	}
	return Position;
}