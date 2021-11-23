//=============================================================================
//
// �{�[������ [Ball.cpp]
// Author : 
//
//=============================================================================
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "Attack.h"
#include "ground.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static BALL Ball;							// �o���b�g�\����
PLAYER* player = GetPlayer();		// �v���C���[�̃|�C���^�[��������
//BALL* ball = GetBall();		// �o���b�g�̃|�C���^�[��������
ATTACK* attack = GetAttack();
static GROUND* ground = GetGround();


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBall(void)
{

	int BallTexture = LoadTexture("data/TEXTURE/tako.png");
	int ShadowTexture = LoadTexture("data/TEXTURE/kage.png");

	// �{�[���\���̂̏�����
	
		Ball.mode   = 1;
		Ball.size = D3DXVECTOR2(40.0f, 40.0f);
		Ball.pos   = D3DXVECTOR2(300, 300.0f);
		Ball.rot   = 0.0f;
		Ball.BallTexture = BallTexture;
		Ball.ShadowTexture = ShadowTexture;
		Ball.move = D3DXVECTOR2(0.0f, 0.0f);	// �ړ��ʂ�������
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
	// ��]������
	//g_Ball.rot += 0.5f;
	
	switch(Ball.mode)
	{
	case 0:
		break;
	case 1:
		Ball.move.y += 0.5f;

		break;
	case 2:
		if (Ball.move.x >= 50 || -50 > Ball.move.x)
		{}
		else
		{
			Ball.move.y += 0.5f;
		}
		break;
				
	}
	if (Ball.move.x > BALL_SPEED_MAX)
	{
		Ball.move.x = BALL_SPEED_MAX;
	}

	//�ʒu�X�V
	Ball.pos += Ball.move;




	// ��ʒ[�ɍs�����Ƃ�
	if (Ball.pos.y < 70) {
		Ball.pos.y = 70;
		Ball.move.y *= -1;
	}
	if (Ball.pos.x > 940) {
		Ball.pos.x = 940;
		Ball.move.x *= -1;
	}
	if (Ball.pos.x < 20) {
		Ball.pos.x = 20;
		Ball.move.x *= -1;
	}
	if (Ball.pos.y > SCREEN_HEIGHT - ground->size.y - (Ball.size.y / 2)) {
		Ball.pos.y = SCREEN_HEIGHT - ground->size.y - (Ball.size.y / 2);
		Ball.move.y *= -1;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBall(void)
{
		if (Ball.mode >= 1)	// ���̃o���b�g���g���Ă���H
		{								// Yes
			//�o���b�g�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = Ball.pos.x;	// �o���b�g�̕\���ʒuX
			float py = Ball.pos.y;	// �o���b�g�̕\���ʒuY
			float pw = Ball.size.x;		// �o���b�g�̕\����
			float ph = Ball.size.y;		// �o���b�g�̕\������
			float mx = Ball.move.x;	// �o���b�g�̈ړ���XY
			float my = Ball.move.y;
			float pr = Ball.rot;	//�p�x
			float BallShadow = 3;				//�{�[���̎c�����������΂��{��
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



			switch (Ball.mode)
			{
			case 0:
				break;
			case 1:
				DrawSpriteColorRotate(Ball.BallTexture, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				
				break;
			case 2:


				if (Ball.move.x >= 50 || -50 > Ball.move.x)
				{
					if (Ball.move.y >= 50 || -50 > Ball.move.y)
					{
						if (Ball.move.x > 0) 
						{
							BallShadow = BallShadow * 1.4;
							if (Ball.move.y > 0)
							{
								pr = 0.77;
							}
							if (Ball.move.y < 0)
							{
								pr = -0.77;
							}
						}
						else
						{
							BallShadow = BallShadow * 1.4;
							if (Ball.move.y > 0)
							{
								pr = -0.77;
							}
							if (Ball.move.y < 0)
							{
								pr = 0.77;
							}
						}
					}
						if (Ball.move.x < 0) {
							DrawSpriteColorRotate(Ball.ShadowTexture, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * -BallShadow, 40.0f,
								0.0f, 0.0f, 1.0f, 0.4f, col,
								pr);
						}
						else
						{
							DrawSpriteColorRotate(Ball.ShadowTexture, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * BallShadow, 40.0f,
								0.0f, 0.6f, 1.0f, 0.3f, col,pr);
						}
					
				}
				DrawSpriteColorRotate(Ball.BallTexture, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				break;
			}
		}

}


//=============================================================================
// �o���b�g�\���̂̐擪�A�h���X���擾
//=============================================================================
BALL* GetBall(void)
{
	return &Ball;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBall(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power)
{
	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	
			Ball.mode = mode;			// �g�p��Ԃ֕ύX����
			Ball.pos = pos;			// ���W���Z�b�g
			Ball.move = power;			//���x�����
			return;							// 1���Z�b�g�����̂ŏI������
}


D3DXVECTOR2* GetBallPos()
{
	return &Ball.pos;
}

D3DXVECTOR2* GetBallSize()
{
	return &Ball.size;
}

SPEED_LEVEL Speed_Level(D3DXVECTOR2 ball_move)
{
	if (Ball.move.x < 0 && Ball.move.x <= 8)
		return level_1;
	if (Ball.move.x < 8 && Ball.move.x <= 16)
		return level_2;
	if (Ball.move.x < 16 && Ball.move.x <= 26)
		return level_3;
	if (Ball.move.x < 26 && Ball.move.x <= 40)
		return level_4;
	if (Ball.move.x < 40 && Ball.move.x <= BALL_SPEED_MAX)
		return level_5;

	return SPEED_LEVEL();
}
