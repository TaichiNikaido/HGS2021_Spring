//=============================================================================
//
// �����L���O�w�i [bg_ranking.cpp]
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
#include "bg_ranking.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Logo/Logo_Title.png")
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CRankingBG::m_pTexture;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRankingBG::CRankingBG()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRankingBG::~CRankingBG()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CRankingBG::TextureLoad(void)
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
void CRankingBG::TextureUnload(void)
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
CRankingBG * CRankingBG::Create()
{
	//�����L���O�w�i�̃|�C���^
	CRankingBG * pRankingBG = NULL;
	//�^�C�g���w�i�̃|�C���^��NULL�̏ꍇ
	if (pRankingBG == NULL)
	{
		//�^�C�g���w�i�̃������m��
		pRankingBG = new CRankingBG;
		//�^�C�g���w�i�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pRankingBG != NULL)
		{
			//�^�C�g���w�i�̈ʒu�ݒ�
			pRankingBG->SetPosition(POSITION);
			//�^�C�g���w�i�̃T�C�Y�ݒ�
			pRankingBG->SetSize(SIZE);
			//�^�C�g���w�i�̏����������֐��Ăяo��
			pRankingBG->Init();
		}
	}
	//�^�C�g�����S�̃{�^���̃|�C���^��Ԃ�
	return pRankingBG;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CRankingBG::Init(void)
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
void CRankingBG::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CRankingBG::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CScene2d::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CRankingBG::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}