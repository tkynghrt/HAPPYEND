//=============================================================================
//
// ���͏��� [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include <XInput.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �v���O������������Ƃ��Ɏg��
#define	USE_KEYBOARD				// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define	USE_MOUSE					// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define	USE_PAD						// �錾����ƃp�b�h�ő���\�ɂȂ�


/* game pad��� */
//#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
//#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
//#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
//#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)

//#define BUTTON_A		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
//#define BUTTON_B		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
//#define BUTTON_C		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
//#define BUTTON_X		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
//#define BUTTON_Y		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
//#define BUTTON_Z		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
//#define BUTTON_L		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
//#define BUTTON_R		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
//#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
//#define BUTTON_M		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)

//#define BUTTON_X		0x00000010l	// �w�{�^��(.rgbButtons[0]&0x80)
//#define BUTTON_A		0x00000020l	// �`�{�^��(.rgbButtons[1]&0x80)
//#define BUTTON_B		0x00000040l	// �a�{�^��(.rgbButtons[2]&0x80)
//#define BUTTON_Y		0x00000080l	// �x�{�^��(.rgbButtons[3]&0x80)
//#define BUTTON_L		0x00000100l	// �k�{�^��(.rgbButtons[4]&0x80)
//#define BUTTON_R		0x00000200l	// �q�{�^��(.rgbButtons[5]&0x80)
//#define BUTTON_L2		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
//#define BUTTON_R2		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
//#define BUTTON_SELECT	0x00001000l	// �y�{�^��(.rgbButtons[8]&0x80)
//#define BUTTON_START	0x00002000l	// �r�s�`�q�s�{�^��(.rgbButtons[9]&0x80)

//#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

//enum {	// �{�^���ɑ΂���rgbButtons[?]�z��̔z��ԍ�(DirectInput��ł�XYAB�{�^���ʒu�ɍ��킹��)
//	rgbButtons_X,
//	rgbButtons_A,
//	rgbButtons_B,
//	rgbButtons_Y,
//	rgbButtons_L,
//	rgbButtons_R,
//	rgbButtons_L2,
//	rgbButtons_R2,
//	rgbButtons_SELECT,
//	rgbButtons_START,
//};


///////////////////////////////////////////////////////////////////////////////////////////
//����������Xinput�Ɋւ�����															 //
///////////////////////////////////////////////////////////////////////////////////////////

//��1������padNo�̓p�b�h�i���o�[�̂Ȃ��Ă鐔�B0����X�^�[�g���邽�߂Ƃ肠����0��OK
//main.h�̃��C�u���������N��#pragma comment (lib, "xinput.lib")�̒ǉ�
//input.cpp�̒��g�̍����ւ��̓L�[�{�[�h�̖�������̂ŏ��X�҂��āB�i�������Ƃ�邩�ǂ����܂Œǂ����ĂȂ�

//�{�^���ꗗ

// XINPUT_GAMEPAD_DPAD_UP			�\���L�[��
// XINPUT_GAMEPAD_DPAD_DOWN			�\���L�[��
// XINPUT_GAMEPAD_DPAD_LEFT			�\���L�[��
// XINPUT_GAMEPAD_DPAD_RIGHT		�\���L�[�E
// XINPUT_GAMEPAD_START
// XINPUT_GAMEPAD_BACK
// XINPUT_GAMEPAD_LEFT_THUMB		L�X�e�B�b�N��������
// XINPUT_GAMEPAD_RIGHT_THUMB		R�X�e�B�b�N��������
// XINPUT_GAMEPAD_LEFT_SHOULDER		L�{�^��
// XINPUT_GAMEPAD_RIGHT_SHOULDER	R�{�^��
// XINPUT_GAMEPAD_A
// XINPUT_GAMEPAD_B
// XINPUT_GAMEPAD_X
// XINPUT_GAMEPAD_Y

//�X�e�B�b�N�͈̔�
// X�� ��-32768�@�E 32767
// Y�� �� 32767�@��-32768

//�g���K�[�͈̔�
// 0 �` 255

// �o�C�u���[�V�����͈̔�
// 0 �` 255

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
long GetMouseX(void);               // �}�E�X��x���W
long GetMouseY(void);               // �}�E�X��y���W
POINT GetMouse(void);               // �}�E�X��xy���W

//---------------------------- game pad
//BOOL IsButtonPressed(int padNo,DWORD button);
//BOOL IsButtonTriggered(int padNo,DWORD button);

int GetThumbLeftX(int padNo); //���X�e�B�b�N��x�����擾�@��1�����F�p�b�h�̃i���o�[
int GetThumbLeftY(int padNo); //���X�e�B�b�N��y�����擾�@��1�����F�p�b�h�̃i���o�[
int GetThumbRightX(int padNo); //�E�X�e�B�b�N��x�����擾�@��1�����F�p�b�h�̃i���o�[
int GetThumbRightY(int padNo); //�E�X�e�B�b�N��y�����擾�@��1�����F�p�b�h�̃i���o�[

void SetLeftVibration(int padNo, int speed); //���T�C�h�̃o�C�u���[�V�����@��1�����F�p�b�h�̃i���o�[�A��2�����F�o�C�u�̑��x
void SetRightVibration(int padNo, int speed); //�E�T�C�h�̃o�C�u���[�V�����@��1�����F�p�b�h�̃i���o�[�A��2�����F�o�C�u�̑��x
void SetVibration(int padNo, int speed); //���T�C�h�̃o�C�u���[�V�����@��1�����F�p�b�h�̃i���o�[�A��2�����F�o�C�u�̑��x
void StopVibration(int padNo); //�o�C�u���[�V�����̒�~

int GetLeftTrigger(int padNo);//L2���ǂꂮ�炢�����ꂽ��
int GetRightTrigger(int padNo);//R2���ǂꂮ�炢�����ꂽ��

BOOL IsButtonPressed(int padNo, DWORD button); //���̃{�^����������Ă��邩�ǂ����@��1�����F�p�b�h�̃i���o�[�A��2�����F�ǂ̃{�^���𔻒肷�邩
BOOL IsButtonTriggered(int padNo, DWORD button); //���̃{�^���������ꂽ���ǂ����@��1�����F�p�b�h�̃i���o�[�A��2�����F�ǂ̃{�^���𔻒肷�邩

