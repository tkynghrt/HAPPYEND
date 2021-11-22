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
#include "Attack.h"
#include "collision.h"
#include "move_block.h"
#include "count_block.h"
#include "accele_block.h"
#include "background.h"
#include "coin.h"
#include "score.h"


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
   �I������������֐�
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
   �X�V����������֐�
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


	//�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE) {

		//RESULT�ֈڍs����
		SceneTransition(SCENE_RESULT);
	}
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
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

