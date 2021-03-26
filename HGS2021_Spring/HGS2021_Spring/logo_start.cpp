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
#include "logo_start.h"

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
LPDIRECT3DTEXTURE9 CStartLogo::m_pTexture;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStartLogo::CStartLogo()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStartLogo::~CStartLogo()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CStartLogo::TextureLoad(void)
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
void CStartLogo::TextureUnload(void)
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
CStartLogo * CStartLogo::Create()
{
	//�^�C�g�����S�̃|�C���^
	CStartLogo * pTitleLogo = NULL;
	//�^�C�g�����S�̃|�C���^��NULL�̏ꍇ
	if (pTitleLogo == NULL)
	{
		//�^�C�g�����S�̃������m��
		pTitleLogo = new CStartLogo;
		//v�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pTitleLogo != NULL)
		{
			//�^�C�g�����S�̈ʒu�ݒ�
			pTitleLogo->SetPosition(POSITION);
			//�^�C�g�����S�̃T�C�Y�ݒ�
			pTitleLogo->SetSize(SIZE);
			//�^�C�g�����S�̐F�ݒ�
			pTitleLogo->SetColor(COLOR);
			//�^�C�g�����S�̏����������֐��Ăяo��
			pTitleLogo->Init();
		}
	}
	//�^�C�g�����S�̃{�^���̃|�C���^��Ԃ�
	return pTitleLogo;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CStartLogo::Init(void)
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
void CStartLogo::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CStartLogo::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CScene2d::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CStartLogo::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}