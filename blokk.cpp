#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "blokk.h"
#include "player.h"

static BLOKK g_blokk[BLOKK_X][BLOKK_Y];
//unsigned int g_blokkTexture;

void InitBlokk(void)
{
	

	for (int x = 0; x < BLOKK_X; x++)
	{
		for (int y = 0; y < BLOKK_Y; y++)
		{
			g_blokk[x][y].pos = D3DXVECTOR2((20 * x)+250, (20 * y)+50);
			g_blokk[x][y].size = 20.0f;
			g_blokk[x][y].isUse = false;
			g_blokk[x][y].texNo = LoadTexture("data/TEXTURE/ƒuƒƒbƒN02.png");
			g_blokk[x][y].nam = 0;
		}
	}
	for (int x = 0; x < BLOKK_X; x++)
	{
		g_blokk[x][21].isUse = true;
	}
	for (int y = 0; y < BLOKK_Y; y++)
	{
		g_blokk[0][y].isUse = true;
	}
	for (int y = 0; y < BLOKK_Y; y++)
	{
		g_blokk[21][y].isUse = true;
	}
}

void UninitBlokk(void)
{

}

void UpdateBlokk(void)
{
	//Float2 playerPosition = GetPlayerPosition();

	/*for (int x = 0; x < BLOKK_X; x++)
	{
		for (int y = 0; y < BLOKK_Y; y++)
		{
			if (g_blokk[x][y].isUse)
			{
				g_blokk[x][y].pos;


			}


		}
	}*/



		/*if (g_bullet[i].pos.y > 560.0f - 100.0f)
		{
			g_bullet[i].pos.y = 560.0f + 100.0f;
			g_bullet[i].vel.y *= -1.0f;

		}*/


		
}

void DrawBlokk(void)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	for (int x = 0; x < BLOKK_X; x++)
	{
		for (int y = 0; y < BLOKK_Y; y++)
		{
			if (g_blokk[x][y].isUse)
			{
					DrawSpriteColorRotate(g_blokk[x][y].texNo, g_blokk[x][y].pos.x, g_blokk[x][y].pos.y, g_blokk[x][y].size,
						g_blokk[x][y].size, 
						g_blokk[x][y].nam % 4 * 0.25f,
						g_blokk[x][y].nam / 4 * 0.25f,
						0.25f,0.25f, col, 0);
			}
		}
	}
}

BLOKK* GetBlokk(void)
{
	return &g_blokk[0][0];
}

void SetBlokk(int x, int y, int c)
{
	g_blokk[x][y].isUse = true;
	g_blokk[x][y].nam = c;
}