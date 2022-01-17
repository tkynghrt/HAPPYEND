/*==============================================================================

   ���_�Ǘ�[polygon.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#define DIRECTION_LEFT		 1
#define DIRECTION_RIGHT		 2
#define DIRECTION_STAY_LEFT  3
#define DIRECTION_STAY_RIGHT 4
#define DIRECTION_JUMP_LEFT	 5
#define DIRECTION_JUMP_RIGHT 6
#define DIRECTION_HIT_LEFT   7
#define DIRECTION_HIT_RIGHT  8


#include "main.h"
#include "renderer.h"

void SetPlayer(D3DXVECTOR2 pos);
void SetSwing(int Swing);

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �v���C���[�\����
struct PLAYER
{
	bool					use;					// true:�g���Ă���  false:���g�p
	D3DXVECTOR2				size;					// ���ƍ���
	D3DXVECTOR2				pos;					// �|���S���̍��W
	D3DXVECTOR2				old_pos;				// 1�t���[���O�̃|���S���̍��W
	float					rot;					// �|���S���̉�]��
	int						player_stay_Texture;			// �e�N�X�`���̎��
	int						player_dash_Texture;	
	int						player_jump_Texture;	
	int						player_hit_Texture;

	int						direction;


	int						animation;
	D3DXVECTOR2				move;
	D3DXVECTOR2				power;
	float					gravity;
	bool					fly;
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);