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
#include "move_block.h"
#include "count_block.h"
#include "accele_block.h"
#include "background.h"
#include "coin.h"
#include "score.h"


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
	InitAcceleBlock();
	InitScore();
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	UninitScore();
	UninitBall();
	UninitPlayer();
	UninitAttack();
	UninitMoveBlock();
	UninitCountBlock();
	UninitAcceleBlock();
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
	UpdateBall();
	UpdateAttack();
	UpdateMoveBlock();
	UpdateCountBlock();
	UpdateAcceleBlock();
	UpdateScore();
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
	DrawScore();
	DrawMoveBlock();
	DrawCountBlock();
	DrawAcceleBlock();

}

