//�S�M�~�b�N�̃|�W�V�����͂����ŊǗ�

#include "All_Gimmick_Pos.h"


//�n�ʂ̍��W
#define GROUND (SCREEN_HEIGHT - ground->size.y - (60 / 2))

GIMMICK_POS Gimick_Pos[MAX_GIMMICK];

HRESULT InitAllGimmickPos(void)
{

	//�ړ�����u���b�N�̍��W
	Gimick_Pos[0].move_block_pos = D3DXVECTOR2(300.0f, 350.0f);

	//�񐔂ŉ���u���b�N�̍��W
	Gimick_Pos[0].count_block_pos = D3DXVECTOR2(800.0f, GROUND);

	//�X�s�[�h���x���ŉ���u���b�N�̍��W
	Gimick_Pos[0].accele_block_pos = D3DXVECTOR2(100.0f, GROUND);

	//�R�C���̍��W
	Gimick_Pos[0].coin = D3DXVECTOR2(500.0f, GROUND);

return S_OK;
}

GIMMICK_POS* GetGimmick_Pos(void)
{
	for (int i = 0; i < 1; i++)
	{
		return &Gimick_Pos[i];
	}
}