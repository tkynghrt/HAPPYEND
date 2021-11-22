//=============================================================================
//
// 当たり判定処理 [collision.cpp]
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
// マクロ定義
//*****************************************************************************
#define HIMELEFT	2
#define BALLACCELE	(2.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
static MOVE_BLOCK* move_block = GetMoveBlock();
static COUNT_BLOCK* count_block = GetCountBlock();
static PLAYER* player = GetPlayer();


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
int CheckHit(F_CIRCLE* pcrCircle, F_RECT_CIRCLE* prcRectCircle);
int InitShapes(D3DXVECTOR2 pos1, float r1, D3DXVECTOR2 pos2, float r2, D3DXVECTOR2 move);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int NoFlame = 0;	//当たり判定を〇フレーム消す
F_CIRCLE crCircle; // 円形Ａ 
F_RECT_CIRCLE rcRectCircle; // 矩形＋円Ｂ 
//////////////////////////////////////////////////////
int speed_number;
//=============================================================================
// 当たり判定処理
//=============================================================================

void UpdateCollision(void)
{
	PLAYER *player = GetPlayer();		// プレイヤーのポインターを初期化
	BALL *ball = GetBall();		// バレットのポインターを初期化
	ATTACK *attack = GetAttack();
	
	if (NoFlame > 0)//当たり判定が消えていればカウントを進め消えて居なければ実行
	{
		NoFlame--;
	}
	else
	{
		if (ball->mode >= 1)
		{
			if (attack->mode == 1)
			{
				InitShapes(attack->pos, attack->h - 35, ball->pos, ball->size.y - 20, D3DXVECTOR2(-ball->move.x, -ball->move.y));//-35-20判定を小さめにする

				if (CheckHit(&crCircle, &rcRectCircle))
				{
					//姫の向き
					int HimeDirection = GetPlayer_Direction();

					//球の加速
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
							//20フレーム当たり判定を消す
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
							//20フレーム当たり判定を消す
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
						NoFlame = 20;//20フレーム当たり判定を消す
					}
				}
			}
		}

		if (ball->mode >= 1)
		{
			if (attack->mode == 2)
			{
				InitShapes(attack->pos, attack->h - 35, ball->pos, ball->size.y - 20, D3DXVECTOR2(-ball->move.x, -ball->move.y));//-35-20判定を小さめにする

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
					NoFlame = 20; // 20フレーム当たり判定を消す
				}
			}
		}
		// 自分と敵の弾(BC)

		// 死亡したら状態遷移

		
		
		//移動するブロックとプレイヤーの当たり判定
		
		//for (int i = 0; i < MAX_MOVEBLOCK; i++)
		//{
			
		//}

			//プレイヤーと動くブロックの当たり判定
		if (CollisionBB(player->pos, move_block[0].pos, D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(move_block[0].size.x, move_block[0].size.y)))
		{
			//プレイヤーがブロックの上にいるとき
			
			if (player->pos.y + (player->size.y / 2) > move_block[0].pos.y - (move_block[0].size.y / 2))
			{
				player->pos.y = move_block[0].pos.y - ((player->size.y / 2) + (move_block[0].size.y / 2));
				player->pos.x += move_block[0].velocity.x * 2;


				//player->player_doingjump = false;
				//moveblock[0].RidingPlayer = true;
			}
			//プレイヤーがブロックの下にぶつかったとき
			if (player->pos.y - (player->size.y / 2) < move_block[0].pos.y + (move_block[0].size.y / 2))
			{
				player->move.y = 0.0f;

				//player->player_doingjump = false;
				//moveblock[0].RidingPlayer = true;
			}

			//プレイヤーの左に当たった場合
			if (ball->pos.x + (ball->size.x / 2) > move_block[0].pos.x - (move_block[0].size.x / 2))
			{
				ball->move.x *= -1;
			}

			//プレイヤーの右に当たった場合
			if (ball->pos.x - (ball->size.x / 2) > move_block[0].pos.x + (move_block[0].size.x / 2))
			{
				ball->move.x *= -1;
			}
		}

	}
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
	
	
	
	//X軸の判定
	if (player_min.x < block_max.x && player_max.x > block_min.x)
	{
		//Y軸の判定
		if (player_min.y < block_max.y && player_max.y > block_min.y)
		{
			//プレイヤーがブロックの上から当たったとき
			if (vertual_player_old_max.y < block_min.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return up;
			}
			//プレイヤーがブロックの下から当たったとき
			if (vertual_player_old_min.y > block_max.y && vertual_player_old_max.x > block_min.x && vertual_player_old_min.x < block_max.x)
			{
				return down;
			}
			//プレイヤーがブロックの左から当たったとき
			if (vertual_player_old_max.x < block_min.x && vertual_player_old_max.y > block_min.y && vertual_player_old_min.y < block_max.y)
			{
				return left;
			}
			//プレイヤーがブロックの右から当たったとき
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
// 円と線分の Collision 判定 
//------------------------------------------------------------ 

int InitShapes(D3DXVECTOR2 pos1, float r1, D3DXVECTOR2 pos2, float r2, D3DXVECTOR2 move) // 最初に１回だけ呼ばれる 
{
	crCircle.x = pos1.x; crCircle.y = pos1.y;
	crCircle.r = r1;
	rcRectCircle.x = pos2.x; rcRectCircle.y = pos2.y;
	rcRectCircle.vx = move.x; rcRectCircle.vy = move.y;
	rcRectCircle.r = r2;
	return 0;
}

int CheckHit(F_CIRCLE* pcrCircle, F_RECT_CIRCLE* prcRectCircle) // Collision チェック 
{
	int nResult = false;
	float dx, dy; // 位置の差分 
	float t;
	float mx, my; // 最小の距離を与える座標 
	float ar; // 2 半径を足したもの 
	float fDistSqr;
	dx = pcrCircle->x - prcRectCircle->x; // ⊿ｘ 
	dy = pcrCircle->y - prcRectCircle->y; // ⊿ｙ 
	t = (prcRectCircle->vx * dx + prcRectCircle->vy * dy) / (prcRectCircle->vx * prcRectCircle->vx + prcRectCircle->vy * prcRectCircle->vy);
	if (t < 0.0f) t = 0.0f; // t の下限 
	if (t > 1.0f) t = 1.0f; // t の上限 
	mx = prcRectCircle->vx * t + prcRectCircle->x; // 最小位置を与える座標 
	my = prcRectCircle->vy * t + prcRectCircle->y;
	fDistSqr = (mx - pcrCircle->x) * (mx - pcrCircle->x) +
		(my - pcrCircle->y) * (my - pcrCircle->y); // 距離の２乗 
	ar = pcrCircle->r + prcRectCircle->r;
	if (fDistSqr < ar * ar) { // ２乗のまま比較 
		nResult = true;
	}
	return nResult;
}