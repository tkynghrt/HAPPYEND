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
#define BALL_SPEED	(4.0f)		// ボールの移動スピード


// ボール構造体
struct BALL
{
	int						mode;					// ボールの状態
	D3DXVECTOR2				size;					// 幅と高さ
	D3DXVECTOR2				pos;					// バレットの座標
	float					rot;					// バレットの回転量
	D3DXVECTOR2				move;					// バレットの移動量
	int						BallTexture;
	int						ShadowTexture;
	
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);

BALL *GetBall(void);
void SetBall(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power);

D3DXVECTOR2* GetBallPos();
D3DXVECTOR2* GetBallSize();



