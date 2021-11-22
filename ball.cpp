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

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static BALL g_Ball;							// �o���b�g�\����
PLAYER* player = GetPlayer();		// �v���C���[�̃|�C���^�[��������
//BALL* ball = GetBall();		// �o���b�g�̃|�C���^�[��������
ATTACK* attack = GetAttack();


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBall(void)
{

	int BallTexture = LoadTexture("data/TEXTURE/tako.png");
	int ShadowTexture = LoadTexture("data/TEXTURE/kage.png");

	// �{�[���\���̂̏�����
	
		g_Ball.mode   = 1;
		g_Ball.size = D3DXVECTOR2(40.0f, 40.0f);
		g_Ball.pos   = D3DXVECTOR2(300, 300.0f);
		g_Ball.rot   = 0.0f;
		g_Ball.BallTexture = BallTexture;
		g_Ball.ShadowTexture = ShadowTexture;
		g_Ball.move = D3DXVECTOR2(0.0f, 0.0f);	// �ړ��ʂ�������
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
	
	switch(g_Ball.mode)
	{
	case 0:
		break;
	case 1:
		g_Ball.move.y += 0.5f;

		break;
	case 2:
		if (g_Ball.move.x >= 50 || -50 > g_Ball.move.x)
		{}
		else
		{
			g_Ball.move.y += 0.5f;
		}
		break;
				
	}
	if (g_Ball.move.x > BALL_SPEED_MAX)
	{
		g_Ball.move.x = BALL_SPEED_MAX;
	}

	//�ʒu�X�V
	g_Ball.pos += g_Ball.move;




	// ��ʒ[�ɍs�����Ƃ�
	if (g_Ball.pos.y < 70) {
		g_Ball.pos.y = 70;
		g_Ball.move.y *= -1;
	}
	if (g_Ball.pos.x > 940) {
		g_Ball.pos.x = 940;
		g_Ball.move.x *= -1;
	}
	if (g_Ball.pos.x < 20) {
		g_Ball.pos.x = 20;
		g_Ball.move.x *= -1;
	}
	if (g_Ball.pos.y > 500) {
		g_Ball.pos.y = 500;
		g_Ball.move.y *= -1;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBall(void)
{
		if (g_Ball.mode >= 1)	// ���̃o���b�g���g���Ă���H
		{								// Yes
			//�o���b�g�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Ball.pos.x;	// �o���b�g�̕\���ʒuX
			float py = g_Ball.pos.y;	// �o���b�g�̕\���ʒuY
			float pw = g_Ball.size.x;		// �o���b�g�̕\����
			float ph = g_Ball.size.y;		// �o���b�g�̕\������
			float mx = g_Ball.move.x;	// �o���b�g�̈ړ���XY
			float my = g_Ball.move.y;
			float pr = g_Ball.rot;	//�p�x
			float BallShadow = 3;				//�{�[���̎c�����������΂��{��
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



			switch (g_Ball.mode)
			{
			case 0:
				break;
			case 1:
				DrawSpriteColorRotate(g_Ball.BallTexture, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				
				break;
			case 2:


				if (g_Ball.move.x >= 50 || -50 > g_Ball.move.x)
				{
					if (g_Ball.move.y >= 50 || -50 > g_Ball.move.y)
					{
						if (g_Ball.move.x > 0) 
						{
							BallShadow = BallShadow * 1.4;
							if (g_Ball.move.y > 0)
							{
								pr = 0.77;
							}
							if (g_Ball.move.y < 0)
							{
								pr = -0.77;
							}
						}
						else
						{
							BallShadow = BallShadow * 1.4;
							if (g_Ball.move.y > 0)
							{
								pr = -0.77;
							}
							if (g_Ball.move.y < 0)
							{
								pr = 0.77;
							}
						}
					}
						if (g_Ball.move.x < 0) {
							DrawSpriteColorRotate(g_Ball.ShadowTexture, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * -BallShadow, 40.0f,
								0.0f, 0.0f, 1.0f, 0.4f, col,
								pr);
						}
						else
						{
							DrawSpriteColorRotate(g_Ball.ShadowTexture, px + ((mx * -3) / 2), py + ((my * -3) / 2),
								mx * BallShadow, 40.0f,
								0.0f, 0.6f, 1.0f, 0.3f, col,pr);
						}
					
				}
				DrawSpriteColorRotate(g_Ball.BallTexture, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, pr);
				break;
			}
		}

}


//=============================================================================
// �o���b�g�\���̂̐擪�A�h���X���擾
//=============================================================================
BALL* GetBall(void)
{
	return &g_Ball;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBall(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power)
{
	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	
			g_Ball.mode = mode;			// �g�p��Ԃ֕ύX����
			g_Ball.pos = pos;			// ���W���Z�b�g
			g_Ball.move = power;			//���x�����
			return;							// 1���Z�b�g�����̂ŏI������
}


D3DXVECTOR2* GetBallPos()
{
	return &g_Ball.pos;
}

D3DXVECTOR2* GetBallSize()
{
	return &g_Ball.size;
}

SPEED_LEVEL Speed_Level(D3DXVECTOR2 ball_move)
{
	if (g_Ball.move.x < 0 && g_Ball.move.x <= 8)
		return level_1;
	if (g_Ball.move.x < 8 && g_Ball.move.x <= 16)
		return level_2;
	if (g_Ball.move.x < 16 && g_Ball.move.x <= 26)
		return level_3;
	if (g_Ball.move.x < 26 && g_Ball.move.x <= 40)
		return level_4;
	if (g_Ball.move.x < 40 && g_Ball.move.x <= BALL_SPEED_MAX)
		return level_5;

	return SPEED_LEVEL();
}
