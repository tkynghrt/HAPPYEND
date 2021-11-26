//=============================================================================
//
// �����蔻�菈�� [collision.h]
// Author : 
//
//=============================================================================
#pragma once

#define PI 3.14159265f // �~����
#define VIEW_WIDTH 640 // ��ʕ� 
#define VIEW_HEIGHT 480 // ��ʍ��� 
#define CIRCLE_VEL 5.0f // �~�`���� 
struct F_CIRCLE {
	float x, y; // ���S�ʒu 
	float r; // ���a 
};
struct F_RECT_CIRCLE {
	float x, y; // �n�_�ʒu 
	float vx, vy; // �x�N�g�� 
	float r; // ������T�C�Y 
};
//���΂̓����蔻��
enum class F_OLD_SURFACE{
	no_hit,
	up,
	right,
	left,
	down
};

//����2
enum class CHECK_HIT{
	no_hit,
	hit
};

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIMELEFT	2
#define BALLACCELE	(2.0f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void UpdateCollision(void);
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
F_OLD_SURFACE CollisionKOBA(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos, 
							D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size);

F_OLD_SURFACE CollisionKOBA2(D3DXVECTOR2 player_pos, D3DXVECTOR2 block_pos, D3DXVECTOR2 player_old_pos,
	D3DXVECTOR2 block_old_pos, D3DXVECTOR2 player_size, D3DXVECTOR2 block_size, D3DXVECTOR2 block_velocity);


