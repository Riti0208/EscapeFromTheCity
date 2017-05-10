/****************************************************************************
* �^�C�g��:  bullet.cpp�̃w�b�_�[
* �t�@�C����:bullet.h
* �쐬�ҁF	 �F���n
* �쐬���F   2015/11/21
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _BULLET_H_
#define _BULLET_H_
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"manager.h"
/*******************************************************************************
* �N���X�̒�`
*******************************************************************************/

class CBullet : public CScene{
protected:
	float speed;
	int attack;
	D3DXVECTOR3 m_move;
	int life;
	::Effekseer::Handle handle;
	CSceneXFile *model;
public:
	CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *modelName);
	~CBullet();
	void Init();
	void Uninit();
	virtual void Update();
	void Draw();
private:
};
class CBulletPlayer : public CBullet{
private:
public:
	CBulletPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~CBulletPlayer();
	void Update();
	static CBulletPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
};
class CBulletEnemy : public CBullet{
private:
public:
	CBulletEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~CBulletEnemy();
	void Update();
	static CBulletEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
};
class CBulletBoss : public CBullet {
private:
public:
	CBulletBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~CBulletBoss() {};
	void Update();
	static CBulletBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
};

class CMissileBoss : public CBullet {
private:
public:
	CMissileBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~CMissileBoss() {};
	void Update();
	static CMissileBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
};
#endif