/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "ball.h"
#include "Attack.h"
#include "collision.h"
#include "moveblock.h"
#include "countblock.h"
#include "background.h"
#include "coin.h"


/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	InitBackGround();
	InitCoin();
	InitPlayer();
	InitBall();
	InitAttack();
	InitMoveBlock();
	InitCountBlock();
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	
	UninitBall();
	UninitPlayer();
	UninitAttack();
	UninitMoveBlock();
	UninitCountBlock();
	UninitCoin();
	UninitBackGround();
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	
	
	UpdateCoin();
	UpdatePlayer();
	UpdateMoveBlock();
	UpdateBall();
	UpdateAttack();
	UpdateCountBlock();
	UpdateCollision();


	//スペースキーが押されていて、フェード処理中ではないとき
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE) {

		//RESULTへ移行する
		SceneTransition(SCENE_RESULT);
	}
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	DrawBackGround();
	DrawCoin();
	DrawBall();
	DrawAttack();
	DrawPlayer();
	DrawMoveBlock();
	DrawCountBlock();

}

