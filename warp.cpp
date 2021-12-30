#include "warp.h"
#include "texture.h"
#include "sprite.h"

WARP warp[MAX_WARP];

HRESULT InitWarp(void)
{
	for (int i = 0; i < MAX_WARP; i++)
	{
		warp[i].use = false;
		//warp[i].Texture = warpTexture3;
		warp[i].size = D3DXVECTOR2(60.0f, 60.0f);
	}
	return S_OK;
}

void UninitWarp(void)
{

}

void UpdateWarp(void)
{

}

void DrawWarp(void)
{
	D3DXCOLOR WarpCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < MAX_WARP; i++)
	{
		if (warp[i].use)
		{
			DrawSpriteColorRotate(warp[i].Texture, warp[i].pos.x, warp[i].pos.y,
				warp[i].size.x, warp[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
				WarpCol,0.0f);
		}
		else
		{
			break;
		}
	}
}

void SetWarp(D3DXVECTOR2 pos)
{
	for (int i = 0; i < MAX_WARP; i++)
	{
		//‚Ü‚¾•\Ž¦‚³‚ê‚Ä‚¢‚È‚¢êŠ‚ð’T‚·
		if (!warp[i].use)
		{
			warp[i].pos = pos;
			warp[i].use = true;
			break;
		}
	}
}

WARP* GetWarp(void)
{
	return nullptr;
}
