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
#include "All_Gimmick.h"
#include "ground.h"
#include "Target_Count.h"
#include "Target_Normal.h"

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
	InitGround();
	InitAllGimmickPos();
	//追加はここから
	InitCoin();
	InitPlayer();
	InitBall();
	InitAttack();
	InitMoveBlock();
	InitCountBlock();
	InitAcceleBlock();
	InitTarget_Normal();
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
	UninitTarget_Normal();
	UninitCoin();
	UninitGround();
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
	UpdateTarget_Normal();
	UpdateScore();
	UpdateGround();
	UpdateCollision();


	//スペースキーが押されていて、フェード処理中ではないとき
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_STATE::FADE_NONE) {

		//RESULTへ移行する
		SceneTransition(SCENE::SCENE_RESULT);
	}
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	DrawBackGround();
	DrawGround();
	DrawCoin();
	DrawBall();
	DrawAttack();
	DrawPlayer();
	DrawScore();
	DrawMoveBlock();
	DrawCountBlock();
	DrawAcceleBlock();
	DrawTarget_Normal();

}