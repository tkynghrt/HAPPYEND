//=============================================================================
//
// 入力処理 [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include <XInput.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// プログラム分けするときに使う
#define	USE_KEYBOARD				// 宣言するとキーボードで操作可能になる
#define	USE_MOUSE					// 宣言するとマウスで操作可能になる
#define	USE_PAD						// 宣言するとパッドで操作可能になる


/* game pad情報 */
//#define BUTTON_UP		0x00000001l	// 方向キー上(.IY<0)
//#define BUTTON_DOWN		0x00000002l	// 方向キー下(.IY>0)
//#define BUTTON_LEFT		0x00000004l	// 方向キー左(.IX<0)
//#define BUTTON_RIGHT	0x00000008l	// 方向キー右(.IX>0)

//#define BUTTON_A		0x00000010l	// Ａボタン(.rgbButtons[0]&0x80)
//#define BUTTON_B		0x00000020l	// Ｂボタン(.rgbButtons[1]&0x80)
//#define BUTTON_C		0x00000040l	// Ｃボタン(.rgbButtons[2]&0x80)
//#define BUTTON_X		0x00000080l	// Ｘボタン(.rgbButtons[3]&0x80)
//#define BUTTON_Y		0x00000100l	// Ｙボタン(.rgbButtons[4]&0x80)
//#define BUTTON_Z		0x00000200l	// Ｚボタン(.rgbButtons[5]&0x80)
//#define BUTTON_L		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)
//#define BUTTON_R		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)
//#define BUTTON_START	0x00001000l	// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
//#define BUTTON_M		0x00002000l	// Ｍボタン(.rgbButtons[9]&0x80)

//#define BUTTON_X		0x00000010l	// Ｘボタン(.rgbButtons[0]&0x80)
//#define BUTTON_A		0x00000020l	// Ａボタン(.rgbButtons[1]&0x80)
//#define BUTTON_B		0x00000040l	// Ｂボタン(.rgbButtons[2]&0x80)
//#define BUTTON_Y		0x00000080l	// Ｙボタン(.rgbButtons[3]&0x80)
//#define BUTTON_L		0x00000100l	// Ｌボタン(.rgbButtons[4]&0x80)
//#define BUTTON_R		0x00000200l	// Ｒボタン(.rgbButtons[5]&0x80)
//#define BUTTON_L2		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)
//#define BUTTON_R2		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)
//#define BUTTON_SELECT	0x00001000l	// Ｚボタン(.rgbButtons[8]&0x80)
//#define BUTTON_START	0x00002000l	// ＳＴＡＲＴボタン(.rgbButtons[9]&0x80)

//#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット

//enum {	// ボタンに対するrgbButtons[?]配列の配列番号(DirectInput上でのXYABボタン位置に合わせた)
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
//↓ここからXinputに関する情報															 //
///////////////////////////////////////////////////////////////////////////////////////////

//第1引数のpadNoはパッドナンバーのつなげてる数。0からスタートするためとりあえず0でOK
//main.hのライブラリリンクに#pragma comment (lib, "xinput.lib")の追加
//input.cppの中身の差し替えはキーボードの問題もあるので少々待って。（整合性とれるかどうかまで追いついてない

//ボタン一覧

// XINPUT_GAMEPAD_DPAD_UP			十字キー上
// XINPUT_GAMEPAD_DPAD_DOWN			十字キー下
// XINPUT_GAMEPAD_DPAD_LEFT			十字キー左
// XINPUT_GAMEPAD_DPAD_RIGHT		十字キー右
// XINPUT_GAMEPAD_START
// XINPUT_GAMEPAD_BACK
// XINPUT_GAMEPAD_LEFT_THUMB		Lスティック押し込み
// XINPUT_GAMEPAD_RIGHT_THUMB		Rスティック押し込み
// XINPUT_GAMEPAD_LEFT_SHOULDER		Lボタン
// XINPUT_GAMEPAD_RIGHT_SHOULDER	Rボタン
// XINPUT_GAMEPAD_A
// XINPUT_GAMEPAD_B
// XINPUT_GAMEPAD_X
// XINPUT_GAMEPAD_Y

//スティックの範囲
// X軸 左-32768　右 32767
// Y軸 上 32767　下-32768

//トリガーの範囲
// 0 ～ 255

// バイブレーションの範囲
// 0 ～ 255

//*****************************************************************************
// プロトタイプ宣言
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
BOOL IsMouseLeftPressed(void);      // 左クリックした状態
BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
long GetMouseX(void);               // マウスのx座標
long GetMouseY(void);               // マウスのy座標
POINT GetMouse(void);               // マウスのxy座標

//---------------------------- game pad
//BOOL IsButtonPressed(int padNo,DWORD button);
//BOOL IsButtonTriggered(int padNo,DWORD button);

int GetThumbLeftX(int padNo); //左スティックのx成分取得　第1引数：パッドのナンバー
int GetThumbLeftY(int padNo); //左スティックのy成分取得　第1引数：パッドのナンバー
int GetThumbRightX(int padNo); //右スティックのx成分取得　第1引数：パッドのナンバー
int GetThumbRightY(int padNo); //右スティックのy成分取得　第1引数：パッドのナンバー

void SetLeftVibration(int padNo, int speed); //左サイドのバイブレーション　第1引数：パッドのナンバー、第2引数：バイブの速度
void SetRightVibration(int padNo, int speed); //右サイドのバイブレーション　第1引数：パッドのナンバー、第2引数：バイブの速度
void SetVibration(int padNo, int speed); //両サイドのバイブレーション　第1引数：パッドのナンバー、第2引数：バイブの速度
void StopVibration(int padNo); //バイブレーションの停止

int GetLeftTrigger(int padNo);//L2がどれぐらい押されたか
int GetRightTrigger(int padNo);//R2がどれぐらい押されたか

BOOL IsButtonPressed(int padNo, DWORD button); //そのボタンが押されているかどうか　第1引数：パッドのナンバー、第2引数：どのボタンを判定するか
BOOL IsButtonTriggered(int padNo, DWORD button); //そのボタンが押されたかどうか　第1引数：パッドのナンバー、第2引数：どのボタンを判定するか

