#include"enemy.h"
#include"bullet.h"
#include"effectManager.h"
#include"bossAction.h"
#include<algorithm>
#include<random>
std::list<CEnemy*> CEnemy::enemyList;
CEnemyStandard *CEnemyStandard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot){
	CEnemyStandard *scene;

	scene = new CEnemyStandard(pos, rot);
	return scene;
}
void CEnemyStandard::Init(){
	bModelCreate = false;
	hp = 20;
	attackCnt = 0;
	attackCntMax = 50;
	modelTop = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\Enemy2.x");
	modelBottom = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\Enemy.x");
	modelTop->SetCanDraw(false);
	modelBottom->SetCanDraw(false);

}
void CEnemyStandard::Uninit(){
	SAFE_RELEASE(modelBottom);
	SAFE_RELEASE(modelTop);
}
void CEnemyStandard::Update(){
	CPlayer *player = CGame::player;
	if (player->GetPos()->z < m_pos.z + 2000.0f){
		if (modelTop != NULL)
		modelTop->SetCanDraw(true);
		if (modelBottom != NULL)
		modelBottom->SetCanDraw(true);
		auto rot = atan2f(m_pos.x - CGame::player->GetPos()->x, m_pos.z - CGame::player->GetPos()->z);

		if (m_pos.z < player->GetPos()->z)
			if (modelTop != NULL){
				modelTop->SetRot(D3DXVECTOR3(0.0f, rot, 0.0f));
			}
		attackCnt++;

		if (modelTop != NULL){
			if (attackCnt > attackCntMax){
				attackCnt = 0;
				player->GetPos()->x;
				auto pos = *modelTop->GetPos();
				pos.y += 20.0f;
				auto rot = *modelTop->GetRot();
				rot.y *= -1;
				CBulletEnemy::Create(D3DXVECTOR3(pos.x - sinf(rot.y + (D3DX_PI)) * 15.0f, 33.0f, pos.z + cosf(rot.y + (D3DX_PI)) * 15.0f), m_rot);
				CEffectManager::CreateEffect("tamakemuri.efk", D3DXVECTOR3(pos.x - sinf(rot.y + (D3DX_PI)) * 15.0f, 33.0f, pos.z + cosf(rot.y + (D3DX_PI)) * 20.0f), m_rot);
			}
		}
	}

	if (player->GetPos()->z < m_pos.z - 100.0f){
		Release();
	}

	if (hp <= 0){
		Uninit();
		Release();
		CEffectManager::CreateEffect("explosion_small.efk", D3DXVECTOR3(m_pos.x, 20.0f, m_pos.z), m_rot);
	}

	bool bWidthCollisonDitect = m_pos.x > player->GetPos()->x - 40.0f && m_pos.x < player->GetPos()->x + 40.0f;
	bool bDepthCollisonDitect = m_pos.z > player->GetPos()->z - 50.0f && m_pos.z < player->GetPos()->z + 50.0f;
	bool bHeightCollisonDitect = m_pos.y > player->GetPos()->y - 0.0f && m_pos.y < player->GetPos()->y + 50.0f;

	if (bWidthCollisonDitect && bDepthCollisonDitect && bHeightCollisonDitect){
		hp = 0;
		int playerHp = player->GetHp();
		playerHp -= 10;
		player->SetHp(playerHp);
		Uninit();
	}
}
void CEnemyStandard::Draw(){

}
void CEnemyStandard::ModelCreate(){

}

