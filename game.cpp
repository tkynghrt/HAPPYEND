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
#include "collision.h"
#include "move_block.h"
#include "count_block.h"
#include "accele_block.h"
#include "block.h"
#include "background.h"
#include "coin.h"
#include "score.h"
#include "ground.h"
#include "Target_Count.h"
#include "Target_Normal.h"
#include "SpeedPanel.h"
#include "map.h"

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
	//追加はここから
	InitCoin();
	InitPlayer();
	InitBall();
	InitMoveBlock();
	InitCountBlock();
	InitBlock();
	InitAcceleBlock();
	InitTarget_Normal();
	InitTarget_Count();
	InitSpeedPanel();
	InitScore();
	SetMap(1);
	InitMap();
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	UninitScore();
	UninitBall();
	UninitPlayer();
	UninitMoveBlock();
	UninitCountBlock();
	UninitAcceleBlock();
	UninitBlock();
	UninitTarget_Normal();
	UninitTarget_Count();
	UninitSpeedPanel();
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
	UpdateMoveBlock();
	UpdateCountBlock();
	UpdateAcceleBlock();
	UpdateBlock();
	UpdateTarget_Normal();
	UpdateTarget_Count();
	UpdateSpeedPanel();
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
	DrawPlayer();
	DrawScore();
	DrawMoveBlock();
	DrawCountBlock();
	DrawAcceleBlock();
	DrawBlock();
	DrawTarget_Normal();
	DrawTarget_Count();
	DrawSpeedPanel();

}