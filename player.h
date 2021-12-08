/*==============================================================================

   ���_�Ǘ�[polygon.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#define DIRECTION_LEFT		1
#define DIRECTION_RIGHT		2

#include "main.h"
#include "renderer.h"

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
	int						Hime_Texture;			// �e�N�X�`���̎��
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