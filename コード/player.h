/****************************************************************************
* �^�C�g��:  player.cpp�̃w�b�_�[
* �t�@�C����:player.h
* �쐬�ҁF	 �F���n
* �쐬���F   2015/05/10
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _PLAYER_H_
#define _PLAYER_H_
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"Effekseer.h"
#include"manager.h"
#include"stensilShadow.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
class CPlayerModel;
class CScore;
/*******************************************************************************
* �\���̂̒�`
*******************************************************************************/
class CPlayer : public CScene{
public:
	CPlayer(int n) : CScene("player") { Init(); nPlayer = n; };
	~CPlayer(){ Uninit(); };
	void Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR3 *GetPos(){ return &m_pos; };
	static CPlayer *Create(int n);
	int GetHp(){ return m_nHp; }
	void SetHp(int hp){ m_nHp = hp; }
	int GetDummyHp(){ return m_nDummyHp; }
	int GetBulletNum(){ return m_nBullet; }
	int GetBulletReloardTime(){ return m_nBulletCnt; }
private:
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rotLast;
	D3DXMATRIX m_world;
	CSceneXFile *cyl;
	void Controll();
	CPlayerModel *model;
	stensilShadow *shadow;
	int m_nHp;
	int nFootSoundCnt;
	void addMove(D3DXVECTOR3 move){ m_move += move; };
	int m_nDummyHp;
	int nPlayer;
	int	nHpCnt;
	CScene2D *stensilFilter;
	int m_nBullet;
	int m_nBulletCnt;
	bool isGoal;
	bool isJump;
	float firstY;
	float jumpCnt;
	::Effekseer::Handle boost;
	float moveSpeed;
};
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/

#endif