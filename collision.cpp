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
#include "count_block.h"
#include "move_block.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIMELEFT	2
#define BALLACCELE	(2.0f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
static MOVE_BLOCK* move_block = GetMoveBlock();
static COUNT_BLOCK* count_block = GetCountBlock();
static PLAYER* player = GetPlayer();


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
int NoFlame = 0;	//�����蔻����Z�t���[������
F_CIRCLE crCircle; // �~�`�` 
F_RECT_CIRCLE rcRectCircle; // ��`�{�~�a 
//////////////////////////////////////////////////////
int speed_number;
//=============================================================================
// �����蔻�菈��
//=============================================================================

void UpdateCollision(void)
{
	PLAYER *player = GetPlayer();		// �v���C���[�̃|�C���^�[��������
	BALL *ball = GetBall();		// �o���b�g�̃|�C���^�[��������
	ATTACK *attack = GetAttack();
	
	if (NoFlame > 0)//�����蔻�肪�����Ă���΃J�E���g��i�ߏ����ċ��Ȃ���Ύ��s
	{
		NoFlame--;
	}
	else
	{
		if (ball->mode >= 1)
		{
			if (attack->mode == 1)
			{
				InitShapes(attack->pos, attack->h - 35, ball->pos, ball->size.y - 20, D3DXVECTOR2(-ball->move.x, -ball->move.y));//-35-20����������߂ɂ���

				if (CheckHit(&crCircle, &rcRectCircle))
				{
					//�P�̌���
					int HimeDirection = GetPlayer_Direction();

					//���̉���
					if (player->power.x <= 200)
					{
						player->power += D3DXVECTOR2(BALLACCELE, 0.0f);

					}


					if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_DOWN))
					{
						if (GetKeyboardPress(DIK_UP))
						{
							if (HimeDirection == HIMELEFT)
							{
								SetBall(2, attack->pos, D3DXVECTOR2(player->power.x / 2, -player->power.x / 2));
							}
							else
							{
								SetBall(2, attack->pos, D3DXVECTOR2(-player->power.x / 2, -player->power.x / 2));
							}
							//20�t���[�������蔻�������
							NoFlame = 20;
						}
						else
						{
							if (HimeDirection == HIMELEFT)
							{
								SetBall(2, attack->pos, D3DXVECTOR2(player->power.x / 2, player->power.x / 2));
							}
							else
							{
								SetBall(2, attack->pos, D3DXVECTOR2(-player->power.x / 2, player->power.x / 2));
							}
							//20�t���[�������蔻�������
							NoFlame = 20;
						}
					}
					else
					{
						if (HimeDirection == HIMELEFT)
						{
							SetBall(2, attack->pos, player->power);
						}
						else
						{
							SetBall(2, attack->pos, D3DXVECTOR2(player->power.x * -1, player->power.y));
						}
						NoFlame = 20;//20�t���[�������蔻�������
					}
				}
			}
		}

		if (ball->mode >= 1)
		{
			if (attack->mode == 2)
			{
				InitShapes(attack->pos, attack->h - 35, ball->pos, ball->size.y - 20, D3DXVECTOR2(-ball->move.x, -ball->move.y));//-35-20����������߂ɂ���

				if (CheckHit(&crCircle, &rcRectCircle))
				{
					int HimeDirection = GetPlayer_Direction();
					if (HimeDirection == HIMELEFT)
					{
						SetBall(1, attack->pos, D3DXVECTOR2(0, -15));
					}
					else
					{
						SetBall(1, attack->pos, D3DXVECTOR2(0, -15));
					}
					NoFlame = 20; // 20�t���[�������蔻�������
				}
			}
		}
		// �����ƓG�̒e(BC)

		// ���S�������ԑJ��

		
		
		//�ړ�����u���b�N�ƃv���C���[�̓����蔻��
		
		//for (int i = 0; i < MAX_MOVEBLOCK; i++)
		//{
			
		//}

			//�v���C���[�Ɠ����u���b�N�̓����蔻��
		if (CollisionBB(player->pos, move_block[0].pos, D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(move_block[0].size.x, move_block[0].size.y)))
		{
			//�v���C���[���u���b�N�̏�ɂ���Ƃ�
			
			if (player->pos.y + (player->size.y / 2) > move_block[0].pos.y - (move_block[0].size.y / 2))
			{
				player->pos.y = move_block[0].pos.y - ((player->size.y / 2) + (move_block[0].size.y / 2));
				player->pos.x += move_block[0].velocity.x * 2;


				//player->player_doingjump = false;
				//moveblock[0].RidingPlayer = true;
			}
			//�v���C���[���u���b�N�̉��ɂԂ������Ƃ�
			if (player->pos.y - (player->size.y / 2) < move_block[0].pos.y + (move_block[0].size.y / 2))
			{
				player->move.y = 0.0f;

				//player->player_doingjump = false;
				//moveblock[0].RidingPlayer = true;
			}

			//�v���C���[�̍��ɓ��������ꍇ
			if (ball->pos.x + (ball->size.x / 2) > move_block[0].pos.x - (move_block[0].size.x / 2))
			{
				ball->move.x *= -1;
			}

			//�v���C���[�̉E�ɓ��������ꍇ
			if (ball->pos.x - (ball->size.x / 2) > move_block[0].pos.x + (move_block[0].size.x / 2))
			{
				ball->move.x *= -1;
			}
		}

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



F_OLD_SURFACE CollisionKOBA(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos, D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size)
{
	
	D3DXVECTOR2 player_min, player_max;
	D3DXVECTOR2 block_min, block_max;
	D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
	


	player_min.x = player_pos.x - player_size.x / 2;
	player_min.y = player_pos.y - player_size.y / 2;
	player_max.x = player_pos.x + player_size.x / 2;
	player_max.y = player_pos.y + player_size.y / 2;

	block_min.x = block_pos.x - block_size.x / 2;
	block_min.y = block_pos.y - block_size.y / 2;
	block_max.x = block_pos.x + block_size.x / 2;
	block_max.y = block_pos.y + block_size.y / 2;

	D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (block_pos - block_old_pos);
	D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

	vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
	vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
	vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
	vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;
	
	
	
	//X���̔���
	if (player_min.x < block_max.x && player_max.x > block_min.x)
	{
		//Y���̔���
		if (player_min.y < block_max.y && player_max.y > block_min.y)
		{
			//�v���C���[���u���b�N�̏ォ�瓖�������Ƃ�
			if (vertual_player_old_max.y < block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return up;
			}
			//�v���C���[���u���b�N�̉����瓖�������Ƃ�
			if (vertual_player_old_min.y > block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return down;
			}
			//�v���C���[���u���b�N�̍����瓖�������Ƃ�
			if (vertual_player_old_max.x < block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return left;
			}
			//�v���C���[���u���b�N�̉E���瓖�������Ƃ�
			if (vertual_player_old_min.x > block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return right;
			}

			float vertual_velocity_angle = atan2(vertual_player_velocity.y, vertual_player_velocity.x);


			
		}
	}
	return no_hit;
	//return F_OLD_SURFACE();
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