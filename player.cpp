/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "ball.h"
#include "xinput.h"
#include "move_block.h"
#include "count_block.h"
#include "collision.h"
#include "ball.h"
#include "score.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYERJUMP	(20.0f)
#define GRAVITY		(1.0f)
#define PLATER_SPEED (10.0f)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float frand(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static PLAYER Player;
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

static MOVE_BLOCK* move_block = GetMoveBlock();
static COUNT_BLOCK* count_block = GetCountBlock();
static BALL* ball = GetBall();


//操作キャラの画像の種類
int animation = 0;
int animation_count = 0;
static bool swing = false;
static int swing_count = 0;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	//テクスチャ読み込み
	Player.player_stay_Texture = LoadTexture("data/TEXTURE/player_stay.png");
	Player.player_dash_Texture = LoadTexture("data/TEXTURE/player_dash.png");
	Player.player_jump_Texture = LoadTexture("data/TEXTURE/player_jump.png");
	Player.player_hit_Texture = LoadTexture("data/TEXTURE/player_jump.png");

	//初期化
	Player.pos = D3DXVECTOR2(0.0f, 0.0f);
	Player.old_pos = Player.pos;
	Player.size.x = 120.0f;
	Player.size.y = 120.0f;
	Player.animation = 0;
	Player.use = true;
	Player.direction = DIRECTION_RIGHT;
	Player.move = D3DXVECTOR2(0.0f, 0.0f);
	Player.power = D3DXVECTOR2(2.0f, 0.0f);
	Player.gravity = GRAVITY;
	Player.fly = false;
	
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	Player.old_pos = Player.pos;
	if (swing_count <= 0)
	{
		swing = false;
	}
		

	//プレイヤーの向きを初期化
	switch(Player.direction)
	{
		case DIRECTION_LEFT:
			Player.direction = DIRECTION_STAY_LEFT;
			break;
		case DIRECTION_RIGHT:
			Player.direction = DIRECTION_STAY_RIGHT;
			break;
		case DIRECTION_STAY_LEFT:
			Player.direction = DIRECTION_STAY_LEFT;
			break;
		case DIRECTION_STAY_RIGHT:
			Player.direction = DIRECTION_STAY_RIGHT;
			break;
		case DIRECTION_JUMP_LEFT:
			Player.direction = DIRECTION_STAY_LEFT;
			break;
		case DIRECTION_JUMP_RIGHT:
			Player.direction = DIRECTION_STAY_RIGHT;
			break;
		case DIRECTION_HIT_LEFT:
			Player.direction = DIRECTION_STAY_LEFT;
			break;
		case DIRECTION_HIT_RIGHT:
			Player.direction = DIRECTION_STAY_RIGHT;
			break;
			
	}

	//重力
	if (!Player.fly) {
		Player.move.y = 0.0f;
	}
	Player.gravity = GRAVITY;
	Player.move.x = 0.0f;
	

	
	if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_A))
	{
		//U = 3;


		if (!Player.fly)
		{
			Player.fly = true;
			Player.move.y = -PLAYERJUMP;
			
		}

	}
	
	if (GetKeyboardPress(DIK_A) || GetThumbLeftX(0) < -16384)
	{
		Player.direction = DIRECTION_LEFT;
		Player.move.x = -PLATER_SPEED;
	}
	if (GetKeyboardPress(DIK_D) || GetThumbLeftX(0) > 16384)
	{
		Player.direction = DIRECTION_RIGHT;
		Player.move.x = +PLATER_SPEED;
	}

	if (Player.fly == true)
	{
		if (Player.direction == DIRECTION_STAY_LEFT || Player.direction == DIRECTION_LEFT)
		{
			Player.direction = DIRECTION_JUMP_LEFT;
		}
		else if (Player.direction == DIRECTION_STAY_RIGHT || Player.direction == DIRECTION_RIGHT)
		{
			Player.direction = DIRECTION_JUMP_RIGHT;
		}
	}

	

	if (swing)
	{
		if (Player.direction == DIRECTION_STAY_LEFT || Player.direction == DIRECTION_LEFT || Player.direction == DIRECTION_JUMP_LEFT)
		{
			Player.direction = DIRECTION_HIT_LEFT;
		}
		else if (Player.direction == DIRECTION_STAY_RIGHT || Player.direction == DIRECTION_RIGHT || Player.direction == DIRECTION_JUMP_RIGHT)
		{
			Player.direction = DIRECTION_HIT_RIGHT;
		}
	}
	swing_count--;


	animation_count++;
	if (animation_count >= 100) {
		animation_count = 0;
		Player.animation++;
		
		if (Player.animation >= 3)
			Player.animation = 0;
	}

	
	

	//位置更新
	Player.move.y += Player.gravity;
	Player.pos += Player.move;

	//Player.move.y = 0.0f;


//画面端
	if (Player.pos.y < 70) {
		Player.pos.y = 70;
	}
	if (Player.pos.x > SCREEN_WIDTH - 20)
	{
			Player.pos.x = SCREEN_WIDTH - 20;
	}
	if (Player.pos.x < 20) 
	{
		Player.pos.x = 20;
	}
	/*if (Player.pos.y > GROUND) {
		Player.pos.y = GROUND;
		Player.move.y = 0.0f;
	}*/


	// 攻撃

	/*if (GetThumbRightX(0) || GetThumbRightY(0))
	{
			ball->move.x += (ball->speed * cosf(reflect));
			ball->move.y += (ball->speed * sinf(reflect));
	}*/

	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
		switch (Player.direction)
		{
		case DIRECTION_LEFT:		//左に移動しているとき
			DrawSprite(Player.player_dash_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			break;
		case DIRECTION_RIGHT:		//右に移動しているとき
			DrawSprite(Player.player_dash_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, 0.0f, 0.0f, -1.0f, 1.0f);
			break;
		case DIRECTION_STAY_LEFT:	//左を向いて止まってるとき
			DrawSprite(Player.player_stay_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			break;
		case DIRECTION_STAY_RIGHT:	//右を向いて止まってるとき
			DrawSprite(Player.player_stay_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y,  0.0f, 0.0f,-1.0f, 1.0f);
			break;
		case DIRECTION_JUMP_LEFT:	//左を向いてジャンプしているとき
			DrawSprite(Player.player_jump_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			break;
		case DIRECTION_JUMP_RIGHT:	//右を向いてジャンプしているとき
			DrawSprite(Player.player_jump_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, 0.0f, 0.0f, -1.0f, 1.0f);
			break;
		case DIRECTION_HIT_LEFT:	//左を向いてスイングしているとき
			DrawSprite(Player.player_hit_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			break;
		case DIRECTION_HIT_RIGHT:	//右を向いてスイングしているとき
			DrawSprite(Player.player_hit_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, 0.0f, 0.0f, -1.0f, 1.0f);
			break;
		}
}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &Player;
}

void SetPlayer(D3DXVECTOR2 pos)
{

	Player.pos = pos;			// 座標をセット
	return;
}

void SetSwing(int Swing_Count)
{

	swing_count = Swing_Count;			// 座標をセット
	return;
}