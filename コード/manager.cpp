/****************************************************************************
* �^�C�g��:  �}�l�[�W���N���X�̏���
* �t�@�C����:manager.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/09
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"manager.h"
#include"effectManager.h"
#include<process.h>
#include"sound.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
HANDLE		loadHandle; //�~���[�e�b�N�X�̃n���h��

unsigned int __stdcall loadThread(void *);

HINSTANCE	m_hInstance;
HWND		m_hWnd;

bool		isLoad;

/*******************************************************************************
* �֐���:void CManager::Init()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	�}�l�[�W���N���X�̏���������
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
* �֐���:void CManager::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	�}�l�[�W���N���X�̏I������
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
* �֐���:void CManager::Update()
*WW
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	�}�l�[�W���N���X�̍X�V����
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
* �֐���:void CManager::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	�}�l�[�W���N���X�̕`�揈��
*
*******************************************************************************/
void CManager::Draw(){
	LPDIRECT3DDEVICE9 pDevice = m_renderer.GetDevice();
	//�`��J�n
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
	//�`��I��
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