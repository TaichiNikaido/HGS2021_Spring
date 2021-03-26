//=============================================================================
//
// �w�i�̏��� [bg.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "block.h"
#include "normal_block.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
LPDIRECT3DTEXTURE9 CNormalBlock::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNormalBlock::CNormalBlock(int nPriority) : CBlock(nPriority)
{
	m_Type = TYPE_NONE;
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = ICE_LIFE;
	m_IsFall = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNormalBlock::~CNormalBlock()
{

}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CNormalBlock::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ICE_BLOCK, &m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CNormalBlock::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CNormalBlock * CNormalBlock::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CNormalBlock *pBlock;

	pBlock = new CNormalBlock;
	if (pBlock != NULL)
	{
		pBlock->SetPosition(Pos);
		pBlock->SetSize(Size);
		pBlock->Init();
	}

	return pBlock;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNormalBlock::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CBlock::Init();

	BindTexture(m_apTexture[m_Type]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNormalBlock::Uninit(void)
{
	CBlock::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CNormalBlock::Update(void)
{
	m_PosOld = GetPosition();
	CBlock::Update();
	D3DXVECTOR3 pos = GetPosition();

	pos += m_Move;
	SetPosition(pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CNormalBlock::Draw(void)
{
	CBlock::Draw();
}