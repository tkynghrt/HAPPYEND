#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "background.h"

static int		BackGroundTexture = 0;


HRESULT InitBackGround()
{
	BackGroundTexture = LoadTexture("data/TEXTURE/NieR.jpg");

	return S_OK;
}

void UninitBackGround()
{
}

void UpdateBackGround()
{
}

void DrawBackGround()
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(BackGroundTexture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
}
