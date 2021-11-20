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
#include "xinput.h"
#include "moveblock.h"
#include "countblock.h"
#include "collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define PLAYERJUMP	(18.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float frand(void);



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER g_Player;
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

static MOVEBLOCK* moveblock = GetMoveBlock();
static COUNTBLOCK* countblock = GetCountBlock();

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
	g_Player.HimeTexture = LoadTexture("data/TEXTURE/hime.png");

	//g_Player.texNo2 = LoadTexture("data/TEXTURE/hime2.png");
	
	//������
	g_Player.pos.x = SCREEN_WIDTH / 2;
	g_Player.pos.y = 440;
	g_Player.size.x = 60.0f;
	g_Player.size.y = 60.0f;
	g_Player.velocity.x = 0.0f;
	g_Player.velocity.y = 0.0f;
	g_Player.use = true;
	g_Player.hp = 5;
	//g_Player.tex = 1;
	//g_Player.texcont = 0;
	g_Player.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.power = D3DXVECTOR2(2.0f, 0.0f);
	g_Player.gravity = 1.0f;
	g_Player.player_doingjump = false;
	
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
	g_Player.gravity = 1.0f;
	g_Player.move.x = 0.0f;
	

	//�W�����v���Ă邩�̔���
	if (g_Player.pos.y >= 500)
	{
		g_Player.player_doingjump = false;

	}
	

	//�W�����v
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//U = 3;

		if (g_Player.player_doingjump == false)
		{
			g_Player.player_doingjump = true;
			g_Player.move.y = -PLAYERJUMP;
		}
		
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		himeTEXTURE = 1;
		g_Player.move.x = -5.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		himeTEXTURE = 2;
		g_Player.move.x = +5.0f;
	}
	
	cont++;
	if (cont >= 10) {
		cont = 0;
		V++;
		
		if (V >= 3)
			V = 0;
	}

	//�񐔂ŉ���u���b�N�ɓ������Ă���Ƃ�
	if (CollisionBB(g_Player.pos, countblock[1].pos, D3DXVECTOR2(g_Player.size.x, g_Player.size.y), D3DXVECTOR2(countblock[1].size.x, countblock[1].size.y)))
	{

		g_Player.move.x = 0.0f;

	}
	

	//�ʒu�X�V
	g_Player.pos += g_Player.move;
	g_Player.move.y += g_Player.gravity;
	//g_Player.move.y = 0.0f;


//��ʒ[
	if (g_Player.pos.y < 70) {
		g_Player.pos.y = 70;
	}
	if (g_Player.pos.x > 940) {
			g_Player.pos.x = 940;
	}
	if (g_Player.pos.x < 20) {
		g_Player.pos.x = 20;
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
	/*if (g_Player.texcont > 0) {
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
	}*/
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{

	//if (g_Player.tex==1)
	//{

		DrawSprite(g_Player.HimeTexture, g_Player.pos.x, g_Player.pos.y, g_Player.size.x, g_Player.size.y, V * 0.33f, himeTEXTURE * 0.081, 0.33f, 0.081f);

	//}
	//else
	//{
	//	DrawSprite(g_Player.texNo2, g_Player.pos.x, g_Player.pos.y, g_Player.w, g_Player.h, V * 0.33f, himeTEXTURE * 0.081, 0.33f, 0.081f);
	//}
	

		
}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}
int GetPlayer_Direction(void)
{
	return himeTEXTURE;
}


