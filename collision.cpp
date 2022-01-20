//=============================================================================
// �����蔻�菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "math.h"
#include "collision.h"
#include "time.h"
#include "fade.h"
#include "player.h"
#include "ball.h"
#include "input.h"
#include "count_block.h"
#include "move_block.h"
#include "accele_block.h"
#include "block.h"
#include "Target_Count.h"
#include "Target_Normal.h"
#include "ground.h"
#include "coin.h"
#include "SpeedPanel.h"
#include "warp.h"
#include "ramdom_shot_block.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BALLACCELE	(2.0f)


#define KOBA4_MAX  4
//�u���b�N�̎�ނ̔ԍ�
#define MOVE_BLOCK_NUM 1
#define COUNT_BLOCK_NUM 2
#define ACCELE_BLOCK_NUM 3
#define RAMDOM_SHOT_BLOCK_NUM 4
#define BLOCK_NUM 5
#define GROUND_NUM 6
#define WARP_NUM 7
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
static MOVE_BLOCK* move_block = GetMoveBlock();
static BLOCK* block = GetBlock();
static COUNT_BLOCK* count_block = GetCountBlock();
static ACCELE_BLOCK* accele_block = GetAcceleBlock();
static GROUND* ground = GetGround();
static COIN* coin = GetCoin();
static PLAYER* player = GetPlayer();
static TARGET_NORMAL* TargetNormal = GetTarget_Normal();
static TARGET_COUNT* TargetCount = GetTarget_Count();
static SPEED_PANEL* pSpeedPanel = GetSpeedPanel();
static BALL* ball = GetBall();
static WARP* pwarp = GetWarp();
static RAMDOM_SHOT_BLOCK* pRamdom_Shot_Block = GetRamdom_Shot_Block();

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
F_OLD_SURFACE CollisionKOBA(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
							D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size);

D3DXVECTOR2 CollisionKOBA3(D3DXVECTOR2 player_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 player_old_pos,
	D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity);

///*int*/PLAYER_BALL_RANGE CheckHit(F_CIRCLE* pcrCircle, F_RECT_CIRCLE* prcRectCircle);
//int InitShapes(D3DXVECTOR2 pos1, float r1, D3DXVECTOR2 pos2, float r2, D3DXVECTOR2 move);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int NoFlame = 0;	//�����蔻����Z�t���[������

//CollisionKOBA3�ŕԂ��Ă�����
static D3DXVECTOR2 koba3_pos = {};
//CollisionKOBA4�ŕԂ��Ă�����
static float koba4_up = {};
static float koba4_down = {};
static float koba4_left = {};
static float koba4_right = {};

static KOBA4 koba4[KOBA4_MAX];
static int koba4_count;


//���˕Ԃ�p�x
static float	reflect;	
//�}�E�X�̍��W�i�}�E�X���삷�鎞�Ɏg���j
D3DXVECTOR2 mouse_pos = D3DXVECTOR2((float)GetMouseX(), (float)GetMouseY());
D3DXVECTOR2 old_mouse_pos = mouse_pos;
float mouse_reflect;



