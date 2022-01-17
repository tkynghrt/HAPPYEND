//=============================================================================
//
// �{�[������ [Ball.cpp]
// Author : 
//
//=============================================================================
#include "input.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "ground.h"
#include "collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	level_1		0
#define	level_2		1
#define	level_3		2
#define	level_4		3
#define	level_5		4


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static BALL Ball;							// �o���b�g�\����
PLAYER* player = GetPlayer();		// �v���C���[�̃|�C���^�[��������
//BALL* ball = GetBall();		// �o���b�g�̃|�C���^�[��������
static GROUND* ground = GetGround();

F_OLD_SURFACE CollisionKOBA(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
							D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size);


float	reflect;				//���˕Ԃ�p�x

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBall(void)
{
	// �{�[���\���̂̏�����

	Ball.BallTexture = LoadTexture("data/TEXTURE/ball.png");
	Ball.size = D3DXVECTOR2(40.0f, 40.0f);
	//Ball.pos   = D3DXVECTOR2(player->pos.x + 60.0f, player->pos.y + 20.0f);
	Ball.pos   = player->pos;
	Ball.old_pos  = Ball.pos;
	Ball.rot   = -PI;
	Ball.speed = 0.0f;
	Ball.velocity = D3DXVECTOR2(0.0f, 0.0f);	// �ړ��ʂ�������
	Ball.Use = false;
	Ball.Speed_Level = level_1;
	Ball.Judgment = 20;
	Ball.judgment_time = 0;

	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBall(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBall(void)
{

	Ball.old_pos = Ball.pos;
	if (Ball.speed == 0.0f)
		Ball.pos = player->pos;

	Ball.Judgment++;
	Ball.judgment_time--;
	//�{�[���ł��Ԃ���
	
	if ((IsButtonTriggered(0, XINPUT_GAMEPAD_X)) || IsMouseLeftTriggered())
	{
		Ball.judgment_time = 5;
	}


	//�ʒu�X�V
	Ball.pos += Ball.velocity;

	Ball.rot++;
	if (Ball.rot > PI)
	{
		Ball.rot = -PI;
	}


	//�{�[���̃X�s�[�h���x��
	if (Ball.velocity.x > 0 && Ball.velocity.x <= 8)
		Ball.Speed_Level = level_1;
	if (Ball.velocity.x > 8 && Ball.velocity.x <= 16)
		Ball.Speed_Level = level_2;
	if (Ball.velocity.x > 16 && Ball.velocity.x <= 26)
		Ball.Speed_Level = level_3;
	if (Ball.velocity.x > 26 && Ball.velocity.x <= 40)
		Ball.Speed_Level = level_4;
	if (Ball.velocity.x > 40 && Ball.velocity.x <= BALL_SPEED_MAX)
		Ball.Speed_Level = level_5;

	if (Ball.speed > BALL_SPEED_MAX)
	{
		Ball.speed = BALL_SPEED_MAX;
	}

	// ��ʒ[�ɍs�����Ƃ�
	if (Ball.pos.y < 20) {
		Ball.pos.y = 20;
		Ball.velocity.y *= -1;
	}
	if (Ball.pos.x > SCREEN_WIDTH - (20 + 60)) {
		Ball.pos.x = SCREEN_WIDTH - (20 + 60);
		Ball.velocity.x *= -1;
	}
	if (Ball.pos.x < (20 + 60)) {
		Ball.pos.x = (20 + 60);
		Ball.velocity.x *= -1;
	}
	if (Ball.pos.y > SCREEN_HEIGHT - ground->size.y - (Ball.size.y / 2) - 60) 
	{
		Ball.pos.y = SCREEN_HEIGHT - ground->size.y - (Ball.size.y / 2) - 60;
		Ball.velocity.y *= -1;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBall(void)
{
	D3DXCOLOR BallCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (Ball.Use)
	{
		DrawSpriteColorRotate(Ball.BallTexture, Ball.pos.x, Ball.pos.y,
			Ball.size.x , Ball.size.y , 0.0f, 0.0f, 1.0f, 1.0f,
			BallCol, Ball.rot);
	}
}

//=============================================================================
// �o���b�g�\���̂̐擪�A�h���X���擾
//=============================================================================
BALL* GetBall(void)
{
	return &Ball;
}