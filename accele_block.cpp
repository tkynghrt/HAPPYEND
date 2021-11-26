#include "accele_block.h"
#include "collision.h"
#include "All_Gimmick.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

ACCELE_BLOCK accele_block[MAX_ACCELE_BLOCK];


static GIMMICK_POS* All_Accele_Block_Pos = GetAccele_Block();

HRESULT InitAcceleBlock(void)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		accele_block[i].Use = true;
		accele_block[i].Texture = LoadTexture("data/TEXTURE/accele_block.png");
		accele_block[i].size.x = 60.0f;
		accele_block[i].size.y = 60.0f;
		accele_block[i].pos = All_Accele_Block_Pos[i].accele_block_pos;
		accele_block[i].rot = 0.0f;
		accele_block[i].level = All_Accele_Block_Pos[i].accele_level;
	}
	return S_OK;
}

void UninitAcceleBlock(void)
{
}

void UpdateAcceleBlock(void)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		accele_block[i].old_pos = accele_block[i].pos;
	}
}

void DrawAcceleBlock(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		if (accele_block[i].Use)
		{
			for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
			{
				DrawSpriteColorRotate(accele_block[0].Texture, accele_block[i].pos.x, accele_block[i].pos.y,
					accele_block[i].size.x, accele_block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
					CountBlockCol, accele_block[i].rot);
			}
		}
	}
}

ACCELE_BLOCK* GetAcceleBlock(void)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		return &accele_block[i];
	}
}
