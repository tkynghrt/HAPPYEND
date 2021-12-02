//=============================================================================
//
// ボール処理 [Ball.cpp]
// Author : 
//
//=============================================================================
#include "input.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "ground.h"
#include "collision.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	level_1		0
#define	level_2		1
#define	level_3		2
#define	level_4		3
#define	level_5		4


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static BALL Ball;							// バレット構造体
PLAYER* player = GetPlayer();		// プレイヤーのポインターを初期化
int Player_Direction = GetPlayer_Direction();
//BALL* ball = GetBall();		// バレットのポインターを初期化
static GROUND* ground = GetGround();

F_OLD_SURFACE CollisionKOBA(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
							D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size);

float reflect;				//跳ね返る角度

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBall(void)
{
	// ボール構造体の初期化

	Ball.BallTexture = LoadTexture("data/TEXTURE/tako.png");
	Ball.size = D3DXVECTOR2(40.0f, 40.0f);
	Ball.pos   = D3DXVECTOR2(player->pos.x, player->pos.y + 20.0f);
	Ball.old_pos  = Ball.pos;
	Ball.rot   = 0.0f;
	Ball.speed = 0.0f;
	Ball.velocity = D3DXVECTOR2(0.0f, 0.0f);	// 移動量を初期化
	Ball.Speed_Level = level_1;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBall(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBall(void)
{
	Ball.old_pos = Ball.pos;
	reflect = atan2f(GetThumbRightY(0), GetThumbRightX(0));
	
	switch (CollisionKOBA(Ball.pos, player->pos, Ball.old_pos, player->old_pos, Ball.size, D3DXVECTOR2(player->size.x + 20.0f, player->size.y)))
	{
	case F_OLD_SURFACE::right:
		
		if (Player_Direction == DIRECTION_RIGHT)
		{
			if (GetThumbRightX(0) || GetThumbRightY(0))
			{
				Ball.speed += BALL_SPEED;

				if (reflect != 0.0f  /*&& 向き変えるよフラグ*/ )
				{

					Ball.velocity.x = Ball.speed * cosf(reflect);
					Ball.velocity.y = Ball.speed * sinf(reflect);
					reflect = 0.0f;
				}
			}
		}
		break;

	case  F_OLD_SURFACE::left:
		
		if (Player_Direction == DIRECTION_LEFT)
		{
			if (GetThumbLeftX(0) || GetThumbLeftY(0))
			{
				Ball.speed += BALL_SPEED;

				if (reflect != 0.0f  /*&& 向き変えるよフラグ*/)
				{

					Ball.velocity.x = Ball.speed * cosf(reflect);
					Ball.velocity.y = Ball.speed * sinf(reflect);
					reflect = 0.0f;
				}
			}
		}
		break;
	}




	//位置更新
	Ball.pos += Ball.velocity;

	//ボールのスピードレベル
	if (Ball.velocity.x > 0 && Ball.velocity.x <= 8)
		Ball.Speed_Level = level_1;
	if (Ball.velocity.x > 8 && Ball.velocity.x <= 16)
		Ball.Speed_Level = level_2;
	if (Ball.velocity.x > 16 && Ball.velocity.x <= 26)
		Ball.Speed_Level = level_3;
	if (Ball.velocity.x > 26 && Ball.velocity.x <= 40)
		Ball.Speed_Level = level_4;
	if (Ball.velocity.x > 40 && Ball.velocity.x <= BALL_SPEED_MAX)
		Ball.Speed_Level = level_5;

	if (Ball.speed > BALL_SPEED_MAX)
	{
		Ball.speed = BALL_SPEED_MAX;
	}

	// 画面端に行ったとき
	if (Ball.pos.y < 20) {
		Ball.pos.y = 20;
		Ball.velocity.y *= -1;
	}
	if (Ball.pos.x > 940) {
		Ball.pos.x = 940;
		Ball.velocity.x *= -1;
	}
	if (Ball.pos.x < 20) {
		Ball.pos.x = 20;
		Ball.velocity.x *= -1;
	}
	if (Ball.pos.y > SCREEN_HEIGHT - ground->size.y - (Ball.size.y / 2)) {
		Ball.pos.y = SCREEN_HEIGHT - ground->size.y - (Ball.size.y / 2);
		Ball.velocity.y *= -1;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBall(void)
{
	D3DXCOLOR BallCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	DrawSpriteColorRotate(Ball.BallTexture, Ball.pos.x, Ball.pos.y,
		Ball.size.x, Ball.size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		BallCol, Ball.rot);

}


//=============================================================================
// バレット構造体の先頭アドレスを取得
//=============================================================================
BALL* GetBall(void)
{
	return &Ball;
}


