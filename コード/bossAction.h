/****************************************************************************
* �^�C�g��:  bossAction.cpp�̃w�b�_�[
* �t�@�C����:bossAction.h
* �쐬�ҁF	 �F���n
* �쐬���F   2017/2/12
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _BOSS_ACTION_H_
#define _BOSS_ACTION_H_
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
//boss��AI�̊��N���X
class bossAction {
public:
	bossAction() {
		attackTime = 0;
		sinCnt = 0;
		targetHeight = 75.0f;
	};
	~bossAction() {};
	virtual bool update(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot) = 0;
protected:
	int attackTime;
	int sinCnt;
	float targetHeight;
};
//�g�U�U��AI
class spreadAttack : public bossAction {
public:
	bool update(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);
};
//�W���U��AI
class concentrationAttack : public bossAction {
public:
	bool update(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);
};
//noActionAI
class newtral : public bossAction {
public:
	bool update(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);
};

#endif