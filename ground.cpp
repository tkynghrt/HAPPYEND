#include "ground.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

GROUND ground;
static PLAYER* player = GetPlayer();
static BALL* ball = GetBall();


void InitGround(void)
{
	//âÒêîÇ≈âÛÇÍÇÈÉuÉçÉbÉN

	ground.pos.x = SCREEN_WIDTH / 2;
	ground.pos.y = (SCREEN_HEIGHT / 20) * 19 ;
	ground.Texture = LoadTexture("data/TEXTURE/ground.jpeg");
	ground.size.x = SCREEN_WIDTH;
	ground.size.y = SCREEN_HEIGHT / 10;
}

void UninitGround(void)
{
}

void UpdateGround(void)
{
	
}

void DrawGround(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
		DrawSpriteColorRotate(ground.Texture, ground.pos.x, ground.pos.y,
			ground.size.x, ground.size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			CountBlockCol,0.0f);
}

GROUND* GetGround(void)
{
	return &ground;
}


