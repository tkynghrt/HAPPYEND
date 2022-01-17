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

	switch (mapnum)//開くテキストを決定
	{
	case 0:
		break;
	case 1://caseの中身全部コピーして読み込むファイルだけ変える
		char fname[] = "stage1.txt";//開くファイルの名前//cppファイルと同じ所に.txtを入れる
		FILE* fp;
		fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
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
	//マップどうりにステージ作成
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			map[y][x].pos = D3DXVECTOR2(((BLOCK_SIZE * x) + (BLOCK_SIZE / 2)), ((BLOCK_SIZE * y) + (BLOCK_SIZE / 2)));//位置を初期化
			switch (map[y][x].num)
			{																//ここにギミックやブロックのSetを入れる
			case 0:

				break;
			case 1:
				SetBlock(map[y][x].pos);
				break;
			case 2:
				SetAcceleBlock(map[y][x].pos, 1);//スピードレベル1で壊れるブロック
				break;
			case 3:
				SetAcceleBlock(map[y][x].pos, 2);//スピードレベル2で壊れるブロック
				break;
			case 4:
				SetAcceleBlock(map[y][x].pos, 3);//スピードレベル3で壊れるブロック
				break;
			case 5:
				SetAcceleBlock(map[y][x].pos, 4);//スピードレベル4で壊れるブロック
				break;
			case 6:
				SetWarp(map[y][x].pos);
				break;
			case 7:
				SetGround(map[y][x].pos);//床
				break;
			case 8:
				SetMoveBlock(map[y][x].pos);//動くブロック
				break;
			case 9:
				SetPlayer(map[y][x].pos); //プレイヤーの位置初期化
				break;
			case 10:
				SetTarget(map[y][x].pos);//最終ターゲット
				break;
			case 11:
				SetCountBlock(map[y][x].pos, 0);//1回当てると壊れるブロック
				break;
			case 12:
				SetCountBlock(map[y][x].pos, 1);//2回当てると壊れるブロック
				break;
			case 13:
				SetCountBlock(map[y][x].pos, 2);//3回当てると壊れるブロック
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