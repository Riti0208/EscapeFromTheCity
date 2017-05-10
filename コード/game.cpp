/****************************************************************************
* ゲーム:  ゲームの処理
* ファイル名:game.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/06/26
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"manager.h"
#include"player.h"
#include"effectManager.h"
#include"IrregularityField.h"
#include"stage.h"
#include"stensilShadow.h"
#include"sound.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
CIrregularityField *CGame::field;
CPlayer *CGame::player;
/*******************************************************************************
* 関数名:void InitGame()
*
* 引数:  なし
* 戻り値:なし
* 説明 ゲームの初期化処理
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
* 関数名:void UninitGame()
*
* 引数:  なし
* 戻り値:なしs
* 説明 ゲームの終了処理
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
* 関数名:void UpdateGame()
*
* 引数:  なし
* 戻り値:なし
* 説明 ゲームの更新処理
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
* 関数名:void DrawGame()
*
* 引数:  なし
* 戻り値:なし
* 説明 ゲームの描画処理
*
*******************************************************************************/
void CGame::Draw(){
	CCamera::Set();
}
