//=============================================================================
// 当たり判定処理 [collision.cpp]
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
// マクロ定義
//*****************************************************************************
#define BALLACCELE	(2.0f)


#define KOBA4_MAX  4
//ブロックの種類の番号
#define MOVE_BLOCK_NUM 1
#define COUNT_BLOCK_NUM 2
#define ACCELE_BLOCK_NUM 3
#define RAMDOM_SHOT_BLOCK_NUM 4
#define BLOCK_NUM 5
#define GROUND_NUM 6
#define WARP_NUM 7
//*****************************************************************************
// 構造体定義
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
// プロトタイプ宣言
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
// グローバル変数
//*****************************************************************************
int NoFlame = 0;	//当たり判定を〇フレーム消す

//CollisionKOBA3で返ってくるやつ
static D3DXVECTOR2 koba3_pos = {};
//CollisionKOBA4で返ってくるやつ
static float koba4_up = {};
static float koba4_down = {};
static float koba4_left = {};
static float koba4_right = {};

static KOBA4 koba4[KOBA4_MAX];
static int koba4_count;


//跳ね返る角度
static float	reflect;	
//マウスの座標（マウス操作する時に使う）
D3DXVECTOR2 mouse_pos = D3DXVECTOR2((float)GetMouseX(), (float)GetMouseY());
D3DXVECTOR2 old_mouse_pos = mouse_pos;
float mouse_reflect;



