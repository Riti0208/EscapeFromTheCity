/****************************************************************************
* タイトル:  inputヘッダー
* ファイル名:input.h
* 作成者：	 芳崎大地
* 作成日：   2015/06/08
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _INPUT_H_
#define _INPUT_H_

#pragma comment(lib, "dinput8.lib")//入力時に必要

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"main.h"
#define DIRECTINPUT_VERSION		(0x0800)
#include "dinput.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/

#define MAX_GAMEPAD_NUM			(4)
#define MAX_BUTTON_NUM			(32)
#define MAX_STICKKEY_NUM		(12)

#define IX_NUM					(0)
#define IY_NUM					(1)

#define RX_NUM					(0)
#define RY_NUM					(1)

#define POV_NUM					(0)


#define GAME_PAD_1				(0)
#define GAME_PAD_2				(1)
#define GAME_PAD_3				(2)
#define GAME_PAD_4				(3)
#define GAME_PAD_5				(4)
#define GAME_PAD_6				(5)
#define GAME_PAD_7				(6)
#define GAME_PAD_8				(7)
#define GAME_PAD_9				(8)
#define GAME_PAD_10				(9)
#define GAME_PAD_11				(10)
#define GAME_PAD_12				(11)
#define GAME_PAD_13				(12)
#define GAME_PAD_14				(13)
#define GAME_PAD_15				(14)
#define GAME_PAD_16				(15)
#define GAME_PAD_17				(16)
#define GAME_PAD_18				(17)
#define GAME_PAD_19				(18)
#define GAME_PAD_20				(19)
#define GAME_PAD_21				(20)
#define GAME_PAD_22				(21)
#define GAME_PAD_23				(22)
#define GAME_PAD_24				(23)
#define GAME_PAD_25				(24)
#define GAME_PAD_26				(25)
#define GAME_PAD_27				(26)
#define GAME_PAD_28				(27)
#define GAME_PAD_29				(28)
#define GAME_PAD_30				(29)
#define GAME_PAD_31				(30)
#define GAME_PAD_32				(31)

#define X_GAME_PAD_A				(0)
#define X_GAME_PAD_B				(1)
#define X_GAME_PAD_X				(2)
#define X_GAME_PAD_Y				(3)
#define X_GAME_PAD_LB				(4)
#define X_GAME_PAD_RB				(5)
#define X_GAME_PAD_BACK				(6)
#define X_GAME_PAD_START			(7)
#define X_GAME_PAD_LSB				(8)
#define X_GAME_PAD_RSB				(9)
#define X_GAME_PAD_LT				(10)
#define X_GAME_PAD_RT				(11)
#define X_GAME_PAD_13				(12)
#define X_GAME_PAD_14				(13)
#define X_GAME_PAD_15				(14)
#define X_GAME_PAD_16				(15)
#define X_GAME_PAD_17				(16)
#define X_GAME_PAD_18				(17)
#define X_GAME_PAD_19				(18)
#define X_GAME_PAD_20				(19)
#define X_GAME_PAD_21				(20)
#define X_GAME_PAD_22				(21)
#define X_GAME_PAD_23				(22)
#define X_GAME_PAD_24				(23)
#define X_GAME_PAD_25				(24)
#define X_GAME_PAD_26				(25)
#define X_GAME_PAD_27				(26)
#define X_GAME_PAD_28				(27)
#define X_GAME_PAD_29				(28)
#define X_GAME_PAD_30				(29)
#define X_GAME_PAD_31				(30)
#define X_GAME_PAD_32				(31)

#define X_GAME_PAD_LUP				(32)
#define X_GAME_PAD_LDOWN			(33)
#define X_GAME_PAD_LRIGHT			(34)
#define X_GAME_PAD_LLEFT			(35)

#define X_GAME_PAD_RUP				(36)
#define X_GAME_PAD_RDOWN			(37)
#define X_GAME_PAD_RRIGHT			(38)
#define X_GAME_PAD_RLEFT			(39)

#define X_GAME_PAD_LEFT				(40)
#define X_GAME_PAD_UP				(41)
#define X_GAME_PAD_RIGHT			(42)
#define X_GAME_PAD_DOWN				(43)

#define GAME_PAD_UP				(32)
#define GAME_PAD_DOWN			(33)
#define GAME_PAD_RIGHT			(34)
#define GAME_PAD_LEFT			(35)

#define MAX_MOUSE_BUTTON		(8)

#define MOUSE_LEFT				(0)
#define MOUSE_RIGHT				(1)
#define MOUSE_WHEEL				(2)
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
typedef struct{
	float lX;
	float lY;
	float lZ;
	float fPosX;
	float fPosY;
}MOUSE_POINT;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
class CInput{
private:
	static LPDIRECTINPUTDEVICE8 g_lpDIDevice[MAX_GAMEPAD_NUM];	//入力デバイス（joypad）へのポインタ
	static DIJOYSTATE g_dijs[MAX_GAMEPAD_NUM];
	static int g_nDevCnt;
	static LPDIRECTINPUT8 g_pInput;//DirectInputオブジェクトへのポインタ
	static BYTE g_aGamepadState[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
	static BYTE g_aGamepadStateTrigger[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
	static BYTE g_aGamepadStateRelease[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
	static LONG g_aGamepadStateStick[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
	static LONG g_aRGamepadStateStick[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
	static LONG g_GamepadCross[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
	static LONG g_GamePadTrigger[MAX_GAMEPAD_NUM];
	static LPDIRECTINPUTDEVICE8	g_pDevKeyboard;	//入力デバイス（キーボード）へのポインタ
	static BYTE g_aKeyState[256];		//キーボードへの入力情報ワーク
	static BYTE g_aKeyStateTrigger[256];
	static BYTE g_aKeyStateRelease[256];
	static LPDIRECTINPUTDEVICE8 pDIMouse;
	static DIMOUSESTATE2 dIMouseState;
	static BYTE g_aMouseState[256];
	static BYTE g_aMouseStateTrigger[256];
	static BYTE g_aMouseStateRelease[256];
	static BYTE g_aMouseStateCharge[256];
	static MOUSE_POINT mp;
	static int mouseChargeFlag;
	static int mouesChargeCnt;
public:
	CInput(){}
	~CInput(){}
	static HRESULT InitJoyPad(HWND hWnd);
	static void UninitJoyPad(void);
	static void UpdateJoyPad(void);
	static DIJOYSTATE *getJoyPadState();
	static bool GetGamePadPress(int nButton, int nPlayer);
	static bool GetGamePadTrigger(int nButton, int nPlayer);
	static bool GetGamePadRelease(int nButton, int nPlayer);
	static HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
	static void UninitInput();
	static HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	static void UninitKeyboard(void);
	static void UpdateKeyboard(void);
	static bool GetKeyboardPress(int nKey);
	static bool GetKeyboardTrigger(int nKey);
	static bool GetKeyboardRelease(int nKey);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, LPVOID lpContext);
	static BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef);
	static void UpdateMouse();
	static HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
	static void UninitMouse();
	static LONG GetGamePadTriggerKey(int nPlayer);
	static MOUSE_POINT GetMousePointer();
	static bool GetMousePress(int nMouseButton);
	static bool GetMouseTrigger(int nMouseButton);
	static bool GetMouseRelease(int nMouseButton);
	static bool GetMouseCharge(int nMouseButton, int nMaxFrame);
	static POINT pt;
};

#endif