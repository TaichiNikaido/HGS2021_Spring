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
	SetRotation(D3DXVECTOR3(D3DXToRadian(180.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)));
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBlock::Uninit(void)
{
	CScene3d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBlock::Update(void)
{
	CScene3d::Update();
	//�e�N�X�`���Z�b�g
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);
	/*Collisaon();*/
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBlock::Draw(void)
{
	CScene3d::Draw();
}

CBlock::IS_COLLISION CBlock::Collision(void)
{
	IS_COLLISION bCollision;

	D3DXVECTOR3 Move;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	D3DXVECTOR3 PosOld;
	CPlayer3d * pPlayer = CGameMode::GetPlayer3d();
	if (pPlayer != nullptr)
	{
		Pos = pPlayer->GetPosition();
		Size = pPlayer->GetSize();
		Size = pPlayer->GetSize();
		PosOld = pPlayer->GetPositionOld();
		/*bCollision.bIsTop = pCharactor->GetIsCollision().bIsTop;
		bCollision.bIsBottom = pCharactor->GetIsCollision().bIsBottom;
		bCollision.bIsRight = pCharactor->GetIsCollision().bIsRight;
		bCollision.bIsLeft = pCharactor->GetIsCollision().bIsLeft;
		bCollision.bIsFront = pCharactor->GetIsCollision().bIsFront;
		bCollision.bIsBack = pCharactor->GetIsCollision().bIsBack;*/
		bool bIsTop = false;
		bool bIsBottom = false;
		bool bIsRight = false;
		bool bIsLeft = false;
		bool bIsFront = false;
		bool bIsBack = false;

		D3DXVECTOR3 box1Max = D3DXVECTOR3(Size.x / 2, Size.y / 2, Size.z / 2) + Pos;
		D3DXVECTOR3 box1Min = D3DXVECTOR3(-Size.x / 2, -Size.y / 2, -Size.z / 2) + Pos;
		D3DXVECTOR3 box2Max = D3DXVECTOR3((GetSize().x / 2), (GetSize().y / 2), (GetSize().z / 2));
		D3DXVECTOR3 box2Min = D3DXVECTOR3((-GetSize().x / 2), (-GetSize().y / 2), (-GetSize().z / 2));

		if (
			box1Max.y >= box2Min.y && //�c��
			box1Min.y <= box2Max.y && //�c��
			box1Max.x >= box2Min.x && //����
			box1Min.x <= box2Max.x //���E
			)
		{
			if (box1Max.y >= box2Min.y && PosOld.y <= box2Min.y)//�c��
			{
				Pos.y = box2Min.y - Size.y / 2;
				bIsBottom = true;
			}

			else if (box1Min.y <= box2Max.y && PosOld.y >= box2Max.y)//�c��
			{
				Pos.y = box2Max.y + Size.y / 2;
				bIsTop = true;
			}

			else if (box1Max.x >= box2Min.x && PosOld.x <= box2Min.x)//�E����
			{
				Pos.x = box2Min.x - Size.x / 2;
				bIsRight = true;
			}

			else if (box1Min.x <= box2Max.x && PosOld.x >= box2Max.x)//������
			{
				Pos.x = box2Max.x + Size.x / 2;
				bIsLeft = true;
			}
		}
	}

	pPlayer->SetPosition(Pos);
	return bCollision;
}