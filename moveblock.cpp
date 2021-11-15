#include "moveblock.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

#define MAXMOVEBLOCK	10

MOVEBLOCK moveblock[MAXMOVEBLOCK];
int FlameCount = 0;

void InitMoveBlock(void)
{
	

	for (int i = 0; i < MAXMOVEBLOCK; i++)
	{
		moveblock[i].Texture = LoadTexture("data/TEXTURE/green.png");
		moveblock[i].pos.x = 0.0f;
		moveblock[i].pos.y = 0.0f;
		moveblock[i].size.x = 100.0f;
		moveblock[i].size.y = 100.0f;
		moveblock[i].velocity.x = 0.0f;
		moveblock[i].velocity.y = 0.0f;
		moveblock[i].rot = 0.0f;
		//moveblock[i].Use = false;
	
	}
}

void UninitMoveBlock(void)
{
	
}

void UpdateMoveBlock(void)
{
	moveblock[1].pos.x = 500;
	moveblock[1].pos.y = 200;

	

}

void DrawMoveBlock(void)
{
	D3DXCOLOR MoveBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



	for (int i = 0; i < 10; i++)
	{
		
			DrawSpriteColorRotate(moveblock[i].Texture, moveblock[i].pos.x, moveblock[i].pos.y,
				moveblock[i].size.x, moveblock[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
				MoveBlockCol, moveblock[i].rot);
		
	}
}

void setMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity)
{
	for (int i = 0; i < 10; i++)
	{
		if (!moveblock[i].Use)
		{
			moveblock[i].pos = pos;
			moveblock[i].size = size;
			moveblock[i].velocity = velocity;
			moveblock[i].Use = true;
			break;
		}
	}
}
