/****************************************************************************
* タイトル:  プレイヤーの処理
* ファイル名:Player.cpp
* 作成者：	 芳崎大地
* 作成日：   2015/10/26
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"player.h"
#include"camera.h"
#include"moionModel.h"
#include"effectManager.h"
#include"debugProc.h"
#include"sound.h"
#include"game.h"
#include"bullet.h"
#include"stensilShadow.h"
#include"number.h"
#include"stage.h"
#include"sound.h"
#include"gameOver.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MOVE_SPEED (1.0f)
#define ROT_SPEED  (D3DX_PI * 0.1f)
#define PLAYER_LENGTH	(10.0f)
/*******************************************************************************
* 構造体の定義
*******************************************************************************/

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************//*******************************************************************************
* グローバル変数
*******************************************************************************/

float x, y, z;
/*******************************************************************************
* 関数名:void InitPlayer()
*
* 引数:  なし
* 戻り値:なし
* 説明 プレイヤーの初期化処理
*
*******************************************************************************/
void CPlayer::Init(){
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	model = CPlayerModel::Create("data\\MOTION\\motion.txt", 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	model->SetMotion(MOTION_TYPE_RUN);
	nFootSoundCnt = 0;
	m_nHp = 800;
	m_nBullet = 10;
	m_nDummyHp = m_nHp;
	nHpCnt = 0;
	m_nBulletCnt = 0;
	isJump = false;
	jumpCnt = 0;
	firstY = 0.0f;
	moveSpeed = 0.25f;
}
/*******************************************************************************
* 関数名:void UninitPlayer()
*
* 引数:  なし
* 戻り値:なし
* 説明 プレイヤーの終了処理
*
*******************************************************************************/
void CPlayer::Uninit(){
}
/*******************************************************************************
* 関数名:void UpdatePlayer()
*
* 引数:  なし
* 戻り値:なし
* 説明 プレイヤーの更新処理
*
*******************************************************************************/
void CPlayer::Update(){

	auto modelPos = D3DXVECTOR3(m_pos.x + x, m_pos.y -30.0f , m_pos.z + z);
	model->SetPos(modelPos);
	model->SetRot(m_rot);
	Controll();
	m_posOld = m_pos;
	//足音用のカウンタのインクリメント

	isGoal = false;

	nFootSoundCnt++;

	if (nFootSoundCnt == 18){
		if (m_pos.y < 10) {
			PlaySound(SOUND_LABEL_FOOT_SOUND_0);
			CEffectManager::CreateEffect("legDust.efk", m_pos, m_rot);
		}
	}

	if (nFootSoundCnt == 20) {
		StopSound(SOUND_LABEL_FOOT_SOUND_0);
		nFootSoundCnt = 0;
	}

	if (m_pos.x > 60) m_pos.x = 60;
	if (m_pos.x < -60) m_pos.x = -60;
	
	nHpCnt++;

	if (nHpCnt > 1 && m_nHp < m_nDummyHp){
		m_nDummyHp--;
		nHpCnt = 0;		
	}

	if ((CInput::GetKeyboardTrigger(DIK_SPACE) || CInput::GetGamePadTrigger(X_GAME_PAD_A, nPlayer)) && !isJump){
		isJump = true;
		jumpCnt = -D3DX_PI * 0.0f;
		boost = CEffectManager::CreateEffect("burnia.efk", D3DXVECTOR3(m_pos.x, m_pos.y + 60.0f, m_pos.z - 20.0f), m_rot);
		PlaySound(SOUND_LABEL_BOOST_SOUND_0);
	}

	if (isJump){
		jumpCnt += D3DX_PI * 0.01f;
		m_pos.y = sinf(jumpCnt) * 50.0f;
		auto boostEffectPos = m_pos;
		boostEffectPos.y += 23.0f;
		boostEffectPos.z += 20.0f;
		CEffectManager::SetPos(boost, boostEffectPos);
		if (jumpCnt > D3DX_PI * 0.5f){
			jumpCnt += D3DX_PI * 0.01f;
			CEffectManager::StopEffect(boost);
			model->SetMotion(MOTION_TYPE_RUN);
		}
		if (jumpCnt > D3DX_PI * 1.0f){
			isJump = false;
			CEffectManager::CreateEffect("smoke.efk", D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f , m_pos.z), m_rot);
			moveSpeed = 0.25f;
			PlaySound(SOUND_LABEL_FOOT_SOUND_1);
		}
	}
	if (m_nHp <= 0) {
		m_nHp = 0;
		CFadeController::SetFade(new CNormalFade, new CResultGameOver, 1.0f);
	}
}
/*******************************************************************************
* 関数名:void DrawPlayer()
*
* 引数:  なし
* 戻り値:なし
* 説明 プレイヤーの描画処理
*
*******************************************************************************/
void CPlayer::Draw(){
}
/*******************************************************************************
* 関数名:void ControllPlayer()
*
* 引数:  なし
* 戻り値:なし
* 説明 プレイヤーのコントロール
*
*******************************************************************************/
void CPlayer::Controll(){
	if (moveSpeed < MOVE_SPEED) moveSpeed += moveSpeed * 0.1f;
	//前移動
	if (CInput::GetKeyboardPress(DIK_A) || CInput::GetGamePadPress(X_GAME_PAD_LLEFT, nPlayer)){
		m_move.x += sinf(D3DX_PI * 0.5f + m_rot.y) * MOVE_SPEED;
		m_move.z += cosf(D3DX_PI * 0.5f + m_rot.y) * MOVE_SPEED;
	}

	if (CInput::GetKeyboardPress(DIK_D) || CInput::GetGamePadPress(X_GAME_PAD_LRIGHT, nPlayer)){
		m_move.x += sinf(D3DX_PI * 1.5f + m_rot.y) * MOVE_SPEED;
		m_move.z += cosf(D3DX_PI * 1.5f + m_rot.y) * MOVE_SPEED;
	}

	if ((CInput::GetGamePadTrigger(X_GAME_PAD_B, nPlayer) || CInput::GetKeyboardTrigger(DIK_E)) && m_nBullet > 0){
		CBulletPlayer::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), m_rot);
		m_nBullet--;
	}

	m_nBulletCnt++;

	if (m_nBulletCnt > 30 && m_nBullet < 10){
		m_nBullet++;
		m_nBulletCnt = 0;
	}

	if (m_pos.z > CStage::goalPosition){
		isGoal = true;
	}

	m_move.x += sinf(D3DX_PI * 1.0f + m_rot.y) * moveSpeed * 4;
	m_move.z += cosf(D3DX_PI * 1.0f + m_rot.y) * moveSpeed * 4;

	m_move.x += (0 - m_move.x) * 0.25f;
	m_move.z += (0 - m_move.z) * 0.25f;

	//移動量の加算
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

}
CPlayer *CPlayer::Create(int n){
	CPlayer *scene;
	scene = new CPlayer(n);
	
	return scene;
}