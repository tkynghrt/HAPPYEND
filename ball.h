//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BALL_SPEED	(2.0f)		// ボールの移動スピード
#define BALL_SPEED_MAX	(52.0f)

// ボール構造体
struct BALL
{
	D3DXVECTOR2				size;					// 幅と高さ
	D3DXVECTOR2				pos;					// バレットの座標
	D3DXVECTOR2				old_pos;				//過去の バレットの座標
	float					rot;					// バレットの回転量
	D3DXVECTOR2				velocity;					// バレットの移動量
	float					speed;
	int						BallTexture;
	int						Speed_Level;
	bool					Use;
	int						Judgment;
	int						judgment_time;
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);

BALL *GetBall(void);



