//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "fade.h"
#include "All_Gimmick.h"
#include "player.h"
#include "ball.h"
#include "attack.h"
#include "input.h"
#include "count_block.h"
#include "move_block.h"
#include "accele_block.h"
#include "Target_Count.h"
#include "Target_Normal.h"
#include "coin.h"

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
static ACCELE_BLOCK* accele_block = GetAcceleBlock();
static COIN* coin = GetCoin();
static PLAYER* player = GetPlayer();
static TARGET_NORMAL* TargetNormal = GetTarget_Normal();
static TARGET_COUNT* TargetCount = GetTarget_Count();


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
F_OLD_SURFACE CollisionKOBA(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
							D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size);
int CheckHit(F_CIRCLE* pcrCircle, F_RECT_CIRCLE* prcRectCircle);
int InitShapes(D3DXVECTOR2 pos1, float r1, D3DXVECTOR2 pos2, float r2, D3DXVECTOR2 move);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int NoFlame = 0;	//�����蔻����Z�t���[������
F_CIRCLE crCircle; // �~�`�` 
F_RECT_CIRCLE rcRectCircle; // ��`�{�~�a 





//=============================================================================
// �����蔻�菈��
//=============================================================================

void UpdateCollision(void)
{
	bool player_fly = true;			//�v���C���[���󒆂ɂ��邩
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


					if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_DOWN))
					{
						if (GetKeyboardTrigger(DIK_UP))
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
	}


	//�ʂƃ^�[�Q�b�g�Ƃ̓����蔻��
	if (TargetNormal->use == true)
	{
		if (CollisionBB(ball->pos, TargetNormal->pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(TargetNormal->size.x, TargetNormal->size.y)))
		{
			TargetNormal->use = false;
			ball->move.x *= -1;
			ball->move.y *= -1;
			TargetNormal->use = true;
		}
	}

	if (TargetCount->use == true)
	{
		if (CollisionBB(ball->pos, TargetCount->pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(TargetCount->size.x, TargetCount->size.y)))
		{
			ball->move.x *= -1;
			ball->move.y *= -1;
			if (TargetCount->Count >= 1)
			{
				TargetCount->Count--;
			}
			else
			{
				TargetCount->use = false;
				SceneTransition(SCENE::SCENE_RESULT);
			}

		}
	}

		

	//�����u���b�N�� 
	//�v���C���[�Ɠ����u���b�N�̓����蔻��
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		if (move_block[i].Use)
		{
			if (CollisionKOBA(player->pos, move_block[i].pos, player->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y)) == F_OLD_SURFACE::up)
			{
				player->pos.y = move_block[i].pos.y - ((player->size.y / 2) + (move_block[i].size.y / 2));
				player->pos.x += move_block[i].velocity.x;
				player_fly = false;
			}
			else if (CollisionKOBA(player->pos, move_block[i].pos, player->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y)) == F_OLD_SURFACE::left)
			{
				player->pos.x = move_block[i].pos.x - ((player->size.x / 2) + (move_block[i].size.x / 2));
			}
			else if (CollisionKOBA(player->pos, move_block[i].pos, player->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y)) == F_OLD_SURFACE::right)
			{
				player->pos.x = move_block[i].pos.x + ((player->size.x / 2) + (move_block[i].size.x / 2));
			}
			else if (CollisionKOBA(player->pos, move_block[i].pos, player->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y)) == F_OLD_SURFACE::down)
			{
				player->pos.y = move_block[i].pos.y + ((player->size.y / 2) + (move_block[i].size.y / 2));
				player->move.y = 0.0f;
			}
		}
	}
	//�o�O�N���Ă܂�
	//�{�[���Ɠ����u���b�N�̓����蔻��
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		if (move_block[i].Use)
		{
			if (CollisionKOBA2(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y), move_block[i].velocity) == F_OLD_SURFACE::up)
			{
				ball->move.y *= -1;
			}
			else if (CollisionKOBA2(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y), move_block[i].velocity) == F_OLD_SURFACE::left)
			{
				
				ball->move.x *= -1;
			}
			else if (CollisionKOBA2(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y), move_block[i].velocity) == F_OLD_SURFACE::right)
			{
				
				ball->move.x *= -1;
			}
			else if (CollisionKOBA2(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y), move_block[i].velocity) == F_OLD_SURFACE::down)
			{
				ball->pos.y = move_block[i].pos.y + ((ball->size.y / 2) + (move_block[i].size.y / 2));
				
				ball->move.y *= -1;
			}
		}
	}





	//�񐔂ŉ���u���b�N��
	//�v���C���[�Ɖ񐔂ŉ���u���b�N�̓����蔻��
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if (count_block[i].Use)
		{
			if (CollisionKOBA(player->pos, count_block[i].pos, player->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::up)
			{
          				player->pos.y = count_block[i].pos.y - ((player->size.y / 2) + (count_block[i].size.y / 2));
						player_fly = false;
			}
			else if (CollisionKOBA(player->pos, count_block[i].pos, player->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::left)
			{
 				player->pos.x = count_block[i].pos.x - ((player->size.x / 2) + (count_block[i].size.x / 2));
			}
			else if (CollisionKOBA(player->pos, count_block[i].pos, player->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::right)
			{
				player->pos.x = count_block[i].pos.x + ((player->size.x / 2) + (count_block[i].size.x / 2));
			}
			else if (CollisionKOBA(player->pos, count_block[i].pos, player->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::down)
			{
				player->pos.y = count_block[i].pos.y - ((player->size.y / 2) + (count_block[i].size.y / 2));
				player->move.y = 0.0f;
			}
		}
	}
	//�{�[���Ɖ񐔂ŉ���u���b�N�̓����蔻��
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if (count_block[i].Use)
		{
			if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::up)
			{
				ball->move.y *= -1;
				if (count_block[i].HitCount <= 0)
				{
					count_block[i].Use = false;
				}
				count_block[i].HitCount--;
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::left)
			{
				ball->move.x *= -1;
				if (count_block[i].HitCount <= 0)
				{
					count_block[i].Use = false;
				}
				count_block[i].HitCount--;
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::right)
			{
				ball->move.x *= -1;
				if (count_block[i].HitCount <= 0)
				{
					count_block[i].Use = false;
				}
				count_block[i].HitCount--;
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::down)
			{
				ball->move.y *= -1;
				if (count_block[i].HitCount <= 0)
				{
					count_block[i].Use = false;
				}
				count_block[i].HitCount--;
			}
		}
	}


	//�X�s�[�h���x���ŉ���u���b�N��
	//�v���C���[�ƃX�s�[�h���x���ŉ���u���b�N�̓����蔻��
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		if (accele_block[i].Use)
		{
			if (CollisionKOBA(player->pos, accele_block[i].pos, player->old_pos, accele_block[i].pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::up)
			{
				player->pos.y = accele_block[i].pos.y - ((player->size.y / 2) + (accele_block[i].size.y / 2));
				player_fly = false;
			}
			else if ((CollisionKOBA(player->pos, accele_block[i].pos, player->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::left))
			{
				player->pos.x = accele_block[i].pos.x - ((player->size.x / 2) + (accele_block[i].size.x / 2));
			}
			else if ((CollisionKOBA(player->pos, accele_block[i].pos, player->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::right))
			{
				player->pos.x = accele_block[i].pos.x + ((player->size.x / 2) + (accele_block[i].size.x / 2));
			}
			else if ((CollisionKOBA(player->pos, accele_block[i].pos, player->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::down))
			{
				player->pos.y = accele_block[i].pos.y - ((player->size.y / 2) + (accele_block[i].size.y / 2));
				player->move.y = 0.0f;
			}
		}
	}
	//�{�[���ƃX�s�[�h���x���ŉ���u���b�N�̓����蔻��
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		if (accele_block[i].Use)
		{
			if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::up)
			{
				ball->move.y *= -1;
				if (accele_block[i].level == ball->Speed_Level)
				{
					accele_block[i].Use = false;
				}
			}
			else if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::left)
			{
				ball->move.x *= -1;
				if (accele_block[i].level == ball->Speed_Level)
				{
					accele_block[i].Use = false;
				}
			}
			else if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::right)
			{
				ball->move.x *= -1;
				if (accele_block[i].level == ball->Speed_Level)
				{
					accele_block[i].Use = false;
				}
			}
			else if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::down)
			{
				ball->move.y *= -1;
				if (accele_block[i].level == ball->Speed_Level)
				{
					accele_block[i].Use = false;
				}
			}
		}
	}


	//�R�C����
	for (int i = 0; i < MAX_COIN; i++)
	{
		if (coin[i].Use)
		{
			//�{�[��������������
			if (CollisionBB(ball->pos, coin[i].pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(coin[i].size.x, coin[i].size.y)))
			{
				coin[i].Use = false;
			}
		}
	}


	//���̓����蔻��
	switch (CollisionKOBA(player->pos, ground->pos, player->old_pos, ground->pos,
		D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(ground->size.x, ground->size.y)))
		{
		case F_OLD_SURFACE::no_hit:
			break;

		case F_OLD_SURFACE::up:
			player->pos.y = ground->pos.y - ((player->size.y / 2) + (ground->size.y / 2));
			player_fly = false;
			break;

		case F_OLD_SURFACE::left:
			player->pos.x = ground->pos.x - ((player->size.x / 2) + (ground->size.x / 2));
			break;

		case F_OLD_SURFACE::right:
			player->pos.x = ground->pos.x + ((player->size.x / 2) + (ground->size.x / 2));
			break;

		case F_OLD_SURFACE::down:
			//player->pos.y = count_block[0].pos.y - ((player->size.y / 2) + (count_block[0].size.y / 2));
			break;
		}
	
	player->fly = player_fly;
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


