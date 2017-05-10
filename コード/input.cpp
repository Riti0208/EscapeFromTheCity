/****************************************************************************
* タイトル:  入力処理
* ファイル名:input.cpp
* 作成者：	 芳崎大地
* 作成日：   2015/06/08
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"manager.h"
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
LPDIRECTINPUTDEVICE8	CInput::g_lpDIDevice[MAX_GAMEPAD_NUM];	//入力デバイス（joypad）へのポインタ
DIJOYSTATE				CInput::g_dijs[MAX_GAMEPAD_NUM];
int						CInput::g_nDevCnt;
LPDIRECTINPUT8			CInput::g_pInput;//DirectInputオブジェクトへのポインタ
BYTE					CInput::g_aGamepadState[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
BYTE					CInput::g_aGamepadStateTrigger[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
BYTE					CInput::g_aGamepadStateRelease[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
LONG					CInput::g_aGamepadStateStick[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
LONG					CInput::g_aRGamepadStateStick[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
LONG					CInput::g_GamepadCross[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
LONG					CInput::g_GamePadTrigger[MAX_GAMEPAD_NUM];
LPDIRECTINPUTDEVICE8	CInput::g_pDevKeyboard;	//入力デバイス（キーボード）へのポインタ
BYTE					CInput::g_aKeyState[256];		//キーボードへの入力情報ワーク
BYTE					CInput::g_aKeyStateTrigger[256];
BYTE					CInput::g_aKeyStateRelease[256];
LPDIRECTINPUTDEVICE8	CInput::pDIMouse;
DIMOUSESTATE2			CInput::dIMouseState;
BYTE					CInput::g_aMouseState[256];
BYTE					CInput::g_aMouseStateTrigger[256];
BYTE					CInput::g_aMouseStateRelease[256];
MOUSE_POINT				CInput::mp;
POINT					CInput::pt;
int						CInput::mouseChargeFlag;
int                     CInput::mouesChargeCnt;
/*******************************************************************************
* 関数名:void InitInput(void)
*
* 引数:HINSTANCE hInstance, HWND hWnd
* 戻り値:HRESULT, S_OK
* 説明 インプット関数の初期化処理
*
*******************************************************************************/
HRESULT CInput::InitInput(HINSTANCE hInstance, HWND hWnd){
	g_pInput = NULL;
	if (g_pInput == NULL){
		if (FAILED(DirectInput8Create(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void **)&g_pInput, NULL))){
		}
	}
	return S_OK;
}
/*******************************************************************************
* 関数名:void UninitInput(void)
*
* 引数:なし
* 戻り値:なし
* 説明 インプット関数の終了処理
*
*******************************************************************************/
void CInput::UninitInput(void){
	if (g_pInput != NULL){
		g_pInput->Release();//解放
		g_pInput = NULL;
	}
}
/*******************************************************************************
* 関数名:HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd){
*
* 引数:HINSTANCE hInstance, HWND hWnd
* 戻り値:HRESULT, S_OK, E_FAIL
* 説明 キーボード関数の初期化処理
*
*******************************************************************************/
HRESULT CInput::InitKeyboard(HINSTANCE hInstance, HWND hWnd){
	if (FAILED(InitInput(hInstance, hWnd))){
		return E_FAIL;
	}
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,
		&g_pDevKeyboard,
		NULL))){
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard))){
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(
		hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))){
		return E_FAIL;
	}
	g_pDevKeyboard->Acquire();

	return S_OK;
}
/*******************************************************************************
* 関数名:void UninitKeyboard(void)
*
* 引数:  なし
* 戻り値:なし
* 説明 キーボード関数の終了処理
*
*******************************************************************************/
void CInput::UninitKeyboard(void){
	if (g_pDevKeyboard != NULL){
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	UninitInput();
}
/*******************************************************************************
* 関数名:void UpdateKeyboard(void)
*
* 引数:  なし
* 戻り値:なし
* 説明 キーボード関数の更新処理
*
*******************************************************************************/
void CInput::UpdateKeyboard(void){
	BYTE aKeyState[256];
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0]))){
		for (int nCntKey = 0; nCntKey < 256; nCntKey++){
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & (aKeyState[nCntKey]);//トリガー判定式

			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & (g_aKeyState[nCntKey]);//リリース判定式

			g_aKeyState[nCntKey] = aKeyState[nCntKey];//OldKeyの設定
		}
	}
	else{
		g_pDevKeyboard->Acquire();
	}
}
/*******************************************************************************
* 関数名:bool GetKeyboardPress(int nKey)
*
* 引数:  int nKey
* 戻り値:bool型
* 説明 キーボードのプレス判定
*
*******************************************************************************/
bool CInput::GetKeyboardPress(int nKey){
	return (g_aKeyState[nKey] & 0x80 ? true : false);
}
/*******************************************************************************
* 関数名:bool GetKeyboardPress(int nKey)
*
* 引数:  int nKey
* 戻り値:bool型
* 説明 キーボードのトリガー判定
*
*******************************************************************************/
bool CInput::GetKeyboardTrigger(int nKey){
	return (g_aKeyStateTrigger[nKey] & 0x80 ? true : false);
}
/*******************************************************************************
* 関数名:bool GetKeyboardPress(int nKey)
*
* 引数:  int nKey
* 戻り値:bool型
* 説明 キーボードのリリース判定
*
*******************************************************************************/
bool CInput::GetKeyboardRelease(int nKey){
	return (g_aKeyStateRelease[nKey] & 0x80 ? true : false);
}
/*******************************************************************************
* 関数名:InitJoyPad(HWND hWnd)
*
* 引数:HWND hWnd
* 戻り値:HRESULT, S_OK, E_FAIL
* 説明 ジョイパッド関数の初期化処理
*
*******************************************************************************/
HRESULT CInput::InitJoyPad(HWND hWnd){
	for (g_nDevCnt = 0; g_nDevCnt < MAX_GAMEPAD_NUM; g_nDevCnt++){
		if (g_lpDIDevice[g_nDevCnt] != NULL){
			//失敗したパッドデバイスを開放する
			g_lpDIDevice[g_nDevCnt]->Release();
			g_lpDIDevice[g_nDevCnt] = NULL;
		}
		// デバイスを列挙して作成
		if (FAILED(g_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)) || g_pInput == NULL){
			return E_FAIL;
		}
		if (g_lpDIDevice[g_nDevCnt] == NULL){
			return E_FAIL;
		}
		// データ形式を設定
		if (FAILED(g_lpDIDevice[g_nDevCnt]->SetDataFormat(&c_dfDIJoystick))){
			return E_FAIL;
		}
		// モードを設定（フォアグラウンド＆非排他モード
		if (FAILED(g_lpDIDevice[g_nDevCnt]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))){
			return E_FAIL;
		}
		// コールバック関数を使って各軸のモードを設定
		if (FAILED(g_lpDIDevice[g_nDevCnt]->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS))){
			return E_FAIL;
		}
		// 入力制御開始
		g_lpDIDevice[g_nDevCnt]->Acquire();
	}
	mp.fPosX = 0.0f;
	mp.fPosY = 0.0f;
	mp.lX = 0.0f;
	mp.lY = 0.0f;
	mp.lZ = 0.0f;
	return S_OK;
}
void CInput::UninitJoyPad(){
	for (int nDevCnt = 0; nDevCnt < MAX_GAMEPAD_NUM; nDevCnt++){
		if (g_lpDIDevice[nDevCnt] != NULL){
			g_lpDIDevice[nDevCnt]->Unacquire();
			g_lpDIDevice[nDevCnt]->Release();
			g_lpDIDevice[nDevCnt] = NULL;
		}
	}
}
void CInput::UpdateJoyPad(){
	// デバイスの直接データを取得する
	BYTE aGamepadState[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM] = { 0 };

	for (int nDevCnt = 0; nDevCnt < MAX_GAMEPAD_NUM; nDevCnt++){
		if (g_lpDIDevice[nDevCnt] == NULL){
			return;
		}
		if (FAILED(g_lpDIDevice[nDevCnt]->Poll())){
			g_lpDIDevice[nDevCnt]->Acquire();
		}
		if (SUCCEEDED(g_lpDIDevice[nDevCnt]->GetDeviceState(sizeof(DIJOYSTATE), &g_dijs[nDevCnt]))){

			for (int nCntButton = 0; nCntButton < MAX_BUTTON_NUM + MAX_STICKKEY_NUM; nCntButton++){
				aGamepadState[nDevCnt][nCntButton] = g_dijs[nDevCnt].rgbButtons[nCntButton];


				g_aGamepadStateStick[nDevCnt][IX_NUM] = g_dijs[nDevCnt].lX;
				g_aGamepadStateStick[nDevCnt][IY_NUM] = g_dijs[nDevCnt].lY;

				g_aRGamepadStateStick[nDevCnt][RX_NUM] = g_dijs[nDevCnt].lRx;
				g_aRGamepadStateStick[nDevCnt][RY_NUM] = g_dijs[nDevCnt].lRy;

				g_GamePadTrigger[nDevCnt] = g_dijs[nDevCnt].lZ;

				g_GamepadCross[nDevCnt][POV_NUM] = g_dijs[nDevCnt].rgdwPOV[POV_NUM];

				g_aGamepadStateStick[nDevCnt][IX_NUM] >= 400 ? aGamepadState[nDevCnt][X_GAME_PAD_LRIGHT] = true : aGamepadState[nDevCnt][X_GAME_PAD_LRIGHT] = false;
				g_aGamepadStateStick[nDevCnt][IX_NUM] <= -400 ? aGamepadState[nDevCnt][X_GAME_PAD_LLEFT] = true : aGamepadState[nDevCnt][X_GAME_PAD_LLEFT] = false;
				g_aGamepadStateStick[nDevCnt][IY_NUM] <= -400 ? aGamepadState[nDevCnt][X_GAME_PAD_LUP] = true : aGamepadState[nDevCnt][X_GAME_PAD_LUP] = false;
				g_aGamepadStateStick[nDevCnt][IY_NUM] >= 400 ? aGamepadState[nDevCnt][X_GAME_PAD_LDOWN] = true : aGamepadState[nDevCnt][X_GAME_PAD_LDOWN] = false;

				g_aRGamepadStateStick[nDevCnt][RX_NUM] >= 320 ? aGamepadState[nDevCnt][X_GAME_PAD_RRIGHT] = true : aGamepadState[nDevCnt][X_GAME_PAD_RRIGHT] = false;
				g_aRGamepadStateStick[nDevCnt][RX_NUM] <= -320 ? aGamepadState[nDevCnt][X_GAME_PAD_RLEFT] = true : aGamepadState[nDevCnt][X_GAME_PAD_RLEFT] = false;
				g_aRGamepadStateStick[nDevCnt][RY_NUM] <= -320 ? aGamepadState[nDevCnt][X_GAME_PAD_RUP] = true : aGamepadState[nDevCnt][X_GAME_PAD_RUP] = false;
				g_aRGamepadStateStick[nDevCnt][RY_NUM] >= 320 ? aGamepadState[nDevCnt][X_GAME_PAD_RDOWN] = true : aGamepadState[nDevCnt][X_GAME_PAD_RDOWN] = false;

				g_GamepadCross[nDevCnt][POV_NUM] <= 31500 && g_GamepadCross[nDevCnt][POV_NUM] >= 22500 ? aGamepadState[nDevCnt][X_GAME_PAD_LEFT] = true : aGamepadState[nDevCnt][X_GAME_PAD_LEFT] = false;
				g_GamepadCross[nDevCnt][POV_NUM] >= 0 && g_GamepadCross[nDevCnt][POV_NUM] <= 4500 ? aGamepadState[nDevCnt][X_GAME_PAD_UP] = true : aGamepadState[nDevCnt][X_GAME_PAD_UP] = false;
				g_GamepadCross[nDevCnt][POV_NUM] <= 13500 && g_GamepadCross[nDevCnt][POV_NUM] >= 4500 ? aGamepadState[nDevCnt][X_GAME_PAD_RIGHT] = true : aGamepadState[nDevCnt][X_GAME_PAD_RIGHT] = false;
				g_GamepadCross[nDevCnt][POV_NUM] <= 22500 && g_GamepadCross[nDevCnt][POV_NUM] >= 13500 ? aGamepadState[nDevCnt][X_GAME_PAD_DOWN] = true : aGamepadState[nDevCnt][X_GAME_PAD_DOWN] = false;



				g_aGamepadStateTrigger[nDevCnt][nCntButton] = (g_aGamepadState[nDevCnt][nCntButton] ^ aGamepadState[nDevCnt][nCntButton]) & (aGamepadState[nDevCnt][nCntButton]);//トリガー判定式

				g_aGamepadStateRelease[nDevCnt][nCntButton] = (g_aGamepadState[nDevCnt][nCntButton] ^ aGamepadState[nDevCnt][nCntButton]) & (g_aGamepadState[nDevCnt][nCntButton]);//リリース判定式

				g_aGamepadState[nDevCnt][nCntButton] = aGamepadState[nDevCnt][nCntButton];//OldKeyの設定

			}
		}
		// エラー
		else if (DIERR_INPUTLOST){
			// アクセス権の再取得
			g_lpDIDevice[nDevCnt]->Acquire();
		}
	}
}
// ジョイスティックを列挙する関数
BOOL CALLBACK CInput::EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, LPVOID lpContext){

	DIDEVCAPS g_diDevCaps;				//ジョイスティックの内容
	GUID pad_discrimination[MAX_GAMEPAD_NUM];	// 各デバイスの識別子を格納

	for (int nDevCnt = 0; nDevCnt < g_nDevCnt; nDevCnt++)
	{
		if (pad_discrimination[nDevCnt] == lpddi->guidInstance)
			return DIENUM_CONTINUE;
	}

	// 列挙されたジョイスティックへのインターフェイスを取得する。
	if (FAILED(g_pInput->CreateDevice(lpddi->guidInstance, &g_lpDIDevice[g_nDevCnt], NULL))){
		return DIENUM_CONTINUE;
	}
	// ジョイスティックの能力を調べる
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(g_lpDIDevice[g_nDevCnt]->GetCapabilities(&g_diDevCaps))){
		// ジョイスティック能力の取得に失敗
		g_lpDIDevice[g_nDevCnt]->Release();
		return DIENUM_CONTINUE;
	}

	// デバイスの識別子を保存
	pad_discrimination[g_nDevCnt] = lpddi->guidInstance;

	return DIENUM_STOP;
}
// ジョイスティックの軸を列挙する関数
BOOL CALLBACK CInput::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef){

	// 軸の値の範囲を設定（-1000～1000）
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj = lpddoi->dwType;
	diprg.diph.dwHow = DIPH_BYID;
	diprg.lMin = -1000;
	diprg.lMax = +1000;
	if (FAILED(g_lpDIDevice[g_nDevCnt]->SetProperty(DIPROP_RANGE, &diprg.diph))){
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}
/*******************************************************************************
* 関数名:DIJOYSTATE *getJoyPadState()
*
* 引数:
* 戻り値:&g_dijs[0];
* 説明 joypadの状態のゲッター
*
*******************************************************************************/
DIJOYSTATE *CInput::getJoyPadState(){
	return &g_dijs[0];
}
/*******************************************************************************
* 関数名:bool GetGamePadPress(int nKey)
*
* 引数:  int nKey
* 戻り値:bool型
* 説明 キーボードのプレス判定
*
*******************************************************************************/
bool CInput::GetGamePadPress(int nButton, int nPlayer){
	if (nButton <= GAME_PAD_32){
		return (g_aGamepadState[nPlayer][nButton] & 0x80 ? true : false);
	}
	return (g_aGamepadState[nPlayer][nButton] ? true : false);
}
/*******************************************************************************
* 関数名:bool GetGamePadPress(int nKey)
*
* 引数:  int nKey
* 戻り値:bool型
* 説明 キーボードのトリガー判定
*
*******************************************************************************/
bool CInput::GetGamePadTrigger(int nButton, int nPlayer){
	if (nButton <= GAME_PAD_32){
		return (g_aGamepadStateTrigger[nPlayer][nButton] & 0x80 ? true : false);
	}
	return (g_aGamepadStateTrigger[nPlayer][nButton] ? true : false);
}
/*******************************************************************************
* 関数名:bool GetGamePadRelease(int nKey)
*
* 引数:  int nKey
* 戻り値:bool型
* 説明 キーボードのリリース判定
*
*******************************************************************************/
bool CInput::GetGamePadRelease(int nButton, int nPlayer){
	if (nButton <= GAME_PAD_32){
		return (g_aGamepadStateRelease[nPlayer][nButton] & 0x80 ? true : false);
	}
	return (g_aGamepadStateRelease[nPlayer][nButton] ? true : false);
}
/*******************************************************************************
* 関数名:LONG GetGamePadTriggerKey(int nPlayer)
*
* 引数:		int nPlayer
* 戻り値:	g_dijs[nPlayer].lZ
* 説明 ゲームパッドのトリゲーキーを返す
*
*******************************************************************************/
LONG CInput::GetGamePadTriggerKey(int nPlayer){
	return g_dijs[nPlayer].lZ;
}
/*******************************************************************************
* 関数名:HRESULT cMouse::InitMouse(HINSTANCE hInstance, HWND hWnd)
*
* 引数:	HINSTANCE hInstance, HWND hWnd
* 戻り値: HRESULT
* 説明 マウスクラスの初期化関数
*
*******************************************************************************/
HRESULT CInput::InitMouse(HINSTANCE hInstance, HWND hWnd){
	if (FAILED(InitInput(hInstance, hWnd))){
		return E_FAIL;
	}
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &pDIMouse, NULL))){
		return E_FAIL;
	}
	if (FAILED(pDIMouse->SetDataFormat(&c_dfDIMouse2))){
		return E_FAIL;
	}
	if (FAILED(pDIMouse->SetCooperativeLevel(
		hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))){
		return E_FAIL;
	}
	// デバイスの設定    
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）    
	if (FAILED(pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph))){
		return E_FAIL;
	}

	pDIMouse->Acquire();
	// 入力制御開始
	return S_OK;
}
/*******************************************************************************
* 関数名:void cMouse::UpdateMouse()
*
* 引数:
* 戻り値:
* 説明 マウスクラスの更新処理
*
*******************************************************************************/
void CInput::UpdateMouse(){
	BYTE aMouseState[MAX_MOUSE_BUTTON];

	dIMouseState.rgbButtons[0];

	for (int nMouseButton = 0; nMouseButton < MAX_MOUSE_BUTTON; nMouseButton++){
		aMouseState[nMouseButton] = dIMouseState.rgbButtons[nMouseButton];
	}

	if (SUCCEEDED(pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &dIMouseState))){
		for (int nMouseButton = 0; nMouseButton < MAX_MOUSE_BUTTON; nMouseButton++){
			g_aMouseStateTrigger[nMouseButton] = (g_aMouseState[nMouseButton] ^ aMouseState[nMouseButton]) & (aMouseState[nMouseButton]);//トリガー判定式

			g_aMouseStateRelease[nMouseButton] = (g_aMouseState[nMouseButton] ^ aMouseState[nMouseButton]) & (g_aMouseState[nMouseButton]);//リリース判定式

			g_aMouseState[nMouseButton] = aMouseState[nMouseButton];//OldMouseの設定
		}
	}
	else if (DIERR_INPUTLOST){
		// アクセス権の再取得
		pDIMouse->Acquire();
	}

	mp.fPosX = (float)pt.x + 8.0f;
	mp.fPosY = (float)pt.y + 14.0f;

	mp.lX = (float)dIMouseState.lX;
	mp.lY = (float)dIMouseState.lY;
	mp.lZ = (float)dIMouseState.lZ;

	if (GetMousePress(MOUSE_LEFT))	mouesChargeCnt++;

}
/*******************************************************************************
* 関数名:void cMouse::UpdateMouse()
*
* 引数:
* 戻り値:
* 説明 マウスクラスの終了処理
*
*******************************************************************************/
void CInput::UninitMouse(){
	if (pDIMouse != NULL){
		pDIMouse->Unacquire();
		pDIMouse->Release();
		pDIMouse = NULL;
	}
}
/*******************************************************************************
* 関数名:bool GetMousePress(int nMouseButton)
*
* 引数:  int nMouseButton
* 戻り値:bool型
* 説明 マウスのプレス判定
*
*******************************************************************************/
bool CInput::GetMousePress(int nMouseButton){
	return (CInput::g_aMouseState[nMouseButton] & 0x80 ? true : false);
}
/*******************************************************************************
* 関数名:bool GetMouseTrigger(int nMouseButton)
*
* 引数:  int nMouseButton
* 戻り値:bool型
* 説明 マウスのトリガー判定
*
*******************************************************************************/
bool CInput::GetMouseTrigger(int nMouseButton){
	return (CInput::g_aMouseStateTrigger[nMouseButton] & 0x80 ? true : false);
}
/*******************************************************************************
* 関数名:bool GetMouseRelease(int nMouseButton)
*
* 引数:  int nMouseButton
* 戻り値:bool型
* 説明 マウスのリリース判定
*
*******************************************************************************/
bool CInput::GetMouseRelease(int nMouseButton){
	return (CInput::g_aMouseStateRelease[nMouseButton] & 0x80 ? true : false);
}
bool CInput::GetMouseCharge(int nMouseButton, int nMaxFrame){
	if (GetMouseRelease(nMouseButton)){
		mouesChargeCnt = 0;
		return false;
	}
	if (mouesChargeCnt > nMaxFrame)		{
		return true;
	}
	return false;
}
/*******************************************************************************
* 関数名:MOUSE_POINT GetMousePointer()
*
* 引数:  なし
* 戻り値:MOUSE_POINT型
* 説明 マウスのＸＹＺの取得
*
*******************************************************************************/
MOUSE_POINT CInput::GetMousePointer(){
	return mp;
}