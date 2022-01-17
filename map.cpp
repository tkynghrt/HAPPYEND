#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "map.h"
#include "player.h"
#include "block.h"
#include "ground.h"
#include "count_block.h"
#include "accele_block.h"
#include "move_block.h"
#include "coin.h"
#include "Target_Normal.h"
#include "SpeedPanel.h"
#include "warp.h"

MAP	map[MAP_Y][MAP_X];

int SetMap(int mapnum) {

	switch (mapnum)//�J���e�L�X�g������
	{
	case 0:
		break;
	case 1://case�̒��g�S���R�s�[���ēǂݍ��ރt�@�C�������ς���
		char fname[] = "stage1.txt";//�J���t�@�C���̖��O//cpp�t�@�C���Ɠ�������.txt������
		FILE* fp;
		fp = fopen(fname, "r"); // �t�@�C�����J���B���s�����NULL��Ԃ��B
		if (fp == NULL) {
			printf("%s file not open!\n", fname);
			return -1;
		}
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				(void)fscanf(fp, "%d", &map[i][j].num);
			}
		}
		fclose(fp);
		break;
	}

	return 0;
}


void InitMap(void)
{
	//�}�b�v�ǂ���ɃX�e�[�W�쐬
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			map[y][x].pos = D3DXVECTOR2(((BLOCK_SIZE * x) + (BLOCK_SIZE / 2)), ((BLOCK_SIZE * y) + (BLOCK_SIZE / 2)));//�ʒu��������
			switch (map[y][x].num)
			{																//�����ɃM�~�b�N��u���b�N��Set������
			case 0:

				break;
			case 1:
				SetBlock(map[y][x].pos);
				break;
			case 2:
				SetAcceleBlock(map[y][x].pos, 1);//�X�s�[�h���x��1�ŉ���u���b�N
				break;
			case 3:
				SetAcceleBlock(map[y][x].pos, 2);//�X�s�[�h���x��2�ŉ���u���b�N
				break;
			case 4:
				SetAcceleBlock(map[y][x].pos, 3);//�X�s�[�h���x��3�ŉ���u���b�N
				break;
			case 5:
				SetAcceleBlock(map[y][x].pos, 4);//�X�s�[�h���x��4�ŉ���u���b�N
				break;
			case 6:
				SetWarp(map[y][x].pos);
				break;
			case 7:
				SetGround(map[y][x].pos);//��
				break;
			case 8:
				SetMoveBlock(map[y][x].pos);//�����u���b�N
				break;
			case 9:
				SetPlayer(map[y][x].pos); //�v���C���[�̈ʒu������
				break;
			case 10:
				SetTarget(map[y][x].pos);//�ŏI�^�[�Q�b�g
				break;
			case 11:
				SetCountBlock(map[y][x].pos, 0);//1�񓖂Ă�Ɖ���u���b�N
				break;
			case 12:
				SetCountBlock(map[y][x].pos, 1);//2�񓖂Ă�Ɖ���u���b�N
				break;
			case 13:
				SetCountBlock(map[y][x].pos, 2);//3�񓖂Ă�Ɖ���u���b�N
				break;
			case 14:
				
				break;
			case 15:
				SetSpeedPanel(map[y][x].pos, SPEED_UP);
				break;
			case 16:
				SetSpeedPanel(map[y][x].pos, SPEED_DOWN);
				break;
			}
		}
	}
}