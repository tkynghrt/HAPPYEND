//�S�M�~�b�N�̃|�W�V�����͂����ŊǗ�

#include "All_Gimmick.h"

//�ړ�����u���b�N�̃T�C�Y
#define MOVE_BLOCK		(60.0f)
//�񐔂ŉ���u���b�N�̃T�C�Y
#define COUNT_BLOCK			(60.0f)
//�X�s�[�h���x���ŉ���u���b�N�̃T�C�Y
#define ACCELE_BLOCK		(60.0f)
//�R�C���̃T�C�Y
#define COIN				(60.0f)



GIMMICK_POS Gimick_Pos[MAX_GIMMICK];

HRESULT InitAllGimmickPos(void)
{
	//�ړ�����u���b�N
	// 
	//���W
	Gimick_Pos[0].move_block_pos = D3DXVECTOR2(300.0f, 350.0f);
	Gimick_Pos[1].move_block_pos = D3DXVECTOR2(300.0f + MOVE_BLOCK, 350.0f);
	Gimick_Pos[2].move_block_pos = D3DXVECTOR2(300.0f +(MOVE_BLOCK * 2), 350.0f);
	Gimick_Pos[3].move_block_pos = D3DXVECTOR2(300.0f +(MOVE_BLOCK * 3), 350.0f);
	Gimick_Pos[4].move_block_pos = D3DXVECTOR2(300.0f +(MOVE_BLOCK * 4), 350.0f);

	//�񐔂ŉ���u���b�N
	//���W
	Gimick_Pos[0].count_block_pos = D3DXVECTOR2(800.0f, GROUND);
	//��
	Gimick_Pos[0].count_block_hit_count = 3;

	//�X�s�[�h���x���ŉ���u���b�N
	//���W
	Gimick_Pos[0].accele_block_pos = D3DXVECTOR2(100.0f, GROUND);
	//���x��
	Gimick_Pos[0].count_block_hit_count = LEVEL_3;

	//���ʂ̃^�[�Q�b�g
	Gimick_Pos[0].normal_target_pos = D3DXVECTOR2(600.0f, GROUND);

	//�񐔂ŉ���^�[�Q�b�g
	Gimick_Pos[0].count_target_pos = D3DXVECTOR2(800.0f, GROUND);

	//�R�C��
	//���W
	Gimick_Pos[0].coin = D3DXVECTOR2(500.0f, GROUND);

return S_OK;
}
//�ړ�����u���b�N
GIMMICK_POS* GetMove_Block(void)
{
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		return &Gimick_Pos[i];
	}
}
//�񐔂ŉ���u���b�N
GIMMICK_POS* GetCount_Block(void)
{
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		return &Gimick_Pos[i];
	}
}
//�X�s�[�h���x���ŉ���u���b�N
GIMMICK_POS* GetAccele_Block(void)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		return &Gimick_Pos[i];
	}
}
//���ʂ̃^�[�Q�b�g
GIMMICK_POS* GetNormal_Target(void)
{
	for (int i = 0; i < TARGET_MAX; i++)
	{
		return &Gimick_Pos[i];
	}
}
//�񐔂ŉ���^�[�Q�b�g
GIMMICK_POS* GetCount_Target(void)
{
	for (int i = 0; i < MAX_TARGET_COUNT; i++)
	{
		return &Gimick_Pos[i];
	}
}
//�R�C��
GIMMICK_POS* GetCoin_(void)
{
	for (int i = 0; i < MAX_COIN; i++)
	{
		return &Gimick_Pos[i];
	}
}