//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static BULLET g_Bullet;							// バレット構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	int texNo = LoadTexture("data/TEXTURE/tako.png");
	int texNo2 = LoadTexture("data/TEXTURE/kage.png");
	// バレット構造体の初期化
	
		g_Bullet.mode   = 1;
		g_Bullet.w     = 40.0f;
		g_Bullet.h     = 40.0f;
		g_Bullet.pos   = D3DXVECTOR2(300, 300.0f);
		g_Bullet.rot   = 0.0f;
		g_Bullet.texNo = texNo;
		g_Bullet.texNo2 = texNo2;
		g_Bullet.move = D3DXVECTOR2(0.0f, 0.0f);	// 移動量を初期化
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	// 回転させる
	//g_Bullet.rot += 0.5f;
	
	switch(g_Bullet.mode)
	{
	case 0:
		break;
	case 1:
		g_Bullet.move.y += 0.5f;

		break;
	case 2:
		if (g_Bullet.move.x >= 50 || -50 > g_Bullet.move.x)
		{}
		else
		{
			g_Bullet.move.y += 0.5f;
		}
		break;
				
	}
	//位置更新
	g_Bullet.pos += g_Bullet.move;
	// 画面外まで進んだ？
	if (g_Bullet.pos.y < 70) {
		g_Bullet.pos.y = 70;
		g_Bullet.move.y *= -1;
	}
	if (g_Bullet.pos.x > 960) {
		g_Bullet.pos.x = 960;
		g_Bullet.move.x *= -1;
	}
	if (g_Bullet.pos.x < 0) {
		g_Bullet.pos.x = 0;
		g_Bullet.move.x *= -1;
	}
	if (g_Bullet.pos.y > 500) {
		g_Bullet.pos.y = 500;
		g_Bullet.move.y *= -1;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
		if (g_Bullet.mode >= 1)	// このバレットが使われている？
		{								// Yes
			//バレットの位置やテクスチャー座標を反映
			float px = g_Bullet.pos.x;	// バレットの表示位置X
			float py = g_Bullet.pos.y;	// バレットの表示位置Y
			float pw = g_Bullet.w;		// バレットの表示幅
			float ph = g_Bullet.h;		// バレットの表示高さ
			float mx = g_Bullet.move.x;	// バレットの移動量XY
			float my = g_Bullet.move.y;
			float pr = g_Bullet.rot;	//角度
			float b = 3;				//影を引き延ばす倍率
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			switch (g_Bullet.mode)
			{
			case 0:
				break;
			case 1:
				DrawSpriteColorRotate(g_Bullet.texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				
				break;
			case 2:


				if (g_Bullet.move.x >= 50 || -50 > g_Bullet.move.x)
				{
					if (g_Bullet.move.y >= 50 || -50 > g_Bullet.move.y)
					{
						if (g_Bullet.move.x > 0) 
						{
							b = b * 1.4;
							if (g_Bullet.move.y > 0)
							{
								pr = 0.77;
							}
							if (g_Bullet.move.y < 0)
							{
								pr = -0.77;
							}
						}
						else
						{
							b = b * 1.4;
							if (g_Bullet.move.y > 0)
							{
								pr = -0.77;
							}
							if (g_Bullet.move.y < 0)
							{
								pr = 0.77;
							}
						}
					}
						if (g_Bullet.move.x < 0) {
							DrawSpriteColorRotate(g_Bullet.texNo2, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * -b, 40.0f,
								0.0f, 0.0f, 1.0f, 0.4f, col,
								pr);
						}
						else
						{
							DrawSpriteColorRotate(g_Bullet.texNo2, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * b, 40.0f,
								0.0f, 0.6f, 1.0f, 0.3f, col,
								pr);
						}
					
				}
				DrawSpriteColorRotate(g_Bullet.texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				break;
			}
		}

}


//=============================================================================
// バレット構造体の先頭アドレスを取得
//=============================================================================
BULLET* GetBullet(void)
{
	return &g_Bullet;
}


//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBullet(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power)
{
	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	
			g_Bullet.mode = mode;			// 使用状態へ変更する
			g_Bullet.pos = pos;			// 座標をセット
			g_Bullet.move = power;			//速度を入力
			return;							// 1発セットしたので終了する
}

