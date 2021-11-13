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

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************


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

int space = 0;
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
	if (space > 0)//当たり判定が消えていればカウントを進め消えて居なければ実行
	{
		space--;
	}
	else
	{
		if (ball->mode >= 1)
		{
			if (attack->mode == 1)
			{
				InitShapes(attack->pos, attack->h - 35, ball->pos, ball->h - 20, D3DXVECTOR2(-ball->move.x, -ball->move.y));//-35-20判定を小さめにする

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
							space = 20;//20フレーム当たり判定を消す
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
							space = 20;//20フレーム当たり判定を消す
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
						space = 20;//20フレーム当たり判定を消す
					}
				}
			}
		}

		if (ball->mode >= 1)
		{
			if (attack->mode == 2)
			{
				InitShapes(attack->pos, attack->h -35, ball->pos, ball->h -20, D3DXVECTOR2 (-ball->move.x, -ball->move.y));//-35-20判定を小さめにする

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
					space = 20; // 20フレーム当たり判定を消す
				}
			}
		}
		// 自分と敵の弾(BC)

		// 死亡したら状態遷移
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