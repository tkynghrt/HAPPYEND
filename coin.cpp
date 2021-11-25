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

HRESULT InitCoin(void)
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
	return S_OK;
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