//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
	srand((unsigned int)time(NULL));
	bool player_fly = true;			//�v���C���[���󒆂ɂ��邩
	old_mouse_pos = mouse_pos;
	mouse_pos = D3DXVECTOR2((float)GetMouseX(), (float)GetMouseY());

	ball->Judgment++;				//�����񓖂��蔻�����Ȃ��悤�ɂ�����
	
	koba4_count = 0;
	//KOBA4�̏�����
	for (int i = 0; i < KOBA4_MAX; i++)
	{
		koba4[i].block_type = 0;
		koba4[i].length = 0.0f;
	}

	////////////////////////////////////////////////////
	//�{�[���ƃv���C���[�̔���
	////////////////////////////////////////////////////
	//�{�[���𔭎˂�����
	if (ball->judgment_time > 0)
	{
		if ((IsButtonTriggered(0, XINPUT_GAMEPAD_X) || IsMouseLeftPressed()) && !ball->Use)
		{
			ball->speed += BALL_SPEED;
			if (((GetThumbLeftX(0) != 0 || GetThumbLeftY(0) != 0)) || IsMouseLeftPressed() /*&& �����ς����t���O*/)
			{
				reflect = atan2f((float)GetThumbLeftY(0), (float)GetThumbLeftX(0));
				if (IsMouseLeftPressed())//�}�E�X�̍��N���b�N�������Ă�Ƃ�
				{
					reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
				}
				ball->velocity.x = ball->speed * cosf(reflect);
				ball->velocity.y -= ball->speed * sinf(reflect);
				reflect = 0.0f;

				ball->Judgment = 0;
				ball->Use = true;
			}
			else
			{
				ball->velocity.x = BALL_SPEED;
				ball->Judgment = 0;
				ball->Use = true;
			}
			ball->Judgment = 0;
		}
	}
	//�{�[���������Ă鎞�̓����蔻��
	//�{�[���̌��݂Ǝ��̍��W�����񂾐����ƁA�v���C���[�̓����蔻��̐����̌�_
	CollisionKOBA3(player->pos, ball->pos, player->old_pos, ball->old_pos, player->size, ball->size, ball->velocity);
	if (ball->judgment_time > 0)
	{
		if (ball->Judgment > 20 && ball->Use)
		{
			switch (CollisionKOBA(koba3_pos, player->pos, ball->old_pos, player->old_pos, ball->size, player->size))
			{
			case F_OLD_SURFACE::up:

				if (((GetThumbLeftX(0) != 0 || GetThumbLeftY(0) != 0) )/*&& �����ς����t���O*/ || IsMouseLeftPressed())
				{
					ball->speed += BALL_SPEED;
					ball->pos = koba3_pos;
					reflect = atan2f((float)GetThumbLeftY(0), (float)GetThumbLeftX(0));
					
					if(IsMouseLeftPressed())//�}�E�X�̍��N���b�N�������Ă�Ƃ�
					{
						reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
					}
					ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
					ball->velocity.x = ball->speed * cosf(reflect);
					ball->velocity.y -= ball->speed * sinf(reflect);
					reflect = 0.0f;
					SetSwing(60);//���������Ƃ��̉摜�ɕύX������
				}
				else
				{
					ball->speed += BALL_SPEED;
					ball->pos = koba3_pos;
					ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
					ball->velocity.x = ball->speed;
					SetSwing(60);//���������Ƃ��̉摜�ɕύX������
					
				}
				ball->Judgment = 0;

				break;
			case F_OLD_SURFACE::down:

				if (((GetThumbLeftX(0) != 0 || GetThumbLeftY(0) != 0)) /*&& �����ς����t���O*/|| IsMouseLeftPressed())
				{
					ball->speed += BALL_SPEED;
					ball->pos = koba3_pos;
					reflect = atan2f((float)GetThumbLeftY(0), (float)GetThumbLeftX(0));
					if (IsMouseLeftPressed())//�}�E�X�̍��N���b�N�������Ă�Ƃ�
					{
						reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
					}
					ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
					ball->velocity.x = ball->speed * cosf(reflect);
					ball->velocity.y -= ball->speed * sinf(reflect);
					reflect = 0.0f;
					SetSwing(60);//���������Ƃ��̉摜�ɕύX������
				}
				else
				{
					ball->speed += BALL_SPEED;
					ball->pos = koba3_pos;
					ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
					ball->velocity.x = ball->speed;

					SetSwing(60);//���������Ƃ��̉摜�ɕύX������
				}
				ball->Judgment = 0;

				break;
			case F_OLD_SURFACE::left:

				if (player->direction == DIRECTION_LEFT)
				{
					if (((GetThumbLeftX(0) != 0 || GetThumbLeftY(0) != 0) && ((reflect >= PI / 2 && reflect < PI) || (reflect <= -PI / 2 && reflect > -PI)))
						|| IsMouseLeftPressed())
					{
						ball->speed += BALL_SPEED;
						ball->pos = koba3_pos;
						reflect = atan2f((float)GetThumbLeftY(0), (float)GetThumbLeftX(0));
						if (IsMouseLeftPressed())//�}�E�X�̍��N���b�N�������Ă�Ƃ�
						{
							reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
						}
						ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
						ball->velocity.x = ball->speed * cosf(reflect);
						ball->velocity.y -= ball->speed * sinf(reflect);
						reflect = 0.0f;
						SetSwing(60);//���������Ƃ��̉摜�ɕύX������
					}
					else
					{
						ball->speed += BALL_SPEED;
						ball->pos = koba3_pos;
						ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
						ball->velocity.x = ball->speed;
						SetSwing(60);//���������Ƃ��̉摜�ɕύX������

					}
				}
				
				ball->Judgment = 0;

				break;
			case F_OLD_SURFACE::right:

				if (player->direction == DIRECTION_RIGHT)
				{
					if (((GetThumbLeftX(0) != 0 || GetThumbLeftY(0) != 0) && (reflect >= -PI / 2 && reflect < PI / 2))
						|| IsMouseLeftPressed())
					{
						ball->speed += BALL_SPEED;
						ball->pos = koba3_pos;
						reflect = atan2f((float)GetThumbLeftY(0), (float)GetThumbLeftX(0));
						if (IsMouseLeftPressed())//�}�E�X�̍��N���b�N�������Ă�Ƃ�
						{
							reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
						}
						ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
						ball->velocity.x = ball->speed * cosf(reflect);
						ball->velocity.y -= ball->speed * sinf(reflect);
						reflect = 0.0f;
						SetSwing(60);//���������Ƃ��̉摜�ɕύX������
					}
					else
					{
						ball->speed += BALL_SPEED;
						ball->pos = koba3_pos;
						ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
						ball->velocity.x = ball->speed;
						SetSwing(60);//���������Ƃ��̉摜�ɕύX������

					}
				}
				ball->Judgment = 0;

				break;
			}
		}
	}


	////////////////////////////////////////////////////
	//�^�[�Q�b�g��
	////////////////////////////////////////////////////
	//���ʂ̃^�[�Q�b�g�ƃ{�[���̓����蔻��
	for (int i = 0; i < TARGET_MAX; i++)
	{
		if (TargetNormal[i].use == true)
		{
			if (CollisionKOBA(ball->pos, TargetNormal[i].pos, ball->old_pos, TargetNormal[i].old_pos, ball->size, TargetNormal[i].size) == F_OLD_SURFACE::up)
			{
				TargetNormal[i].use = false;
				ball->velocity.y *= -1;
				TargetNormal[i].use = true;
				SceneTransition(SCENE::SCENE_RESULT);
			}
			else if (CollisionKOBA(ball->pos, TargetNormal[i].pos, ball->old_pos, TargetNormal[i].old_pos, ball->size, TargetNormal[i].size) == F_OLD_SURFACE::down)
			{
				TargetNormal[i].use = false;
				ball->velocity.y *= -1;
				TargetNormal[i].use = true;
				SceneTransition(SCENE::SCENE_RESULT);
			}
			else if (CollisionKOBA(ball->pos, TargetNormal[i].pos, ball->old_pos, TargetNormal[i].old_pos, ball->size, TargetNormal[i].size) == F_OLD_SURFACE::right)
			{
				TargetNormal[i].use = false;
				ball->velocity.x *= -1;
				TargetNormal[i].use = true;
				SceneTransition(SCENE::SCENE_RESULT);
			}
			else if (CollisionKOBA(ball->pos, TargetNormal[i].pos, ball->old_pos, TargetNormal[i].old_pos, ball->size, TargetNormal[i].size) == F_OLD_SURFACE::left)
			{
				TargetNormal[i].use = false;
				ball->velocity.x *= -1;
				TargetNormal[i].use = true;
				SceneTransition(SCENE::SCENE_RESULT);
			}
		}
	}

	//�񐔂ŉ���^�[�Q�b�g�ƃ{�[���̓����蔻��
	for (int i = 0; i < TARGET_MAX; i++)
	{
		if (TargetCount[i].use == true)
		{
			if (CollisionBB(ball->pos, TargetCount[i].pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(TargetCount[i].size.x, TargetCount[i].size.y)))
			{
				ball->velocity.x *= -1;
				ball->velocity.y *= -1;
				if (TargetCount[i].Count >= 1)
				{
					TargetCount[i].Count--;
				}
				else
				{
					TargetCount[i].use = false;
					SceneTransition(SCENE::SCENE_RESULT);
				}

			}
		}
	}
		
	////////////////////////////////////////////////////
	//�������Ă�u���b�N�ƃ{�[���̋����𒲂ׂ�
	////////////////////////////////////////////////////
	//�ړ�����u���b�N
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		if (move_block[i].use)
		{
			if (CollisionKOBA(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				ball->size, move_block[i].size) == F_OLD_SURFACE::up)
			{
				CollisionKOBA4_UP(move_block[i].pos, ball->pos, ball->old_pos, move_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_up;
				koba4[koba4_count].block_type = MOVE_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, move_block[i].pos, player->old_pos, move_block[i].old_pos,
				ball->size,move_block[i].size) == F_OLD_SURFACE::left)
			{
				CollisionKOBA4_LEFT(move_block[i].pos, ball->pos, ball->old_pos, move_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_left;
				koba4[koba4_count].block_type = MOVE_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, move_block[i].pos, player->old_pos, move_block[i].old_pos,
				ball->size, move_block[i].size) == F_OLD_SURFACE::right)
			{
				CollisionKOBA4_RIGHT(move_block[i].pos, ball->pos, ball->old_pos, move_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_right;
				koba4[koba4_count].block_type = MOVE_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, move_block[i].pos, player->old_pos, move_block[i].old_pos,
				ball->size, move_block[i].size) == F_OLD_SURFACE::down)
			{
				CollisionKOBA4_DOWN(move_block[i].pos, ball->pos, ball->old_pos, move_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_down;
				koba4[koba4_count].block_type = MOVE_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
		}
	}
	//�񐔂ŉ���u���b�N
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if (count_block[i].use)
		{
			if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].pos,
				ball->size, count_block[i].size) == F_OLD_SURFACE::up)
			{
				CollisionKOBA4_UP(count_block[i].pos, ball->pos, ball->old_pos, count_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].block_type = COUNT_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4[koba4_count].length = koba4_up;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, player->old_pos, count_block[i].pos,
				ball->size, count_block[i].size) == F_OLD_SURFACE::left)
			{
				CollisionKOBA4_LEFT(count_block[i].pos, ball->pos, ball->old_pos, count_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_left;
				koba4[koba4_count].block_type = COUNT_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, player->old_pos, count_block[i].pos,
				ball->size, count_block[i].size) == F_OLD_SURFACE::right)
			{
				CollisionKOBA4_RIGHT(count_block[i].pos, ball->pos, ball->old_pos, count_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_right;
				koba4[koba4_count].block_type = COUNT_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, player->old_pos, count_block[i].pos,
				ball->size, count_block[i].size) == F_OLD_SURFACE::down)
			{
				CollisionKOBA4_DOWN(count_block[i].pos, ball->pos, ball->old_pos, count_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_down;
				koba4[koba4_count].block_type = COUNT_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
		}
	}
	//�X�s�[�h���x���ŉ���u���b�N
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		if (accele_block[i].use)
		{
			if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].pos,
				ball->size, accele_block[i].size) == F_OLD_SURFACE::up)
			{
				CollisionKOBA4_UP(accele_block[i].pos, ball->pos, ball->old_pos, accele_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].block_type = MOVE_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4[koba4_count].length = koba4_up;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, accele_block[i].pos, player->old_pos, accele_block[i].pos,
				ball->size, accele_block[i].size) == F_OLD_SURFACE::left)
			{
				CollisionKOBA4_LEFT(accele_block[i].pos, ball->pos, ball->old_pos, accele_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_left;
				koba4[koba4_count].block_type = MOVE_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, accele_block[i].pos, player->old_pos, accele_block[i].pos,
				ball->size, accele_block[i].size) == F_OLD_SURFACE::right)
			{
				CollisionKOBA4_RIGHT(accele_block[i].pos, ball->pos, ball->old_pos, accele_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_right;
				koba4[koba4_count].block_type = MOVE_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, player->old_pos, count_block[i].pos,
				ball->size, count_block[i].size) == F_OLD_SURFACE::down)
			{
				CollisionKOBA4_DOWN(accele_block[i].pos, ball->pos, ball->old_pos, accele_block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_down;
				koba4[koba4_count].block_type = MOVE_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
		}
	}
	//�����_�������Ƀ{�[������΂����u���b�N
	for (int i = 0; i < MAX_RAMDOM_SHOT_BLOCK; i++)
	{
		if (pRamdom_Shot_Block[i].use)
		{
			if (CollisionKOBA(ball->pos, pRamdom_Shot_Block[i].pos, ball->old_pos, pRamdom_Shot_Block[i].pos,
				ball->size, pRamdom_Shot_Block[i].size) == F_OLD_SURFACE::up)
			{
				CollisionKOBA4_UP(pRamdom_Shot_Block[i].pos, ball->pos, ball->old_pos, pRamdom_Shot_Block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].block_type = RAMDOM_SHOT_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4[koba4_count].length = koba4_up;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, pRamdom_Shot_Block[i].pos, player->old_pos, pRamdom_Shot_Block[i].pos,
				ball->size, pRamdom_Shot_Block[i].size) == F_OLD_SURFACE::left)
			{
				CollisionKOBA4_LEFT(pRamdom_Shot_Block[i].pos, ball->pos, ball->old_pos, pRamdom_Shot_Block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_left;
				koba4[koba4_count].block_type = RAMDOM_SHOT_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, pRamdom_Shot_Block[i].pos, player->old_pos, pRamdom_Shot_Block[i].pos,
				ball->size, pRamdom_Shot_Block[i].size) == F_OLD_SURFACE::right)
			{
				CollisionKOBA4_RIGHT(pRamdom_Shot_Block[i].pos, ball->pos, ball->old_pos, pRamdom_Shot_Block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_right;
				koba4[koba4_count].block_type = RAMDOM_SHOT_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, pRamdom_Shot_Block[i].pos, player->old_pos, pRamdom_Shot_Block[i].pos,
				ball->size, pRamdom_Shot_Block[i].size) == F_OLD_SURFACE::down)
			{
				CollisionKOBA4_DOWN(pRamdom_Shot_Block[i].pos, ball->pos, ball->old_pos, pRamdom_Shot_Block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_down;
				koba4[koba4_count].block_type = RAMDOM_SHOT_BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
		}
	}
	//�u���b�N(��)
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (block[i].Use)
		{
			if (CollisionKOBA(ball->pos, block[i].pos, ball->old_pos, block[i].pos,
				ball->size, block[i].size) == F_OLD_SURFACE::up)
			{
				CollisionKOBA4_UP(block[i].pos, ball->pos, ball->old_pos, block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].block_type = BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4[koba4_count].length = koba4_up;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, block[i].pos, player->old_pos, block[i].pos,
				ball->size, block[i].size) == F_OLD_SURFACE::left)
			{
				CollisionKOBA4_LEFT(block[i].pos, ball->pos, ball->old_pos, block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_left;
				koba4[koba4_count].block_type = BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, block[i].pos, player->old_pos, block[i].pos,
				ball->size, block[i].size) == F_OLD_SURFACE::right)
			{
				CollisionKOBA4_RIGHT(block[i].pos, ball->pos, ball->old_pos, block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_right;
				koba4[koba4_count].block_type = BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, block[i].pos, player->old_pos, block[i].pos,
				ball->size, block[i].size) == F_OLD_SURFACE::down)
			{
				CollisionKOBA4_DOWN(block[i].pos, ball->pos, ball->old_pos, block[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_down;
				koba4[koba4_count].block_type = BLOCK_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
		}
	}
	//��
	for (int i = 0; i < MAX_GROUND; i++)
	{
		if (ground[i].use)
		{
			if (CollisionKOBA(ball->pos, ground[i].pos, ball->old_pos, ground[i].pos,
				ball->size, ground[i].size) == F_OLD_SURFACE::up)
			{
				CollisionKOBA4_UP(ground[i].pos, ball->pos, ball->old_pos, ground[i].size, ball->size, ball->velocity);
				koba4[koba4_count].block_type = GROUND_NUM;
				koba4[koba4_count].block_num = i;
				koba4[koba4_count].length = koba4_up;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, ground[i].pos, player->old_pos, ground[i].pos,
				ball->size, ground[i].size) == F_OLD_SURFACE::left)
			{
				CollisionKOBA4_LEFT(ground[i].pos, ball->pos, ball->old_pos, ground[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_left;
				koba4[koba4_count].block_type = GROUND_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, ground[i].pos, player->old_pos, ground[i].pos,
				ball->size, ground[i].size) == F_OLD_SURFACE::right)
			{
				CollisionKOBA4_RIGHT(ground[i].pos, ball->pos, ball->old_pos, ground[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_right;
				koba4[koba4_count].block_type = GROUND_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, ground[i].pos, player->old_pos, ground[i].pos,
				ball->size, ground[i].size) == F_OLD_SURFACE::down)
			{
				CollisionKOBA4_DOWN(ground[i].pos, ball->pos, ball->old_pos, ground[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_down;
				koba4[koba4_count].block_type = GROUND_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
		}
	}
	//���[�v
	for (int i = 0; i < MAX_WARP; i++)
	{
		if (pwarp[i].use)
		{
			if (CollisionKOBA(ball->pos, pwarp[i].pos, ball->old_pos, pwarp[i].pos,
				ball->size, pwarp[i].size) == F_OLD_SURFACE::up)
			{
				CollisionKOBA4_UP(pwarp[i].pos, ball->pos, ball->old_pos, pwarp[i].size, ball->size, ball->velocity);
				koba4[koba4_count].block_type = WARP_NUM;
				koba4[koba4_count].block_num = i;
				koba4[koba4_count].length = koba4_up;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, pwarp[i].pos, player->old_pos, pwarp[i].pos,
				ball->size, pwarp[i].size) == F_OLD_SURFACE::left)
			{
				CollisionKOBA4_LEFT(pwarp[i].pos, ball->pos, ball->old_pos, pwarp[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_left;
				koba4[koba4_count].block_type = WARP_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, pwarp[i].pos, player->old_pos, pwarp[i].pos,
				ball->size, pwarp[i].size) == F_OLD_SURFACE::right)
			{
				CollisionKOBA4_RIGHT(pwarp[i].pos, ball->pos, ball->old_pos, pwarp[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_right;
				koba4[koba4_count].block_type = WARP_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
			else if (CollisionKOBA(ball->pos, pwarp[i].pos, player->old_pos, pwarp[i].pos,
				ball->size, pwarp[i].size) == F_OLD_SURFACE::down)
			{
				CollisionKOBA4_DOWN(pwarp[i].pos, ball->pos, ball->old_pos, pwarp[i].size, ball->size, ball->velocity);
				koba4[koba4_count].length = koba4_down;
				koba4[koba4_count].block_type = WARP_NUM;
				koba4[koba4_count].block_num = i;
				koba4_count++;
			}
		}
	}

	//�����̔�r
	switch (koba4_count)
	{
	case 0:
		break;
	case 1:
		if (koba4[0].length < koba4[1].length)
		{
			koba4[0].block_num = koba4[1].block_num;
			koba4[0].block_type = koba4[1].block_type;
		}
		break;
	case 2:
		if (koba4[0].length < koba4[1].length)
		{
			koba4[0].block_num = koba4[1].block_num;
			koba4[0].block_type = koba4[1].block_type;
		}
		if (koba4[0].length < koba4[2].length)
		{
			koba4[0].block_num = koba4[2].block_num;
			koba4[0].block_type = koba4[2].block_type;
		}
		break;
	case 3:
		if (koba4[0].length < koba4[1].length)
		{
			koba4[0].block_num = koba4[1].block_num;
			koba4[0].block_type = koba4[1].block_type;
		}
		if (koba4[0].length < koba4[2].length)
		{
			koba4[0].block_num = koba4[2].block_num;
			koba4[0].block_type = koba4[2].block_type;
		}
		if (koba4[0].length < koba4[3].length)
		{
			koba4[0].block_num = koba4[3].block_num;
			koba4[0].block_type = koba4[3].block_type;
		}
		break;
	}

	switch (koba4[0].block_type)
	{
	case 0:
		break;
	case MOVE_BLOCK_NUM://�ړ�����u���b�N�ƃ{�[���̔���
		switch (CollisionKOBA2(ball->pos, move_block[koba4[0].block_num].pos, ball->old_pos, move_block[koba4[0].block_num].old_pos,
			ball->size, move_block[koba4[0].block_num].size, move_block[koba4[0].block_num].velocity))
		{
		case F_OLD_SURFACE::up:
			ball->pos.y = move_block[koba4[0].block_num].pos.y - ((ball->size.y / 2) + (move_block[koba4[0].block_num].size.y / 2));
			ball->velocity.y *= -1;
			break;
		case F_OLD_SURFACE::left :
			if (ball->velocity.x == 0.0f)
				ball->velocity.x -= move_block[koba4[0].block_num].velocity.x;
			ball->pos.x = move_block[koba4[0].block_num].pos.x - ((ball->size.x / 2) + (move_block[koba4[0].block_num].size.x / 2));
			ball->velocity.x *= -1;
			break;
		case F_OLD_SURFACE::right:
			if (ball->velocity.x == 0.0f)
				ball->velocity.x += move_block[koba4[0].block_num].velocity.x;
			ball->pos.x = move_block[koba4[0].block_num].pos.x + ((ball->size.x / 2) + (move_block[koba4[0].block_num].size.x / 2));
			ball->velocity.x *= -1;
			break;
		case F_OLD_SURFACE::down:
			ball->pos.y = move_block[koba4[0].block_num].pos.y + ((ball->size.y / 2) + (move_block[koba4[0].block_num].size.y / 2));
			ball->velocity.y *= -1;
			break;
		}
		break;
	case COUNT_BLOCK_NUM://�񐔂ŉ���u���b�N�ƃ{�[���̔���
		switch (CollisionKOBA(ball->pos, count_block[koba4[0].block_num].pos, ball->old_pos, count_block[koba4[0].block_num].pos,
			ball->size, count_block[koba4[0].block_num].size))
		{
		case F_OLD_SURFACE::up:
			ball->velocity.y *= -1;
			count_block[koba4[0].block_num].HitCount--;
			if (count_block[koba4[0].block_num].HitCount < 0)
			{
				count_block[koba4[0].block_num].use = false;
			}
			break;
		case F_OLD_SURFACE::left:
			ball->velocity.x *= -1;
			count_block[koba4[0].block_num].HitCount--;
			if (count_block[koba4[0].block_num].HitCount < 0)
			{
				count_block[koba4[0].block_num].use = false;
			}
			break;
		case F_OLD_SURFACE::right:
			ball->velocity.x *= -1;
			count_block[koba4[0].block_num].HitCount--;
			if (count_block[koba4[0].block_num].HitCount < 0)
			{
				count_block[koba4[0].block_num].use = false;
			}
			break;
		case F_OLD_SURFACE::down:
			ball->velocity.y *= -1;
			count_block[koba4[0].block_num].HitCount--;
			if (count_block[koba4[0].block_num].HitCount < 0)
			{
				count_block[koba4[0].block_num].use = false;
			}
			break;
		}
		break;
	case ACCELE_BLOCK_NUM://���x���x���ŉ���
		switch (CollisionKOBA(ball->pos, accele_block[koba4[0].block_num].pos, ball->old_pos, accele_block[koba4[0].block_num].pos,
			ball->size, accele_block[koba4[0].block_num].size))
		{
		case F_OLD_SURFACE::up:
			ball->velocity.y *= -1;
			if (accele_block[koba4[0].block_num].level == ball->Speed_Level)
			{
				accele_block[koba4[0].block_num].use = false;
			}
			break;
		case F_OLD_SURFACE::left:
			ball->velocity.x *= -1;
			if (accele_block[koba4[0].block_num].level == ball->Speed_Level)
			{
				accele_block[koba4[0].block_num].use = false;
			}
			break;
		case F_OLD_SURFACE::right:
			ball->velocity.x *= -1;
			if (accele_block[koba4[0].block_num].level == ball->Speed_Level)
			{
				accele_block[koba4[0].block_num].use = false;
			}
			break;
		case F_OLD_SURFACE::down:
			ball->velocity.y *= -1;
			if (accele_block[koba4[0].block_num].level == ball->Speed_Level)
			{
				accele_block[koba4[0].block_num].use = false;
			}
			break;
		}
		break;
	case RAMDOM_SHOT_BLOCK_NUM://�����_�������Ƀ{�[������΂����u���b�N
		if (CollisionBB(ball->pos, pRamdom_Shot_Block[koba4[0].block_num].pos, ball->size, pRamdom_Shot_Block[koba4[0].block_num].size))
		{
			ball->pos = pRamdom_Shot_Block[koba4[0].block_num].pos;
			//����
			int ramdom = rand() % 3;
			//�����ŏo�������ɉ����Ĕ�΂����������߂�
			switch (ramdom)
			{
			case 0:
				reflect = atan2f(1.0f, 1.0f);
				break;
			case 1:
				reflect = atan2f(-1.0f, 1.0f);
				break;
			case 2:
				reflect = atan2f(1.0f, -1.0f);
				break;
			case 3:
				reflect = atan2f(-1.0f, -1.0f);
				break;

			}
			ball->velocity.x = ball->speed * cosf(reflect);
			ball->velocity.y -= ball->speed * sinf(reflect);
		}
		break;
	case BLOCK_NUM://�u���b�N(��)
		switch (CollisionKOBA(ball->pos, block[koba4[0].block_num].pos, ball->old_pos, block[koba4[0].block_num].pos,
			ball->size, block[koba4[0].block_num].size))
		{
		case F_OLD_SURFACE::up:
			ball->velocity.y *= -1;
			break;
		case F_OLD_SURFACE::left:
			ball->velocity.x *= -1;
			break;
		case F_OLD_SURFACE::right:
			ball->velocity.x *= -1;
			break;
		case F_OLD_SURFACE::down:
			ball->velocity.y *= -1;
			break;
		}
		break;
	case GROUND_NUM://��
		switch (CollisionKOBA(ball->pos, ground[koba4[0].block_num].pos, ball->old_pos, ground[koba4[0].block_num].pos,
			ball->size, ground[koba4[0].block_num].size))
		{
		case F_OLD_SURFACE::no_hit:
			break;

		case F_OLD_SURFACE::up:
			ball->pos.y = (ground[koba4[0].block_num].pos.y - ((ground[koba4[0].block_num].size.y / 2) + (ball->size.y / 2)));
			ball->velocity.y *= -1;
			break;
		}
		break;
	case WARP_NUM://���[�v
		switch (CollisionKOBA(ball->pos, pwarp[koba4[0].block_num].pos, ball->old_pos, pwarp[koba4[0].block_num].pos, 
			ball->size, pwarp[koba4[0].block_num].size))
		{
		case F_OLD_SURFACE::up:
			//i�������Ȃ�+1�A��Ȃ�-1�������[�v�ɔ�΂�
			if (koba4[0].block_num % 2 == 0)
			{
				ball->pos.y = pwarp[koba4[0].block_num + 1].pos.y - (pwarp[koba4[0].block_num + 1].size.y / 2);
			}
			else if (koba4[0].block_num % 2 == 1)
			{
				ball->pos.y = pwarp[koba4[0].block_num - 1].pos.y - (pwarp[koba4[0].block_num - 1].size.y / 2);
			}
			break;
		case F_OLD_SURFACE::down:
			if (koba4[0].block_num % 2 == 0)
			{
				ball->pos.y = pwarp[koba4[0].block_num + 1].pos.y + (pwarp[koba4[0].block_num + 1].size.y / 2);
			}
			else if (koba4[0].block_num % 2 == 1)
			{
				ball->pos.y = pwarp[koba4[0].block_num - 1].pos.y + (pwarp[koba4[0].block_num - 1].size.y / 2);
			}
			break;
		case F_OLD_SURFACE::left:
			if (koba4[0].block_num % 2 == 0)
			{
				ball->pos.x = pwarp[koba4[0].block_num + 1].pos.x + (pwarp[koba4[0].block_num + 1].size.x / 2);
			}
			else if (koba4[0].block_num % 2 == 1)
			{
				ball->pos.x = pwarp[koba4[0].block_num - 1].pos.x + (pwarp[koba4[0].block_num - 1].size.x / 2);
			}
			break;
		case F_OLD_SURFACE::right:
			if (koba4[0].block_num % 2 == 0)
			{
				ball->pos.x = pwarp[koba4[0].block_num + 1].pos.x - (pwarp[koba4[0].block_num + 1].size.x / 2);
			}
			else if (koba4[0].block_num % 2 == 1)
			{
				ball->pos.x = pwarp[koba4[0].block_num - 1].pos.x - (pwarp[koba4[0].block_num - 1].size.x / 2);
			}
			break;
		}
		break;
	}









	////////////////////////////////////////////////////
	//�����u���b�N��*
	// /////////////////////////////////////////////////
	//�v���C���[�Ɠ����u���b�N�̓����蔻��
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		if (move_block[i].use)
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

	//�{�[���Ɠ����u���b�N�̓����蔻��
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		if (move_block[i].use)
		{
			if (CollisionKOBA2(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				ball->size, move_block[i].size, move_block[i].velocity) == F_OLD_SURFACE::up)
			{
				ball->pos.y = move_block[i].pos.y - ((ball->size.y / 2) + (move_block[i].size.y / 2));
				ball->velocity.y *= -1;
			}
			else if (CollisionKOBA2(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y), move_block[i].velocity) == F_OLD_SURFACE::left)
			{
				if (ball->velocity.x == 0.0f)
				ball->velocity.x -= move_block[i].velocity.x;
				ball->pos.x = move_block[i].pos.x - ((ball->size.x / 2) + (move_block[i].size.x / 2));
				ball->velocity.x *= -1;
			}
			else if (CollisionKOBA2(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y), move_block[i].velocity) == F_OLD_SURFACE::right)
			{
				if (ball->velocity.x == 0.0f)
				ball->velocity.x += move_block[i].velocity.x;
				ball->pos.x = move_block[i].pos.x + ((ball->size.x / 2) + (move_block[i].size.x / 2));
				ball->velocity.x *= -1;
			}
			else if (CollisionKOBA2(ball->pos, move_block[i].pos, ball->old_pos, move_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[i].size.x, move_block[i].size.y), move_block[i].velocity) == F_OLD_SURFACE::down)
			{
				ball->pos.y = move_block[i].pos.y + ((ball->size.y / 2) + (move_block[i].size.y / 2));
				ball->velocity.y *= -1;
			}
		}
	}

	////////////////////////////////////////////////////
	//�񐔂ŉ���u���b�N��*
	// /////////////////////////////////////////////////
	//�v���C���[�Ɖ񐔂ŉ���u���b�N�̓����蔻��
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if (count_block[i].use)
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
				player->pos.y = count_block[i].pos.y + ((player->size.y / 2) + (count_block[i].size.y / 2));
				player->move.y = 0.0f;
			}
		}
	}
	//�{�[���Ɖ񐔂ŉ���u���b�N�̓����蔻��
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if (count_block[i].use)
		{
			if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].old_pos,
				ball->size, count_block[i].size) == F_OLD_SURFACE::up)
			{
				ball->velocity.y *= -1;
				count_block[i].HitCount--;
				if (count_block[i].HitCount < 0)
				{
					count_block[i].use = false;
				}
				
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::left)
			{
				ball->velocity.x *= -1;
				count_block[i].HitCount--;
				if (count_block[i].HitCount < 0)
				{
					count_block[i].use = false;
				}
				
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::right)
			{
				ball->velocity.x *= -1;
				count_block[i].HitCount--;
				if (count_block[i].HitCount < 0)
				{
					count_block[i].use = false;
				}
				
			}
			else if (CollisionKOBA(ball->pos, count_block[i].pos, ball->old_pos, count_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(count_block[i].size.x, count_block[i].size.y)) == F_OLD_SURFACE::down)
			{
				ball->velocity.y *= -1;
				count_block[i].HitCount--;
				if (count_block[i].HitCount < 0)
				{
					count_block[i].use = false;
				}
				
			}
		}
	}

	////////////////////////////////////////////////////
	//�X�s�[�h���x���ŉ���u���b�N��*
	////////////////////////////////////////////////////
	//�v���C���[�ƃX�s�[�h���x���ŉ���u���b�N�̓����蔻��
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		if (accele_block[i].use)
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
		if (accele_block[i].use)
		{
			if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::up)
			{
				ball->velocity.y *= -1;
				if (accele_block[i].level == ball->Speed_Level)
				{
					accele_block[i].use = false;
				}
			}
			else if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::left)
			{
				ball->velocity.x *= -1;
				if (accele_block[i].level == ball->Speed_Level)
				{
					accele_block[i].use = false;
				}
			}
			else if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::right)
			{
				ball->velocity.x *= -1;
				if (accele_block[i].level == ball->Speed_Level)
				{
					accele_block[i].use = false;
				}
			}
			else if (CollisionKOBA(ball->pos, accele_block[i].pos, ball->old_pos, accele_block[i].old_pos,
				D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(accele_block[i].size.x, accele_block[i].size.y)) == F_OLD_SURFACE::down)
			{
				ball->velocity.y *= -1;
				if (accele_block[i].level == ball->Speed_Level)
				{
					accele_block[i].use = false;
				}
			}
		}
	}
	
	////////////////////////////////////////////////////
	//�����_�����˃u���b�N*
	////////////////////////////////////////////////////
	for (int i = 0; i < MAX_RAMDOM_SHOT_BLOCK; i++)
	{
		if (pRamdom_Shot_Block[i].use)
		{

			if(CollisionBB(ball->pos, pRamdom_Shot_Block[i].pos, ball->size, pRamdom_Shot_Block[i].size))
			{
				ball->pos = pRamdom_Shot_Block[i].pos;
				//����
				int ramdom = rand() % 3;
				//�����ŏo�������ɉ����Ĕ�΂����������߂�
				switch (ramdom)
				{
				case 0:
					reflect = atan2f(1.0f, 1.0f);
					break;
				case 1:
					reflect = atan2f(-1.0f, 1.0f);
					break;
				case 2:
					reflect = atan2f(1.0f, -1.0f);
					break;
				case 3:
					reflect = atan2f(-1.0f, -1.0f);
					break;

				}
				ball->velocity.x =  ball->speed * cosf(reflect);
				ball->velocity.y -= ball->speed * sinf(reflect);
			}
		}
	}

	////////////////////////////////////////////////////
	//�X�s�[�h�p�l���̔����
	////////////////////////////////////////////////////
	for(int i = 0;i < MAX_Panel;i++)
	{
		if (pSpeedPanel[i].use && !CollisionBB(ball->old_pos,pSpeedPanel[i].pos,ball->size,pSpeedPanel[i].size))
		{
			if (pSpeedPanel[i].type == SPEED_UP)
			{
				ball->speed += (BALL_SPEED * 2);
			}
			else if (pSpeedPanel[i].type == SPEED_DOWN)
			{
				ball->speed -= (BALL_SPEED * 2);
				if (ball->speed < 0)
					ball->speed = 0;
			}
		}
	}
	
	////////////////////////////////////////////////////
	//���[�v��*
	////////////////////////////////////////////////////
	for (int i = 0; i < MAX_WARP; i++)
	{
		if (pwarp[i].use)
		{
			switch (CollisionKOBA(ball->pos, pwarp[i].pos, ball->old_pos, pwarp[i].pos, ball->size, pwarp[i].size))
			{
			case F_OLD_SURFACE::up:
				//i�������Ȃ�+1�A��Ȃ�-1�������[�v�ɔ�΂�
				if (i % 2 == 0)		
				{
					ball->pos.y = pwarp[i + 1].pos.y - (pwarp[i + 1].size.y / 2);
				}
				else if (i % 2 == 1)
				{
					ball->pos.y = pwarp[i - 1].pos.y - (pwarp[i - 1].size.y / 2);
				}
				break;
			case F_OLD_SURFACE::down:
				if (i % 2 == 0)
				{
					ball->pos.y = pwarp[i + 1].pos.y + (pwarp[i + 1].size.y / 2);
				}
				else if (i % 2 == 1)
				{
					ball->pos.y = pwarp[i - 1].pos.y + (pwarp[i - 1].size.y / 2);
				}
				break;
			case F_OLD_SURFACE::left:
				if (i % 2 == 0)
				{
					ball->pos.x = pwarp[i + 1].pos.x + (pwarp[i + 1].size.x / 2);
				}
				else if (i % 2 == 1)
				{
					ball->pos.x = pwarp[i - 1].pos.x + (pwarp[i - 1].size.x / 2);
				}
				break;
			case F_OLD_SURFACE::right:
				if (i % 2 == 0)
				{
					ball->pos.x = pwarp[i + 1].pos.x - (pwarp[i + 1].size.x / 2);
				}
				else if (i % 2 == 1)
				{
					ball->pos.x = pwarp[i - 1].pos.x - (pwarp[i - 1].size.x / 2);
				}
				break;
			}
		}
	}

	///////////////////////////////////////
    //���Ȃ��u���b�N��*
    // ////////////////////////////////////
    //�{�[���Ƃ̓����蔻��
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		switch (CollisionKOBA(ball->pos, block[i].pos, ball->old_pos, block[i].pos,
			ball->size, block[i].size))
		{
		case F_OLD_SURFACE::no_hit:
			break;

		case F_OLD_SURFACE::up:
			ball->pos.y = (block[i].pos.y - ((block[i].size.y / 2) + (block->size.y / 2)));
			ball->velocity.y *= -1;
			break;

		case F_OLD_SURFACE::down:
			ball->pos.y = (block[i].pos.y + ((block[i].size.y / 2) + (ball->size.y / 2)));
			ball->velocity.y *= -1;
			break;
		case F_OLD_SURFACE::left:
			ball->pos.x = (block[i].pos.x - ((block[i].size.x / 2) + (ball->size.x / 2)));
			ball->velocity.x *= -1;
			break;
		case F_OLD_SURFACE::right:
			ball->pos.x = (block[i].pos.x + ((block[i].size.x / 2) + (ball->size.x / 2)));
			ball->velocity.x *= -1;
			break;
		}
	}

	//�v���C���[�Ƃ̔���
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if (block[i].Use)
		{
			if (CollisionKOBA(player->pos, block[i].pos, player->old_pos, block[i].pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(block[i].size.x, block[i].size.y)) == F_OLD_SURFACE::up)
			{
				player->pos.y = block[i].pos.y - ((player->size.y / 2) + (block[i].size.y / 2));
				player_fly = false;
			}
			else if (CollisionKOBA(player->pos, block[i].pos, player->old_pos, block[i].pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(block[i].size.x, block[i].size.y)) == F_OLD_SURFACE::left)
			{
				player->pos.x = block[i].pos.x - ((player->size.x / 2) + (block[i].size.x / 2));
			}
			else if (CollisionKOBA(player->pos, block[i].pos, player->old_pos, block[i].pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(block[i].size.x, block[i].size.y)) == F_OLD_SURFACE::right)
			{
				player->pos.x = block[i].pos.x + ((player->size.x / 2) + (block[i].size.x / 2));
			}
			else if (CollisionKOBA(player->pos, block[i].pos, player->old_pos, block[i].pos,
				D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(block[i].size.x, block[i].size.y)) == F_OLD_SURFACE::down)
			{
				player->pos.y = block[i].pos.y + ((player->size.y / 2) + (block[i].size.y / 2));
				player->move.y = 0.0f;
			}
		}
	}

	////////////////////////////////////////////////////
	//��*
	////////////////////////////////////////////////////
	//�v���C���[�Ə��̔���
	for (int i = 0; i < MAX_GROUND; i++)
	{
		switch (CollisionKOBA(player->pos, ground[i].pos, player->old_pos, ground[i].pos,
			D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(ground[i].size.x, ground[i].size.y)))
		{
		case F_OLD_SURFACE::no_hit:
			break;

		case F_OLD_SURFACE::up:
			player->pos.y = ground[i].pos.y - ((player->size.y / 2) + (ground[i].size.y / 2));
			player_fly = false;
			break;

		case F_OLD_SURFACE::left:
			//player->pos.x = ground[i].pos.x - ((player->size.x / 2) + (ground[i].size.x / 2));
			break;

		case F_OLD_SURFACE::right:
			//player->pos.x = ground[i].pos.x + ((player->size.x / 2) + (ground[i].size.x / 2));
			break;

		case F_OLD_SURFACE::down:
			//player->pos.y = count_block[0].pos.y - ((player->size.y / 2) + (count_block[0].size.y / 2));
			break;
		}
	}

	//�{�[���̏��̔���
	for (int i = 0; i < MAX_GROUND; i++)
	{
		switch (CollisionKOBA(ball->pos, ground[i].pos, ball->old_pos, ground[i].pos,
				ball->size,ground[i].size))
		{
		case F_OLD_SURFACE::no_hit:
			break;

		case F_OLD_SURFACE::up:
			ball->pos.y = (ground[i].pos.y - ((ground[i].size.y / 2) + (ball->size.y / 2)));
			ball->velocity.y *= -1;
			break;
		}
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
// 1�t���[���O�̈ʒu���Q�Ƃ��������蔻�菈��
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
// �ړ�����u���b�N��p��CollisionKOBA2
//=============================================================================
F_OLD_SURFACE CollisionKOBA2(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos, 
							 D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size, D3DXVECTOR2 block_velocity)
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

	//�u���b�N�̈ړ���
	D3DXVECTOR2 block_move =(block_pos - block_old_pos);

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
			if (block_move < 0)
			{
				if ((-PI / 2 >= InnerProduct_angle && -PI < InnerProduct_angle) || (PI / 2 <= InnerProduct_angle && PI > InnerProduct_angle))
				{
					if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
					{
						return F_OLD_SURFACE::left;
					}
				}
				else
				{
					return F_OLD_SURFACE::no_hit;
				}
			}
			else
			{
				if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
				{
					return F_OLD_SURFACE::left;
				}
			}
			//�v���C���[���u���b�N�̉E���瓖�������Ƃ�
			if (block_velocity > 0)
			{
				if ((-PI / 2 <= InnerProduct_angle && 0 > InnerProduct_angle) || (PI / 2 >= InnerProduct && 0 < InnerProduct_angle))
				{
					if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
					{
						return F_OLD_SURFACE::right;
					}
				}
			}
			else
			{
				if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
				{
					return F_OLD_SURFACE::right;
				}
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
				if (block_velocity > 0)
				{
					if (PI / 2 <= InnerProduct_angle && PI > InnerProduct_angle)
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
				else
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
			}

			//�u���b�N����E���̔���
			if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
			{
				if (block_velocity > 0)
				{
					if (-PI / 2 >= InnerProduct_angle && -PI < InnerProduct_angle)
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
				else
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
			}

			//�u���b�N���獶��̔���
			if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
			{
				//�u���b�N�̉����x���}�C�i�X�̎�
				if (block_velocity.x < 0)
				{
					if (PI / 2 >= InnerProduct_angle && 0 < InnerProduct_angle)
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
				else
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
			}

			//�u���b�N���獶���̔���
			if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
			{
				//�u���b�N�̉����x���}�C�i�X�̎�
				if (block_velocity < 0)
				{
					if (-PI / 2 >= InnerProduct_angle && 0 < InnerProduct_angle)
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
				else
					if (-PI / 2 >= InnerProduct_angle && 0 < InnerProduct_angle)
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
	}
	return F_OLD_SURFACE::no_hit;
	//return F_OLD_SURFACE();
}


//=============================================================================
// �v���C���[�ƃ{�[���̃x�N�g�����W���o��CollisionKOBA3
//=============================================================================
	D3DXVECTOR2 CollisionKOBA3(D3DXVECTOR2 player_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 player_old_pos,
							   D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		//��_���W�̏�����
		koba3_pos = D3DXVECTOR2(0.0f, 0.0f);

		D3DXVECTOR2 player_min, player_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;

		player_min.x = player_pos.x - player_size.x / 2;
		player_min.y = player_pos.y - player_size.y / 2;
		player_max.x = player_pos.x + player_size.x / 2;
		player_max.y = player_pos.y + player_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//�{�[���̎��̍��W
		ball_next_pos = ball_pos + ball_velocity;

		//�v���C���[�̉��z�����x
		D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (ball_pos - ball_old_pos);
		D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

		vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
		vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
		vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
		vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;


		//X���̔���
		if (player_min.x < ball_max.x && player_max.x > ball_min.x)
		{
			//Y���̔���
			if (player_min.y < ball_max.y && player_max.y > ball_min.y)
			{
				//�v���C���[���u���b�N�̏ォ�瓖�������Ƃ�
				if (vertual_player_old_max.y <= ball_min.y && vertual_player_old_max.x > ball_min.x && vertual_player_old_min.x < ball_max.x)
				{
					float Bunbo = (player_max.x - player_min.x)
								* (ball_pos.y - ball_next_pos.y)
								- (player_min.y - player_min.y)
								* (ball_pos.x - ball_next_pos.x);

					D3DXVECTOR2 vectorUP = ball_next_pos - player_min;

					float dS = ((player_min.y - player_min.y) * vectorUP.x
						- (player_max.x - player_min.x) * vectorUP.y) / Bunbo;

					koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

					return (koba3_pos);
				}
				//�v���C���[���u���b�N�̉����瓖�������Ƃ�
				if (vertual_player_old_min.y >= ball_max.y && vertual_player_old_max.x > ball_min.x && vertual_player_old_min.x < ball_max.x)
				{
					float Bunbo = (player_max.x - player_min.x)
								* (ball_pos.y - ball_next_pos.y)
								- (player_max.y - player_max.y)
								* (ball_pos.x - ball_next_pos.x);

					D3DXVECTOR2 vectorDOWN = ball_next_pos - player_min;

					float dS = ((player_max.y - player_max.y) * vectorDOWN.x
						- (player_max.x - player_min.x) * vectorDOWN.y) / Bunbo;

					koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

					return (koba3_pos);
				}
				//�v���C���[���u���b�N�̍����瓖�������Ƃ�
				if (vertual_player_old_max.x <= ball_min.x && vertual_player_old_max.y > ball_min.y && vertual_player_old_min.y < ball_max.y)
				{
					float Bunbo = (player_max.x - player_max.x)
								* (ball_pos.y - ball_next_pos.y)
								- (player_max.y - player_min.y)
								* (ball_pos.x - ball_next_pos.x);

					D3DXVECTOR2 vectorLEFT = ball_next_pos - player_min;

					float dS = ((player_max.y - player_min.y) * vectorLEFT.x
						- (player_max.x - player_max.x) * vectorLEFT.y) / Bunbo;

					koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

					return (koba3_pos);
				}
				//�v���C���[���u���b�N�̉E���瓖�������Ƃ�
				if (vertual_player_old_min.x >= ball_max.x && vertual_player_old_max.y > ball_min.y && vertual_player_old_min.y < ball_max.y)
				{
					float Bunbo = (player_min.x - player_min.x)
								* (ball_pos.y - ball_next_pos.y)
								- (player_max.y - player_min.y)
								* (ball_pos.x - ball_next_pos.x);

					D3DXVECTOR2 vectorRIGHT = ball_next_pos - player_min;

					float dS = ((player_max.y - player_min.y) * vectorRIGHT.x
						- (player_min.x - player_min.x) * vectorRIGHT.y) / Bunbo;

					koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

					return (koba3_pos);
				}

				//�v���C���[�̉����x�̉��z�p�x
				float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);


				//�v���C���[�̒��_����u���b�N�̒��_�����񂾒����̊p�x
				//�v���C���[���獶��
				float LeftDown_angle = atan2f((player_max.y - ball_min.y), (player_min.x - ball_max.x));
				//�v���C���[���獶��
				float LeftUp_angle = atan2f((player_min.y - ball_max.y), (player_min.x - ball_max.x));
				//�v���C���[����E��
				float RightDown_angle = atan2f((player_max.y - ball_min.y), (player_max.x - ball_min.x));
				//�v���C���[����E��
				float RightUp_angle = atan2f((player_min.y - ball_max.y), (player_max.x - ball_min.x));

				//�u���b�N����E��̔���
				if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
				{
					if (vertual_velocity_angle > LeftDown_angle)
					{
						//��
						float Bunbo = (player_max.x - player_min.x)
							* (ball_pos.y - ball_next_pos.y)
							- (player_max.y - player_min.y)
							* (ball_pos.x - ball_next_pos.x);

						D3DXVECTOR2 vectorUP = ball_next_pos - player_min;

						float dS = ((player_max.y - player_min.y) * vectorUP.x
							- (player_max.x - player_min.x) * vectorUP.y) / Bunbo;

						koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

						return (koba3_pos);
					}
					else
					{
						//�E
						float Bunbo = (player_min.x - player_min.x)
							* (ball_pos.y - ball_next_pos.y)
							- (player_max.y - player_min.y)
							* (ball_pos.x - ball_next_pos.x);

						D3DXVECTOR2 vectorRIGHT = ball_next_pos - player_min;

						float dS = ((player_max.y - player_min.y) * vectorRIGHT.x
							- (player_min.x - player_min.x) * vectorRIGHT.y) / Bunbo;

						koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

						return (koba3_pos);
					}
				}

				//�u���b�N����E���̔���
				if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
				{
					if (vertual_velocity_angle > LeftUp_angle)
					{
						//�E
						float Bunbo = (player_min.x - player_min.x)
							* (ball_pos.y - ball_next_pos.y)
							- (player_max.y - player_min.y)
							* (ball_pos.x - ball_next_pos.x);

						D3DXVECTOR2 vectorRIGHT = ball_next_pos - player_min;

						float dS = ((player_max.y - player_min.y) * vectorRIGHT.x
							- (player_min.x - player_min.x) * vectorRIGHT.y) / Bunbo;

						koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

						return (koba3_pos);
					}
					else
					{
						//��
						float Bunbo = (player_max.x - player_min.x)
							* (ball_pos.y - ball_next_pos.y)
							- (player_max.y - player_max.y)
							* (ball_pos.x - ball_next_pos.x);

						D3DXVECTOR2 vectorDOWN = ball_next_pos - player_min;

						float dS = ((player_max.y - player_max.y) * vectorDOWN.x
							- (player_max.x - player_min.x) * vectorDOWN.y) / Bunbo;

						koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

						return (koba3_pos);
					}
				}

				//�u���b�N���獶��̔���
				if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
				{
					if (vertual_velocity_angle > RightDown_angle)
					{
						//��
						float Bunbo = (player_max.x - player_max.x)
							* (ball_pos.y - ball_next_pos.y)
							- (player_max.y - player_min.y)
							* (ball_pos.x - ball_next_pos.x);

						D3DXVECTOR2 vectorLEFT = ball_next_pos - player_min;

						float dS = ((player_max.y - player_min.y) * vectorLEFT.x
							- (player_max.x - player_max.x) * vectorLEFT.y) / Bunbo;

						koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

						return (koba3_pos);
					}
					else
					{
						//��
						float Bunbo = (player_max.x - player_min.x)
							* (ball_pos.y - ball_next_pos.y)
							- (player_max.y - player_min.y)
							* (ball_pos.x - ball_next_pos.x);

						D3DXVECTOR2 vectorUP = ball_next_pos - player_min;

						float dS = ((player_max.y - player_min.y) * vectorUP.x
							- (player_max.x - player_min.x) * vectorUP.y) / Bunbo;

						koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);
						
						return (koba3_pos);
					}
				}

				//�u���b�N���獶���̔���
				if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
				{
					if (vertual_velocity_angle > RightUp_angle)
					{
						//��
						float Bunbo = (player_max.x - player_min.x)
							* (ball_pos.y - ball_next_pos.y)
							- (player_max.y - player_max.y)
							* (ball_pos.x - ball_next_pos.x);

						D3DXVECTOR2 vectorDOWN = ball_next_pos - player_min;

						float dS = ((player_max.y - player_max.y) * vectorDOWN.x
							- (player_max.x - player_min.x) * vectorDOWN.y) / Bunbo;

						koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

						return (koba3_pos);
					}
					else
					{
						//��
						float Bunbo = (player_max.x - player_max.x)
							* (ball_pos.y - ball_next_pos.y)
							- (player_max.y - player_min.y)
							* (ball_pos.x - ball_next_pos.x);

						D3DXVECTOR2 vectorLEFT = ball_next_pos - player_min;

						float dS = ((player_max.y - player_min.y) * vectorLEFT.x
							- (player_max.x - player_max.x) * vectorLEFT.y) / Bunbo;

						koba3_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

						return (koba3_pos);
					}
				}
			}
		}

		return (koba3_pos);

	}

//=============================================================================
// �u���b�N�ƃ{�[���̌�_���W�ƃ{�[����pos�̒������o��CollisionKOBA4
//=============================================================================	
	//�u���b�N����݂ď�
	float CollisionKOBA4_UP(D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 ball_old_pos,
							D3DXVECTOR2 block_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		//��_���W�̏�����
		koba3_pos = D3DXVECTOR2(0.0f, 0.0f);

		D3DXVECTOR2 block_min, block_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;
		//��_���W
		D3DXVECTOR2 Intersection_pos;
		//�{�[���̉ߋ��̍��W�����_���W�̉����x
		D3DXVECTOR2 ball_Intersection_vector;

		block_min.x = block_size.x - block_size.x / 2;
		block_min.y = block_size.y - block_size.y / 2;
		block_max.x = block_size.x + block_size.x / 2;
		block_max.y = block_size.y + block_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//�{�[���̎��̍��W
		ball_next_pos = ball_pos + ball_velocity;

		float Bunbo = (block_max.x - ball_min.x)
					* (ball_pos.y - ball_next_pos.y)
					- (block_max.y - block_max.y)
					* (ball_pos.x - ball_next_pos.x);

		D3DXVECTOR2 vectorUP = ball_next_pos - ball_min;

		float dS = ((block_max.y - block_max.y) * vectorUP.x
			- (block_max.x - ball_min.x) * vectorUP.y) / Bunbo;

		ball_Intersection_vector = ball_next_pos + dS * (ball_pos - ball_next_pos);

		ball_Intersection_vector = Intersection_pos - ball_old_pos;
		//�{�[���̉ߋ��̍��W�����_���W�̒�����2��
		koba4_up = fabsf((ball_Intersection_vector.x + ball_Intersection_vector.x) + (ball_Intersection_vector.y + ball_Intersection_vector.y));
		return(koba4_up);
	}

	//�u���b�N����݂ĉ�
	float CollisionKOBA4_DOWN(D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 ball_old_pos,
						      D3DXVECTOR2 block_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		
		D3DXVECTOR2 block_min, block_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;
		//��_���W
		D3DXVECTOR2 Intersection_pos;
		//�{�[���̉ߋ��̍��W�����_���W�̉����x
		D3DXVECTOR2 ball_Intersection_vector;

		block_min.x = block_size.x - block_size.x / 2;
		block_min.y = block_size.y - block_size.y / 2;
		block_max.x = block_size.x + block_size.x / 2;
		block_max.y = block_size.y + block_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//�{�[���̎��̍��W
		ball_next_pos = ball_pos + ball_velocity;

		float Bunbo = (block_max.x - block_min.x)
			* (ball_pos.y - ball_next_pos.y)
			- (block_min.y - block_min.y)
			* (ball_pos.x - ball_next_pos.x);

		D3DXVECTOR2 vectorDOWN = ball_next_pos - block_min;

		float dS = ((block_min.y - block_min.y) * vectorDOWN.x
			- (block_max.x - block_min.x) * vectorDOWN.y) / Bunbo;

		Intersection_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

		ball_Intersection_vector = Intersection_pos - ball_old_pos;
		//�{�[���̉ߋ��̍��W�����_���W�̒�����2��
		koba4_down = fabsf((ball_Intersection_vector.x + ball_Intersection_vector.x) + (ball_Intersection_vector.y + ball_Intersection_vector.y));

		return(koba4_down);
	}

	//�u���b�N����݂č�
	float CollisionKOBA4_LEFT(D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 ball_old_pos,
							  D3DXVECTOR2 block_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		//��_���W�̏�����
		koba3_pos = D3DXVECTOR2(0.0f, 0.0f);

		D3DXVECTOR2 block_min, block_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;
		//��_���W
		D3DXVECTOR2 Intersection_pos;
		//�{�[���̉ߋ��̍��W�����_���W�̉����x
		D3DXVECTOR2 ball_Intersection_vector;

		block_min.x = block_size.x - block_size.x / 2;
		block_min.y = block_size.y - block_size.y / 2;
		block_max.x = block_size.x + block_size.x / 2;
		block_max.y = block_size.y + block_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//�{�[���̎��̍��W
		ball_next_pos = ball_pos + ball_velocity;
		
			float Bunbo = (block_min.x - block_min.x)
				* (ball_pos.y - ball_next_pos.y)
				- (block_max.y - block_min.y)
				* (ball_pos.x - ball_next_pos.x);

			D3DXVECTOR2 vectorLEFT = ball_next_pos - block_min;

			float dS = ((block_max.y - block_min.y) * vectorLEFT.x
				- (block_min.x - block_min.x) * vectorLEFT.y) / Bunbo;

			ball_Intersection_vector = ball_next_pos + dS * (ball_pos - ball_next_pos);

		ball_Intersection_vector = Intersection_pos - ball_old_pos;
		//�{�[���̉ߋ��̍��W�����_���W�̒�����2��
		koba4_up = fabsf((ball_Intersection_vector.x + ball_Intersection_vector.x) + (ball_Intersection_vector.y + ball_Intersection_vector.y));


		return(koba4_left);
	}

	//�u���b�N����݂ĉE
	float CollisionKOBA4_RIGHT(D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 ball_old_pos,
							   D3DXVECTOR2 block_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		//��_���W�̏�����
		koba3_pos = D3DXVECTOR2(0.0f, 0.0f);

		D3DXVECTOR2 block_min, block_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;
		//��_���W
		D3DXVECTOR2 Intersection_pos;
		//�{�[���̉ߋ��̍��W�����_���W�̉����x
		D3DXVECTOR2 ball_Intersection_vector;

		block_min.x = block_size.x - block_size.x / 2;
		block_min.y = block_size.y - block_size.y / 2;
		block_max.x = block_size.x + block_size.x / 2;
		block_max.y = block_size.y + block_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//�{�[���̎��̍��W
		ball_next_pos = ball_pos + ball_velocity;

		float Bunbo = (block_max.x - block_max.x)
			* (ball_pos.y - ball_next_pos.y)
			- (block_max.y - block_min.y)
			* (ball_pos.x - ball_next_pos.x);

		D3DXVECTOR2 vectorRIGHT = ball_next_pos - block_min;

		float dS = ((block_max.y - block_min.y) * vectorRIGHT.x
			- (block_max.x - block_max.x) * vectorRIGHT.y) / Bunbo;

		Intersection_pos = ball_next_pos + dS * (ball_pos - ball_next_pos);

		ball_Intersection_vector = Intersection_pos - ball_old_pos;
		//�{�[���̉ߋ��̍��W�����_���W�̒�����2��
		koba4_right = fabsf((ball_Intersection_vector.x + ball_Intersection_vector.x) + (ball_Intersection_vector.y + ball_Intersection_vector.y));

		return(koba4_right);
	}