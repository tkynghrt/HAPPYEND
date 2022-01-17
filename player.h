/*==============================================================================

   頂点管理[polygon.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#define DIRECTION_LEFT		 1
#define DIRECTION_RIGHT		 2
#define DIRECTION_STAY_LEFT  3
#define DIRECTION_STAY_RIGHT 4
#define DIRECTION_JUMP_LEFT	 5
#define DIRECTION_JUMP_RIGHT 6
#define DIRECTION_HIT_LEFT   7
#define DIRECTION_HIT_RIGHT  8


#include "main.h"
#include "renderer.h"

void SetPlayer(D3DXVECTOR2 pos);
void SetSwing(int Swing);

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// プレイヤー構造体
struct PLAYER
{
	bool					use;					// true:使っている  false:未使用
	D3DXVECTOR2				size;					// 幅と高さ
	D3DXVECTOR2				pos;					// ポリゴンの座標
	D3DXVECTOR2				old_pos;				// 1フレーム前のポリゴンの座標
	float					rot;					// ポリゴンの回転量
	int						player_stay_Texture;			// テクスチャの種類
	int						player_dash_Texture;	
	int						player_jump_Texture;	
	int						player_hit_Texture;

	int						direction;


	int						animation;
	D3DXVECTOR2				move;
	D3DXVECTOR2				power;
	float					gravity;
	bool					fly;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);