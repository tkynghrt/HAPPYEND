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
#include "move_block.h"
#include "count_block.h"
#include "collision.h"
#include "ball.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYERJUMP	(20.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float frand(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER Player;
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

static MOVE_BLOCK* move_block = GetMoveBlock();
static COUNT_BLOCK* count_block = GetCountBlock();
static BALL* ball = GetBall();

//����L�����̉摜�̎��
int himeTEXTURE = 0;

//���Ƃŉ��&��������
int animation = 0;
int animation_count = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	//�e�N�X�`���ǂݍ���
	Player.Hime_Texture = LoadTexture("data/TEXTURE/hime.png");
	
	//������
	Player.pos.x = 200;
	Player.pos.y = 440;
	Player.old_pos = Player.pos;
	Player.size.x = 60.0f;
	Player.size.y = 60.0f;
	Player.velocity.x = 0.0f;
	Player.velocity.y = 0.0f;
	Player.animation = 0;
	Player.use = true;
	Player.hp = 5;
	//Player.tex = 1;
	//Player.texcont = 0;
	Player.move = D3DXVECTOR2(0.0f, 0.0f);
	Player.power = D3DXVECTOR2(2.0f, 0.0f);
	Player.gravity = 1.0f;
	Player.player_doingjump = false;
	
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
	Player.old_pos = Player.pos;

	//�d��
	Player.gravity = 1.0f;
	Player.move.x = 0.0f;
	

	//�W�����v���Ă邩�̔���
	if (Player.pos.y >= 500)
	{
		Player.player_doingjump = false;

	}
	

	//�W�����v
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//U = 3;

		if (Player.player_doingjump == false)
		{
			Player.player_doingjump = true;
			Player.move.y = -PLAYERJUMP;
		}
		
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		himeTEXTURE = 1;
		Player.move.x = -5.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		himeTEXTURE = 2;
		Player.move.x = +5.0f;
	}
	
	animation_count++;
	if (animation_count >= 10) {
		animation_count = 0;
		Player.animation++;
		
		if (Player.animation >= 3)
			Player.animation = 0;
	}

	
	

	//�ʒu�X�V
	Player.pos += Player.move;
	Player.move.y += Player.gravity;
	//Player.move.y = 0.0f;


//��ʒ[
	if (Player.pos.y < 70) {
		Player.pos.y = 70;
	}
	if (Player.pos.x > 940) {
			Player.pos.x = 940;
	}
	if (Player.pos.x < 20) {
		Player.pos.x = 20;
	}
	if (Player.pos.y > 500) {
		Player.pos.y = 500;
		Player.move.y = 0.0f;
	}

	// �U��
	if (GetKeyboardTrigger(DIK_Z))
	{
		AddScore(2);
		if (himeTEXTURE == 2)
		{
			//Player.power += Player.power;

			//SetBullet(2, Player.pos, Player.power);
			SetAttack(1, D3DXVECTOR2(Player.pos.x + 40, Player.pos.y));
		}
		else
		{
			//Player.power += Player.power;

			//SetBullet(2, Player.pos, D3DXVECTOR2(Player.power.x * -1, Player.power.y));
			SetAttack(1, D3DXVECTOR2(Player.pos.x -40, Player.pos.y));
		}
	}
	////////////////////////////////////////////////////////
	// �U��(�З͌���)
	if (GetKeyboardTrigger(DIK_A))
	{
		if(ball->move.x > 0)
		ball->move.x -= 2.0f;

		if (ball->move.x < 0)
			ball->move.x += 2.0f;

		AddScore(-2);
	}
	// �U��(�З͌���)
	if (GetKeyboardTrigger(DIK_S))
	{
		if (ball->move.x > 0)
			ball->move.x += 2.0f;

		if (ball->move.x < 0)
			ball->move.x -= 2.0f;

		AddScore(2);
	}

	/////////////////////////////////////////////////////
	

	if (GetKeyboardTrigger(DIK_X))
	{
		if (himeTEXTURE == 2)
		{
			//Player.power += Player.power;

			//SetBullet(2, Player.pos, Player.power);
			SetAttack(2, D3DXVECTOR2(Player.pos.x + 40, Player.pos.y));
		}
		else
		{
			//Player.power += Player.power;

			//SetBullet(2, Player.pos, D3DXVECTOR2(Player.power.x * -1, Player.power.y));
			SetAttack(2, D3DXVECTOR2(Player.pos.x - 40, Player.pos.y));
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
		DrawSprite(Player.Hime_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, Player.animation * 0.33f, himeTEXTURE * 0.081, 0.33f, 0.081f);

}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &Player;
}
int GetPlayer_Direction(void)
{
	return himeTEXTURE;
}


