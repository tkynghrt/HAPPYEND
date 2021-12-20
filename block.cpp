#include "block.h"
#include "map.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"


static BLOCK Block[MAX_BLOCK];

HRESULT InitBlock(void)
{
	for (int i = 0; i < 30; i++)
	{
		Block[i].Texture = LoadTexture("data/TEXTURE/black.jpeg");
		Block[i].pos = D3DXVECTOR2(100.0f,300.0f);
		Block[i].pos = D3DXVECTOR2(0.0f,0.0f);
		Block[i].size = D3DXVECTOR2(40.0f,40.0f);
		Block[i].Use = true;
		Block[i].rot = 0.0f;
	}
	Block[1].pos  = D3DXVECTOR2(30.0f, SCREEN_HEIGHT - Block[0].size.y * 10);
	Block[2].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 1),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[3].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 2),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[4].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 3),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[5].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 4),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[6].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 5),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[7].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 6),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[8].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 7),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[9].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 8),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[10].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 9),  (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[11].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 10), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[12].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 11), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[13].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 12), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[14].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 13), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[15].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 14), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[16].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 15), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[17].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 16), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[18].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 17), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[19].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 18), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[20].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 19), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);
	Block[21].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 10);

	Block[0].pos  = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 1);
	Block[22].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 2);
	Block[23].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 3);
	Block[24].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 4);
	Block[25].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 4);
	Block[26].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 6);
	Block[27].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 7);
	Block[28].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 8);
	Block[29].pos = D3DXVECTOR2(30.0f + (Block[0].size.x * 20), (SCREEN_HEIGHT - 30.0f) - Block[0].size.y * 9);
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

	for (int i = 0; i < 22; i++)
	{
		DrawSpriteColorRotate(Block[i].Texture, Block[i].pos.x, Block[i].pos.y,
			Block[i].size.x, Block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			BlockCol, Block[i].rot);
	}
}
BLOCK* GetBlock(void)
{
	return Block;
}

void SetBlock_1(D3DXVECTOR2 pos)
{
	Block[0].pos = pos;
}