CEnemyLv1 *CEnemyLv1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot){
	CEnemyLv1 *scene;

	scene = new CEnemyLv1(pos, rot);
	return scene;
}
void CEnemyLv1::Init(){
	bModelCreate = false;
	hp = 20;
	attackCnt = 0;
	attackCntMax = 120;
	modelTop = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\Enemy1.x");
	modelBottom = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\Enemy.x");
	modelTop->SetCanDraw(false);
	modelBottom->SetCanDraw(false);
}
void CEnemyLv1::Uninit(){
	SAFE_RELEASE(modelBottom);
	SAFE_RELEASE(modelTop);
}
void CEnemyLv1::Update(){
	CPlayer *player = CGame::player;
	if (player->GetPos()->z < m_pos.z + 2000.0f){
		if (modelTop != NULL)
			modelTop->SetCanDraw(true);
		if (modelBottom != NULL)
			modelBottom->SetCanDraw(true);
		auto rot = atan2f(m_pos.x - CGame::player->GetPos()->x, m_pos.z - CGame::player->GetPos()->z);

		if (m_pos.z < player->GetPos()->z)
			if (modelTop != NULL){
				modelTop->SetRot(D3DXVECTOR3(0.0f, rot, 0.0f));
			}
		attackCnt++;

		if (modelTop != NULL){
			if (attackCnt > attackCntMax){
				attackCnt = 0;
				player->GetPos()->x;
				auto pos = *modelTop->GetPos();
				pos.y += 20.0f;
				auto rot = *modelTop->GetRot();
				rot.y *= -1;

				D3DXVECTOR3 RIGHT_CANON_START(pos.x - sinf(rot.y + (0.14f * D3DX_PI)) * 30.0f, pos.y + 7.5f, pos.z + cosf(rot.y + (0.14f * D3DX_PI)) * 30.0f);
				D3DXVECTOR3 LEFT_CANON_START(pos.x - sinf(rot.y - (0.14f * D3DX_PI)) * 30.0f, pos.y + 7.5f, pos.z + cosf(rot.y + (0.14f * D3DX_PI)) * 30.0f);

				CBulletEnemy::Create(RIGHT_CANON_START, rot);
				CBulletEnemy::Create(LEFT_CANON_START, rot);

				CEffectManager::CreateEffect("tamakemuri.efk", RIGHT_CANON_START, rot);
				CEffectManager::CreateEffect("tamakemuri.efk", LEFT_CANON_START, rot);

			}
		}
	}

	if (player->GetPos()->z < m_pos.z - 100.0f){
		Release();
	}

	if (hp <= 0){
		Uninit();
		Release();
		CEffectManager::CreateEffect("explosion_small.efk", D3DXVECTOR3(m_pos.x, 20.0f, m_pos.z), m_rot);
	}

	bool bWidthCollisonDitect = m_pos.x > player->GetPos()->x - 40.0f && m_pos.x < player->GetPos()->x + 40.0f;
	bool bDepthCollisonDitect = m_pos.z > player->GetPos()->z - 50.0f && m_pos.z < player->GetPos()->z + 50.0f;
	bool bHeightCollisonDitect = m_pos.y > player->GetPos()->y - 0.0f && m_pos.y < player->GetPos()->y + 50.0f;
	if (bWidthCollisonDitect && bDepthCollisonDitect && bHeightCollisonDitect){
		hp = 0;
		int playerHp = player->GetHp();
		playerHp -= 10;
		player->SetHp(playerHp);
		Uninit();
	}
}
void CEnemyLv1::Draw(){

}
void CEnemyLv1::ModelCreate(){

}


CEnemyFly *CEnemyFly::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot){
	CEnemyFly *scene;

	scene = new CEnemyFly(pos, rot);
	return scene;
}
void CEnemyFly::Init(){
	bModelCreate = false;
	hp = 20;
	attackCnt = 0;
	attackCntMax = 50;
	modelTop = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\EnemyFly2.x");
	modelBottom = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\EnemyFly.x");
	modelTop->SetCanDraw(false);
	modelBottom->SetCanDraw(false);
}
void CEnemyFly::Uninit(){
	SAFE_RELEASE(modelBottom);
	SAFE_RELEASE(modelTop);
}
void CEnemyFly::Update(){
	CPlayer *player = CGame::player;
	if (player->GetPos()->z < m_pos.z + 2000.0f){
		if (modelTop != NULL){
			modelTop->SetCanDraw(true);
			auto rot = modelTop->GetRot();
			rot->y += D3DX_PI * 2.0f;
			modelTop->SetRot(*rot);
		}
		if (modelBottom != NULL)
			modelBottom->SetCanDraw(true);
		auto rot = atan2f(m_pos.x - CGame::player->GetPos()->x, m_pos.z - CGame::player->GetPos()->z);

		if (m_pos.z < player->GetPos()->z)
			if (modelTop != NULL){
				modelTop->SetRot(D3DXVECTOR3(0.0f, rot, 0.0f));
			}
		attackCnt++;

		if (modelBottom != NULL){
			if (attackCnt > attackCntMax){
				attackCnt = 0;
				player->GetPos()->x;
				auto pos = *modelBottom->GetPos();
				pos.y += 20.0f;
				auto rot = *modelBottom->GetRot();
				rot.y *= -1;
				CBulletEnemy::Create(D3DXVECTOR3(pos.x - sinf(rot.y + (D3DX_PI)) * 15.0f, 85.0f, pos.z + cosf(rot.y + (D3DX_PI)) * 15.0f), rot);
				CEffectManager::CreateEffect("tamakemuri.efk", D3DXVECTOR3(pos.x - sinf(rot.y + (D3DX_PI)) * 15.0f, 85.0f, pos.z + cosf(rot.y + (D3DX_PI)) * 20.0f), m_rot);
			}
		}
	}

	if (player->GetPos()->z < m_pos.z - 100.0f){
		Release();
	}

	if (hp <= 0){
		Uninit();
		Release();
		CEffectManager::CreateEffect("explosion_small.efk", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot);
	}

	bool bWidthCollisonDitect = m_pos.x > player->GetPos()->x - 40.0f && m_pos.x < player->GetPos()->x + 40.0f;
	bool bDepthCollisonDitect = m_pos.z > player->GetPos()->z - 50.0f && m_pos.z < player->GetPos()->z + 50.0f;
	bool bHeightCollisonDitect = m_pos.y > player->GetPos()->y - 0.0f && m_pos.y < player->GetPos()->y + 50.0f;
	if (bWidthCollisonDitect && bDepthCollisonDitect && bHeightCollisonDitect){
		hp = 0;
		int playerHp = player->GetHp();
		playerHp -= 10;
		player->SetHp(playerHp);
		Uninit();
	}
}
void CEnemyFly::Draw(){

}
void CEnemyFly::ModelCreate(){

}



