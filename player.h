/*==============================================================================

   頂点管理[polygon.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// プレイヤー構造体
struct PLAYER
{
	bool					use;					// true:使っている  false:未使用
	D3DXVECTOR2				size;					// 幅と高さ
	D3DXVECTOR2				pos;					// ポリゴンの座標
	D3DXVECTOR2				velocity;				// ブロックに乗ってるときの加速
	float					rot;					// ポリゴンの回転量
	int						HimeTexture;			// テクスチャの種類
	int						texNo2;

	//int texcont;
	//int tex;

	int                     hp;
	int						animation;
	D3DXVECTOR2				move;
	D3DXVECTOR2				power;
	float					gravity;
	bool					player_doingjump;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
int GetPlayer_Direction(void);