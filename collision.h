//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : 
//
//=============================================================================
#pragma once

#define PI 3.14159265f // 円周率
#define VIEW_WIDTH 640 // 画面幅 
#define VIEW_HEIGHT 480 // 画面高さ 
#define CIRCLE_VEL 5.0f // 円形速さ 
struct F_CIRCLE {
	float x, y; // 中心位置 
	float r; // 半径 
};
struct F_RECT_CIRCLE {
	float x, y; // 始点位置 
	float vx, vy; // ベクトル 
	float r; // 当たりサイズ 
};
//こばの当たり判定
enum class F_OLD_SURFACE{
	no_hit,
	up,
	right,
	left,
	down
};

//こば2
enum class CHECK_HIT{
	no_hit,
	hit
};

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HIMELEFT	2
#define BALLACCELE	(2.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void UpdateCollision(void);
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
F_OLD_SURFACE CollisionKOBA(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos, 
							D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size);

F_OLD_SURFACE CollisionKOBA2(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
	D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size, D3DXVECTOR2 block_velocity);


