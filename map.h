#pragma once
#pragma once
#include "main.h"
#include "renderer.h"

#define MAP_X 32	//���x��ʈ�t�̃u���b�N��	//�ύX�����ۂ�input�G���[�����������̂Ŋ��ɂ�邩���H
#define MAP_Y 17	//���x��ʈ�t�̃u���b�N����
#define BLOCK_SIZE 60

struct MAP
{
	int						num{};
	D3DXVECTOR2				pos{};
};

void InitMap(void);//Init�̍Ō�œǂ܂Ȃ��Ə㏑������Ă��܂�
int SetMap(int mapnam);//�X�e�[�W�Z���N�g�Ƃ��Ŏg���������ǂƂ肠����Init�̑O�œǂ�
