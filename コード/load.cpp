
/****************************************************************************
* �^�C�g��:  ���[�h�̏���
* �t�@�C����:laod.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/12/8
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"load.h"
#include"debugProc.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
* �֐���:void load::Init()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	load�N���X�̏���������
*
*******************************************************************************/
void load::Init(){
	//	bg = new CScene2DwL(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, "data/TEXTURE/loadingBG.png", COLOR_WHITE);
	loadStringImage = new CScene2DwL(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, "data/TEXTURE/loadingImage00.png", COLOR_WHITE);
	loadingImage = new CScene2DwLAnimation(D3DXVECTOR3(SCREEN_WIDTH * 0.925f, SCREEN_HEIGHT * 0.875f, 0.0f), SCREEN_WIDTH * 0.1f, SCREEN_WIDTH * 0.1f, "data/TEXTURE/loadingImage.png", COLOR_WHITE, 12, 5);
	loadStringImageAlpha = 0.0f;
}
/*******************************************************************************
* �֐���:void load::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	load�N���X�̏I������
*
*******************************************************************************/
void load::Uninit(){
	//SAFE_DELETE(bg);
	SAFE_DELETE(loadStringImage);
	SAFE_DELETE(loadingImage);
}
/*******************************************************************************
* �֐���:void load::Update()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	load�N���X�̍X�V����
*
*******************************************************************************/
void load::Update(){
	loadStringImageAlpha += 0.1f;
	if (loadStringImage){
		loadStringImage->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, sinf((loadStringImageAlpha)+1) / 2 + 0.5f));
		loadStringImage->Update();
	}
	if (loadingImage){
		loadingImage->Update();
	}
}
/*******************************************************************************
* �֐���:void load::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	load�N���X�̕`�揈��
*
*******************************************************************************/
void load::Draw(){
//	if (bg != NULL)					bg->Draw();
	if (loadStringImage != NULL)	loadStringImage->Draw();
	if (loadingImage != NULL)		loadingImage->Draw();
}