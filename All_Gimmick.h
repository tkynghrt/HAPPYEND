#pragma once
#include "main.h"
#include "ground.h"

static GROUND* ground = GetGround();

HRESULT InitAllGimmickPos(void);

//�}�N����`
//�e�u���b�N����
#define MAX_GIMMICK	100

// �ړ�����u���b�N�֘A
//�\�����鑍��(x��)
#define MAX_MOVE_BLOCK_X	5
//�\�����鑍��(y��)
#define MAX_MOVE_BLOCK_Y	1

//�񐔂ŉ���u���b�N�֘A
//�\�����鑍��
#define MAX_COUNT_BLOCK	1

//����̑��x�ŉ���u���b�N�֘A
//�\�����鑍��
#define MAX_ACCELE_BLOCK	1
//���x���x��
#define	LEVEL_1		0
#define	LEVEL_2		1
#define	LEVEL_3		2
#define	LEVEL_4		3
#define	LEVEL_5		4


//���ʂ̃^�[�Q�b�g�̑���
#define TARGET_MAX		1

//�񐔂ŉ���^�[�Q�b�g�̑���
#define MAX_TARGET_COUNT	1

//�\������R�C������
#define MAX_COIN	1


//�񐔂ŉ���u���b�N�̍\����
struct GIMMICK_POS {
	//�ړ�����u���b�N(x��)
	D3DXVECTOR2 move_block_pos_x;
	//�ړ�����u���b�N(y��)
	D3DXVECTOR2 move_block_pos_y;

	//�񐔂ŉ���u���b�N
	D3DXVECTOR2 count_block_pos;
	int			count_block_hit_count;

	//�X�s�[�h���x���ŉ���u���b�N
	D3DXVECTOR2 accele_block_pos;
	int			accele_level;

	//���ʂ̃^�[�Q�b�g
	D3DXVECTOR2 normal_target_pos;

	//�񐔂ŉ���^�[�Q�b�g
	D3DXVECTOR2 count_target_pos;

	//�R�C��
	D3DXVECTOR2 coin;	
};

//�ړ�����u���b�N(x��)
GIMMICK_POS* GetMove_Block_X(void);
//�ړ�����u���b�N(y��)
GIMMICK_POS* GetMove_Block_X(void);

//�񐔂ŉ���u���b�N
GIMMICK_POS* GetCount_Block(void);

//�X�s�[�h���x���ŉ���u���b�N
GIMMICK_POS* GetAccele_Block(void);

//���ʂ̃^�[�Q�b�g
GIMMICK_POS* GetNormal_Target(void);

//�񐔂ŉ���^�[�Q�b�g
GIMMICK_POS* GetCount_Target(void);

//�R�C��
GIMMICK_POS* GetCoin_(void);
