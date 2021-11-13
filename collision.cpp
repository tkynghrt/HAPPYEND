//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "ball.h"
#include "attack.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
int CheckHit(F_CIRCLE* pcrCircle, F_RECT_CIRCLE* prcRectCircle);
int InitShapes(D3DXVECTOR2 pos1, float r1, D3DXVECTOR2 pos2, float r2, D3DXVECTOR2 move);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

int space = 0;
F_CIRCLE crCircle; // �~�`�` 
F_RECT_CIRCLE rcRectCircle; // ��`�{�~�a 
//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
	PLAYER *player = GetPlayer();		// �v���C���[�̃|�C���^�[��������
	BALL *ball = GetBall();		// �o���b�g�̃|�C���^�[��������
	ATTACK *attack = GetAttack();
	if (space > 0)//�����蔻�肪�����Ă���΃J�E���g��i�ߏ����ċ��Ȃ���Ύ��s
	{
		space--;
	}
	else
	{
		if (ball->mode >= 1)
		{
			if (attack->mode == 1)
			{
				InitShapes(attack->pos, attack->h - 35, ball->pos, ball->h - 20, D3DXVECTOR2(-ball->move.x, -ball->move.y));//-35-20����������߂ɂ���

				if (CheckHit(&crCircle, &rcRectCircle))
				{
					int U = GetPlayer_U();
					if (player->power.x <= 200)
						player->power += player->power;
					if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_DOWN))
					{
						if (GetKeyboardPress(DIK_UP))
						{
							if (U == 2)
							{
								SetBall(2, attack->pos, D3DXVECTOR2(player->power.x / 2, -player->power.x / 2));
							}
							else
							{
								SetBall(2, attack->pos, D3DXVECTOR2(-player->power.x / 2, -player->power.x / 2));
							}
							space = 20;//20�t���[�������蔻�������
						}
						else
						{
							if (U == 2)
							{
								SetBall(2, attack->pos, D3DXVECTOR2(player->power.x / 2, player->power.x / 2));
							}
							else
							{
								SetBall(2, attack->pos, D3DXVECTOR2(-player->power.x / 2, player->power.x / 2));
							}
							space = 20;//20�t���[�������蔻�������
						}
					}
					else
					{
						if (U == 2)
						{
							SetBall(2, attack->pos, player->power);
						}
						else
						{
							SetBall(2, attack->pos, D3DXVECTOR2(player->power.x * -1, player->power.y));
						}
						space = 20;//20�t���[�������蔻�������
					}
				}
			}
		}

		if (ball->mode >= 1)
		{
			if (attack->mode == 2)
			{
				InitShapes(attack->pos, attack->h -35, ball->pos, ball->h -20, D3DXVECTOR2 (-ball->move.x, -ball->move.y));//-35-20����������߂ɂ���

				if (CheckHit(&crCircle,  &rcRectCircle))
				{
					int U = GetPlayer_U();
					if (U == 2)
					{
						SetBall(1, attack->pos, D3DXVECTOR2(0, -15));
					}
					else
					{
						SetBall(1, attack->pos, D3DXVECTOR2(0, -15));
					}
					space = 20; // 20�t���[�������蔻�������
				}
			}
		}
		// �����ƓG�̒e(BC)

		// ���S�������ԑJ��
	}
}

//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X���̔���
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y���̔���
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//�S�Ă̏�����TRUE�Ȃ�q�b�g����
			return true;
		}
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistance�̃x�N�g�����𓾂�
	float length;
//	length = D3DXVec2Length(&vDistance);
	length = D3DXVec2LengthSq(&vDistance);

//	float size = size1 + size2;
	float size = (size1 + size2) * (size1 + size2);

	//1��2�̔��a�𑫂��Ĕ��肷��
	//�����̃x�N�g�����̕������������
	//�q�b�g���Ă���
	if (length < size)
	{
		return true;
	}

	return false;
}


//------------------------------------------------------------ 
// �~�Ɛ����� Collision ���� 
//------------------------------------------------------------ 


int InitShapes(D3DXVECTOR2 pos1, float r1, D3DXVECTOR2 pos2, float r2, D3DXVECTOR2 move) // �ŏ��ɂP�񂾂��Ă΂�� 
{
	crCircle.x = pos1.x; crCircle.y = pos1.y;
	crCircle.r = r1;
	rcRectCircle.x = pos2.x; rcRectCircle.y = pos2.y;
	rcRectCircle.vx = move.x; rcRectCircle.vy = move.y;
	rcRectCircle.r = r2;
	return 0;
}
int CheckHit(F_CIRCLE* pcrCircle, F_RECT_CIRCLE* prcRectCircle) // Collision �`�F�b�N 
{
	int nResult = false;
	float dx, dy; // �ʒu�̍��� 
	float t;
	float mx, my; // �ŏ��̋�����^������W 
	float ar; // 2 ���a�𑫂������� 
	float fDistSqr;
	dx = pcrCircle->x - prcRectCircle->x; // ���� 
	dy = pcrCircle->y - prcRectCircle->y; // ���� 
	t = (prcRectCircle->vx * dx + prcRectCircle->vy * dy) / (prcRectCircle->vx * prcRectCircle->vx + prcRectCircle->vy * prcRectCircle->vy);
	if (t < 0.0f) t = 0.0f; // t �̉��� 
	if (t > 1.0f) t = 1.0f; // t �̏�� 
	mx = prcRectCircle->vx * t + prcRectCircle->x; // �ŏ��ʒu��^������W 
	my = prcRectCircle->vy * t + prcRectCircle->y;
	fDistSqr = (mx - pcrCircle->x) * (mx - pcrCircle->x) +
		(my - pcrCircle->y) * (my - pcrCircle->y); // �����̂Q�� 
	ar = pcrCircle->r + prcRectCircle->r;
	if (fDistSqr < ar * ar) { // �Q��̂܂ܔ�r 
		nResult = true;
	}
	return nResult;
}