//=============================================================================
// BB�ɂ��1�t���[���̈ʒu���Q�Ƃ��������蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���ʂ�Ԃ�
//=============================================================================
F_OLD_SURFACE CollisionKOBA(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
							D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size)
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

	//�v���C���[�̉��z�����x
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
			if (vertual_player_old_max.y <= block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::up;
			}
			//�v���C���[���u���b�N�̉����瓖�������Ƃ�
			if (vertual_player_old_min.y >= block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::down;
			}
			//�v���C���[���u���b�N�̍����瓖�������Ƃ�
			if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::left;
			}
			//�v���C���[���u���b�N�̉E���瓖�������Ƃ�
			if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::right;
			}

			//�v���C���[�̉����x�̉��z�p�x
			float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);
			

			//�v���C���[�̒��_����u���b�N�̒��_�����񂾒����̊p�x
			//�v���C���[���獶��
			float LeftDown_angle = atan2f((player_max.y - block_min.y), (player_min.x - block_max.x));
			//�v���C���[���獶��
			float LeftUp_angle = atan2f((player_min.y - block_max.y), (player_min.x - block_max.x));
			//�v���C���[����E��
			float RightDown_angle = atan2f((player_max.y - block_min.y), (player_max.x - block_min.x));
			//�v���C���[����E��
			float RightUp_angle = atan2f((player_min.y - block_max.y), (player_max.x - block_min.x));

			//�u���b�N����E��̔���
			if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
			{
      				if (vertual_velocity_angle > LeftDown_angle)
				{
					//��
					return F_OLD_SURFACE::up;
				}
				else
				{
					//�E
					return F_OLD_SURFACE::right;
				}
			}

			//�u���b�N����E���̔���
			if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
			{
				if (vertual_velocity_angle > LeftUp_angle)
				{
					//�E
					return F_OLD_SURFACE::right;
				}
				else
				{
					//��
					return F_OLD_SURFACE::down;
				}
			}

			//�u���b�N���獶��̔���
			if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
			{
				if (vertual_velocity_angle > RightDown_angle)
				{
					//��
					return F_OLD_SURFACE::left;
				}
				else
				{
					//��
					return F_OLD_SURFACE::up;
				}
			}

			//�u���b�N���獶���̔���
			if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
			{
				if (vertual_velocity_angle > RightUp_angle)
				{
					//��
					return F_OLD_SURFACE::down;
				}
				else
				{
					//��
					return F_OLD_SURFACE::left;
				}
			}
		}
	}
	return F_OLD_SURFACE::no_hit;
	//return F_OLD_SURFACE();
}

