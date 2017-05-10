/****************************************************************************
* �^�C�g��:  camera.cpp�̃w�b�_�[
* �t�@�C����:camera.h
* �쐬�ҁF	 �F���n
* �쐬���F   2015/07/06
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _CAMERA_H_
#define _CAMERA_H_
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"renderer.h"
#include"player.h"
#include<list>
/*******************************************************************************
* �N���X�̒�`
*******************************************************************************/
class CScene2D;
class CCamera{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static void Set();
	static D3DXVECTOR3 GetPosLookAt(){ return posR; };
	static D3DXVECTOR3 GetPosEye(){ return posV; };
	static D3DXVECTOR3 GetRot(){ return rot; };
	static float GetAngleCamera(){ return g_fAngleCamera; };
	static D3DXMATRIX *getProj(){ return &mtxProjection; };
	static D3DXMATRIX *getView(){ return &mtxView; };
	static void ForrowPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static void SetPosLookAt(D3DXVECTOR3 pos){ posR = pos; };
	static void SetPosEye(D3DXVECTOR3 pos){ posV = pos; }
	static void SetRot(D3DXVECTOR3 _rot){ rot = _rot; }
private:
	static D3DXVECTOR3 posV;			//���_
	static D3DXVECTOR3 posR;			//�����_
	static D3DXVECTOR3 vecU;			//������x�N�g��
	static D3DXVECTOR3	moveV;			//�ړ���}
	static D3DXVECTOR3	moveR;			//�ړ���
	static D3DXVECTOR3 rot;			//�J�����̌���
	static D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	static D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	static float fDistance;			//���_�ƒ����_�̋���
	static D3DXVECTOR3 NowRot;
	static int nWateTimeCnt;
	static float g_fAngleCamera;
	static D3DXVECTOR3 RRot;
	static void ForrowPlayer();
	static void ControllCamera();
	static bool	bEdit;
	static bool bRotateR;
	static bool bRotateL;
	static float fRotLast;
	static D3DXVECTOR3 *CalcScreenToWorld(D3DXVECTOR3* pout,
		int Sx,  // �X�N���[��X���W
		int Sy,  // �X�N���[��Y���W
		float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj);
	static D3DXVECTOR3 *CalcScreenToXZ(D3DXVECTOR3* pout,
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj);
	static CScene2D	  *scene2d;
	static D3DXVECTOR3 scenePos;
	static D3DXVECTOR3 billboardPos;
	static bool LevelZeroCamera();
	static bool LevelOneCamera();
	static bool LevelTwoCamera();
	static int		cameraLevel;
	static float	zeroCameraRot, oneCameraRot, twoCameraRot, fVarSin;
};
class CameraMover{
public:
	virtual void	Update();
	bool			isChangeCamera;
	float			nextCameraTimeLimit;
	static			std::list<CameraMover> cameraMoverList;
};
class CameraFirstMover : public CameraMover{
public:
	void Update();
};
class CameraSecondMover : public CameraMover{
public:
	void Update();
};
class CameraThirdMover : public CameraMover{
public:
	void Update();
};
class CamerabattleMover : public CameraMover{
public:
	void Update();
};
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/

#endif