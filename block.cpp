#include "block.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"

static BLOCK block[MAX_BLOCK] = {};
static PLAYER* player = GetPlayer();

HRESULT InitBlock(void)
{

	for (int i = 0; i < MAX_BLOCK; i++)
	{
		block[i].Texture = LoadTexture("data/TEXTURE/Block.png");
		block[i].size = D3DXVECTOR2(60.0f, 60.0f);
		block[i].rot = 0.0f;
		block[i].Use = false;
	}
	return S_OK;
}

void UninitBlock(void)
{

}

void UpdateBlock(void)
{
	

}

void DrawBlock(void)
{
	D3DXCOLOR BlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (block[i].Use)
		{
				DrawSpriteColorRotate(block[i].Texture, block[i].pos.x, block[i].pos.y,
					block[i].size.x, block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
					BlockCol, block[i].rot);
			
		}
		else
		{
			break;
		}
	}
}




BLOCK* GetBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		return &block[i];
	}
	
}

void SetBlock(D3DXVECTOR2 pos)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		//‚Ü‚¾•\Ž¦‚³‚ê‚Ä‚¢‚È‚¢êŠ‚ð’T‚·
		if (!block[i].Use)
		{
			block[i].pos = pos;
			block[i].Use = true;
			break;
		}
	}
}