#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"manager.h"
#include<list>
#include<vector>
class bossAction;

class CEnemy : public CScene{
private:
protected:
	int hp;
	int attack;
	int attackCnt;
	int attackCntMax;
	bool bModelCreate;
	bool damageFlag;
	int damageCnt;
public:
	void setPos(D3DXVECTOR3 _pos){ m_pos = _pos; }
	D3DXVECTOR3 getPos(){ return m_pos; }
	void setRot(D3DXVECTOR3 _rot){ m_rot = _rot; }
	D3DXVECTOR3 getRot(){ return m_rot; }
	int GetHp(){ return hp; }
	void SetHp(int _hp){ hp = _hp; }
	static std::list<CEnemy*> enemyList;
	virtual void addDamage() = 0;
};
class CEnemyStandard : public CEnemy{
private:
	CSceneXFile *modelTop;
	CSceneXFile *modelBottom;
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void ModelCreate();
	bool bCreate;
public:
	CEnemyStandard(D3DXVECTOR3 pos, D3DXVECTOR3 rot){ m_pos = pos; m_rot = rot; CEnemyStandard::Init(); };
	~CEnemyStandard(){ Uninit(); };
	static CEnemyStandard *CEnemyStandard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void addDamage() {}
};
class CEnemyLv1 : public CEnemy{
private:
	CSceneXFile *modelTop;
	CSceneXFile *modelBottom;
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void ModelCreate();
	bool bCreate;
public:
	CEnemyLv1(D3DXVECTOR3 pos, D3DXVECTOR3 rot){ m_pos = pos; m_rot = rot; CEnemyLv1::Init(); };
	~CEnemyLv1(){ Uninit(); };
	static CEnemyLv1 *CEnemyLv1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void addDamage() {}
};

class CEnemyFly : public CEnemy{
private:
	CSceneXFile *modelTop;
	CSceneXFile *modelBottom;
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void ModelCreate();
	bool bCreate;
public:
	CEnemyFly(D3DXVECTOR3 pos, D3DXVECTOR3 rot){ m_pos = pos; m_rot = rot; CEnemyFly::Init(); };
	~CEnemyFly(){ Uninit(); };
	static CEnemyFly *CEnemyFly::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void addDamage() {}
};
class CEnemyBoss : public CEnemy{
private:
	bossAction *ba;
	bool findPlayer;
	CSceneXFile *model;
	CSceneXFile *modelArm;
	std::vector<::Effekseer::Handle> hane;
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void ModelCreate();
	bool bCreate;
	int sinCnt;
	bool isDown;
	bool isDraw;
public:
	CEnemyBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot){ m_pos = pos; m_rot = rot; CEnemyBoss::Init(); };
	~CEnemyBoss(){ Uninit(); };
	static CEnemyBoss *CEnemyBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void addDamage();
};

#endif