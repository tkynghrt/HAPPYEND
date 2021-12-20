#pragma once
#pragma once
#include "main.h"
#include "renderer.h"

#define MAP_X 32	//丁度画面一杯のブロック幅	//変更した際にinputエラーが発生したので環境によるかも？
#define MAP_Y 17	//丁度画面一杯のブロック高さ
#define BLOCK_SIZE 60

struct MAP
{
	int						num{};
	D3DXVECTOR2				pos{};
};

void InitMap(void);//Initの最後で読まないと上書きされてしまう
int SetMap(int mapnam);//ステージセレクトとかで使いたいけどとりあえずInitの前で読む