CEnemyBoss *CEnemyBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot){
	CEnemyBoss *scene;
	scene = new CEnemyBoss(pos, rot);
	return scene;
}
void CEnemyBoss::Init(){
	findPlayer = false;
	bModelCreate = false;
	hp = 200;
	attackCnt = 0;
	attackCntMax = 360;
	model = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\hati.x");
	modelArm = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\hatiArm.x");
	model->SetCanDraw(false);
	modelArm->SetCanDraw(false);
	sinCnt = 0;
	ba = new newtral();
	isDown = false;
	isDraw = false;
	damageFlag = false;
	damageCnt = 0;
}
void CEnemyBoss::Uninit(){
	SAFE_RELEASE(model);
	SAFE_RELEASE(modelArm);
}
void CEnemyBoss::Update(){
	CPlayer *player = CGame::player;
	if (player->GetPos()->z < m_pos.z + 2000.0f){
		StopSound(BGM_LABEL_BATTLE_0);
		if (!isDraw) {
			isDraw = true;
			PlaySound(SOUND_LABEL_KEIHOU_SOUND_0);
		}
		if (model != NULL){
 			model->SetCanDraw(true);
			modelArm->SetCanDraw(true);
			auto rot = model->GetRot();
			rot->y += D3DX_PI * 2.0f;
			model->SetRot(*rot);
			modelArm->SetRot(*rot);
			findPlayer = true;
			model->SetScl(0.5f, 0.5f, 0.5f);
			modelArm->SetScl(0.5f, 0.5f, 0.5f);
			if (m_pos.y >= 80.0f)	m_pos.y -= 1.0f;
			if (m_pos.y < 90.0f && !isDown) {
				isDown = true;
				PlaySound(BGM_LABEL_BOSS_0);
			}
		}
	}
	if (damageFlag) {
		damageCnt++;

		model->SetCol(COLOR_RED);
		modelArm ->SetCol(COLOR_RED);

		if (damageCnt >= 10) {
			damageFlag = false;
		}
	}
	if (player->GetPos()->z < m_pos.z + 500.0f){
		if (model != NULL){
			findPlayer = true;
		}
	}

	if (findPlayer){

		m_pos.z = player->GetPos()->z - 500.0f;

		auto handle = CEffectManager::CreateEffect("hane.efk", D3DXVECTOR3(m_pos.x, m_pos.y - 40.0f, m_pos.z - 300.0f), m_rot);
		hane.push_back(handle);
		sinCnt++;
		
		auto heightWave = sinf((float)((float)sinCnt / 2)) * 100.0f / 100;

		m_pos.y = heightWave + m_pos.y;

		if (ba->update(&m_pos, &m_rot)) {
			delete ba;
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dice(0, 1);
			auto rand = dice(mt);
			if (rand) {
				ba = new spreadAttack();
			}
			else {
				ba = new concentrationAttack();
			}
		}

		model->SetPos(m_pos);
		modelArm->SetPos(m_pos);

		auto rotX = atan2f(CGame::player->GetPos()->y - 30.0f - m_pos.y, CGame::player->GetPos()->z - m_pos.z);
		auto rotY = atan2f(m_pos.x - CGame::player->GetPos()->x, m_pos.z - CGame::player->GetPos()->z);

		m_rot = D3DXVECTOR3(rotX, rotY, 0.0f);

		model->SetRot(m_rot);

		std::for_each(hane.begin(), hane.end(), [=](Effekseer::Handle handle) {
			CEffectManager::SetPos(handle, D3DXVECTOR3(m_pos.x, m_pos.y - 40.0f, m_pos.z - 15.0f));
		});
	}

	if (hp <= 0){
		delete ba;
		model->SetCanDraw(false);
		modelArm->SetCanDraw(false);
		model->Release();
		modelArm->Release();
		Uninit();
		Release();
		std::for_each(hane.begin(), hane.end(), [](Effekseer::Handle handle) {
			CEffectManager::StopEffect(handle);
		});
		CEffectManager::CreateEffect("explosion_small.efk", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot);
		CFadeController::SetFade(new CNormalFade, new CResult, 1.0f);

	}
	
}
void CEnemyBoss::Draw(){

}
void CEnemyBoss::ModelCreate(){

}
void CEnemyBoss::addDamage() {

}