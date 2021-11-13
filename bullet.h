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
#define BULLET_SPEED	(4.0f)		// バレットの移動スピード


// バレット構造体
struct BULLET
{
	int						mode;					// ボールの状態
	float					w, h;					// 幅と高さ
	D3DXVECTOR2				pos;					// バレットの座標
	float					rot;					// バレットの回転量
	D3DXVECTOR2				move;					// バレットの移動量
	int						texNo;					// 何番目のテクスチャーを使用するのか
	int						texNo2;
	
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(void);
void SetBullet(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power);


