/****************************************************************************
* �^�C�g��:  ���C�������i���[�v�����j
* �t�@�C����:main.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/04/18
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"main.h"
#include"renderer.h"
#include <stdio.h>
#include <io.h>
#include <Fcntl.h>
#include"manager.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd);
void Update();
void Draw();
void Uninit();
void DrawFPS();
void SetClientWindowSize(HWND hWnd, int width, int height);
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
int g_nCountFPS;						//FPS�J�E���^
HWND hWnd;								//�E�C���h�E�̃n���h��
int hConsole;
CManager manager;
int	g_changeFase;
/*******************************************************************************
* �֐���:int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
*
* ����:  HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
* �߂�l:msg.wParam;
* ���� ���C���֐�
*
*******************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DWORD dwFrameCount;		//�t���[���J�E���^
	DWORD dwCurrentTime;	//���݂̎���
	DWORD dwExecLastTime;	//�O��̎���
	DWORD dwFPSLastTime;	//�O�񎞂̂e�o�r
	//---------------------------------------------------------------------------
	//�E�C���h�E�N���X�̍쐬
	//---------------------------------------------------------------------------
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),			//�\���̂̃T�C�Y
		CS_CLASSDC,					//�E�C���h�E�X�^�C��
		WndProc,					//�R�[���o�b�N�֐��ւ̃|�C���^
		0,							//�E�C���h�E�\���̂̌��Ɋ��蓖�Ă�⑫�o�C�g��
		0,							//�E�C���h�E�C���X�^���X�̌��Ɋ��蓖�Ă�o�C�g��
		hInstance,					//�E�C���h�E�v���V�[�W���̃C���X�^���X�n���h��
		NULL,						//�A�C�R���̃n���h��
		LoadCursor(NULL, IDC_ARROW),//�}�E�X�J�[�\���̃n���h��
		(HBRUSH)(COLOR_WINDOW + 1),	//�E�C���h�E�w�i�F
		NULL,						//�f�t�H���g���j���[��
		"EscapeFromTheCity",			//���̃E�C���h�E�N���X�ɂ��閼�O
		NULL						//16 * 16�̏������T�C�Y�̃A�C�R��
	};
	HWND hWnd;						//�E�C���h�E�̃n���h��
	MSG msg;
	RegisterClassEx(&wcex);			//�E�C���h�N���X�̓o�^
	//----------------------------------------------------------------------------------------------
	//�E�C���h�E�̍쐬
	//----------------------------------------------------------------------------------------------
	hWnd = CreateWindowEx(			//�E�C���h�E�̍쐬
		0,
		"EscapeFromTheCity",			//wcex�Œ�`�����N���X��
		"EscapeFromTheCity",			//�^�C�g���o�[�ɕ\�����镶����
		WS_OVERLAPPEDWINDOW,		//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�C���h�E����X���W�i�K���̏ꍇ��CW_USEDEFAULT�ł���
		CW_USEDEFAULT,				//�E�C���h�E����Y���W�i�K���̏ꍇ��CW_USEDEFAULT�ł���
		(int)SCREEN_WIDTH,				//�E�C���h�E���i�K���ł����ꍇ��CW_USEDEFAULT�ł���
		(int)SCREEN_HEIGHT,				//�E�C���h�E�����i�K���ł����ꍇ��CW_USEDEFAULT�ł���
		NULL,						//�e�E�C���h�E�̃n���h��
		NULL,						//�E�C���h�E�𐶐�����Ƃ��̃��W���[���̃C���X�^���X�̃n���h��
		hInstance,					//�쐬���ꂽ�E�B���h�E�̃n���h���A���s�����ꍇ��NULL�̒l
		NULL
		);
	//----------------------------------------------------------------------------------------------
	//Init�����s�ł��Ȃ��������̏���
	//----------------------------------------------------------------------------------------------
	if (FAILED(Init(hInstance, hWnd))){
		return -1;
	}

	timeBeginPeriod(1);

	dwFrameCount = dwCurrentTime = 0;
	dwExecLastTime = dwFPSLastTime = timeGetTime();

	ShowWindow(hWnd, nCmdShow);		//�E�C���h�E�̕\�����@�̎w��	
	UpdateWindow(hWnd);				//�X�V�������E�C���h�E�̃n���h���̎w��

	g_changeFase = 0;

	// WS_CAPTION�����̐ݒ�
	LONG lStyle;

	lStyle = GetWindowLong(hWnd, GWL_STYLE);
	lStyle |= WS_CAPTION;
	lStyle = SetWindowLong(hWnd, GWL_STYLE, lStyle);

	//�E�B���h�E����ʂɍ��킹��

	//----------------------------------------------------------------------------------------------
	//���C�����[�v
	//----------------------------------------------------------------------------------------------
	while (1){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0){
			if (msg.message == WM_QUIT){
				break;
			}
			else{
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W��|��
				DispatchMessage(&msg);		//�E�C���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o����
			}
		}
		else{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500){
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwFPSLastTime) >= (1000 / 60)){
				dwExecLastTime = dwCurrentTime;

				Update();	//�X�V����

				Draw();		//�`�揈��

				dwFrameCount++;
			}
		}
	}

	Uninit();			//�I������

	UnregisterClass("EscapeFromTheCity", hInstance);	//�E�C���h�E�N���X�����������������������

	timeEndPeriod(1);

	return msg.wParam;
}
/*******************************************************************************
* �֐���:LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
*
* ����:  HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
* �߂�l:DefWindowProc( hWnd, uMsg, wParam, lParam )
* ����
*
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	int nID;
	switch (uMsg){
	case WM_DESTROY:			//�E�C���h�E���j�������ꍇ
		PostQuitMessage(0);		//�I������
		break;
	case WM_KEYDOWN:
		switch (wParam){
		case VK_ESCAPE:			//E�����������ꂽ�Ƃ�
			nID = MessageBox(hWnd, "�I�����܂���", "�I������", MB_YESNO);
			if (nID == IDYES){
				DestroyWindow(hWnd);	//�E�C���h�E�̔j��
			}
			break;
		case VK_F1 :
			// WS_CAPTION�����̐ݒ�
			LONG lStyle;
			HDC hdc = GetDC(hWnd);
			int dispx = GetDeviceCaps(hdc, HORZRES);
			int dispy = GetDeviceCaps(hdc, VERTRES);
			switch (g_changeFase){
			case 0:


				lStyle = GetWindowLong(hWnd, GWL_STYLE);
				lStyle |= WS_CAPTION;
				lStyle = SetWindowLong(hWnd, GWL_STYLE, lStyle);

				MoveWindow(hWnd, GetSystemMetrics(SM_XVIRTUALSCREEN),
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2, TRUE);
				break;
			case 1:


				lStyle = GetWindowLong(hWnd, GWL_STYLE);
				lStyle &= ~WS_CAPTION;
				lStyle = SetWindowLong(hWnd, GWL_STYLE, lStyle);

				MoveWindow(hWnd, GetSystemMetrics(SM_XVIRTUALSCREEN),
					GetSystemMetrics(SM_YVIRTUALSCREEN),
					SCREEN_WIDTH,
					SCREEN_HEIGHT, TRUE);
				//�E�B���h�E����ʂɍ��킹��
				break;
			}
			ReleaseDC(hWnd, hdc);
			g_changeFase++;
			if (g_changeFase == 2)	g_changeFase = 0;
			break;
		}
		break;
	case WM_NCHITTEST:
		GetCursorPos(&CInput::pt);
		ScreenToClient(hWnd, &CInput::pt);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
/*******************************************************************************
* �֐���:void Init()
*
* ����:  void,�Ȃ�
* �߂�l:void,�Ȃ�
* ���� ����������
*
*******************************************************************************/
HRESULT Init(HINSTANCE hInstance, HWND hWnd){
	manager.Init(hInstance, hWnd);
	return S_OK;
}
/*******************************************************************************
* �֐���:void Uninit()
*
* ����:  void,�Ȃ�
* �߂�l:void,�Ȃ�
* ���� �I������
*
*******************************************************************************/
void Uninit(){
	manager.Uninit();
}
/*******************************************************************************
* �֐���:void Update()
*
* ����:  void,�Ȃ�
* �߂�l:void,�Ȃ�
* ���� �X�V����
*
*******************************************************************************/
void Update(){
	manager.Update();
}
/*******************************************************************************
* �֐���:void Draw()
*
* ����:  void,�Ȃ�
* �߂�l:void,�Ȃ�
* ���� �`�揈��
*
*******************************************************************************/
void Draw(){
	manager.Draw();
}
/*******************************************************************************
* �֐���:HWND GetHWnd(void)
*
* ����:  void,�Ȃ�
* �߂�l:�Ȃ�
* ���� �E�B���h�E�n���h���[�̎擾
*
*******************************************************************************/
HWND GetHWnd(void){
	return hWnd;
}
/*******************************************************************************
* �֐���:int GetFPS()
*
* ����:  void,�Ȃ�
* �߂�l:int g_FPS
* ���� �`�揈��
*
*******************************************************************************/
int GetFPS(){
	return g_nCountFPS;
}
void SetClientWindowSize(HWND hWnd, int width, int height){
	RECT windowRect;
	GetWindowRect(hWnd, &windowRect);
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	int clientWidth = clientRect.right - clientRect.left;
	int clientHeight = clientRect.bottom - clientRect.top;

	int deltaWidth = windowWidth - clientWidth;
	int deltaHeight = windowHeight - clientHeight;

	int newWindowWidth = width + deltaWidth;
	int newWindowHeight = height + deltaHeight;

	MoveWindow(hWnd, windowRect.left, windowRect.top,
		newWindowWidth, newWindowHeight, FALSE);
}