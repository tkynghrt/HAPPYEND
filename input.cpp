//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)

// game pad用設定値
//#define DEADZONE			2500			// 各軸の25%を無効ゾーンとする
#define DEADZONE			8200			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX			1000			// 有効範囲の最大値
#define RANGE_MIN			-1000			// 有効範囲の最小値
#define MAX_CONTROLLERS     4


struct CONTROLER_STATE
{
	XINPUT_STATE		lastState;
	XINPUT_STATE		state;
	XINPUT_STATE		trigger;
	XINPUT_VIBRATION	vibration;
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow); // マウスの初期化
void UninitMouse();						// マウスの終了処理
HRESULT UpdateMouse();					// マウスの更新処理

HRESULT InitializePad(void);			// パッド初期化
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//------------------------------- keyboard
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
BYTE					g_keyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
BYTE					g_keyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

//--------------------------------- mouse
static LPDIRECTINPUTDEVICE8 pMouse = NULL; // mouse

static DIMOUSESTATE2   mouseState;		// マウスのダイレクトな状態
static DIMOUSESTATE2   mouseTrigger;	// 押された瞬間だけON

POINT g_mouse_point;
//--------------------------------- game pad

//static LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = {NULL,NULL,NULL,NULL};// パッドデバイス
//
//static DWORD	padState[GAMEPADMAX];	// パッド情報（複数対応）
//static DWORD	padTrigger[GAMEPADMAX];
//static int		padCount = 0;			// 検出したパッドの数
CONTROLER_STATE g_Controllers[MAX_CONTROLLERS];

//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if (!g_pDInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// キーボードの初期化
	InitKeyboard(hInst, hWnd);

	// マウスの初期化
	InitializeMouse(hInst, hWnd);

	// パッドの初期化
	InitializePad();

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// マウスの終了処理
	UninitMouse();

	// パッドの終了処理
	UninitPad();

	if (g_pDInput)
	{
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();

	// マウスの更新
	UpdateMouse();

	// パッドの更新
	UpdatePad();

}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if (FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
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
// キーボードの更新
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	// デバイスからデータを取得
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
		// キーボードへのアクセス権を取得
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}


