#include "coin.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"


static BALL* Ball = GetBall();

COIN coin[MAX_COIN];

void InitCoin(void)
{

	for (int i = 0; i < MAX_COIN; i++)
	{
		//coin[i].Texture = LoadTexture("data/TEXTURE/ScoreUp.png");
		coin[i].Texture = LoadTexture("data/TEXTURE/coin.png");
		coin[i].size = D3DXVECTOR2(60.0f, 60.0f);
		coin[i].Use = false;
	}
	
}
void UninitCoin(void)
{

}
void UpdateCoin(void)
{
	
}
void DrawCoin(void)
{
	D3DXCOLOR coinCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < MAX_COIN; i++)
	{
		if (coin[i].Use)
		{
			for (int i = 0; i < MAX_COIN; i++)
			{
				DrawSpriteColorRotate(coin[i].Texture, coin[i].pos.x, coin[i].pos.y,
					coin[0].size.x, coin[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
					coinCol, coin[i].rot);
			}
		}
	}
}

COIN* GetCoin(void)
{
	for (int i = 0; i < MAX_COIN; i++)
	{
		return &coin[i];
	}
}

void SetCoin(D3DXVECTOR2 pos)
{

}