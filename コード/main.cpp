/****************************************************************************
* タイトル:  メイン処理（ループ処理）
* ファイル名:main.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/04/18
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"main.h"
#include"renderer.h"
#include <stdio.h>
#include <io.h>
#include <Fcntl.h>
#include"manager.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd);
void Update();
void Draw();
void Uninit();
void DrawFPS();
void SetClientWindowSize(HWND hWnd, int width, int height);
/*******************************************************************************
* グローバル変数
*******************************************************************************/
int g_nCountFPS;						//FPSカウンタ
HWND hWnd;								//ウインドウのハンドル
int hConsole;
CManager manager;
int	g_changeFase;
/*******************************************************************************
* 関数名:int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
*
* 引数:  HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
* 戻り値:msg.wParam;
* 説明 メイン関数
*
*******************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DWORD dwFrameCount;		//フレームカウンタ
	DWORD dwCurrentTime;	//現在の時間
	DWORD dwExecLastTime;	//前回の時間
	DWORD dwFPSLastTime;	//前回時のＦＰＳ
	//---------------------------------------------------------------------------
	//ウインドウクラスの作成
	//---------------------------------------------------------------------------
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),			//構造体のサイズ
		CS_CLASSDC,					//ウインドウスタイル
		WndProc,					//コールバック関数へのポインタ
		0,							//ウインドウ構造体の後ろに割り当てる補足バイト数
		0,							//ウインドウインスタンスの後ろに割り当てるバイト数
		hInstance,					//ウインドウプロシージャのインスタンスハンドル
		NULL,						//アイコンのハンドル
		LoadCursor(NULL, IDC_ARROW),//マウスカーソルのハンドル
		(HBRUSH)(COLOR_WINDOW + 1),	//ウインドウ背景色
		NULL,						//デフォルトメニュー名
		"EscapeFromTheCity",			//このウインドウクラスにつける名前
		NULL						//16 * 16の小さいサイズのアイコン
	};
	HWND hWnd;						//ウインドウのハンドル
	MSG msg;
	RegisterClassEx(&wcex);			//ウインドクラスの登録
	//----------------------------------------------------------------------------------------------
	//ウインドウの作成
	//----------------------------------------------------------------------------------------------
	hWnd = CreateWindowEx(			//ウインドウの作成
		0,
		"EscapeFromTheCity",			//wcexで定義したクラス名
		"EscapeFromTheCity",			//タイトルバーに表示する文字列
		WS_OVERLAPPEDWINDOW,		//ウインドウスタイル
		CW_USEDEFAULT,				//ウインドウ左上X座標（適当の場合はCW_USEDEFAULTでおｋ
		CW_USEDEFAULT,				//ウインドウ左上Y座標（適当の場合はCW_USEDEFAULTでおｋ
		(int)SCREEN_WIDTH,				//ウインドウ幅（適当でいい場合はCW_USEDEFAULTでおｋ
		(int)SCREEN_HEIGHT,				//ウインドウ高さ（適当でいい場合はCW_USEDEFAULTでおｋ
		NULL,						//親ウインドウのハンドル
		NULL,						//ウインドウを生成するときのモジュールのインスタンスのハンドル
		hInstance,					//作成されたウィンドウのハンドル、失敗した場合はNULLの値
		NULL
		);
	//----------------------------------------------------------------------------------------------
	//Initが実行できなかった時の処理
	//----------------------------------------------------------------------------------------------
	if (FAILED(Init(hInstance, hWnd))){
		return -1;
	}

	timeBeginPeriod(1);

	dwFrameCount = dwCurrentTime = 0;
	dwExecLastTime = dwFPSLastTime = timeGetTime();

	ShowWindow(hWnd, nCmdShow);		//ウインドウの表示方法の指定	
	UpdateWindow(hWnd);				//更新したいウインドウのハンドルの指定

	g_changeFase = 0;

	// WS_CAPTION属性の設定
	LONG lStyle;

	lStyle = GetWindowLong(hWnd, GWL_STYLE);
	lStyle |= WS_CAPTION;
	lStyle = SetWindowLong(hWnd, GWL_STYLE, lStyle);

	//ウィンドウを画面に合わせる

	//----------------------------------------------------------------------------------------------
	//メインループ
	//----------------------------------------------------------------------------------------------
	while (1){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0){
			if (msg.message == WM_QUIT){
				break;
			}
			else{
				TranslateMessage(&msg);		//仮想キーメッセージを翻訳
				DispatchMessage(&msg);		//ウインドウプロシージャにメッセージを送出する
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

				Update();	//更新処理

				Draw();		//描画処理

				dwFrameCount++;
			}
		}
	}

	Uninit();			//終了処理

	UnregisterClass("EscapeFromTheCity", hInstance);	//ウインドウクラスを消去しメモリを解放する

	timeEndPeriod(1);

	return msg.wParam;
}
/*******************************************************************************
* 関数名:LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
*
* 引数:  HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
* 戻り値:DefWindowProc( hWnd, uMsg, wParam, lParam )
* 説明
*
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	int nID;
	switch (uMsg){
	case WM_DESTROY:			//ウインドウが破棄される場合
		PostQuitMessage(0);		//終了する
		break;
	case WM_KEYDOWN:
		switch (wParam){
		case VK_ESCAPE:			//Eｓｃが押されたとき
			nID = MessageBox(hWnd, "終了しますか", "終了処理", MB_YESNO);
			if (nID == IDYES){
				DestroyWindow(hWnd);	//ウインドウの破棄
			}
			break;
		case VK_F1 :
			// WS_CAPTION属性の設定
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
				//ウィンドウを画面に合わせる
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
* 関数名:void Init()
*
* 引数:  void,なし
* 戻り値:void,なし
* 説明 初期化処理
*
*******************************************************************************/
HRESULT Init(HINSTANCE hInstance, HWND hWnd){
	manager.Init(hInstance, hWnd);
	return S_OK;
}
/*******************************************************************************
* 関数名:void Uninit()
*
* 引数:  void,なし
* 戻り値:void,なし
* 説明 終了処理
*
*******************************************************************************/
void Uninit(){
	manager.Uninit();
}
/*******************************************************************************
* 関数名:void Update()
*
* 引数:  void,なし
* 戻り値:void,なし
* 説明 更新処理
*
*******************************************************************************/
void Update(){
	manager.Update();
}
/*******************************************************************************
* 関数名:void Draw()
*
* 引数:  void,なし
* 戻り値:void,なし
* 説明 描画処理
*
*******************************************************************************/
void Draw(){
	manager.Draw();
}
/*******************************************************************************
* 関数名:HWND GetHWnd(void)
*
* 引数:  void,なし
* 戻り値:なし
* 説明 ウィンドウハンドラーの取得
*
*******************************************************************************/
HWND GetHWnd(void){
	return hWnd;
}
/*******************************************************************************
* 関数名:int GetFPS()
*
* 引数:  void,なし
* 戻り値:int g_FPS
* 説明 描画処理
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