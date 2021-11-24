#pragma once
#include "main.h"
#include "ground.h"

static GROUND* ground = GetGround();

HRESULT InitAllGimmickPos(void);


//�e�u���b�N����
#define MAX_GIMMICK	100

//�\������񐔂ŉ���u���b�N����
#define MAX_COUNT_BLOCK	1
//�\���������̑��x�ŉ���u���b�N����
#define MAX_ACCELE_BLOCK	1
//�\������ړ��u���b�N����
#define MAX_MOVE_BLOCK	1
//�\������R�C������
#define MAX_COIN	1

//�񐔂ŉ���u���b�N�̍\����
struct GIMMICK_POS {
	D3DXVECTOR2 count_block_pos;	//�񐔂ŉ���u���b�N
	D3DXVECTOR2 move_block_pos;		//�ړ�����u���b�N
	D3DXVECTOR2 accele_block_pos;	//�X�s�[�h���x���ŉ���u���b�N
	D3DXVECTOR2 coin;	//�R�C��
};

GIMMICK_POS* GetGimmick_Pos(void);

