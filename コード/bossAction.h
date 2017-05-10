/****************************************************************************
* タイトル:  bossAction.cppのヘッダー
* ファイル名:bossAction.h
* 作成者：	 芳崎大地
* 作成日：   2017/2/12
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _BOSS_ACTION_H_
#define _BOSS_ACTION_H_
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"manager.h"
/*******************************************************************************
* クラスの定義
*******************************************************************************/
//bossのAIの基底クラス
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
//拡散攻撃AI
class spreadAttack : public bossAction {
public:
	bool update(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);
};
//集中攻撃AI
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