#include "All_Gimmick.h"
#include "Target_Normal.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
static GIMMICK_POS* All_Normal_Target = GetNormal_Target();
TARGET_NORMAL Normal[TARGET_MAX];
//*****************************************************************************
// グローバル変数
//*****************************************************************************




//=============================================================================
// 初期化処理
//=============================================================================
void InitTarget_Normal(void)
{
	// 普通のターゲット構造体の初期化
	for (int i = 0; i < TARGET_MAX; i++)
	{
		Normal[i].Tex = LoadTexture("data/TEXTURE/Target.png");
		Normal[i].Bom = LoadTexture("data/TEXTURE/explosion.png");
		Normal[i].pos = All_Normal_Target[i].normal_target_pos;
		Normal[i].old_pos = Normal[i].pos;
		Normal[i].size.x = 70.0f;
		Normal[i].size.y = 70.0f;
		Normal[i].rot = 0.0f;
		Normal[i].flame = 0;
		Normal[i].normal_target_count = 0;
		Normal[i].use = true;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTarget_Normal(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTarget_Normal(void)
{
	

	for (int i = 0; i < TARGET_MAX; i++)
	{
		Normal[i].old_pos = Normal[i].pos;

		if (Normal[i].use == false)
		{
			if (Normal[i].normal_target_count >= 1)
			{
				Normal[i].normal_target_count++;
				if (Normal[i].flame >= 16)
				{
					Normal[i].flame = 0;
					Normal[i].normal_target_count = 0;
					return;
				}
				Normal[i].flame += 1;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTarget_Normal(void)
{
	D3DXCOLOR Target_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < TARGET_MAX; i++)
	{
		if (Normal[i].use)
		{
			DrawSpriteColorRotate(Normal[i].Tex,
				Normal[i].pos.x, Normal[i].pos.y,
				Normal[i].size.x, Normal[i].size.y,
				0.0f, 0.0f,
				1.0f, 1.0f,
				Target_col, Normal[i].rot);
		}
		else
		{
			DrawSpriteColorRotate(Normal[i].Bom,
				Normal[i].pos.x, Normal[i].pos.y,
				Normal[i].size.x, Normal[i].size.y,
				Normal[i].flame % 4 * 0.25, Normal[i].flame / 4 * 0.25,
				0.25f, 0.25f,
				Target_col, Normal[i].rot);
		}
	}
}

//=============================================================================
// バレット構造体の先頭アドレスを取得
//=============================================================================
TARGET_NORMAL* GetTarget_Normal(void)
{
	for (int i = 0; i < TARGET_MAX; i++)
	{
		return &Normal[i];
	}
}