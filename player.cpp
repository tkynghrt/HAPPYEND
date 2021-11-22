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
#include "Attack.h"
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
int himeTEXTURE = 0;

//あとで解析&書き換え
int animation = 0;
int animation_count = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	//テクスチャ読み込み
	Player.Hime_Texture = LoadTexture("data/TEXTURE/hime.png");
	
	//初期化
	Player.pos.x = 200;
	Player.pos.y = 440;
	Player.old_pos = Player.pos;
	Player.size.x = 60.0f;
	Player.size.y = 60.0f;
	Player.velocity.x = 0.0f;
	Player.velocity.y = 0.0f;
	Player.animation = 0;
	Player.use = true;
	Player.hp = 5;
	//Player.tex = 1;
	//Player.texcont = 0;
	Player.move = D3DXVECTOR2(0.0f, 0.0f);
	Player.power = D3DXVECTOR2(2.0f, 0.0f);
	Player.gravity = 1.0f;
	Player.player_doingjump = false;
	
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

	//重力
	Player.gravity = 1.0f;
	Player.move.x = 0.0f;
	

	//ジャンプしてるかの判定
	if (Player.pos.y >= 500)
	{
		Player.player_doingjump = false;

	}
	

	//ジャンプ
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//U = 3;

		if (Player.player_doingjump == false)
		{
			Player.player_doingjump = true;
			Player.move.y = -PLAYERJUMP;
		}
		
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		himeTEXTURE = 1;
		Player.move.x = -5.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		himeTEXTURE = 2;
		Player.move.x = +5.0f;
	}
	
	animation_count++;
	if (animation_count >= 10) {
		animation_count = 0;
		Player.animation++;
		
		if (Player.animation >= 3)
			Player.animation = 0;
	}

	
	

	//位置更新
	Player.pos += Player.move;
	Player.move.y += Player.gravity;
	//Player.move.y = 0.0f;


//画面端
	if (Player.pos.y < 70) {
		Player.pos.y = 70;
	}
	if (Player.pos.x > 940) {
			Player.pos.x = 940;
	}
	if (Player.pos.x < 20) {
		Player.pos.x = 20;
	}
	if (Player.pos.y > 500) {
		Player.pos.y = 500;
		Player.move.y = 0.0f;
	}

	// 攻撃
	if (GetKeyboardTrigger(DIK_Z))
	{
		AddScore(2);
		if (himeTEXTURE == 2)
		{
			//Player.power += Player.power;

			//SetBullet(2, Player.pos, Player.power);
			SetAttack(1, D3DXVECTOR2(Player.pos.x + 40, Player.pos.y));
		}
		else
		{
			//Player.power += Player.power;

			//SetBullet(2, Player.pos, D3DXVECTOR2(Player.power.x * -1, Player.power.y));
			SetAttack(1, D3DXVECTOR2(Player.pos.x -40, Player.pos.y));
		}
	}
	////////////////////////////////////////////////////////
	// 攻撃(威力減衰)
	if (GetKeyboardTrigger(DIK_A))
	{
		if(ball->move.x > 0)
		ball->move.x -= 2.0f;

		if (ball->move.x < 0)
			ball->move.x += 2.0f;

		AddScore(-2);
	}
	// 攻撃(威力減衰)
	if (GetKeyboardTrigger(DIK_S))
	{
		if (ball->move.x > 0)
			ball->move.x += 2.0f;

		if (ball->move.x < 0)
			ball->move.x -= 2.0f;

		AddScore(2);
	}

	/////////////////////////////////////////////////////
	

	if (GetKeyboardTrigger(DIK_X))
	{
		if (himeTEXTURE == 2)
		{
			//Player.power += Player.power;

			//SetBullet(2, Player.pos, Player.power);
			SetAttack(2, D3DXVECTOR2(Player.pos.x + 40, Player.pos.y));
		}
		else
		{
			//Player.power += Player.power;

			//SetBullet(2, Player.pos, D3DXVECTOR2(Player.power.x * -1, Player.power.y));
			SetAttack(2, D3DXVECTOR2(Player.pos.x - 40, Player.pos.y));
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
		DrawSprite(Player.Hime_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, Player.animation * 0.33f, himeTEXTURE * 0.081, 0.33f, 0.081f);

}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &Player;
}
int GetPlayer_Direction(void)
{
	return himeTEXTURE;
}


