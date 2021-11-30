//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)

// game pad�p�ݒ�l
//#define DEADZONE			2500			// �e����25%�𖳌��]�[���Ƃ���
#define DEADZONE			8200			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX			1000			// �L���͈͂̍ő�l
#define RANGE_MIN			-1000			// �L���͈͂̍ŏ��l
#define MAX_CONTROLLERS     4


struct CONTROLER_STATE
{
	XINPUT_STATE		lastState;
	XINPUT_STATE		state;
	XINPUT_STATE		trigger;
	XINPUT_VIBRATION	vibration;
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow); // �}�E�X�̏�����
void UninitMouse();						// �}�E�X�̏I������
HRESULT UpdateMouse();					// �}�E�X�̍X�V����

HRESULT InitializePad(void);			// �p�b�h������
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//------------------------------- keyboard
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
BYTE					g_keyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

//--------------------------------- mouse
static LPDIRECTINPUTDEVICE8 pMouse = NULL; // mouse

static DIMOUSESTATE2   mouseState;		// �}�E�X�̃_�C���N�g�ȏ��
static DIMOUSESTATE2   mouseTrigger;	// �����ꂽ�u�Ԃ���ON

POINT g_mouse_point;
//--------------------------------- game pad

//static LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = {NULL,NULL,NULL,NULL};// �p�b�h�f�o�C�X
//
//static DWORD	padState[GAMEPADMAX];	// �p�b�h���i�����Ή��j
//static DWORD	padTrigger[GAMEPADMAX];
//static int		padCount = 0;			// ���o�����p�b�h�̐�
CONTROLER_STATE g_Controllers[MAX_CONTROLLERS];

