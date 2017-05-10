/****************************************************************************
* �^�C�g��:  ���͏���
* �t�@�C����:input.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2015/06/08
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"manager.h"
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
LPDIRECTINPUTDEVICE8	CInput::g_lpDIDevice[MAX_GAMEPAD_NUM];	//���̓f�o�C�X�ijoypad�j�ւ̃|�C���^
DIJOYSTATE				CInput::g_dijs[MAX_GAMEPAD_NUM];
int						CInput::g_nDevCnt;
LPDIRECTINPUT8			CInput::g_pInput;//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
BYTE					CInput::g_aGamepadState[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
BYTE					CInput::g_aGamepadStateTrigger[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
BYTE					CInput::g_aGamepadStateRelease[MAX_GAMEPAD_NUM][MAX_BUTTON_NUM + MAX_STICKKEY_NUM];
LONG					CInput::g_aGamepadStateStick[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
LONG					CInput::g_aRGamepadStateStick[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
LONG					CInput::g_GamepadCross[MAX_GAMEPAD_NUM][MAX_STICKKEY_NUM / 2];
LONG					CInput::g_GamePadTrigger[MAX_GAMEPAD_NUM];
LPDIRECTINPUTDEVICE8	CInput::g_pDevKeyboard;	//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE					CInput::g_aKeyState[256];		//�L�[�{�[�h�ւ̓��͏�񃏁[�N
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
* �֐���:void InitInput(void)
*
* ����:HINSTANCE hInstance, HWND hWnd
* �߂�l:HRESULT, S_OK
* ���� �C���v�b�g�֐��̏���������
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
* �֐���:void UninitInput(void)
*
* ����:�Ȃ�
* �߂�l:�Ȃ�
* ���� �C���v�b�g�֐��̏I������
*
*******************************************************************************/
void CInput::UninitInput(void){
	if (g_pInput != NULL){
		g_pInput->Release();//���
		g_pInput = NULL;
	}
}
/*******************************************************************************
* �֐���:HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd){
*
* ����:HINSTANCE hInstance, HWND hWnd
* �߂�l:HRESULT, S_OK, E_FAIL
* ���� �L�[�{�[�h�֐��̏���������
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
* �֐���:void UninitKeyboard(void)
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �L�[�{�[�h�֐��̏I������
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
* �֐���:void UpdateKeyboard(void)
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �L�[�{�[�h�֐��̍X�V����
*
*******************************************************************************/
void CInput::UpdateKeyboard(void){
	BYTE aKeyState[256];
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0]))){
		for (int nCntKey = 0; nCntKey < 256; nCntKey++){
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & (aKeyState[nCntKey]);//�g���K�[���莮

			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & (g_aKeyState[nCntKey]);//�����[�X���莮

			g_aKeyState[nCntKey] = aKeyState[nCntKey];//OldKey�̐ݒ�
		}
	}
	else{
		g_pDevKeyboard->Acquire();
	}
}
/*******************************************************************************
* �֐���:bool GetKeyboardPress(int nKey)
*
* ����:  int nKey
* �߂�l:bool�^
* ���� �L�[�{�[�h�̃v���X����
*
*******************************************************************************/
bool CInput::GetKeyboardPress(int nKey){
	return (g_aKeyState[nKey] & 0x80 ? true : false);
}
/*******************************************************************************
* �֐���:bool GetKeyboardPress(int nKey)
*
* ����:  int nKey
* �߂�l:bool�^
* ���� �L�[�{�[�h�̃g���K�[����
*
*******************************************************************************/
bool CInput::GetKeyboardTrigger(int nKey){
	return (g_aKeyStateTrigger[nKey] & 0x80 ? true : false);
}
/*******************************************************************************
* �֐���:bool GetKeyboardPress(int nKey)
*
* ����:  int nKey
* �߂�l:bool�^
* ���� �L�[�{�[�h�̃����[�X����
*
*******************************************************************************/
bool CInput::GetKeyboardRelease(int nKey){
	return (g_aKeyStateRelease[nKey] & 0x80 ? true : false);
}
/*******************************************************************************
* �֐���:InitJoyPad(HWND hWnd)
*
* ����:HWND hWnd
* �߂�l:HRESULT, S_OK, E_FAIL
* ���� �W���C�p�b�h�֐��̏���������
*
*******************************************************************************/
HRESULT CInput::InitJoyPad(HWND hWnd){
	for (g_nDevCnt = 0; g_nDevCnt < MAX_GAMEPAD_NUM; g_nDevCnt++){
		if (g_lpDIDevice[g_nDevCnt] != NULL){
			//���s�����p�b�h�f�o�C�X���J������
			g_lpDIDevice[g_nDevCnt]->Release();
			g_lpDIDevice[g_nDevCnt] = NULL;
		}
		// �f�o�C�X��񋓂��č쐬
		if (FAILED(g_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)) || g_pInput == NULL){
			return E_FAIL;
		}
		if (g_lpDIDevice[g_nDevCnt] == NULL){
			return E_FAIL;
		}
		// �f�[�^�`����ݒ�
		if (FAILED(g_lpDIDevice[g_nDevCnt]->SetDataFormat(&c_dfDIJoystick))){
			return E_FAIL;
		}
		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h
		if (FAILED(g_lpDIDevice[g_nDevCnt]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))){
			return E_FAIL;
		}
		// �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
		if (FAILED(g_lpDIDevice[g_nDevCnt]->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS))){
			return E_FAIL;
		}
		// ���͐���J�n
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
	// �f�o�C�X�̒��ڃf�[�^���擾����
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



				g_aGamepadStateTrigger[nDevCnt][nCntButton] = (g_aGamepadState[nDevCnt][nCntButton] ^ aGamepadState[nDevCnt][nCntButton]) & (aGamepadState[nDevCnt][nCntButton]);//�g���K�[���莮

				g_aGamepadStateRelease[nDevCnt][nCntButton] = (g_aGamepadState[nDevCnt][nCntButton] ^ aGamepadState[nDevCnt][nCntButton]) & (g_aGamepadState[nDevCnt][nCntButton]);//�����[�X���莮

				g_aGamepadState[nDevCnt][nCntButton] = aGamepadState[nDevCnt][nCntButton];//OldKey�̐ݒ�

			}
		}
		// �G���[
		else if (DIERR_INPUTLOST){
			// �A�N�Z�X���̍Ď擾
			g_lpDIDevice[nDevCnt]->Acquire();
		}
	}
}
// �W���C�X�e�B�b�N��񋓂���֐�
BOOL CALLBACK CInput::EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, LPVOID lpContext){

	DIDEVCAPS g_diDevCaps;				//�W���C�X�e�B�b�N�̓��e
	GUID pad_discrimination[MAX_GAMEPAD_NUM];	// �e�f�o�C�X�̎��ʎq���i�[

	for (int nDevCnt = 0; nDevCnt < g_nDevCnt; nDevCnt++)
	{
		if (pad_discrimination[nDevCnt] == lpddi->guidInstance)
			return DIENUM_CONTINUE;
	}

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����B
	if (FAILED(g_pInput->CreateDevice(lpddi->guidInstance, &g_lpDIDevice[g_nDevCnt], NULL))){
		return DIENUM_CONTINUE;
	}
	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(g_lpDIDevice[g_nDevCnt]->GetCapabilities(&g_diDevCaps))){
		// �W���C�X�e�B�b�N�\�͂̎擾�Ɏ��s
		g_lpDIDevice[g_nDevCnt]->Release();
		return DIENUM_CONTINUE;
	}

	// �f�o�C�X�̎��ʎq��ۑ�
	pad_discrimination[g_nDevCnt] = lpddi->guidInstance;

	return DIENUM_STOP;
}
// �W���C�X�e�B�b�N�̎���񋓂���֐�
BOOL CALLBACK CInput::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef){

	// ���̒l�͈̔͂�ݒ�i-1000�`1000�j
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
* �֐���:DIJOYSTATE *getJoyPadState()
*
* ����:
* �߂�l:&g_dijs[0];
* ���� joypad�̏�Ԃ̃Q�b�^�[
*
*******************************************************************************/
DIJOYSTATE *CInput::getJoyPadState(){
	return &g_dijs[0];
}
/*******************************************************************************
* �֐���:bool GetGamePadPress(int nKey)
*
* ����:  int nKey
* �߂�l:bool�^
* ���� �L�[�{�[�h�̃v���X����
*
*******************************************************************************/
bool CInput::GetGamePadPress(int nButton, int nPlayer){
	if (nButton <= GAME_PAD_32){
		return (g_aGamepadState[nPlayer][nButton] & 0x80 ? true : false);
	}
	return (g_aGamepadState[nPlayer][nButton] ? true : false);
}
/*******************************************************************************
* �֐���:bool GetGamePadPress(int nKey)
*
* ����:  int nKey
* �߂�l:bool�^
* ���� �L�[�{�[�h�̃g���K�[����
*
*******************************************************************************/
bool CInput::GetGamePadTrigger(int nButton, int nPlayer){
	if (nButton <= GAME_PAD_32){
		return (g_aGamepadStateTrigger[nPlayer][nButton] & 0x80 ? true : false);
	}
	return (g_aGamepadStateTrigger[nPlayer][nButton] ? true : false);
}
/*******************************************************************************
* �֐���:bool GetGamePadRelease(int nKey)
*
* ����:  int nKey
* �߂�l:bool�^
* ���� �L�[�{�[�h�̃����[�X����
*
*******************************************************************************/
bool CInput::GetGamePadRelease(int nButton, int nPlayer){
	if (nButton <= GAME_PAD_32){
		return (g_aGamepadStateRelease[nPlayer][nButton] & 0x80 ? true : false);
	}
	return (g_aGamepadStateRelease[nPlayer][nButton] ? true : false);
}
/*******************************************************************************
* �֐���:LONG GetGamePadTriggerKey(int nPlayer)
*
* ����:		int nPlayer
* �߂�l:	g_dijs[nPlayer].lZ
* ���� �Q�[���p�b�h�̃g���Q�[�L�[��Ԃ�
*
*******************************************************************************/
LONG CInput::GetGamePadTriggerKey(int nPlayer){
	return g_dijs[nPlayer].lZ;
}
/*******************************************************************************
* �֐���:HRESULT cMouse::InitMouse(HINSTANCE hInstance, HWND hWnd)
*
* ����:	HINSTANCE hInstance, HWND hWnd
* �߂�l: HRESULT
* ���� �}�E�X�N���X�̏������֐�
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
	// �f�o�C�X�̐ݒ�    
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j    
	if (FAILED(pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph))){
		return E_FAIL;
	}

	pDIMouse->Acquire();
	// ���͐���J�n
	return S_OK;
}
/*******************************************************************************
* �֐���:void cMouse::UpdateMouse()
*
* ����:
* �߂�l:
* ���� �}�E�X�N���X�̍X�V����
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
			g_aMouseStateTrigger[nMouseButton] = (g_aMouseState[nMouseButton] ^ aMouseState[nMouseButton]) & (aMouseState[nMouseButton]);//�g���K�[���莮

			g_aMouseStateRelease[nMouseButton] = (g_aMouseState[nMouseButton] ^ aMouseState[nMouseButton]) & (g_aMouseState[nMouseButton]);//�����[�X���莮

			g_aMouseState[nMouseButton] = aMouseState[nMouseButton];//OldMouse�̐ݒ�
		}
	}
	else if (DIERR_INPUTLOST){
		// �A�N�Z�X���̍Ď擾
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
* �֐���:void cMouse::UpdateMouse()
*
* ����:
* �߂�l:
* ���� �}�E�X�N���X�̏I������
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
* �֐���:bool GetMousePress(int nMouseButton)
*
* ����:  int nMouseButton
* �߂�l:bool�^
* ���� �}�E�X�̃v���X����
*
*******************************************************************************/
bool CInput::GetMousePress(int nMouseButton){
	return (CInput::g_aMouseState[nMouseButton] & 0x80 ? true : false);
}
/*******************************************************************************
* �֐���:bool GetMouseTrigger(int nMouseButton)
*
* ����:  int nMouseButton
* �߂�l:bool�^
* ���� �}�E�X�̃g���K�[����
*
*******************************************************************************/
bool CInput::GetMouseTrigger(int nMouseButton){
	return (CInput::g_aMouseStateTrigger[nMouseButton] & 0x80 ? true : false);
}
/*******************************************************************************
* �֐���:bool GetMouseRelease(int nMouseButton)
*
* ����:  int nMouseButton
* �߂�l:bool�^
* ���� �}�E�X�̃����[�X����
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
* �֐���:MOUSE_POINT GetMousePointer()
*
* ����:  �Ȃ�
* �߂�l:MOUSE_POINT�^
* ���� �}�E�X�̂w�x�y�̎擾
*
*******************************************************************************/
MOUSE_POINT CInput::GetMousePointer(){
	return mp;
}