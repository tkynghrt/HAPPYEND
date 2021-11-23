/*==============================================================================

   ���_�Ǘ�[polygon.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


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
	int						texNo2;

	//int texcont;
	//int tex;

	int                     hp;
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
int GetPlayer_Direction(void);