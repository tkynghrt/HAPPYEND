#include "Target_Normal.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
TARGET_NORMAL Normal[TARGET_MAX] = {};
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************




//=============================================================================
// ����������
//=============================================================================
void InitTarget_Normal(void)
{
	// ���ʂ̃^�[�Q�b�g�\���̂̏�����
	for (int i = 0; i < TARGET_MAX; i++)
	{
		Normal[i].Tex = LoadTexture("data/TEXTURE/Target.png");
		Normal[i].Bom = LoadTexture("data/TEXTURE/explosion.png");
		Normal[i].old_pos = Normal[i].pos;
		Normal[i].size.x = 70.0f;
		Normal[i].size.y = 70.0f;
		Normal[i].use = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitTarget_Normal(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTarget_Normal(void)
{
	

	for (int i = 0; i < TARGET_MAX; i++)
	{
		Normal[i].old_pos = Normal[i].pos;

		if (Normal[i].use == false)
		{
			if (Normal[i].normal_target_count >= 1)
			{
				Normal[i].normal_target_count++;
				if (Normal[i].flame >= 16)
				{
					Normal[i].flame = 0;
					Normal[i].normal_target_count = 0;
					return;
				}
				Normal[i].flame += 1;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTarget_Normal(void)
{
	D3DXCOLOR Target_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < TARGET_MAX; i++)
	{
		if (Normal[i].use)
		{
			DrawSpriteColorRotate(Normal[i].Tex,
				Normal[i].pos.x, Normal[i].pos.y,
				Normal[i].size.x, Normal[i].size.y,
				0.0f, 0.0f,
				1.0f, 1.0f,
				Target_col, Normal[i].rot);
		}
		else
		{
			DrawSpriteColorRotate(Normal[i].Bom,
				Normal[i].pos.x, Normal[i].pos.y,
				Normal[i].size.x, Normal[i].size.y,
				Normal[i].flame % 4 * 0.25, Normal[i].flame / 4 * 0.25,
				0.25f, 0.25f,
				Target_col, Normal[i].rot);
		}
	}
}

TARGET_NORMAL* GetTarget_Normal(void)
{
	for (int i = 0; i < TARGET_MAX; i++)
	{
		return &Normal[i];
	}
}

void SetTarget(D3DXVECTOR2 pos)
{
	for (int i = 0; i < TARGET_MAX; i++)
	{
		//�܂��\������Ă��Ȃ��ꏊ��T��
		if (!Normal[i].use)
		{
			Normal[i].pos = pos;
			Normal[i].use = true;
			break;
		}
	}
}