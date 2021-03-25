//=============================================================================
//
// �v���C���[ [player.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

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
#include "player_2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("")
#define SIZE (D3DXVECTOR3(0.0f,0.0f,0.0))
#define SPEED (0.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer2d::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer2d::CPlayer2d(int nPriority) : CScene2d(nPriority)
{
	m_Move = INITIAL_D3DXVECTOR3;						//�ړ���
	m_State = STATE_NONE;								//���
	m_Input = INPUT_NONE;								//���̓L�[���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer2d::~CPlayer2d()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CPlayer2d::TextureLoad(void)
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
void CPlayer2d::TextureUnload(void)
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
CPlayer2d * CPlayer2d::Create(D3DXVECTOR3 Position)
{
	//�v���C���[�̃|�C���^
	CPlayer2d * pPlayer2d = NULL;
	//�v���C���[��NULL�̏ꍇ
	if (pPlayer2d == NULL)
	{
		//�v���C���[�̃������m��
		pPlayer2d = new CPlayer2d;
		//�v���C���[��NULL�ł͂Ȃ��ꍇ
		if (pPlayer2d != NULL)
		{
			//�v���C���[�̏����������֐��Ăяo��
			pPlayer2d->Init();
			//�v���C���[�̈ʒu��ݒ肷��
			pPlayer2d->SetPosition(Position);
			//�v���C���[�̃T�C�Y��ݒ肷��
			pPlayer2d->SetSize(SIZE);
		}
	}
	//�v���C���[�̃|�C���^��Ԃ�
	return pPlayer2d;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayer2d::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2D�V�[���Ǘ������������֐��Ăяo��
	CScene2d::Init();
	//�ړ����x�̏����ݒ�
	m_fSpeed = SPEED;
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayer2d::Uninit(void)
{
	//2D�V�[���Ǘ��I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer2d::Update(void)
{
	//2D�V�[���Ǘ��X�V�����֐��Ăяo��
	CScene2d::Update();
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�ړ��\�͈͏����֐��Ăяo��
	Position = MovableRange();
	//�ʒu�X�V
	Position += m_Move;
	//�ʒu�̐ݒ�
	SetPosition(Position);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayer2d::Draw(void)
{
	//2D�V�[���Ǘ��`�揈���֐��Ăяo��
	CScene2d::Draw();
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPlayer2d::Input(void)
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
	//�v���C���[���ړ����Ă��Ȃ��Ƃ�
	m_Move = INITIAL_D3DXVECTOR3;
	//��ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//���̓L�[������ɂ���
		m_Input = INPUT_UP;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_DOWN;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_LEFT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�E�ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//���̓L�[�����E�ɂ���
		m_Input = INPUT_RIGHT;
		//�ړ������֐��Ăяo��
		Move();
	}
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer2d::Move(void)
{
	//�������S��Ԃ���Ȃ��Ƃ�
	if (m_State != STATE_DEATH)
	{
		switch (m_Input)
		{
			//�������͏�񂪏�̎�
		case INPUT_UP:
			//Y���̏�����Ɉړ��ʂ����Z
			m_Move.y = cosf(D3DX_PI) * m_fSpeed;
			break;
			//�������͏�񂪉��̎�
		case INPUT_DOWN:
			//Y���̉������Ɉړ��ʂ����Z
			m_Move.y = cosf(D3DX_PI) * -m_fSpeed;
			break;
			//�������͏�񂪍��̎�
		case INPUT_LEFT:
			//X���̍������Ɉړ��ʂ����Z
			m_Move.x = cosf(D3DX_PI) * m_fSpeed;
			break;
			//�������͏�񂪉E�̎�
		case INPUT_RIGHT:
			//X���̉E�����Ɉړ��ʂ����Z
			m_Move.x = cosf(D3DX_PI) * -m_fSpeed;
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// �ړ��\�͈͏����֐�
//=============================================================================
D3DXVECTOR3 CPlayer2d::MovableRange()
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y���擾����
	D3DXVECTOR3 Size = GetSize();
	//�����v���C���[�����ʊO�ɍs������
	if (Position.y - Size.y / 2 < 0)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.y = Size.y / 2;
	}
	//�����v���C���[������ʊO�ɍs������
	if (Position.y + Size.y / 2 > SCREEN_HEIGHT)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.y = SCREEN_HEIGHT - Size.y / 2;
	}
	//�����v���C���[������ʊO�ɍs������
	if (Position.x - Size.y / 2 < 0)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.x = Size.y / 2 + 0;
	}
	//�����v���C���[���E��ʊO�ɍs������
	if (Position.x + Size.y / 2 > SCREEN_WIDTH)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.x = SCREEN_WIDTH - Size.y / 2;
	}
	return Position;
}