/****************************************************************************
* �Q�[��:  �Q�[���̏���
* �t�@�C����:game.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/06/26
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"manager.h"
#include"player.h"
#include"effectManager.h"
#include"IrregularityField.h"
#include"stage.h"
#include"stensilShadow.h"
#include"sound.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �\���̂̒�`
*******************************************************************************/
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
CIrregularityField *CGame::field;
CPlayer *CGame::player;
/*******************************************************************************
* �֐���:void InitGame()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �Q�[���̏���������
*
*******************************************************************************/
void CGame::Init(){
	CCamera::Init();
	CSky::Create();

	CStage::load("data/MAP/map.csv");
	CStage::create();
	
	CGuiPanel::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.85f, 0.0f), SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.075f, "data\\TEXTURE\\ui_hp.png", COLOR_WHITE);
	CGuiPanel::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.85f, 0.0f), SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.075f, "data\\TEXTURE\\bulletAmount.png", COLOR_WHITE);

	shadow = stensilShadow::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	player = CPlayer::Create(0);

	bulletNum = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f, 0.0f), SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, player->GetBulletNum(), 2, "data\\TEXTURE\\number.png");

	score = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.75f, 0.0f), SCREEN_WIDTH * 0.125f, SCREEN_HEIGHT * 0.2f, player->GetBulletNum(), 3, "data\\TEXTURE\\number.png");

	auto test = CEffectManager::CreateEffect("test.efk", D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -100.0f, 0.0f));

	CScene::SetFog(true);

	PlaySound(BGM_LABEL_BATTLE_0);
}
/*******************************************************************************
* �֐���:void UninitGame()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�s
* ���� �Q�[���̏I������
*
*******************************************************************************/
void CGame::Uninit(){
	StopSound();
	CCamera::Uninit();
	CGui::ReleaseAll();
	CScene::ReleaseAll();
	CScene::SetFog(false);
}
/*******************************************************************************
* �֐���:void UpdateGame()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �Q�[���̍X�V����
*
*******************************************************************************/
void CGame::Update(){
	bulletNum->Set(player->GetBulletNum());
	score->Set(player->GetDummyHp());
	auto pos = *player->GetPos();
	pos.z += 10.0f;
	shadow->SetPos(pos);

	CCamera::Update();
}
/*******************************************************************************
* �֐���:void DrawGame()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �Q�[���̕`�揈��
*
*******************************************************************************/
void CGame::Draw(){
	CCamera::Set();
}