//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(void)
{
	srand((unsigned int)time(NULL));
	bool player_fly = true;			//プレイヤーが空中にいるか
	old_mouse_pos = mouse_pos;
	mouse_pos = D3DXVECTOR2((float)GetMouseX(), (float)GetMouseY());

	ball->Judgment++;				//複数回当たり判定を貰わないようにするやつ
	
	koba4_count = 0;
	//KOBA4の初期化
	for (int i = 0; i < KOBA4_MAX; i++)
	{
		koba4[i].block_type = 0;
		koba4[i].length = 0.0f;
	}

	////////////////////////////////////////////////////
	//ボールとプレイヤーの判定
	////////////////////////////////////////////////////
	//ボールを発射させる
	if (ball->judgment_time > 0)
	{
		if ((IsButtonTriggered(0, XINPUT_GAMEPAD_X) || IsMouseLeftPressed()) && !ball->Use)
		{
			ball->speed += BALL_SPEED;
			if (((GetThumbLeftX(0) != 0 || GetThumbLeftY(0) != 0)) || IsMouseLeftPressed() /*&& 向き変えるよフラグ*/)
			{
				reflect = atan2f((float)GetThumbLeftY(0), (float)GetThumbLeftX(0));
				if (IsMouseLeftPressed())//マウスの左クリックを押してるとき
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
	//ボールが動いてる時の当たり判定
	//ボールの現在と次の座標を結んだ線分と、プレイヤーの当たり判定の線分の交点
	CollisionKOBA3(player->pos, ball->pos, player->old_pos, ball->old_pos, player->size, ball->size, ball->velocity);
	if (ball->judgment_time > 0)
	{
		if (ball->Judgment > 20 && ball->Use)
		{
			switch (CollisionKOBA(koba3_pos, player->pos, ball->old_pos, player->old_pos, ball->size, player->size))
			{
			case F_OLD_SURFACE::up:

				if (((GetThumbLeftX(0) != 0 || GetThumbLeftY(0) != 0) )/*&& 向き変えるよフラグ*/ || IsMouseLeftPressed())
				{
					ball->speed += BALL_SPEED;
					ball->pos = koba3_pos;
					reflect = atan2f((float)GetThumbLeftY(0), (float)GetThumbLeftX(0));
					
					if(IsMouseLeftPressed())//マウスの左クリックを押してるとき
					{
						reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
					}
					ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
					ball->velocity.x = ball->speed * cosf(reflect);
					ball->velocity.y -= ball->speed * sinf(reflect);
					reflect = 0.0f;
					SetSwing(60);//当たったときの画像に変更するやつ
				}
				else
				{
					ball->speed += BALL_SPEED;
					ball->pos = koba3_pos;
					ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
					ball->velocity.x = ball->speed;
					SetSwing(60);//当たったときの画像に変更するやつ
					
				}
				ball->Judgment = 0;

				break;
			case F_OLD_SURFACE::down:

				if (((GetThumbLeftX(0) != 0 || GetThumbLeftY(0) != 0)) /*&& 向き変えるよフラグ*/|| IsMouseLeftPressed())
				{
					ball->speed += BALL_SPEED;
					ball->pos = koba3_pos;
					reflect = atan2f((float)GetThumbLeftY(0), (float)GetThumbLeftX(0));
					if (IsMouseLeftPressed())//マウスの左クリックを押してるとき
					{
						reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
					}
					ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
					ball->velocity.x = ball->speed * cosf(reflect);
					ball->velocity.y -= ball->speed * sinf(reflect);
					reflect = 0.0f;
					SetSwing(60);//当たったときの画像に変更するやつ
				}
				else
				{
					ball->speed += BALL_SPEED;
					ball->pos = koba3_pos;
					ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
					ball->velocity.x = ball->speed;

					SetSwing(60);//当たったときの画像に変更するやつ
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
						if (IsMouseLeftPressed())//マウスの左クリックを押してるとき
						{
							reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
						}
						ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
						ball->velocity.x = ball->speed * cosf(reflect);
						ball->velocity.y -= ball->speed * sinf(reflect);
						reflect = 0.0f;
						SetSwing(60);//当たったときの画像に変更するやつ
					}
					else
					{
						ball->speed += BALL_SPEED;
						ball->pos = koba3_pos;
						ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
						ball->velocity.x = ball->speed;
						SetSwing(60);//当たったときの画像に変更するやつ

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
						if (IsMouseLeftPressed())//マウスの左クリックを押してるとき
						{
							reflect = atan2f((mouse_pos.y - old_mouse_pos.y), (mouse_pos.x - old_mouse_pos.x));
						}
						ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
						ball->velocity.x = ball->speed * cosf(reflect);
						ball->velocity.y -= ball->speed * sinf(reflect);
						reflect = 0.0f;
						SetSwing(60);//当たったときの画像に変更するやつ
					}
					else
					{
						ball->speed += BALL_SPEED;
						ball->pos = koba3_pos;
						ball->velocity = D3DXVECTOR2(0.0f, 0.0f);
						ball->velocity.x = ball->speed;
						SetSwing(60);//当たったときの画像に変更するやつ

					}
				}
				ball->Judgment = 0;

				break;
			}
		}
	}


	////////////////////////////////////////////////////
	//ターゲット編
	////////////////////////////////////////////////////
	//普通のターゲットとボールの当たり判定
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

	//回数で壊れるターゲットとボールの当たり判定
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
	//当たってるブロックとボールの距離を調べる
	////////////////////////////////////////////////////
	//移動するブロック
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
	//回数で壊れるブロック
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
	//スピードレベルで壊れるブロック
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
	//ランダム方向にボールが飛ばされるブロック
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
	//ブロック(壁)
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
	//床
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
	//ワープ
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

	//距離の比較
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
	case MOVE_BLOCK_NUM://移動するブロックとボールの判定
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
	case COUNT_BLOCK_NUM://回数で壊れるブロックとボールの判定
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
	case ACCELE_BLOCK_NUM://速度レベルで壊れる
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
	case RAMDOM_SHOT_BLOCK_NUM://ランダム方向にボールが飛ばされるブロック
		if (CollisionBB(ball->pos, pRamdom_Shot_Block[koba4[0].block_num].pos, ball->size, pRamdom_Shot_Block[koba4[0].block_num].size))
		{
			ball->pos = pRamdom_Shot_Block[koba4[0].block_num].pos;
			//乱数
			int ramdom = rand() % 3;
			//乱数で出た数字に応じて飛ばす向きを決める
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
	case BLOCK_NUM://ブロック(壁)
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
	case GROUND_NUM://床
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
	case WARP_NUM://ワープ
		switch (CollisionKOBA(ball->pos, pwarp[koba4[0].block_num].pos, ball->old_pos, pwarp[koba4[0].block_num].pos, 
			ball->size, pwarp[koba4[0].block_num].size))
		{
		case F_OLD_SURFACE::up:
			//iが偶数なら+1、奇数なら-1したワープに飛ばす
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
	//動くブロック編*
	// /////////////////////////////////////////////////
	//プレイヤーと動くブロックの当たり判定
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

	//ボールと動くブロックの当たり判定
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
	//回数で壊れるブロック編*
	// /////////////////////////////////////////////////
	//プレイヤーと回数で壊れるブロックの当たり判定
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
	//ボールと回数で壊れるブロックの当たり判定
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
	//スピードレベルで壊れるブロック編*
	////////////////////////////////////////////////////
	//プレイヤーとスピードレベルで壊れるブロックの当たり判定
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
	//ボールとスピードレベルで壊れるブロックの当たり判定
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
	//ランダム反射ブロック*
	////////////////////////////////////////////////////
	for (int i = 0; i < MAX_RAMDOM_SHOT_BLOCK; i++)
	{
		if (pRamdom_Shot_Block[i].use)
		{

			if(CollisionBB(ball->pos, pRamdom_Shot_Block[i].pos, ball->size, pRamdom_Shot_Block[i].size))
			{
				ball->pos = pRamdom_Shot_Block[i].pos;
				//乱数
				int ramdom = rand() % 3;
				//乱数で出た数字に応じて飛ばす向きを決める
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
	//スピードパネルの判定編
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
	//ワープ編*
	////////////////////////////////////////////////////
	for (int i = 0; i < MAX_WARP; i++)
	{
		if (pwarp[i].use)
		{
			switch (CollisionKOBA(ball->pos, pwarp[i].pos, ball->old_pos, pwarp[i].pos, ball->size, pwarp[i].size))
			{
			case F_OLD_SURFACE::up:
				//iが偶数なら+1、奇数なら-1したワープに飛ばす
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
    //壊れないブロック編*
    // ////////////////////////////////////
    //ボールとの当たり判定
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

	//プレイヤーとの判定
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
	//床*
	////////////////////////////////////////////////////
	//プレイヤーと床の判定
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

	//ボールの床の判定
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
// BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
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

	//X軸の判定
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y軸の判定
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistanceのベクトル長を得る
	float length;
//	length = D3DXVec2Length(&vDistance);
	length = D3DXVec2LengthSq(&vDistance);

//	float size = size1 + size2;
	float size = (size1 + size2) * (size1 + size2);

	//1と2の半径を足して判定する
	//差分のベクトル長の方が小さければ
	//ヒットしている
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// 1フレーム前の位置を参照した当たり判定処理
// サイズは半径
// 戻り値：当たっている面を返す
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

	//プレイヤーの仮想加速度
	D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (block_pos - block_old_pos);
	D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

	vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
	vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
	vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
	vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;

	


	//X軸の判定
	if (player_min.x < block_max.x && player_max.x > block_min.x)
	{
		//Y軸の判定
		if (player_min.y < block_max.y && player_max.y > block_min.y)
		{
			//プレイヤーがブロックの上から当たったとき
			if (vertual_player_old_max.y <= block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::up;
			}
			//プレイヤーがブロックの下から当たったとき
			if (vertual_player_old_min.y >= block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::down;
			}
			//プレイヤーがブロックの左から当たったとき
			if (vertual_player_old_max.x <= block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::left;
			}
			//プレイヤーがブロックの右から当たったとき
			if (vertual_player_old_min.x >= block_max.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return F_OLD_SURFACE::right;
			}

			//プレイヤーの加速度の仮想角度
			float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);
			

			//プレイヤーの頂点からブロックの頂点を結んだ直線の角度
			//プレイヤーから左下
			float LeftDown_angle = atan2f((player_max.y - block_min.y), (player_min.x - block_max.x));
			//プレイヤーから左上
			float LeftUp_angle = atan2f((player_min.y - block_max.y), (player_min.x - block_max.x));
			//プレイヤーから右下
			float RightDown_angle = atan2f((player_max.y - block_min.y), (player_max.x - block_min.x));
			//プレイヤーから右上
			float RightUp_angle = atan2f((player_min.y - block_max.y), (player_max.x - block_min.x));

			//ブロックから右上の判定
			if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
			{
      				if (vertual_velocity_angle > LeftDown_angle)
				{
					//上
					return F_OLD_SURFACE::up;
				}
				else
				{
					//右
					return F_OLD_SURFACE::right;
				}
			}

			//ブロックから右下の判定
			if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
			{
				if (vertual_velocity_angle > LeftUp_angle)
				{
					//右
					return F_OLD_SURFACE::right;
				}
				else
				{
					//下
					return F_OLD_SURFACE::down;
				}
			}

			//ブロックから左上の判定
			if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
			{
				if (vertual_velocity_angle > RightDown_angle)
				{
					//左
					return F_OLD_SURFACE::left;
				}
				else
				{
					//上
					return F_OLD_SURFACE::up;
				}
			}

			//ブロックから左下の判定
			if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
			{
				if (vertual_velocity_angle > RightUp_angle)
				{
					//下
					return F_OLD_SURFACE::down;
				}
				else
				{
					//左
					return F_OLD_SURFACE::left;
				}
			}
		}
	}
	return F_OLD_SURFACE::no_hit;
	//return F_OLD_SURFACE();

}


//=============================================================================
// 移動するブロック専用のCollisionKOBA2
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

	//プレイヤーの仮想加速度
	D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (block_pos - block_old_pos);
	D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

	//ブロックの移動量
	D3DXVECTOR2 block_move =(block_pos - block_old_pos);

	vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
	vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
	vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
	vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;

	//ブロックの加速度と仮想加速度の内積と長さ
	float InnerProduct = (vertual_player_velocity.x * block_velocity.x) + (vertual_player_velocity.y * block_velocity.y);
	float vertual_player_velocity_length = sqrtf((vertual_player_velocity.x * vertual_player_velocity.x) + (vertual_player_velocity.y * vertual_player_velocity.y));
	float block_velocity_length = sqrtf((block_velocity.x * block_velocity.x) + (block_velocity.y * block_velocity.y));
	//ブロックの加速度と仮想加速度の内積の角度
	float InnerProduct_angle = InnerProduct / (vertual_player_velocity_length * block_velocity_length);



	//X軸の判定
	if (player_min.x < block_max.x && player_max.x > block_min.x)
	{
		//Y軸の判定
		if (player_min.y < block_max.y && player_max.y > block_min.y)
		{
			//プレイヤーがブロックの上から当たったとき
			if (vertual_player_old_max.y <= block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
					return F_OLD_SURFACE::up;
			}
			//プレイヤーがブロックの下から当たったとき
			if (vertual_player_old_min.y >= block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return F_OLD_SURFACE::down;
			}
			//プレイヤーがブロックの左から当たったとき
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
			//プレイヤーがブロックの右から当たったとき
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

			//プレイヤーの加速度の仮想角度
			float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);


			//プレイヤーの頂点からブロックの頂点を結んだ直線の角度
			//プレイヤーから左下
			float LeftDown_angle = atan2f((player_max.y - block_min.y), (player_min.x - block_max.x));
			//プレイヤーから左上
			float LeftUp_angle = atan2f((player_min.y - block_max.y), (player_min.x - block_max.x));
			//プレイヤーから右下
			float RightDown_angle = atan2f((player_max.y - block_min.y), (player_max.x - block_min.x));
			//プレイヤーから右上
			float RightUp_angle = atan2f((player_min.y - block_max.y), (player_max.x - block_min.x));

			//ブロックから右上の判定
			if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
			{
				if (block_velocity > 0)
				{
					if (PI / 2 <= InnerProduct_angle && PI > InnerProduct_angle)
					{
						if (vertual_velocity_angle > LeftDown_angle)
						{
							//上
							return F_OLD_SURFACE::up;
						}
						else
						{
							//右
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
						//上
						return F_OLD_SURFACE::up;
					}
					else
					{
						//右
						return F_OLD_SURFACE::right;
					}
				}
			}

			//ブロックから右下の判定
			if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
			{
				if (block_velocity > 0)
				{
					if (-PI / 2 >= InnerProduct_angle && -PI < InnerProduct_angle)
					{
						if (vertual_velocity_angle > LeftUp_angle)
						{
							//右
							return F_OLD_SURFACE::right;
						}
						else
						{
							//下
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
						//右
						return F_OLD_SURFACE::right;
					}
					else
					{
						//下
						return F_OLD_SURFACE::down;
					}
				}
			}

			//ブロックから左上の判定
			if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
			{
				//ブロックの加速度がマイナスの時
				if (block_velocity.x < 0)
				{
					if (PI / 2 >= InnerProduct_angle && 0 < InnerProduct_angle)
					{
						if (vertual_velocity_angle > RightDown_angle)
						{
							//左
							return F_OLD_SURFACE::left;
						}
						else
						{
							//上
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
						//左
						return F_OLD_SURFACE::left;
					}
					else
					{
						//上
						return F_OLD_SURFACE::up;
					}
				}
			}

			//ブロックから左下の判定
			if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
			{
				//ブロックの加速度がマイナスの時
				if (block_velocity < 0)
				{
					if (-PI / 2 >= InnerProduct_angle && 0 < InnerProduct_angle)
					{
						if (vertual_velocity_angle > RightUp_angle)
						{
							//下
							return F_OLD_SURFACE::down;
						}
						else
						{
							//左
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
							//下
							return F_OLD_SURFACE::down;
						}
						else
						{
							//左
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
// プレイヤーとボールのベクトル座標を出すCollisionKOBA3
//=============================================================================
	D3DXVECTOR2 CollisionKOBA3(D3DXVECTOR2 player_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 player_old_pos,
							   D3DXVECTOR2 ball_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		//交点座標の初期化
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

		//ボールの次の座標
		ball_next_pos = ball_pos + ball_velocity;

		//プレイヤーの仮想加速度
		D3DXVECTOR2 vertual_player_velocity = (player_pos - player_old_pos) - (ball_pos - ball_old_pos);
		D3DXVECTOR2 vertual_player_old_pos = player_pos - vertual_player_velocity;

		vertual_player_old_min.x = vertual_player_old_pos.x - player_size.x / 2;
		vertual_player_old_min.y = vertual_player_old_pos.y - player_size.y / 2;
		vertual_player_old_max.x = vertual_player_old_pos.x + player_size.x / 2;
		vertual_player_old_max.y = vertual_player_old_pos.y + player_size.y / 2;


		//X軸の判定
		if (player_min.x < ball_max.x && player_max.x > ball_min.x)
		{
			//Y軸の判定
			if (player_min.y < ball_max.y && player_max.y > ball_min.y)
			{
				//プレイヤーがブロックの上から当たったとき
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
				//プレイヤーがブロックの下から当たったとき
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
				//プレイヤーがブロックの左から当たったとき
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
				//プレイヤーがブロックの右から当たったとき
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

				//プレイヤーの加速度の仮想角度
				float vertual_velocity_angle = atan2f(vertual_player_velocity.y, vertual_player_velocity.x);


				//プレイヤーの頂点からブロックの頂点を結んだ直線の角度
				//プレイヤーから左下
				float LeftDown_angle = atan2f((player_max.y - ball_min.y), (player_min.x - ball_max.x));
				//プレイヤーから左上
				float LeftUp_angle = atan2f((player_min.y - ball_max.y), (player_min.x - ball_max.x));
				//プレイヤーから右下
				float RightDown_angle = atan2f((player_max.y - ball_min.y), (player_max.x - ball_min.x));
				//プレイヤーから右上
				float RightUp_angle = atan2f((player_min.y - ball_max.y), (player_max.x - ball_min.x));

				//ブロックから右上の判定
				if (vertual_velocity_angle >= PI / 2 && vertual_velocity_angle <= PI)
				{
					if (vertual_velocity_angle > LeftDown_angle)
					{
						//上
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
						//右
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

				//ブロックから右下の判定
				if (vertual_velocity_angle >= -PI && vertual_velocity_angle <= -PI / 2)
				{
					if (vertual_velocity_angle > LeftUp_angle)
					{
						//右
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
						//下
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

				//ブロックから左上の判定
				if (vertual_velocity_angle >= 0 && vertual_velocity_angle <= PI / 2)
				{
					if (vertual_velocity_angle > RightDown_angle)
					{
						//左
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
						//上
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

				//ブロックから左下の判定
				if (vertual_velocity_angle >= -PI / 2 && vertual_velocity_angle <= 0)
				{
					if (vertual_velocity_angle > RightUp_angle)
					{
						//下
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
						//左
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
// ブロックとボールの交点座標とボールのposの長さを出すCollisionKOBA4
//=============================================================================	
	//ブロックからみて上
	float CollisionKOBA4_UP(D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 ball_old_pos,
							D3DXVECTOR2 block_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		//交点座標の初期化
		koba3_pos = D3DXVECTOR2(0.0f, 0.0f);

		D3DXVECTOR2 block_min, block_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;
		//交点座標
		D3DXVECTOR2 Intersection_pos;
		//ボールの過去の座標から交点座標の加速度
		D3DXVECTOR2 ball_Intersection_vector;

		block_min.x = block_size.x - block_size.x / 2;
		block_min.y = block_size.y - block_size.y / 2;
		block_max.x = block_size.x + block_size.x / 2;
		block_max.y = block_size.y + block_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//ボールの次の座標
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
		//ボールの過去の座標から交点座標の長さの2乗
		koba4_up = fabsf((ball_Intersection_vector.x + ball_Intersection_vector.x) + (ball_Intersection_vector.y + ball_Intersection_vector.y));
		return(koba4_up);
	}

	//ブロックからみて下
	float CollisionKOBA4_DOWN(D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 ball_old_pos,
						      D3DXVECTOR2 block_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		
		D3DXVECTOR2 block_min, block_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;
		//交点座標
		D3DXVECTOR2 Intersection_pos;
		//ボールの過去の座標から交点座標の加速度
		D3DXVECTOR2 ball_Intersection_vector;

		block_min.x = block_size.x - block_size.x / 2;
		block_min.y = block_size.y - block_size.y / 2;
		block_max.x = block_size.x + block_size.x / 2;
		block_max.y = block_size.y + block_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//ボールの次の座標
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
		//ボールの過去の座標から交点座標の長さの2乗
		koba4_down = fabsf((ball_Intersection_vector.x + ball_Intersection_vector.x) + (ball_Intersection_vector.y + ball_Intersection_vector.y));

		return(koba4_down);
	}

	//ブロックからみて左
	float CollisionKOBA4_LEFT(D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 ball_old_pos,
							  D3DXVECTOR2 block_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		//交点座標の初期化
		koba3_pos = D3DXVECTOR2(0.0f, 0.0f);

		D3DXVECTOR2 block_min, block_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;
		//交点座標
		D3DXVECTOR2 Intersection_pos;
		//ボールの過去の座標から交点座標の加速度
		D3DXVECTOR2 ball_Intersection_vector;

		block_min.x = block_size.x - block_size.x / 2;
		block_min.y = block_size.y - block_size.y / 2;
		block_max.x = block_size.x + block_size.x / 2;
		block_max.y = block_size.y + block_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//ボールの次の座標
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
		//ボールの過去の座標から交点座標の長さの2乗
		koba4_up = fabsf((ball_Intersection_vector.x + ball_Intersection_vector.x) + (ball_Intersection_vector.y + ball_Intersection_vector.y));


		return(koba4_left);
	}

	//ブロックからみて右
	float CollisionKOBA4_RIGHT(D3DXVECTOR2 block_pos, D3DXVECTOR2 ball_pos, D3DXVECTOR2 ball_old_pos,
							   D3DXVECTOR2 block_size, D3DXVECTOR2 ball_size, D3DXVECTOR2 ball_velocity)
	{
		//交点座標の初期化
		koba3_pos = D3DXVECTOR2(0.0f, 0.0f);

		D3DXVECTOR2 block_min, block_max;
		D3DXVECTOR2 ball_min, ball_max;
		D3DXVECTOR2 vertual_player_old_min, vertual_player_old_max;
		D3DXVECTOR2 ball_next_pos;
		//交点座標
		D3DXVECTOR2 Intersection_pos;
		//ボールの過去の座標から交点座標の加速度
		D3DXVECTOR2 ball_Intersection_vector;

		block_min.x = block_size.x - block_size.x / 2;
		block_min.y = block_size.y - block_size.y / 2;
		block_max.x = block_size.x + block_size.x / 2;
		block_max.y = block_size.y + block_size.y / 2;

		ball_min.x = ball_pos.x - ball_size.x / 2;
		ball_min.y = ball_pos.y - ball_size.y / 2;
		ball_max.x = ball_pos.x + ball_size.x / 2;
		ball_max.y = ball_pos.y + ball_size.y / 2;

		//ボールの次の座標
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
		//ボールの過去の座標から交点座標の長さの2乗
		koba4_right = fabsf((ball_Intersection_vector.x + ball_Intersection_vector.x) + (ball_Intersection_vector.y + ball_Intersection_vector.y));

		return(koba4_right);
	}