//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if (!g_pDInput)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// �L�[�{�[�h�̏�����
	InitKeyboard(hInst, hWnd);

	// �}�E�X�̏�����
	InitializeMouse(hInst, hWnd);

	// �p�b�h�̏�����
	InitializePad();

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitInput(void)
{
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	// �}�E�X�̏I������
	UninitMouse();

	// �p�b�h�̏I������
	UninitPad();

	if (g_pDInput)
	{
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdateInput(void)
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	// �}�E�X�̍X�V
	UpdateMouse();

	// �p�b�h�̍X�V
	UpdatePad();

}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if (FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void UninitKeyboard(void)
{
	if (g_pDIDevKeyboard)
	{
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�̍X�V
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// �O��̃f�[�^��ۑ�
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	// �f�o�C�X����f�[�^���擾
	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
	if (SUCCEEDED(hr))
	{
		for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];
			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];

			if (g_keyState[cnt])
			{
				g_keyStateRepeatCnt[cnt]++;
				if (g_keyStateRepeatCnt[cnt] >= 20)
				{
					g_keyStateRepeat[cnt] = g_keyState[cnt];
				}
			}
			else
			{
				g_keyStateRepeatCnt[cnt] = 0;
				g_keyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}


//=============================================================================
// �}�E�X�֌W�̏���
//=============================================================================
// �}�E�X�̏�����
HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow)
{
	HRESULT result;
	// �f�o�C�X�쐬
	result = g_pDInput->CreateDevice(GUID_SysMouse, &pMouse, NULL);
	if (FAILED(result) || pMouse == NULL)
	{
		MessageBox(hWindow, "No mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// �f�[�^�t�H�[�}�b�g�ݒ�
	result = pMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(result))
	{
		MessageBox(hWindow, "Can't setup mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// ���̃A�v���Ƌ������[�h�ɐݒ�
	result = pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(result))
	{
		MessageBox(hWindow, "Mouse mode error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD prop;

	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// �}�E�X�̈ړ��l�@���Βl

	result = pMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(result))
	{
		MessageBox(hWindow, "Mouse property error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	// �A�N�Z�X���𓾂�
	pMouse->Acquire();
	return result;
}
//---------------------------------------------------------
void UninitMouse()
{
	if (pMouse)
	{
		pMouse->Unacquire();
		pMouse->Release();
		pMouse = NULL;
	}

}
//-----------------------------------------------------------
HRESULT UpdateMouse()
{
	HRESULT result;
	// �O��̒l�ۑ�
	DIMOUSESTATE2 lastMouseState = mouseState;
	// �f�[�^�擾
	result = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(result))
	{
		mouseTrigger.lX = mouseState.lX;
		mouseTrigger.lY = mouseState.lY;
		mouseTrigger.lZ = mouseState.lZ;
		// �}�E�X�̃{�^�����
		for (int i = 0; i < 8; i++)
		{
			mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);
		}
	}
	else	// �擾���s
	{
		// �A�N�Z�X���𓾂Ă݂�
		result = pMouse->Acquire();
	}
	return result;

}

//----------------------------------------------
BOOL IsMouseLeftPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// �����ꂽ�Ƃ��ɗ��r�b�g������
}
BOOL IsMouseLeftTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
}
BOOL IsMouseRightPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[1] & 0x80);
}
BOOL IsMouseRightTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
}
BOOL IsMouseCenterPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[2] & 0x80);
}
BOOL IsMouseCenterTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
}
//------------------
long GetMouseX(void) //�}�E�X��x���W�̎擾(long�^)
{
	GetCursorPos(&g_mouse_point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &g_mouse_point);
	return g_mouse_point.x;
}
long GetMouseY(void) //�}�E�X��x���W�̎擾(long�^)
{
	GetCursorPos(&g_mouse_point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &g_mouse_point);
	return g_mouse_point.y;
}
POINT GetMouse(void) //�}�E�X��xy���W�̎擾(POINT�\���̌^�B���g��long�^��x��y)
{
	GetCursorPos(&g_mouse_point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &g_mouse_point);
	return g_mouse_point;
}
//================================================= game pad
//---------------------------------------- �R�[���o�b�N�֐�
//BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID )
//{
//	HRESULT result;
//
//	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
//	return DIENUM_CONTINUE;	// ���̃f�o�C�X���
//
//}
//---------------------------------------- ������
HRESULT InitializePad(void)			// �p�b�h������
{
	//	HRESULT		result;
	//	int			i;
	//
	//	padCount = 0;
	//	// �W���C�p�b�h��T��
	//	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	//	// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B
	//
	//	for ( i=0 ; i<padCount ; i++ ) {
	//		// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	//		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
	//		if ( FAILED(result) )
	//			return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s
	//
	//		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	////		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	////		if ( FAILED(result) )
	////			return false; // ���[�h�̐ݒ�Ɏ��s
	//
	//		// ���̒l�͈̔͂�ݒ�
	//		// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
	//		// (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
	//		// ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
	//		DIPROPRANGE				diprg;
	//		ZeroMemory(&diprg, sizeof(diprg));
	//		diprg.diph.dwSize		= sizeof(diprg); 
	//		diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	//		diprg.diph.dwHow		= DIPH_BYOFFSET; 
	//		diprg.lMin				= RANGE_MIN;
	//		diprg.lMax				= RANGE_MAX;
	//		// X���͈̔͂�ݒ�
	//		diprg.diph.dwObj		= DIJOFS_X; 
	//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
	//		// Y���͈̔͂�ݒ�
	//		diprg.diph.dwObj		= DIJOFS_Y;
	//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
	//
	//		// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
	//		// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
	//		// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
	//		DIPROPDWORD				dipdw;
	//		dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
	//		dipdw.diph.dwHeaderSize	= sizeof(dipdw.diph);
	//		dipdw.diph.dwHow		= DIPH_BYOFFSET;
	//		dipdw.dwData			= DEADZONE;
	//		//X���̖����]�[����ݒ�
	//		dipdw.diph.dwObj		= DIJOFS_X;
	//		pGamePad[i]->SetProperty( DIPROP_DEADZONE, &dipdw.diph);
	//		//Y���̖����]�[����ݒ�
	//		dipdw.diph.dwObj		= DIJOFS_Y;
	//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
	//			
	//		//�W���C�X�e�B�b�N���͐���J�n
	//		pGamePad[i]->Acquire();
	//	}
		//������
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	XInputEnable(true);

	return S_OK;

}
//------------------------------------------- �I������
void UninitPad(void)
{
	/*for (int i=0 ; i<GAMEPADMAX ; i++) {
		if ( pGamePad[i] )
		{
			pGamePad[i]->Unacquire();
			pGamePad[i]->Release();
		}
	}*/
	//�p�����[�^�̃��Z�b�g
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	//�o�C�u���[�V������~
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		XInputSetState(i, &g_Controllers[i].vibration);

	XInputEnable(false);
}

//------------------------------------------ �X�V
//float GY, GX;