//=============================================================================
// マウス関係の処理
//=============================================================================
// マウスの初期化
HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow)
{
	HRESULT result;
	// デバイス作成
	result = g_pDInput->CreateDevice(GUID_SysMouse, &pMouse, NULL);
	if (FAILED(result) || pMouse == NULL)
	{
		MessageBox(hWindow, "No mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// データフォーマット設定
	result = pMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(result))
	{
		MessageBox(hWindow, "Can't setup mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// 他のアプリと協調モードに設定
	result = pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(result))
	{
		MessageBox(hWindow, "Mouse mode error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	// デバイスの設定
	DIPROPDWORD prop;

	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値　相対値

	result = pMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(result))
	{
		MessageBox(hWindow, "Mouse property error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	// アクセス権を得る
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
	// 前回の値保存
	DIMOUSESTATE2 lastMouseState = mouseState;
	// データ取得
	result = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(result))
	{
		mouseTrigger.lX = mouseState.lX;
		mouseTrigger.lY = mouseState.lY;
		mouseTrigger.lZ = mouseState.lZ;
		// マウスのボタン状態
		for (int i = 0; i < 8; i++)
		{
			mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);
		}
	}
	else	// 取得失敗
	{
		// アクセス権を得てみる
		result = pMouse->Acquire();
	}
	return result;

}

//----------------------------------------------
BOOL IsMouseLeftPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
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
long GetMouseX(void) //マウスのx座標の取得(long型)
{
	GetCursorPos(&g_mouse_point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &g_mouse_point);
	return g_mouse_point.x;
}
long GetMouseY(void) //マウスのx座標の取得(long型)
{
	GetCursorPos(&g_mouse_point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &g_mouse_point);
	return g_mouse_point.y;
}
POINT GetMouse(void) //マウスのxy座標の取得(POINT構造体型。中身はlong型でxとy)
{
	GetCursorPos(&g_mouse_point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &g_mouse_point);
	return g_mouse_point;
}
//================================================= game pad
//---------------------------------------- コールバック関数
//BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID )
//{
//	HRESULT result;
//
//	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
//	return DIENUM_CONTINUE;	// 次のデバイスを列挙
//
//}
//---------------------------------------- 初期化
HRESULT InitializePad(void)			// パッド初期化
{
	//	HRESULT		result;
	//	int			i;
	//
	//	padCount = 0;
	//	// ジョイパッドを探す
	//	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	//	// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。
	//
	//	for ( i=0 ; i<padCount ; i++ ) {
	//		// ジョイスティック用のデータ・フォーマットを設定
	//		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
	//		if ( FAILED(result) )
	//			return false; // データフォーマットの設定に失敗
	//
	//		// モードを設定（フォアグラウンド＆非排他モード）
	////		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	////		if ( FAILED(result) )
	////			return false; // モードの設定に失敗
	//
	//		// 軸の値の範囲を設定
	//		// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
	//		// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
	//		// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドの性能による)
	//		DIPROPRANGE				diprg;
	//		ZeroMemory(&diprg, sizeof(diprg));
	//		diprg.diph.dwSize		= sizeof(diprg); 
	//		diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	//		diprg.diph.dwHow		= DIPH_BYOFFSET; 
	//		diprg.lMin				= RANGE_MIN;
	//		diprg.lMax				= RANGE_MAX;
	//		// X軸の範囲を設定
	//		diprg.diph.dwObj		= DIJOFS_X; 
	//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
	//		// Y軸の範囲を設定
	//		diprg.diph.dwObj		= DIJOFS_Y;
	//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
	//
	//		// 各軸ごとに、無効のゾーン値を設定する。
	//		// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
	//		// 指定する値は、10000に対する相対値(2000なら20パーセント)。
	//		DIPROPDWORD				dipdw;
	//		dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
	//		dipdw.diph.dwHeaderSize	= sizeof(dipdw.diph);
	//		dipdw.diph.dwHow		= DIPH_BYOFFSET;
	//		dipdw.dwData			= DEADZONE;
	//		//X軸の無効ゾーンを設定
	//		dipdw.diph.dwObj		= DIJOFS_X;
	//		pGamePad[i]->SetProperty( DIPROP_DEADZONE, &dipdw.diph);
	//		//Y軸の無効ゾーンを設定
	//		dipdw.diph.dwObj		= DIJOFS_Y;
	//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
	//			
	//		//ジョイスティック入力制御開始
	//		pGamePad[i]->Acquire();
	//	}
		//初期化
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	XInputEnable(true);

	return S_OK;

}
//------------------------------------------- 終了処理
void UninitPad(void)
{
	/*for (int i=0 ; i<GAMEPADMAX ; i++) {
		if ( pGamePad[i] )
		{
			pGamePad[i]->Unacquire();
			pGamePad[i]->Release();
		}
	}*/
	//パラメータのリセット
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	//バイブレーション停止
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		XInputSetState(i, &g_Controllers[i].vibration);

	XInputEnable(false);
}

//------------------------------------------ 更新
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
	//	padState[i] = 0x00000000l;	// 初期化

	//	result = pGamePad[i]->Poll();	// ジョイスティックにポールをかける
	//	if ( FAILED(result) ) {
	//		result = pGamePad[i]->Acquire();
	//		while ( result == DIERR_INPUTLOST )
	//			result = pGamePad[i]->Acquire();
	//	}

	//	result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
	//	if ( result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED ) {
	//		result = pGamePad[i]->Acquire();
	//		while ( result == DIERR_INPUTLOST )
	//			result = pGamePad[i]->Acquire();
	//	}

	//	// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
	//	//* y-axis (forward)
	//	if ( dijs.lY < 0 )					padState[i] |= BUTTON_UP;
	//	//* y-axis (backward)
	//	if ( dijs.lY > 0 )					padState[i] |= BUTTON_DOWN;
	//	//* x-axis (left)
	//	if ( dijs.lX < 0 )					padState[i] |= BUTTON_LEFT;
	//	//* x-axis (right)
	//	if ( dijs.lX > 0 )					padState[i] |= BUTTON_RIGHT;
	//	//* Ｘボタン
	//	if (dijs.rgbButtons[rgbButtons_X] & 0x80)	padState[i] |= BUTTON_X;
	//	//* Ａボタン
	//	if ( dijs.rgbButtons[rgbButtons_A] & 0x80 )	padState[i] |= BUTTON_A;
	//	//* Ｂボタン
	//	if ( dijs.rgbButtons[rgbButtons_B] & 0x80 )	padState[i] |= BUTTON_B;
	//	//* Ｙボタン
	//	if (dijs.rgbButtons[rgbButtons_Y] & 0x80)	padState[i] |= BUTTON_Y;
	//	//* Ｌボタン
	//	if ( dijs.rgbButtons[rgbButtons_L] & 0x80 )	padState[i] |= BUTTON_L;
	//	//* Ｒボタン
	//	if ( dijs.rgbButtons[rgbButtons_R] & 0x80 )	padState[i] |= BUTTON_R;
	//	//* Ｌ2ボタン
	//	if (dijs.rgbButtons[rgbButtons_L2] & 0x80)	padState[i] |= BUTTON_L2;
	//	//* Ｒ2ボタン
	//	if (dijs.rgbButtons[rgbButtons_R2] & 0x80)	padState[i] |= BUTTON_R2;
	//	//* Selectボタン
	//	if (dijs.rgbButtons[rgbButtons_SELECT] & 0x80)	padState[i] |= BUTTON_SELECT;
	//	//* ＳＴＡＲＴボタン
	//	if ( dijs.rgbButtons[rgbButtons_START] & 0x80 )	padState[i] |= BUTTON_START;

	//	// Trigger設定
	//	padTrigger[i] = ((lastPadState ^ padState[i])	// 前回と違っていて
	//					& padState[i]);					// しかも今ONのやつ
	//	
	//}

	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		XInputSetState(i, &g_Controllers[i].vibration);

		g_Controllers[i].lastState = g_Controllers[i].state;

		//正常：ERROR_SUCCESS　0
		//接続無し：ERROR_DEVICE_NOT_CONNECTED 1167
		DWORD result;
		result = XInputGetState(i, &g_Controllers[i].state);

		//トリガー作成
		g_Controllers[i].trigger.Gamepad.wButtons = ((g_Controllers[i].lastState.Gamepad.wButtons ^ g_Controllers[i].state.Gamepad.wButtons) & g_Controllers[i].state.Gamepad.wButtons);

		//LスティックX軸のデッドゾーン設定
		if (fabs(g_Controllers[i].state.Gamepad.sThumbLX) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbLX = 0;
		//LスティックY軸のデッドゾーン設定
		if (fabs(g_Controllers[i].state.Gamepad.sThumbLY) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbLY = 0;
		//RスティックX軸のデッドゾーン設定
		if (fabs(g_Controllers[i].state.Gamepad.sThumbRX) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbRX = 0;
		//RスティックY軸のデッドゾーン設定
		if (fabs(g_Controllers[i].state.Gamepad.sThumbRY) < DEADZONE)
			g_Controllers[i].state.Gamepad.sThumbRY = 0;
	}

}

//スティックの範囲
// X 左-32768　右 32767
// Y 上 32767　下-32768
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

//トリガーの範囲
// 0 ～ 255
int GetLeftTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bLeftTrigger;
}

int GetRightTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bRightTrigger;
}

// バイブレーションの範囲
// 0 ～ 255
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


