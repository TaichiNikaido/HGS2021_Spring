//=============================================================================
//
// �^�C�g���w�i [bg_title.cpp]
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
#include "speedup.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/title_bg.png")
#define POSITION (D3DXVECTOR3(-200.0f,SCREEN_HEIGHT/2,0.0f))
#define SIZE (D3DXVECTOR3(500,100,0.0f))
#define ADD_MOVE (50.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CSpeedUp::m_pTexture;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSpeedUp::CSpeedUp()
{
	m_nCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSpeedUp::~CSpeedUp()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CSpeedUp::TextureLoad(void)
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
void CSpeedUp::TextureUnload(void)
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
CSpeedUp * CSpeedUp::Create()
{
	//�^�C�g���w�i�̃|�C���^
	CSpeedUp * pTitleBG = NULL;
	//�^�C�g���w�i�̃|�C���^��NULL�̏ꍇ
	if (pTitleBG == NULL)
	{
		//�^�C�g���w�i�̃������m��
		pTitleBG = new CSpeedUp;
		//�^�C�g���w�i�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pTitleBG != NULL)
		{
			//�^�C�g���w�i�̈ʒu�ݒ�
			pTitleBG->SetPosition(POSITION);
			//�^�C�g���w�i�̃T�C�Y�ݒ�
			pTitleBG->SetSize(SIZE);
			//�^�C�g���w�i�̏����������֐��Ăяo��
			pTitleBG->Init();
		}
	}
	//�^�C�g�����S�̃{�^���̃|�C���^��Ԃ�
	return pTitleBG;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CSpeedUp::Init(void)
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
void CSpeedUp::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CSpeedUp::Update(void)
{
	D3DXVECTOR3 Pos = GetPosition();
	//�{�^���̍X�V�����֐��Ăяo��
	CScene2d::Update();
	m_nCount++;
	//�ړ��J�E���g��
	if (m_nCount < 25)
	{
		Pos.x += ADD_MOVE;
	}
	if (m_nCount < 60 && m_nCount > 25)
	{

	}
	//�ړ��J�E���g��
	if (m_nCount < 90 && m_nCount > 60)
	{
		Pos.x += ADD_MOVE;
	}
	SetPosition(Pos);
	if (m_nCount > 90)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CSpeedUp::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}