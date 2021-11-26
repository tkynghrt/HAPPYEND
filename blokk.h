#pragma once


#define BLOKK_X 22
#define BLOKK_Y 22


struct BLOKK
{
	D3DXVECTOR2 pos;	//位置
	float size;	//サイズ
	bool isUse;	//使用フラグ
	int						texNo;
	int nam;
};

void InitBlokk(void);
void UninitBlokk(void);
void UpdateBlokk(void);
void DrawBlokk(void);

BLOKK* GetBlokk(void);
void SetBlokk(int x,int y, int c);
