//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static BULLET g_Bullet;							// �o���b�g�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(void)
{
	int texNo = LoadTexture("data/TEXTURE/tako.png");
	int texNo2 = LoadTexture("data/TEXTURE/kage.png");
	// �o���b�g�\���̂̏�����
	
		g_Bullet.mode   = 1;
		g_Bullet.w     = 40.0f;
		g_Bullet.h     = 40.0f;
		g_Bullet.pos   = D3DXVECTOR2(300, 300.0f);
		g_Bullet.rot   = 0.0f;
		g_Bullet.texNo = texNo;
		g_Bullet.texNo2 = texNo2;
		g_Bullet.move = D3DXVECTOR2(0.0f, 0.0f);	// �ړ��ʂ�������
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	// ��]������
	//g_Bullet.rot += 0.5f;
	
	switch(g_Bullet.mode)
	{
	case 0:
		break;
	case 1:
		g_Bullet.move.y += 0.5f;

		break;
	case 2:
		if (g_Bullet.move.x >= 50 || -50 > g_Bullet.move.x)
		{}
		else
		{
			g_Bullet.move.y += 0.5f;
		}
		break;
				
	}
	//�ʒu�X�V
	g_Bullet.pos += g_Bullet.move;
	// ��ʊO�܂Ői�񂾁H
	if (g_Bullet.pos.y < 70) {
		g_Bullet.pos.y = 70;
		g_Bullet.move.y *= -1;
	}
	if (g_Bullet.pos.x > 960) {
		g_Bullet.pos.x = 960;
		g_Bullet.move.x *= -1;
	}
	if (g_Bullet.pos.x < 0) {
		g_Bullet.pos.x = 0;
		g_Bullet.move.x *= -1;
	}
	if (g_Bullet.pos.y > 500) {
		g_Bullet.pos.y = 500;
		g_Bullet.move.y *= -1;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
		if (g_Bullet.mode >= 1)	// ���̃o���b�g���g���Ă���H
		{								// Yes
			//�o���b�g�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Bullet.pos.x;	// �o���b�g�̕\���ʒuX
			float py = g_Bullet.pos.y;	// �o���b�g�̕\���ʒuY
			float pw = g_Bullet.w;		// �o���b�g�̕\����
			float ph = g_Bullet.h;		// �o���b�g�̕\������
			float mx = g_Bullet.move.x;	// �o���b�g�̈ړ���XY
			float my = g_Bullet.move.y;
			float pr = g_Bullet.rot;	//�p�x
			float b = 3;				//�e���������΂��{��
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			switch (g_Bullet.mode)
			{
			case 0:
				break;
			case 1:
				DrawSpriteColorRotate(g_Bullet.texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				
				break;
			case 2:


				if (g_Bullet.move.x >= 50 || -50 > g_Bullet.move.x)
				{
					if (g_Bullet.move.y >= 50 || -50 > g_Bullet.move.y)
					{
						if (g_Bullet.move.x > 0) 
						{
							b = b * 1.4;
							if (g_Bullet.move.y > 0)
							{
								pr = 0.77;
							}
							if (g_Bullet.move.y < 0)
							{
								pr = -0.77;
							}
						}
						else
						{
							b = b * 1.4;
							if (g_Bullet.move.y > 0)
							{
								pr = -0.77;
							}
							if (g_Bullet.move.y < 0)
							{
								pr = 0.77;
							}
						}
					}
						if (g_Bullet.move.x < 0) {
							DrawSpriteColorRotate(g_Bullet.texNo2, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * -b, 40.0f,
								0.0f, 0.0f, 1.0f, 0.4f, col,
								pr);
						}
						else
						{
							DrawSpriteColorRotate(g_Bullet.texNo2, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * b, 40.0f,
								0.0f, 0.6f, 1.0f, 0.3f, col,
								pr);
						}
					
				}
				DrawSpriteColorRotate(g_Bullet.texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				break;
			}
		}

}


//=============================================================================
// �o���b�g�\���̂̐擪�A�h���X���擾
//=============================================================================
BULLET* GetBullet(void)
{
	return &g_Bullet;
}


//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBullet(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power)
{
	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	
			g_Bullet.mode = mode;			// �g�p��Ԃ֕ύX����
			g_Bullet.pos = pos;			// ���W���Z�b�g
			g_Bullet.move = power;			//���x�����
			return;							// 1���Z�b�g�����̂ŏI������
}

