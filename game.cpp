/*==============================================================================

   �Q�[������ [game.cpp]
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
#include "move_block_x.h"
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
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitGame(void)
{
	InitBackGround();
	InitGround();
	InitAllGimmickPos();
	//�ǉ��͂�������
	InitCoin();
	InitPlayer();
	InitBall();
	/*InitMoveBlock_X();
	InitCountBlock();
	InitAcceleBlock();
	InitTarget_Normal();
	InitTarget_Count();
	InitScore();*/
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitGame()
{
	UninitScore();
	UninitBall();
	UninitPlayer();
	UninitMoveBlock_X();
	UninitCountBlock();
	UninitAcceleBlock();
	UninitTarget_Normal();
	UninitTarget_Count();
	UninitCoin();
	UninitGround();
	UninitBackGround();
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	
	
	UpdateCoin();
	UpdatePlayer();
	UpdateBall();
	/*UpdateMoveBlock_X();
	UpdateCountBlock();
	UpdateAcceleBlock();
	UpdateTarget_Normal();
	UpdateTarget_Count();
	UpdateScore();*/
	UpdateGround();
	UpdateCollision();


	//�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_STATE::FADE_NONE) {

		//RESULT�ֈڍs����
		SceneTransition(SCENE::SCENE_RESULT);
	}
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	DrawBackGround();
	DrawGround();
	//DrawCoin();
	DrawBall();
	DrawPlayer();
	/*DrawScore();
	DrawMoveBlock_X();
	DrawCountBlock();
	DrawAcceleBlock();
	DrawTarget_Normal();
	DrawTarget_Count();*/

}