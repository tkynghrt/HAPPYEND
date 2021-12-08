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
#include "xinput.h"
#include "move_block_x.h"
#include "count_block.h"
#include "collision.h"
#include "ball.h"
#include "score.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYERJUMP	(20.0f)
#define GRAVITY		(1.0f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float frand(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER Player;
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

static MOVE_BLOCK_X* move_block_x = GetMoveBlock_X();
static COUNT_BLOCK* count_block = GetCountBlock();
static BALL* ball = GetBall();


//����L�����̉摜�̎��
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
	Player.animation = 0;
	Player.use = true;
	Player.direction = 0;
	Player.move = D3DXVECTOR2(0.0f, 0.0f);
	Player.power = D3DXVECTOR2(2.0f, 0.0f);
	Player.gravity = GRAVITY;
	Player.fly = false;
	
	
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
	if (!Player.fly) {
		Player.move.y = 0.0f;
	}
	Player.gravity = GRAVITY;
	Player.move.x = 0.0f;
	

	
	if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_A))
	{
		//U = 3;

		if (!Player.fly)
		{
			Player.fly = true;
			Player.move.y = -PLAYERJUMP;
		}

	}
	if (GetKeyboardPress(DIK_LEFT) || GetThumbLeftX(0) < -16384)
	{
		Player.direction = DIRECTION_LEFT;
		Player.move.x = -6.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) || GetThumbLeftX(0) > 16384)
	{
		Player.direction = DIRECTION_RIGHT;
		Player.move.x = +6.0f;
	}


	animation_count++;
	if (animation_count >= 100) {
		animation_count = 0;
		Player.animation++;
		
		if (Player.animation >= 3)
			Player.animation = 0;
	}

	
	

	//�ʒu�X�V
	Player.move.y += Player.gravity;
	Player.pos += Player.move;

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

	/*if (GetThumbRightX(0) || GetThumbRightY(0))
	{
			ball->move.x += (ball->speed * cosf(reflect));
			ball->move.y += (ball->speed * sinf(reflect));
	}*/

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
		DrawSprite(Player.Hime_Texture, Player.pos.x, Player.pos.y, Player.size.x, Player.size.y, Player.animation * 0.33f, Player.direction * 0.081, 0.33f, 0.081f);

}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &Player;
}



