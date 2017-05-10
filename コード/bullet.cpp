#include"bullet.h"
#include"enemy.h"
#include"effectManager.h"
#include"sound.h"
CBullet::CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *modelName){
	m_pos = pos;
	m_rot = rot;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
CBullet::~CBullet(){
	Uninit();
}
CBulletPlayer::~CBulletPlayer(){
}
CBulletEnemy::~CBulletEnemy(){
	SAFE_RELEASE(model);
}
void CBullet::Init(){
}
void CBullet::Uninit(){
	
}
void CBullet::Draw(){
}
void CBullet::Update(){
	
}
CBulletEnemy::CBulletEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot) : CBullet(pos, rot, "data\\MODEL\\bullet.x"){
	speed = 4.0f;
	attack = 20;
	life = 120;
	model = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\missile.x");
	PlaySound(SOUND_LABEL_MISSILE_SOUND_0);
}
void CBulletEnemy::Update(){


	CPlayer *player = CGame::player;

	//ˆÚ“®—Ê‚Ì‰ÁŽZ
	m_pos += D3DXVECTOR3(-sinf(m_rot.y) * 10.0f, 0.0f, -cosf(m_rot.y) * 10.0f);

	m_rot.z += D3DX_PI * 5.0f;
	if (model != NULL) {
		model->SetRot(m_rot);
	}

	CEffectManager::CreateEffect("missleSmoke.efk", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot);

	bool bWidthCollisonDitect = m_pos.x > player->GetPos()->x - 20.0f && m_pos.x < player->GetPos()->x + 20.0f;
	bool bDepthCollisonDitect = m_pos.z > player->GetPos()->z - 10.0f && m_pos.z < player->GetPos()->z + 10.0f;
	bool bHeightCollisonDitect = m_pos.y > player->GetPos()->y && m_pos.y < player->GetPos()->y + 50.0f;

	if (bWidthCollisonDitect && bDepthCollisonDitect && bHeightCollisonDitect){
		PlaySound(SOUND_LABEL_EXPLOSION_SOUND_0);
		int hp = player->GetHp();
		hp -= attack;
		player->SetHp(hp);
		if (model != NULL)
		model->SetCanDraw(false);
		CEffectManager::CreateEffect("explosion_small.efk", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot);
		SAFE_RELEASE(model);
		Release();
	}
	if (model != NULL)
	model->SetPos(m_pos);
	life--;
	if (life <= 0){
		if (model != NULL)
		model->SetCanDraw(false);
		SAFE_RELEASE(model);
		Release();
	}
}
CBulletPlayer::CBulletPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot) : CBullet(pos, rot, "data\\MODEL\\bullet.x"){
	speed = 20.0f;
	attack = 20;
	life = 30;
	handle = CEffectManager::CreateEffect("shot.efk", D3DXVECTOR3(m_pos.x, 20.0f, m_pos.z), m_rot);
	PlaySound(SOUND_LABEL_BEAM_SOUND_0);
}
void CBulletPlayer::Update(){
	if (life > 0){
		m_move.x += sinf(D3DX_PI * 1.0f + m_rot.y) * speed;
		m_move.z += cosf(D3DX_PI * 1.0f + m_rot.y) * speed;

		//ˆÚ“®—Ê‚Ì‰ÁŽZ
		m_pos.x += m_move.x;
		m_pos.z += m_move.z;

		m_move.x += (0 - m_move.x) * 0.5f;
		m_move.z += (0 - m_move.z) * 0.5f;

		std::for_each(CEnemy::enemyList.begin(), CEnemy::enemyList.end(), [=](CEnemy *enemy){
			bool bWidthCollisonDitect = m_pos.x > enemy->GetPos()->x - 20.0f && m_pos.x < enemy->GetPos()->x + 20.0f;
			bool bDepthCollisonDitect = m_pos.z > enemy->GetPos()->z - 50.0f && m_pos.z < enemy->GetPos()->z + 50.0f;
			bool bHeightCollisonDitect = m_pos.y > enemy->GetPos()->y && m_pos.y < enemy->GetPos()->y + 50.0f;

			if (bWidthCollisonDitect && bDepthCollisonDitect && bHeightCollisonDitect && enemy->GetHp() > 0){
				PlaySound(SOUND_LABEL_EXPLOSION_SOUND_0);
				int hp = enemy->GetHp();
				hp -= attack;
				enemy->SetHp(hp);
				
				CEffectManager::StopEffect(handle);
				Release();
			}
			return true;
		});
		CEffectManager::SetPos(handle, m_pos);
		life--;
		if (life <= 0){
			CEffectManager::StopEffect(handle);
			Release();
		}
	}
}
CBulletEnemy *CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot){
	CBulletEnemy *bullet;
	bullet = new CBulletEnemy(pos, rot);
	return bullet;
}
CBulletPlayer *CBulletPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot){
	CBulletPlayer *bullet;
	bullet = new CBulletPlayer(pos, rot);
	return bullet;
}


