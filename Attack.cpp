//=============================================================================
//
// 攻撃処理 [Attack.cpp]
// Author : 
//
//=============================================================================
#include "Attack.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static ATTACK g_Attack;							// バレット構造体
int count;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitAttack(void)
{
	int texNo = LoadTexture("data/TEXTURE/explosion.png");
	int texNo2 = LoadTexture("data/TEXTURE/explosion02.png");

	// バレット構造体の初期化

	g_Attack.mode = 0;
	g_Attack.w = 50.0f;
	g_Attack.h = 50.0f;
	g_Attack.pos = D3DXVECTOR2(300, 300.0f);
	g_Attack.rot = 0.0f;
	g_Attack.texNo = texNo;
	g_Attack.texNo2 = texNo2;
	g_Attack.move = D3DXVECTOR2(0.0f, 0.0f);	// 移動量を初期化
	g_Attack.flame = 0;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitAttack(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateAttack(void)
{
	switch (g_Attack.mode)
	{
	case 0:
		break;
	case 1:
		count++;
		if (count >= 1)
		{
			if (g_Attack.flame >= 16)
			{
				g_Attack.mode = 0;
				g_Attack.flame = 0;
			}
			g_Attack.flame += 1;
			count = 0;
		}
		break;
	case 2:
		count++;
		if (count >= 1)
		{
			if (g_Attack.flame >= 16)
			{
				g_Attack.mode = 0;
				g_Attack.flame = 0;
			}
			g_Attack.flame += 1;
			count = 0;
		}
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawAttack(void)
{

	if (g_Attack.mode >= 1)
	{
		//ボールの位置やテクスチャー座標を反映
		float px = g_Attack.pos.x;	// ボールの表示位置X
		float py = g_Attack.pos.y;	// ボールの表示位置Y
		float pw = g_Attack.w;		// ボールの表示幅
		float ph = g_Attack.h;		// ボールの表示高さ
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (g_Attack.mode)
		{
		case 0:
			break;
		case 1:


			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Attack.texNo, px, py, pw, ph,
				g_Attack.flame % 4 * 0.25, g_Attack.flame / 4 * 0.25,
				0.25f, 0.25f, col, g_Attack.rot);
			break;
		case 2:

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Attack.texNo2, px, py, pw, ph,
				g_Attack.flame % 4 * 0.25, g_Attack.flame / 4 * 0.25,
				0.25f, 0.25f, col, g_Attack.rot);
			break;
		}
	}
}


//=============================================================================
// ボール構造体の先頭アドレスを取得
//=============================================================================
ATTACK* GetAttack(void)
{
	return &g_Attack;
}


//=============================================================================
// ボールの発射設定
//=============================================================================
void SetAttack(int mode, D3DXVECTOR2 pos)
{
	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )

	g_Attack.mode = mode;			// 使用状態へ変更する
	g_Attack.pos = pos;			// 座標をセット
	g_Attack.flame = 6;
	return;							// 1発セットしたので終了する
}