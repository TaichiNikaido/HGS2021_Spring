//=============================================================================
//
// �u���b�N�̏��� [block.cpp]
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
#include "player_3d.h"
#include "mode_game.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBlock::m_apTexture[1] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBlock::CBlock(int nPriority)
{
	m_nPatternAnim = 2;
	m_nCountAnim = 0;
	m_nBreakIces = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBlock::~CBlock()
{

}
//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CBlock::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK, &m_apTexture[0]);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CBlock::Unload(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CBlock::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CPolygon3d::Init();

	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//������ݒ�
	SetRotation(D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));

	BindTexture(m_apTexture[0]);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBlock::Uninit(void)
{
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBlock::Update(void)
{
	CPolygon3d::Update();
	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);
	Collision();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBlock::Draw(void)
{
	CPolygon3d::Draw();
}

CBlock::IS_COLLISION CBlock::Collision(void)
{
	IS_COLLISION bCollision;

	D3DXVECTOR3 Move;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	D3DXVECTOR3 PosOld;
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	bool bIsTop = false;
	bool bIsBottom = false;
	bool bIsRight = false;
	bool bIsLeft = false;
	bool bIsFront = false;
	bool bIsBack = false;
	if (pPlayer != nullptr)
	{
		Pos = pPlayer->GetPosition();
		Size = pPlayer->GetSize();
		PosOld = pPlayer->GetPositionOld();
		Move = pPlayer->GetMove();
		bCollision.bIsTop = pPlayer->GetIsCollision().bIsTop;
		bCollision.bIsBottom = pPlayer->GetIsCollision().bIsBottom;
		bCollision.bIsRight = pPlayer->GetIsCollision().bIsRight;
		bCollision.bIsLeft = pPlayer->GetIsCollision().bIsLeft;
		bCollision.bIsFront = pPlayer->GetIsCollision().bIsFront;
		bCollision.bIsBack = pPlayer->GetIsCollision().bIsBack;


		D3DXVECTOR3 box1Max = D3DXVECTOR3(Size.x / 2, Size.y / 2, Size.z / 2) + Pos;
		D3DXVECTOR3 box1Min = D3DXVECTOR3(-Size.x / 2, -Size.y / 2, -Size.z / 2) + Pos;
		D3DXVECTOR3 box2Max = D3DXVECTOR3((GetSize().x / 2), (GetSize().y / 2), (GetSize().z / 2)) + GetPosition();
		D3DXVECTOR3 box2Min = D3DXVECTOR3((-GetSize().x / 2), (-GetSize().y / 2), (-GetSize().z / 2)) + GetPosition();

		if (
			box1Max.y > box2Min.y && //�c��
			box1Min.y < box2Max.y && //�c��
			box1Max.x > box2Min.x && //����
			box1Min.x < box2Max.x //���E
			)
		{
			if (box1Max.y > box2Min.y && PosOld.y <= box2Min.y)//�c��
			{
				Pos.y = box2Min.y - Size.y / 2;
				Move.y = 0.0f;
				bCollision.bIsTop = true;
			}

			else if (box1Min.y < box2Max.y && PosOld.y >= box2Max.y)//�c��
			{
				Pos.y = box2Max.y + Size.y / 2;
				Move.y = 0.0f;
				bCollision.bIsBottom = true;
			}

			else if (box1Max.x > box2Min.x && PosOld.x <= box2Min.x)//�E����
			{
				Pos.x = box2Min.x - Size.x / 2;
				Move.x = 0.0f;
				bCollision.bIsRight = true;
			}

			else if (box1Min.x < box2Max.x && PosOld.x >= box2Max.x)//������
			{
				Pos.x = box2Max.x + Size.x / 2;
 				Move.x = 0.0f;
				bCollision.bIsLeft = true;
			}
		}
	}
	////�O��ʒu����ς���Ă����瓖�����Ă���ʂ̔��������
	//if (fabsf(PosOld.x) >= 0.0f ||
	//	fabsf(PosOld.y) >= 0.0f )
	//{
	//	if (bIsTop == false)
	//	{
	//		bCollision.bIsTop = false;
	//	}
	//	else
	//	{
	//		bCollision.bIsTop = true;
	//	}
	//	if (bIsBottom == false)
	//	{
	//		bCollision.bIsBottom = false;
	//	}
	//	else
	//	{
	//		bCollision.bIsBottom = true;
	//	}
	//	if (bIsRight == false)
	//	{
	//		bCollision.bIsRight = false;
	//	}
	//	else
	//	{
	//		bCollision.bIsRight = true;
	//	}
	//	if (bIsLeft == false)
	//	{
	//		bCollision.bIsLeft = false;
	//	}
	//	else
	//	{
	//		bCollision.bIsLeft = true;
	//	}
	//	if (bIsFront == false)
	//	{
	//		bCollision.bIsFront = false;
	//	}
	//	else
	//	{
	//		bCollision.bIsFront = true;
	//	}
	//	if (bIsBack == false)
	//	{
	//		bCollision.bIsBack = false;
	//	}
	//	else
	//	{
	//		bCollision.bIsBack = true;
	//	}
	//}

	pPlayer->SetMove(Move);
	pPlayer->SetIsCollision(bCollision);
	pPlayer->SetPosition(Pos);
	return bCollision;
}