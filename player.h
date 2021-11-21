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
	D3DXVECTOR2				velocity;				// �u���b�N�ɏ���Ă�Ƃ��̉���
	float					rot;					// �|���S���̉�]��
	int						HimeTexture;			// �e�N�X�`���̎��
	int						texNo2;

	//int texcont;
	//int tex;

	int                     hp;
	int						animation;
	D3DXVECTOR2				move;
	D3DXVECTOR2				power;
	float					gravity;
	bool					player_doingjump;
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