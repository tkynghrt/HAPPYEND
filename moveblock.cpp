#include "moveblock.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"




static MOVEBLOCK moveblock[MAX_MOVEBLOCK];
int MoveCount = 0;

void InitMoveBlock(void)
{
		//ˆÚ“®ƒuƒƒbƒN‚»‚Ì1
		moveblock[1].Texture = LoadTexture("data/TEXTURE/green.png");
		moveblock[1].pos.x = 500.0f;
		moveblock[1].pos.y = 400.0f;
		moveblock[1].size.x = 100.0f;
		moveblock[1].size.y = 30.0f;
		moveblock[1].velocity.x = 3.0f;
		moveblock[1].velocity.y = 0.0f;
		moveblock[1].rot = 0.0f;
		moveblock[1].RidingPlayer = false;
		
}

void UninitMoveBlock(void)
{
	
}

void UpdateMoveBlock(void)
{
	

	moveblock[1].pos.x += moveblock[1].velocity.x;
	MoveCount++;
	if (MoveCount >= 90)
	{
		moveblock[1].velocity.x *= -1;
		MoveCount = 0;
	}
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


MOVEBLOCK* GetMoveBlock(void)
{
	return &moveblock[0];
}