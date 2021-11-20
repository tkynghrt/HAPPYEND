//=============================================================================
//
// �U������ [Attack.cpp]
// Author : 
//
//=============================================================================
#include "Attack.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static ATTACK g_Attack;							// �o���b�g�\����
int count;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitAttack(void)
{
	int texNo = LoadTexture("data/TEXTURE/explosion.png");
	int texNo2 = LoadTexture("data/TEXTURE/explosion02.png");

	// �o���b�g�\���̂̏�����

	g_Attack.mode = 0;
	g_Attack.w = 50.0f;
	g_Attack.h = 50.0f;
	g_Attack.pos = D3DXVECTOR2(300, 300.0f);
	g_Attack.rot = 0.0f;
	g_Attack.texNo = texNo;
	g_Attack.texNo2 = texNo2;
	g_Attack.move = D3DXVECTOR2(0.0f, 0.0f);	// �ړ��ʂ�������
	g_Attack.flame = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitAttack(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateAttack(void)
{
	switch (g_Attack.mode)
	{
	case 0:
		break;
	case 1:
		count++;
		if (count >= 1)
		{
			if (g_Attack.flame >= 16)
			{
				g_Attack.mode = 0;
				g_Attack.flame = 0;
			}
			g_Attack.flame += 1;
			count = 0;
		}
		break;
	case 2:
		count++;
		if (count >= 1)
		{
			if (g_Attack.flame >= 16)
			{
				g_Attack.mode = 0;
				g_Attack.flame = 0;
			}
			g_Attack.flame += 1;
			count = 0;
		}
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawAttack(void)
{

	if (g_Attack.mode >= 1)
	{
		//�{�[���̈ʒu��e�N�X�`���[���W�𔽉f
		float px = g_Attack.pos.x;	// �{�[���̕\���ʒuX
		float py = g_Attack.pos.y;	// �{�[���̕\���ʒuY
		float pw = g_Attack.w;		// �{�[���̕\����
		float ph = g_Attack.h;		// �{�[���̕\������
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (g_Attack.mode)
		{
		case 0:
			break;
		case 1:


			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			DrawSpriteColorRotate(g_Attack.texNo, px, py, pw, ph,
				g_Attack.flame % 4 * 0.25, g_Attack.flame / 4 * 0.25,
				0.25f, 0.25f, col, g_Attack.rot);
			break;
		case 2:

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			DrawSpriteColorRotate(g_Attack.texNo2, px, py, pw, ph,
				g_Attack.flame % 4 * 0.25, g_Attack.flame / 4 * 0.25,
				0.25f, 0.25f, col, g_Attack.rot);
			break;
		}
	}
}


//=============================================================================
// �{�[���\���̂̐擪�A�h���X���擾
//=============================================================================
ATTACK* GetAttack(void)
{
	return &g_Attack;
}


//=============================================================================
// �{�[���̔��ːݒ�
//=============================================================================
void SetAttack(int mode, D3DXVECTOR2 pos)
{
	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )

	g_Attack.mode = mode;			// �g�p��Ԃ֕ύX����
	g_Attack.pos = pos;			// ���W���Z�b�g
	g_Attack.flame = 6;
	return;							// 1���Z�b�g�����̂ŏI������
}