//=============================================================================
// BB�ɂ��1�t���[���̈ʒu���Q�Ƃ��������蔻�菈�����s�����ǂ����̏���
// �T�C�Y�͔��a
// �߂�l�F�������Ă��邩�A���Ȃ�����Ԃ�
//=============================================================================
F_OLD_SURFACE CollisionKOBA2(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos, D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size, D3DXVECTOR2 block_velocity)
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

	//�v���C���[�̉��z�����x
	D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (block_pos - block_old_pos);
	D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

	vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
	vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
	vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
	vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;

	//�u���b�N�̉����x�Ɖ��z�����x�̓��ςƒ���
	float InnerProduct = (vertual_player_velocity.x * block_velocity.x) + (vertual_player_velocity.y * block_velocity.y);
	float vertual_player_velocity_length = sqrtf((vertual_player_velocity.x * vertual_player_velocity.x) + (vertual_player_velocity.y * vertual_player_velocity.y));
	float block_velocity_length = sqrtf((block_velocity.x * block_velocity.x) + (block_velocity.y * block_velocity.y));
	//�u���b�N�̉����x�Ɖ��z�����x�̓��ς̊p�x
	float InnerProduct_angle = InnerProduct / (vertual_player_velocity_length * block_velocity_length);




	//X���̔���
	if (player_min.x < block_max.x && player_max.x > block_min.x)
	{
		//Y���̔���
		if (player_min.y < block_max.y && player_max.y > block_min.y)
		{
			//�v���C���[���u���b�N�̏ォ�瓖�������Ƃ�
			if (vertual_player_old_max.y <= block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				
					return F_OLD_SURFACE::up;
			}
			//�v���C���[���u���b�N�̉����瓖�������Ƃ�
			if (vertual_player_old_min.y >= block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::down;
			}
			//�v���C���[���u���b�N�̍����瓖�������Ƃ�
			if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::left;
			}
			//�v���C���[���u���b�N�̉E���瓖�������Ƃ�
			if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::right;
			}

			//�v���C���[�̉����x�̉��z�p�x
			float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);


			//�v���C���[�̒��_����u���b�N�̒��_�����񂾒����̊p�x
			//�v���C���[���獶��
			float LeftDown_angle = atan2f((player_max.y - block_min.y), (player_min.x - block_max.x));
			//�v���C���[���獶��
			float LeftUp_angle = atan2f((player_min.y - block_max.y), (player_min.x - block_max.x));
			//�v���C���[����E��
			float RightDown_angle = atan2f((player_max.y - block_min.y), (player_max.x - block_min.x));
			//�v���C���[����E��
			float RightUp_angle = atan2f((player_min.y - block_max.y), (player_max.x - block_min.x));

			//�u���b�N����E��̔���
			if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
			{
				if (InnerProduct_angle >= PI / 2)
				{
					if (vertual_velocity_angle > LeftDown_angle)
					{
						//��
						return F_OLD_SURFACE::up;
					}
					else
					{
						//�E
						return F_OLD_SURFACE::right;
					}
				}
				else
				{
					return F_OLD_SURFACE::no_hit;
				}
			}

			//�u���b�N����E���̔���
			if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
			{
				if (InnerProduct_angle <= -PI / 2)
				{
					if (vertual_velocity_angle > LeftUp_angle)
					{
						//�E
						return F_OLD_SURFACE::right;
					}
					else
					{
						//��
						return F_OLD_SURFACE::down;
					}
				}
				else
				{
					return F_OLD_SURFACE::no_hit;
				}
			}

			//�u���b�N���獶��̔���
			if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
			{
				if (InnerProduct_angle <= PI / 2)
				{
					if (vertual_velocity_angle > RightDown_angle)
					{
						//��
						return F_OLD_SURFACE::left;
					}
					else
					{
						//��
						return F_OLD_SURFACE::up;
					}
				}
				else
				{
					return F_OLD_SURFACE::no_hit;
				}
			}

			//�u���b�N���獶���̔���
			if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
			{
				if (InnerProduct_angle >= -PI / 2)
				{
					if (vertual_velocity_angle > RightUp_angle)
					{
						//��
						return F_OLD_SURFACE::down;
					}
					else
					{
						//��
						return F_OLD_SURFACE::left;
					}
				}
				else
				{
					return F_OLD_SURFACE::no_hit;
				}
			}
		}
	}
	return F_OLD_SURFACE::no_hit;
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