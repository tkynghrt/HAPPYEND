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

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static BALL g_Ball;							// バレット構造体
PLAYER* player = GetPlayer();		// プレイヤーのポインターを初期化
//BALL* ball = GetBall();		// バレットのポインターを初期化
ATTACK* attack = GetAttack();


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBall(void)
{

	int BallTexture = LoadTexture("data/TEXTURE/tako.png");
	int ShadowTexture = LoadTexture("data/TEXTURE/kage.png");

	// ボール構造体の初期化
	
		g_Ball.mode   = 1;
		g_Ball.size = D3DXVECTOR2(40.0f, 40.0f);
		g_Ball.pos   = D3DXVECTOR2(300, 300.0f);
		g_Ball.rot   = 0.0f;
		g_Ball.BallTexture = BallTexture;
		g_Ball.ShadowTexture = ShadowTexture;
		g_Ball.move = D3DXVECTOR2(0.0f, 0.0f);	// 移動量を初期化
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
	
	switch(g_Ball.mode)
	{
	case 0:
		break;
	case 1:
		g_Ball.move.y += 0.5f;

		break;
	case 2:
		if (g_Ball.move.x >= 50 || -50 > g_Ball.move.x)
		{}
		else
		{
			g_Ball.move.y += 0.5f;
		}
		break;
				
	}
	if (g_Ball.move.x > BALL_SPEED_MAX)
	{
		g_Ball.move.x = BALL_SPEED_MAX;
	}

	//位置更新
	g_Ball.pos += g_Ball.move;




	// 画面端に行ったとき
	if (g_Ball.pos.y < 70) {
		g_Ball.pos.y = 70;
		g_Ball.move.y *= -1;
	}
	if (g_Ball.pos.x > 940) {
		g_Ball.pos.x = 940;
		g_Ball.move.x *= -1;
	}
	if (g_Ball.pos.x < 20) {
		g_Ball.pos.x = 20;
		g_Ball.move.x *= -1;
	}
	if (g_Ball.pos.y > 500) {
		g_Ball.pos.y = 500;
		g_Ball.move.y *= -1;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBall(void)
{
		if (g_Ball.mode >= 1)	// このバレットが使われている？
		{								// Yes
			//バレットの位置やテクスチャー座標を反映
			float px = g_Ball.pos.x;	// バレットの表示位置X
			float py = g_Ball.pos.y;	// バレットの表示位置Y
			float pw = g_Ball.size.x;		// バレットの表示幅
			float ph = g_Ball.size.y;		// バレットの表示高さ
			float mx = g_Ball.move.x;	// バレットの移動量XY
			float my = g_Ball.move.y;
			float pr = g_Ball.rot;	//角度
			float BallShadow = 3;				//ボールの残像を引き延ばす倍率
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



			switch (g_Ball.mode)
			{
			case 0:
				break;
			case 1:
				DrawSpriteColorRotate(g_Ball.BallTexture, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				
				break;
			case 2:


				if (g_Ball.move.x >= 50 || -50 > g_Ball.move.x)
				{
					if (g_Ball.move.y >= 50 || -50 > g_Ball.move.y)
					{
						if (g_Ball.move.x > 0) 
						{
							BallShadow = BallShadow * 1.4;
							if (g_Ball.move.y > 0)
							{
								pr = 0.77;
							}
							if (g_Ball.move.y < 0)
							{
								pr = -0.77;
							}
						}
						else
						{
							BallShadow = BallShadow * 1.4;
							if (g_Ball.move.y > 0)
							{
								pr = -0.77;
							}
							if (g_Ball.move.y < 0)
							{
								pr = 0.77;
							}
						}
					}
						if (g_Ball.move.x < 0) {
							DrawSpriteColorRotate(g_Ball.ShadowTexture, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * -BallShadow, 40.0f,
								0.0f, 0.0f, 1.0f, 0.4f, col,
								pr);
						}
						else
						{
							DrawSpriteColorRotate(g_Ball.ShadowTexture, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * BallShadow, 40.0f,
								0.0f, 0.6f, 1.0f, 0.3f, col,pr);
						}
					
				}
				DrawSpriteColorRotate(g_Ball.BallTexture, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				break;
			}
		}

}


//=============================================================================
// バレット構造体の先頭アドレスを取得
//=============================================================================
BALL* GetBall(void)
{
	return &g_Ball;
}

//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBall(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power)
{
	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	
			g_Ball.mode = mode;			// 使用状態へ変更する
			g_Ball.pos = pos;			// 座標をセット
			g_Ball.move = power;			//速度を入力
			return;							// 1発セットしたので終了する
}


D3DXVECTOR2* GetBallPos()
{
	return &g_Ball.pos;
}

D3DXVECTOR2* GetBallSize()
{
	return &g_Ball.size;
}

SPEED_LEVEL Speed_Level(D3DXVECTOR2 ball_move)
{
	if (g_Ball.move.x < 0 && g_Ball.move.x <= 8)
		return level_1;
	if (g_Ball.move.x < 8 && g_Ball.move.x <= 16)
		return level_2;
	if (g_Ball.move.x < 16 && g_Ball.move.x <= 26)
		return level_3;
	if (g_Ball.move.x < 26 && g_Ball.move.x <= 40)
		return level_4;
	if (g_Ball.move.x < 40 && g_Ball.move.x <= BALL_SPEED_MAX)
		return level_5;

	return SPEED_LEVEL();
}
