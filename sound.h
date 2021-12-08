
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);
void UninitSound(void);

int LoadSound(char* pFilename);
void PlaySound(int index, int loopCount);
void ReplaySound(int index);//�v���C�T�E���h������������łȂ��Ǝd�����Ȃ�
void StopSound(int index);
void PauseSound(int index);
void StopSoundAll(void);

