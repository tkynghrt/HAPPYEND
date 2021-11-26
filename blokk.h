#pragma once


#define BLOKK_X 22
#define BLOKK_Y 22


struct BLOKK
{
	D3DXVECTOR2 pos;	//�ʒu
	float size;	//�T�C�Y
	bool isUse;	//�g�p�t���O
	int						texNo;
	int nam;
};

void InitBlokk(void);
void UninitBlokk(void);
void UpdateBlokk(void);
void DrawBlokk(void);

BLOKK* GetBlokk(void);
void SetBlokk(int x,int y, int c);
