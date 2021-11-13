/*==============================================================================

   ���_�Ǘ� [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "ball.h"
#include "Attack.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float frand(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER g_Player;

//����L�����̉摜�̎��
int himeTEXTURE = 0;

int V = 0;
int cont = 0;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	//�e�N�X�`���ǂݍ���
	g_Player.texNo = LoadTexture("data/TEXTURE/hime.png");
	g_Player.texNo2 = LoadTexture("data/TEXTURE/hime2.png");
	//������
	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = 440;
	g_Player.w = 60.0f;
	g_Player.h = 60.0f;
	g_Player.use = true;
	g_Player.hp = 5;
	g_Player.tex = 1;
	g_Player.texcont = 0;
	g_Player.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.power = D3DXVECTOR2(2.0f, 0.0f);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//�d��
	g_Player.move.y += 1.0f;
	g_Player.move.x = +0.0f;

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//U = 3;
		g_Player.move.y -= 20.0f;

	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		himeTEXTURE = 1;
		g_Player.move.x = -3.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		himeTEXTURE = 2;
		g_Player.move.x = +3.0f;
	}
	
	cont++;
	if (cont >= 10) {
		cont = 0;
		V++;
		
		if (V >= 3)
			V = 0;
	}
	
	//�ʒu�X�V

	g_Player.pos += g_Player.move;

	//��ʒp
	if (g_Player.pos.y < 70) {
		g_Player.pos.y = 70;
	}
	if (g_Player.pos.x > 960) {
			g_Player.pos.x = 960;
	}
	if (g_Player.pos.x < 0) {
		g_Player.pos.x = 0;
	}
	if (g_Player.pos.y > 500) {
		g_Player.pos.y = 500;
		g_Player.move.y = 0.0f;
	}

	// �U��
	if (GetKeyboardTrigger(DIK_Z))
	{
		
		if (himeTEXTURE == 2)
		{
			//g_Player.power += g_Player.power;

			//SetBullet(2, g_Player.pos, g_Player.power);
			SetAttack(1, D3DXVECTOR2(g_Player.pos.x + 40, g_Player.pos.y));
		}
		else
		{
			//g_Player.power += g_Player.power;

			//SetBullet(2, g_Player.pos, D3DXVECTOR2(g_Player.power.x * -1, g_Player.power.y));
			SetAttack(1, D3DXVECTOR2(g_Player.pos.x -40, g_Player.pos.y));
		}
	}
	if (GetKeyboardTrigger(DIK_X))
	{
		if (himeTEXTURE == 2)
		{
			//g_Player.power += g_Player.power;

			//SetBullet(2, g_Player.pos, g_Player.power);
			SetAttack(2, D3DXVECTOR2(g_Player.pos.x + 40, g_Player.pos.y));
		}
		else
		{
			//g_Player.power += g_Player.power;

			//SetBullet(2, g_Player.pos, D3DXVECTOR2(g_Player.power.x * -1, g_Player.power.y));
			SetAttack(2, D3DXVECTOR2(g_Player.pos.x - 40, g_Player.pos.y));
		}
	}
	//��e
	if (g_Player.texcont > 0) {
		g_Player.texcont--;
		if (cont % 5 == 1) {
			if (g_Player.tex == 1)
			{
				g_Player.tex = 0;
			}
			else
			{
				g_Player.tex = 1;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{

	if (g_Player.tex==1)
	{
		DrawSprite(g_Player.texNo, g_Player.pos.x, g_Player.pos.y, g_Player.w, g_Player.h, V * 0.33f, himeTEXTURE * 0.081, 0.33f, 0.081f);
	}
	else
	{
		DrawSprite(g_Player.texNo2, g_Player.pos.x, g_Player.pos.y, g_Player.w, g_Player.h, V * 0.33f, himeTEXTURE * 0.081, 0.33f, 0.081f);
	}
	

		
}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}
int GetPlayer_U(void)
{
	return himeTEXTURE;
}


