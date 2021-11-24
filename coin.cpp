#include "coin.h"
#include "collision.h"
#include "All_Gimmick_Pos.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"


static BALL* Ball = GetBall();
static GIMMICK_POS* All_Gimmick_Pos = GetGimmick_Pos();


COIN coin[MAX_COIN];

void InitCoin(void)
{

	for (int i = 0; i < MAX_COIN; i++)
	{
		coin[i].Texture = LoadTexture("data/TEXTURE/coin.png");
		coin[i].size.x = 60.0f;
		coin[i].size.y = 60.0f;
		coin[i].pos = All_Gimmick_Pos[i].coin;
		coin[i].rot = 0.0f;
		coin[i].point = 10;
		coin[i].Use = true;
	}
}
void UninitCoin(void)
{

}
void UpdateCoin(void)
{
	if (coin[0].Use)
	{
		//ƒ{[ƒ‹‚ª“–‚½‚Á‚½Žž
		if (CollisionBB(Ball->pos, coin[0].pos, D3DXVECTOR2(Ball->size.x, Ball->size.y), D3DXVECTOR2(coin[0].size.x, coin[0].size.y)))
		{
				coin[0].Use = false;	
		}
	}
}
void DrawCoin(void)
{
	D3DXCOLOR coinCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (coin[0].Use)
	{
		//for (int i = 0; i < MAX_COIN; i++)
		//{
		DrawSpriteColorRotate(coin[0].Texture, coin[0].pos.x, coin[0].pos.y,
			coin[0].size.x, coin[0].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			coinCol, coin[1].rot);
		//}
	}
}