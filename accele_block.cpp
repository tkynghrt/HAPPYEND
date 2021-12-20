#include "accele_block.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

ACCELE_BLOCK accele_block[MAX_ACCELE_BLOCK];



HRESULT InitAcceleBlock(void)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		
		accele_block[i].Texture = LoadTexture("data/TEXTURE/accele_block.png");
		accele_block[i].size = D3DXVECTOR2(60.0f, 60.0f);
		accele_block[i].use = false;
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
		if (accele_block[i].use)
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

void SetAcceleBlock(D3DXVECTOR2 pos, int level)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		//‚Ü‚¾•\Ž¦‚³‚ê‚Ä‚¢‚È‚¢êŠ‚ð’T‚·
		if (!accele_block[i].use)
		{
			accele_block[i].pos = pos;
			accele_block[i].level = level;
			accele_block[i].use = true;
			break;
		}
	}
}