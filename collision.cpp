//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 
//156行に先生に聞きたいとこアリ
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "ball.h"
#include "attack.h"
#include "input.h"
#include "countblock.h"
#include "moveblock.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define HIMELEFT	2
#define BALLACCELE	(5.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

static MOVEBLOCK* moveblock = GetMoveBlock();
static COUNTBLOCK* countblock = GetCountBlock();
PLAYER* player = GetPlayer();


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
						player->power += D3DXVECTOR2(2.0f, 0.0f);

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

		//
		
		//移動するブロックとプレイヤーの当たり判定
		
		for (int i = 0; i < MAX_MOVEBLOCK; i++)
		{
			if (CollisionBB(player->pos, moveblock[i].pos, D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(moveblock->size.x, moveblock->size.y)))
			{

				if (player->pos.y - player->size.y < moveblock[i].pos.y - (1.5f * moveblock[i].size.y))			
				{
					player->pos.y = moveblock[i].pos.y - (1.5f * moveblock[i].size.y);

					player->player_doingjump = false;
					moveblock[i].RidingPlayer = true;
					player->pos.x += moveblock[i].velocity.x;

				}
				else
				{
					player->pos.y = moveblock[i].pos.y + (1.5f * moveblock[i].size.y);
				}

				
				if (moveblock[i].velocity.y > 0.0f)
				{
					player->pos.y += moveblock[i].velocity.y;
				}

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
	dx = pcrCircle->x - prcRectCircle->x; // �凾� 
	dy = pcrCircle->y - prcRectCircle->y; // �凾� 
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