CBulletBoss::CBulletBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot) : CBullet(pos, rot, "data\\MODEL\\bullet.x") {
	speed = 10.0f;
	attack = 20;
	life = 30;
	handle = CEffectManager::CreateEffect("bossAttack1.efk", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot);
	PlaySound(SOUND_LABEL_MISSILE_SOUND_0);
}
void CBulletBoss::Update() {

	CPlayer *player = CGame::player;

	if (life > 0) {

		//ˆÚ“®—Ê‚Ì‰ÁŽZ

		m_pos += D3DXVECTOR3(-sinf(m_rot.y) * speed, sinf(m_rot.x) * 10.0f, -cosf(m_rot.y) * speed);

		bool bWidthCollisonDitect = m_pos.x > player->GetPos()->x - 20.0f && m_pos.x < player->GetPos()->x + 20.0f;
		bool bDepthCollisonDitect = m_pos.z > player->GetPos()->z - 10.0f && m_pos.z < player->GetPos()->z + 10.0f;
		bool bHeightCollisonDitect = m_pos.y > player->GetPos()->y&& m_pos.y < player->GetPos()->y + 50.0f;

		if (bWidthCollisonDitect && bDepthCollisonDitect && bHeightCollisonDitect) {
			PlaySound(SOUND_LABEL_EXPLOSION_SOUND_0);
			int hp = player->GetHp();
			hp -= attack;
			player->SetHp(hp);
			CEffectManager::CreateEffect("explosion_small.efk", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot);
			Release();
		}

		CEffectManager::SetPos(handle, m_pos);

		life--;
		if (life <= 0) {
			CEffectManager::StopEffect(handle);
			Release();
		}
	}
}
CBulletBoss *CBulletBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	CBulletBoss *bullet;
	bullet = new CBulletBoss(pos, rot);
	return bullet;
}


CMissileBoss::CMissileBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot) : CBullet(pos, rot, "data\\MODEL\\bullet.x") {
	speed = 10.0f;
	attack = 20;
	life = 100;
	model = CSceneXFile::Create(m_pos, m_rot, "data\\MODEL\\missile.x");
	PlaySound(SOUND_LABEL_MISSILE_SOUND_0);
}
void CMissileBoss::Update() {

	CPlayer *player = CGame::player;
	if (life > 0) {

		//ˆÚ“®—Ê‚Ì‰ÁŽZ

		if (m_pos.z < player->GetPos()->z) {
			if (life < 80) {
				speed = 5.0f;
				auto rotX = atan2f(m_pos.y - CGame::player->GetPos()->y, m_pos.z - CGame::player->GetPos()->z);
				auto rotY = atan2f(m_pos.x - CGame::player->GetPos()->x, m_pos.z - CGame::player->GetPos()->z);
				m_rot = D3DXVECTOR3(rotX, rotY, 0.0f);
			}
			else {
				speed = 1.0f;
			}
		}

		m_pos += D3DXVECTOR3(-sinf(m_rot.y) * speed, -sinf(m_rot.x) * speed, -cosf(m_rot.y) * speed);

		CEffectManager::CreateEffect("missleSmoke.efk", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot);

		bool bWidthCollisonDitect = m_pos.x > player->GetPos()->x - 20.0f && m_pos.x < player->GetPos()->x + 20.0f;
		bool bDepthCollisonDitect = m_pos.z > player->GetPos()->z - 10.0f && m_pos.z < player->GetPos()->z + 10.0f;
		bool bHeightCollisonDitect = m_pos.y > player->GetPos()->y&& m_pos.y < player->GetPos()->y + 50.0f;

		if (bWidthCollisonDitect && bDepthCollisonDitect && bHeightCollisonDitect) {
			PlaySound(SOUND_LABEL_EXPLOSION_SOUND_0);
			int hp = player->GetHp();
			hp -= attack;
			player->SetHp(hp);
			CEffectManager::CreateEffect("explosion_small.efk", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot);
			Release();
		}

		CEffectManager::SetPos(handle, m_pos);

		life--;
		if (life <= 0) {
			CEffectManager::StopEffect(handle);
			model->SetCanDraw(false);
			Release();
		}
		model->SetPos(m_pos);
		model->SetRot(-m_rot);
	}
}
CMissileBoss *CMissileBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	CMissileBoss *bullet;
	bullet = new CMissileBoss(pos, rot);
	return bullet;
}
