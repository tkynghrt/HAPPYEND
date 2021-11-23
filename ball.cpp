//=============================================================================
//
// ボール処理 [Ball.cpp]
// Author : 
//
//=============================================================================
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "Attack.h"
#include "ground.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static BALL Ball;							// バレット構造体
PLAYER* player = GetPlayer();		// プレイヤーのポインターを初期化
//BALL* ball = GetBall();		// バレットのポインターを初期化
ATTACK* attack = GetAttack();
static GROUND* ground = GetGround();


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBall(void)
{

	int BallTexture = LoadTexture("data/TEXTURE/tako.png");
	int ShadowTexture = LoadTexture("data/TEXTURE/kage.png");

	// ボール構造体の初期化
	
		Ball.mode   = 1;
		Ball.size = D3DXVECTOR2(40.0f, 40.0f);
		Ball.pos   = D3DXVECTOR2(300, 300.0f);
		Ball.rot   = 0.0f;
		Ball.BallTexture = BallTexture;
		Ball.ShadowTexture = ShadowTexture;
		Ball.move = D3DXVECTOR2(0.0f, 0.0f);	// 移動量を初期化
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
	// 回転させる
	//g_Ball.rot += 0.5f;
	
	switch(Ball.mode)
	{
	case 0:
		break;
	case 1:
		Ball.move.y += 0.5f;

		break;
	case 2:
		if (Ball.move.x >= 50 || -50 > Ball.move.x)
		{}
		else
		{
			Ball.move.y += 0.5f;
		}
		break;
				
	}
	if (Ball.move.x > BALL_SPEED_MAX)
	{
		Ball.move.x = BALL_SPEED_MAX;
	}

	//位置更新
	Ball.pos += Ball.move;




	// 画面端に行ったとき
	if (Ball.pos.y < 70) {
		Ball.pos.y = 70;
		Ball.move.y *= -1;
	}
	if (Ball.pos.x > 940) {
		Ball.pos.x = 940;
		Ball.move.x *= -1;
	}
	if (Ball.pos.x < 20) {
		Ball.pos.x = 20;
		Ball.move.x *= -1;
	}
	if (Ball.pos.y > SCREEN_HEIGHT - ground->size.y - (Ball.size.y / 2)) {
		Ball.pos.y = SCREEN_HEIGHT - ground->size.y - (Ball.size.y / 2);
		Ball.move.y *= -1;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBall(void)
{
		if (Ball.mode >= 1)	// このバレットが使われている？
		{								// Yes
			//バレットの位置やテクスチャー座標を反映
			float px = Ball.pos.x;	// バレットの表示位置X
			float py = Ball.pos.y;	// バレットの表示位置Y
			float pw = Ball.size.x;		// バレットの表示幅
			float ph = Ball.size.y;		// バレットの表示高さ
			float mx = Ball.move.x;	// バレットの移動量XY
			float my = Ball.move.y;
			float pr = Ball.rot;	//角度
			float BallShadow = 3;				//ボールの残像を引き延ばす倍率
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



			switch (Ball.mode)
			{
			case 0:
				break;
			case 1:
				DrawSpriteColorRotate(Ball.BallTexture, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				
				break;
			case 2:


				if (Ball.move.x >= 50 || -50 > Ball.move.x)
				{
					if (Ball.move.y >= 50 || -50 > Ball.move.y)
					{
						if (Ball.move.x > 0) 
						{
							BallShadow = BallShadow * 1.4;
							if (Ball.move.y > 0)
							{
								pr = 0.77;
							}
							if (Ball.move.y < 0)
							{
								pr = -0.77;
							}
						}
						else
						{
							BallShadow = BallShadow * 1.4;
							if (Ball.move.y > 0)
							{
								pr = -0.77;
							}
							if (Ball.move.y < 0)
							{
								pr = 0.77;
							}
						}
					}
						if (Ball.move.x < 0) {
							DrawSpriteColorRotate(Ball.ShadowTexture, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * -BallShadow, 40.0f,
								0.0f, 0.0f, 1.0f, 0.4f, col,
								pr);
						}
						else
						{
							DrawSpriteColorRotate(Ball.ShadowTexture, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * BallShadow, 40.0f,
								0.0f, 0.6f, 1.0f, 0.3f, col,pr);
						}
					
				}
				DrawSpriteColorRotate(Ball.BallTexture, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				break;
			}
		}

}


//=============================================================================
// バレット構造体の先頭アドレスを取得
//=============================================================================
BALL* GetBall(void)
{
	return &Ball;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBall(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power)
{
	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	
			Ball.mode = mode;			// 使用状態へ変更する
			Ball.pos = pos;			// 座標をセット
			Ball.move = power;			//速度を入力
			return;							// 1発セットしたので終了する
}


D3DXVECTOR2* GetBallPos()
{
	return &Ball.pos;
}

D3DXVECTOR2* GetBallSize()
{
	return &Ball.size;
}

SPEED_LEVEL Speed_Level(D3DXVECTOR2 ball_move)
{
	if (Ball.move.x < 0 && Ball.move.x <= 8)
		return level_1;
	if (Ball.move.x < 8 && Ball.move.x <= 16)
		return level_2;
	if (Ball.move.x < 16 && Ball.move.x <= 26)
		return level_3;
	if (Ball.move.x < 26 && Ball.move.x <= 40)
		return level_4;
	if (Ball.move.x < 40 && Ball.move.x <= BALL_SPEED_MAX)
		return level_5;

	return SPEED_LEVEL();
}
