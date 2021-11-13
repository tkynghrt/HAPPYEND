#pragma once
#include "main.h"
#include "renderer.h"


// 攻撃構造体
struct ATTACK
{
	bool					use;					// true:使っている  false:未使用
	float					w, h;					// 幅と高さ
	D3DXVECTOR2				pos;					// ポリゴンの座標
	float					rot;					// ポリゴンの回転量
	int						texNo;					// 何番目のテクスチャーを使用するのか
	int						texNo2;
	D3DXVECTOR2             move;                   //速度
	int						mode;
	int						flame;
};

HRESULT InitAttack(void);
void UninitAttack(void);
void UpdateAttack(void);
void DrawAttack(void);

ATTACK *GetAttack(void);
void SetAttack(int mode, D3DXVECTOR2 pos);
