#pragma once

#include "main.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_MAX			(99999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT			(5)			// ����

HRESULT InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();

void AddScore(int Score);
void SetScore(int Score);
