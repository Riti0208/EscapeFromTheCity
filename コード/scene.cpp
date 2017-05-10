/****************************************************************************
* �^�C�g��:  �V�[���̏���
* �t�@�C����:scene.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/16
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"scene.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
std::list<CScene*> CScene::sceneList;
bool			   CScene::isFog;
/*******************************************************************************
* �֐���:CScene::CScene()
*
* ����:		�Ȃ�
* �߂�l:	�Ȃ�
* ����		scene�̃R���X�g���N�^
*
*******************************************************************************/
CScene::CScene(){
	m_bDelete = false;
	m_bDraw = true;
	m_curItr = sceneList.end();
	sceneList.push_back(this);
	name = "";
}
CScene::CScene(std::string  _name = ""){

	m_bDelete = false;
	m_bDraw = true;
	m_curItr = sceneList.end();
	sceneList.push_back(this);
	name = _name;
}
/*******************************************************************************
* �֐���:void CScene::UpdateAll();
*
* ����:	�Ȃ�
* �߂�l:	�Ȃ�
* ����		scene�̍X�V����
*
*******************************************************************************/
void CScene::UpdateAll(){
	std::for_each(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		scene->Update();
	});
	
	auto iter = std::find_if(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		return scene->m_bDelete;
	});
	if (iter != sceneList.end()){
		delete *iter;
		sceneList.erase(iter);
	}

}
/*******************************************************************************
* �֐���:void CScene::DrawAll();
*
* ����:		�Ȃ�
* �߂�l:	�Ȃ�
* ����		scene�̕`�揈��
*
*******************************************************************************/
void CScene::DrawAll(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (isFog){
		float FogStart = 900.0f, FogEnd = 3000.0f;

		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); // �t�H�O�L��
		pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f)); // �t�H�O�F
		pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR); // �o�[�e�b�N�X�t�H�O
		pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE); // �͈̓x�[�X�̃t�H�O
		pDevice->SetRenderState(D3DRS_FOGSTART, *((DWORD*)(&FogStart))); // �t�H�O�J�n�_
		pDevice->SetRenderState(D3DRS_FOGEND, *((DWORD*)(&FogEnd))); // �t�H�O�I���_
	}
	std::for_each(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		if (scene->m_bDraw)	scene->Draw();
	});
	if (isFog){
		pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	}
}
/*******************************************************************************
* �֐���:void CScene::ReleaseAll();
*
* ����:		�Ȃ�
* �߂�l:	�Ȃ�
* ����		scene�̑S�̍폜
*
*******************************************************************************/
void CScene::ReleaseAll(){
	std::for_each(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		SAFE_DELETE(scene);
		scene = NULL;
	});
	sceneList.erase(sceneList.begin(), sceneList.end());
}
/*******************************************************************************
* �֐���:void CScene::Release();
*
* ����:		�Ȃ�
* �߂�l:	�Ȃ�
* ����		scene�̒P�̍폜
*
*******************************************************************************/
void CScene::Release(){
	m_bDelete = true;
}
CScene *CScene::Find(std::string string){
	auto scene = std::find_if(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		if (string == scene->name)	return true;
		return false;
	});
	if (scene != sceneList.end())
	return *scene;
	return NULL;
}
static void SetFog(){
}