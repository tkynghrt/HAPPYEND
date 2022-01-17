//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(16)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(32)	// 
#define TEXTURE_MAX					(1)		// �e�N�X�`���̐�


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static bool						g_Use;						// true:�g���Ă���  false:���g�p
static float					g_w, g_h;					// ���ƍ���
static D3DXVECTOR3				g_Pos;						// �|���S���̍��W
static int						g_TexNo;					// �e�N�X�`���ԍ�
static int						g_TexNo2;
static int						g_Score;					// �X�R�A
bool IsResult = false;




//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{
	//�e�N�X�`������
	g_TexNo = LoadTexture("data/TEXTURE/number2.png");
	g_TexNo2 = LoadTexture("data/TEXTURE/number.png");
	//������
	g_Use = true;
	g_w = TEXTURE_WIDTH;
	g_h = TEXTURE_HEIGHT;
	g_Pos = D3DXVECTOR3(800.0f, 33.0f, 0.0f);

	g_Score = 0;	// �X�R�A�̏�����
	IsResult = false;



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{


	/*if (GetFadeState() == FADE_NONE && g_Score > 1600)
	{
		SceneTransition(SCENE_RESULT);
	}*/
}



//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	//�L�����t���O��ON�Ȃ�`�悷��
	if (!g_Use)
	{
		// �e�N�X�`���ݒ�
		if (IsResult == true)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo2));
			g_Pos.x = 500.0f;
			g_Pos.y = 245.0f;
		}
		else
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));
		}

		// ��������������
		int number = g_Score;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// ����\�����錅�̐���
			float x = (float)(number % 10);

			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Pos.x - (g_w * 1.5f) * i;	// �v���C���[�̕\���ʒuX
			float py = g_Pos.y;			// �v���C���[�̕\���ʒuY
			float pw = g_w * 2.5;				// �v���C���[�̕\����
			float ph = g_h * 2.5;				// �v���C���[�̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			if (IsResult == true)
			{
				DrawSprite(g_TexNo2, px, py, pw, ph, tx, ty, tw, th);
			}
			else
			{
				DrawSprite(g_TexNo, px, py, pw, ph, tx, ty, tw, th);
			}

			// ���̌���
			number /= 10;
		}
	}

	IsResult = false;
}

//=============================================================================
// �X�R�A�����Z����
// ����:add :�ǉ�����_���B�}�C�i�X���\
//=============================================================================
void AddScore(int add)
{
	g_Score += add;

	if (g_Score > SCORE_MAX)
	{
		g_Score = SCORE_MAX;
	}
}

void ResultScore(bool ReScore)
{
	IsResult = ReScore;
}

