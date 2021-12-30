#include "SpeedPanel.h"
#include "texture.h"
#include "sprite.h"

SPEED_PANEL SpeedPanel[MAX_Panel] = {};

void InitSpeedPanel(void)
{
	//回数で壊れるブロック

	for (int i = 0; i < MAX_Panel; i++)
	{
		SpeedPanel[i].use = false;
		SpeedPanel[i].size = D3DXVECTOR2(60.0f, 60.0f);
	}
}

void UninitSpeedPanel(void)
{

}

void UpdateSpeedPanel(void)
{

}

void DrawSpeedPanel(void)
{
	D3DXCOLOR SpeedPanelkCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < MAX_Panel; i++)
	{
		if (SpeedPanel[i].use)
		{
			DrawSpriteColorRotate(SpeedPanel[i].Texture, SpeedPanel[i].pos.x, SpeedPanel[i].pos.y,
				SpeedPanel[i].size.x, SpeedPanel[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
				SpeedPanelkCol, SpeedPanel[i].rot);
		}
		else
		{
			break;
		}
	}
}

void SetSpeedPanel(D3DXVECTOR2 pos, int type)
{
	for (int i = 0; i < MAX_Panel; i++)
	{
		//まだ表示されていない場所を探す
		if (!SpeedPanel[i].use)
		{
			SpeedPanel[i].pos = pos;
			SpeedPanel[i].type = type;
			SpeedPanel[i].use = true;
			break;
		}
	}
}

SPEED_PANEL* GetSpeedPanel(void)
{
	return SpeedPanel;
}
