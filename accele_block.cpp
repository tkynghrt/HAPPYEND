#include "accele_block.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

ACCELE_BLOCK accele_block[MAX_ACCELE_BLOCK];

void InitAcceleBlock(void)
{
	accele_block[0].pos.x = 800.0f;
	accele_block[0].pos.y = 500.0f;
	accele_block[0].Texture = LoadTexture("data/TEXTURE/pink.png");
	accele_block[0].size.x = 60.0f;
	accele_block[0].size.y = 60.0f;
	accele_block[0].rot = 0.0f;
	accele_block[0].HitCount = 10;
	accele_block[0].Use = true;
}

void UninitAcceleBlock(void)
{
}

void UpdateAcceleBlock(void)
{
	//switch()
}

void DrawAcceleBlock(void)
{
}

ACCELE_BLOCK* GetAcceleBlock(void)
{
	return &accele_block[0];
}
