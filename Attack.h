#pragma once
#include "main.h"
#include "renderer.h"


// �U���\����
struct ATTACK
{
	bool					use;					// true:�g���Ă���  false:���g�p
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �|���S���̍��W
	float					rot;					// �|���S���̉�]��
	int						texNo;					// ���Ԗڂ̃e�N�X�`���[���g�p����̂�
	int						texNo2;
	D3DXVECTOR2             move;                   //���x
	int						mode;
	int						flame;
};

HRESULT InitAttack(void);
void UninitAttack(void);
void UpdateAttack(void);
void DrawAttack(void);

ATTACK *GetAttack(void);
void SetAttack(int mode, D3DXVECTOR2 pos);