void UpdatePad(void)
{
	//HRESULT			result;
	//DIJOYSTATE2		dijs;
	//int				i;

	//for ( i=0 ; i<padCount ; i++ ) 
	//{
	//	DWORD lastPadState;
	//	lastPadState = padState[i];
	//	padState[i] = 0x00000000l;	// ������

	//	result = pGamePad[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
	//	if ( FAILED(result) ) {
	//		result = pGamePad[i]->Acquire();
	//		while ( result == DIERR_INPUTLOST )
	//			result = pGamePad[i]->Acquire();
	//	}

	//	result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
	//	if ( result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED ) {
	//		result = pGamePad[i]->Acquire();
	//		while ( result == DIERR_INPUTLOST )
	//			result = pGamePad[i]->Acquire();
	//	}

	//	// �R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���
	//	//* y-axis (forward)
	//	if ( dijs.lY < 0 )					padState[i] |= BUTTON_UP;
	//	//* y-axis (backward)
	//	if ( dijs.lY > 0 )					padState[i] |= BUTTON_DOWN;
	//	//* x-axis (left)
	//	if ( dijs.lX < 0 )					padState[i] |= BUTTON_LEFT;
	//	//* x-axis (right)
	//	if ( dijs.lX > 0 )					padState[i] |= BUTTON_RIGHT;
	//	//* �w�{�^��
	//	if (dijs.rgbButtons[rgbButtons_X] & 0x80)	padState[i] |= BUTTON_X;
	//	//* �`�{�^��
	//	if ( dijs.rgbButtons[rgbButtons_A] & 0x80 )	padState[i] |= BUTTON_A;
	//	//* �a�{�^��
	//	if ( dijs.rgbButtons[rgbButtons_B] & 0x80 )	padState[i] |= BUTTON_B;
	//	//* �x�{�^��
	//	if (dijs.rgbButtons[rgbButtons_Y] & 0x80)	padState[i] |= BUTTON_Y;
	//	//* �k�{�^��
	//	if ( dijs.rgbButtons[rgbButtons_L] & 0x80 )	padState[i] |= BUTTON_L;
	//	//* �q�{�^��
	//	if ( dijs.rgbButtons[rgbButtons_R] & 0x80 )	padState[i] |= BUTTON_R;
	//	//* �k2�{�^��
	//	if (dijs.rgbButtons[rgbButtons_L2] & 0x80)	padState[i] |= BUTTON_L2;
	//	//* �q2�{�^��
	//	if (dijs.rgbButtons[rgbButtons_R2] & 0x80)	padState[i] |= BUTTON_R2;
	//	//* Select�{�^��
	//	if (dijs.rgbButtons[rgbButtons_SELECT] & 0x80)	padState[i] |= BUTTON_SELECT;
	//	//* �r�s�`�q�s�{�^��
	//	if ( dijs.rgbButtons[rgbButtons_START] & 0x80 )	padState[i] |= BUTTON_START;

	//	// Trigger�ݒ�
	//	padTrigger[i] = ((lastPadState ^ padState[i])	// �O��ƈ���Ă���
	//					& padState[i]);					// ��������ON�̂��
	//	
	//}

	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		XInputSetState(i, &g_Controllers[i].vibration);

		g_Controllers[i].lastState = g_Controllers[i].state;

		//����FERROR_SUCCESS�@0
		//�ڑ������FERROR_DEVICE_NOT_CONNECTED 1167
		DWORD result;
		result = XInputGetState(i, &g_Controllers[i].state);

		//�g���K�[�쐬
		g_Controllers[i].trigger.Gamepad.wButtons = ((g_Controllers[i].lastState.Gamepad.wButtons ^ g_Controllers[i].state.Gamepad.wButtons) & g_Controllers[i].state.Gamepad.wButtons);

		//L�X�e�B�b�NX���̃f�b�h�]�[���ݒ�
		if (fabs(g_Controllers[i].state.Gamepad.sThumbLX) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbLX = 0;
		//L�X�e�B�b�NY���̃f�b�h�]�[���ݒ�
		if (fabs(g_Controllers[i].state.Gamepad.sThumbLY) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbLY = 0;
		//R�X�e�B�b�NX���̃f�b�h�]�[���ݒ�
		if (fabs(g_Controllers[i].state.Gamepad.sThumbRX) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbRX = 0;
		//R�X�e�B�b�NY���̃f�b�h�]�[���ݒ�
		if (fabs(g_Controllers[i].state.Gamepad.sThumbRY) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbRY = 0;
	}

}

//�X�e�B�b�N�͈̔�
// X ��-32768�@�E 32767
// Y �� 32767�@��-32768
int GetThumbLeftX(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.sThumbLX;
}

int GetThumbLeftY(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.sThumbLY;
}

int GetThumbRightX(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.sThumbRX;
}

int GetThumbRightY(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.sThumbRY;
}

//�g���K�[�͈̔�
// 0 �` 255
int GetLeftTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bLeftTrigger;
}

int GetRightTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bRightTrigger;
}

// �o�C�u���[�V�����͈̔�
// 0 �` 255
void SetLeftVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
}

void SetRightVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void SetVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
	g_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void StopVibration(int padNo)
{
	g_Controllers[padNo].vibration.wLeftMotorSpeed = 0;
	g_Controllers[padNo].vibration.wRightMotorSpeed = 0;
}

BOOL IsButtonPressed(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].state.Gamepad.wButtons);
}

BOOL IsButtonTriggered(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].trigger.Gamepad.wButtons);
}


