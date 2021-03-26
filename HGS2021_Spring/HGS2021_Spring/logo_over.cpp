//=============================================================================
//
// �X�^�[�g���S [logo_start.cpp]
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
#include "logo_over.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/title_logo.png")
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 - 100.0f,0.0f))
#define SIZE (D3DXVECTOR3(1000.0f,200.0f,0.0f))
#define COLOR (D3DXCOLOR(0.4f,0.6f,0.3f,1.0f))

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 COverLogo::m_pTexture;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
COverLogo::COverLogo()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
COverLogo::~COverLogo()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT COverLogo::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,					// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void COverLogo::TextureUnload(void)
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
// ���������֐��Ăяo��
//=============================================================================
COverLogo * COverLogo::Create()
{
	//�I�[�o�[���S�̃|�C���^
	COverLogo * pOverLogo = NULL;
	//�I�[�o�[���S�̃|�C���^��NULL�̏ꍇ
	if (pOverLogo == NULL)
	{
		//�I�[�o�[���S�̃������m��
		pOverLogo = new COverLogo;
		//�I�[�o�[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pOverLogo != NULL)
		{
			//�I�[�o�[���S�̈ʒu�ݒ�
			pOverLogo->SetPosition(POSITION);
			//�I�[�o�[���S�̃T�C�Y�ݒ�
			pOverLogo->SetSize(SIZE);
			//�I�[�o�[���S�̐F�ݒ�
			pOverLogo->SetColor(COLOR);
			//�I�[�o�[���S�̏����������֐��Ăяo��
			pOverLogo->Init();
		}
	}
	//�I�[�o�[���S�̃{�^���̃|�C���^��Ԃ�
	return pOverLogo;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT COverLogo::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�{�^���̏����������֐��Ăяo��
	CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void COverLogo::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void COverLogo::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CScene2d::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void COverLogo::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}