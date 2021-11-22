#pragma once

#include "main.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_MAX			(99999)		// スコアの最大値
#define SCORE_DIGIT			(5)			// 桁数

HRESULT InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();

void AddScore(int Score);
void SetScore(int Score);
