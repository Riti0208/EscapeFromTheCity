/****************************************************************************
* タイトル:  マネージャクラスの処理
* ファイル名:manager.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/05/09
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"manager.h"
#include"effectManager.h"
#include<process.h>
#include"sound.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
HANDLE		loadHandle; //ミューテックスのハンドル

unsigned int __stdcall loadThread(void *);

HINSTANCE	m_hInstance;
HWND		m_hWnd;

bool		isLoad;

/*******************************************************************************
* 関数名:void CManager::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	マネージャクラスの初期化処理
*
*******************************************************************************/
void CManager::Init(HINSTANCE hInstance, HWND hWnd){
	m_hInstance = hInstance;
	m_hWnd = hWnd;
	m_bWireFrame = false;

	InitSound(hWnd);

	isLoad = false;
	isInit = false;
	m_renderer.Init(m_hInstance, m_hWnd);
	CDebugProc::Init();
	loadScene = new load();
	loadHandle = (HANDLE)_beginthreadex(
		NULL,
		0,
		loadThread,
		NULL,
		0,
		&loadId);

}
/*******************************************************************************
* 関数名:void CManager::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	マネージャクラスの終了処理
*
*******************************************************************************/
void CManager::Uninit(){

	CFadeController::Uninit();

	UninitSound();

	CScene::ReleaseAll();
	CGui::ReleaseAll();
	CDebugProc::Uninit();

	CInput::UninitKeyboard();
	CInput::UninitJoyPad();
	CInput::UninitMouse();

	CEffectManager::Uninit();

	m_renderer.Uninit();
}
/*******************************************************************************
* 関数名:void CManager::Update()
*WW
* 引数:  void、なし
* 戻り値:void、なし
* 説明	マネージャクラスの更新処理
*
*******************************************************************************/
void CManager::Update(){

	if (loadScene != NULL){
		loadScene->Update();
	}

	if (isLoad){
		if (!isInit){
			CMode::Set(new CTitle);
			isInit = true;
		}
		LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

		CScene::UpdateAll();
		m_renderer.Update();
		CInput::UpdateKeyboard();
		CInput::UpdateJoyPad();
		CInput::UpdateMouse();

		CDebugProc::Update();

		CGui::UpdateAll();

		CEffectManager::Update();

		CMode::currentMode->Update();

		CFadeController::Update();

#ifdef _DEBUG

		CDebugProc::print("%d\n", GetFPS());

		if (CInput::GetKeyboardTrigger(DIK_R)){
			if (!m_bWireFrame){
				m_bWireFrame = true;
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
			else{
				m_bWireFrame = false;
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
		}

#endif
	}
}
/*******************************************************************************
* 関数名:void CManager::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	マネージャクラスの描画処理
*
*******************************************************************************/
void CManager::Draw(){
	LPDIRECT3DDEVICE9 pDevice = m_renderer.GetDevice();
	//描画開始
	m_renderer.DrawBegin();

	m_renderer.Draw();

	if (loadScene != NULL){
		loadScene->Draw();
	}
	if (isLoad){
		if (isInit){
			SAFE_DELETE(loadScene);
			CMode::currentMode->Draw();
		}			

		CGui::DrawAll();

		CScene::DrawAll();

		CDebugProc::Draw();

		CEffectManager::Draw();

		CFadeController::Draw();
	}
	//描画終了
	m_renderer.DrawEnd();
}
unsigned int __stdcall loadThread(void *){

	CInput::InitKeyboard(m_hInstance, m_hWnd);

	CInput::InitJoyPad(m_hWnd);

	CInput::InitMouse(m_hInstance, m_hWnd);

	CLight::Init();

	CFadeController::Init();

	CTexture::Create();

	CModel::Create();

	isLoad = true;

	return 0;
}