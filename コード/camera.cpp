/****************************************************************************
* �^�C�g��:  �J�����̏���
* �t�@�C����:camera.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2015/10/20
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"input.h"
#include"camera.h"
#include"scene.h"
#include"manager.h"
#include"sceneRect.h"
#include"scene2D.h"
#include"player.h"
#include"effectManager.h"
#include"stage.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define NEAR_Z	(10)					//�J�����̕`��J�n����
#define FAR_Z	(10000)					//�J�����̕`��I������
#define MOVE_SPEED	(4.0f)				//�J�����̂PF������̈ړ���
#define ROT_VALUE	(0.2f)			//�J�����̂PF������̉�]��
#define DISNTANCE_TRANS_PER_FRAME (1.0f)//���_�ƒ����_�̊Ԃ̋����̂PF������̕ω���

#define BETWEEN_PLAYER_CAMERA_Z (300.0f)	//�v���C���[�ƃJ�����̂y���ł̋���
#define BETWEEN_PLAYER_CAMERA_VIEW_X (200.0f)	//�v���C���[�ƃJ�����̎��_��X���ł̋���
/*******************************************************************************
* �\���̂̒�`
*******************************************************************************/
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
D3DXVECTOR3 CCamera::posV;			//���_
D3DXVECTOR3 CCamera::posR;			//�����_
D3DXVECTOR3 CCamera::vecU;			//������x�N�g��
D3DXVECTOR3	CCamera::moveV;			//�ړ���}
D3DXVECTOR3	CCamera::moveR;			//�ړ���
D3DXVECTOR3 CCamera::rot;			//�J�����̌���
D3DXMATRIX	CCamera::mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
D3DXMATRIX	CCamera::mtxView;			//�r���[�}�g���b�N�X
float		CCamera::fDistance;			//���_�ƒ����_�̋���
bool		CCamera::bEdit;
D3DXVECTOR3 CCamera::NowRot;
int			CCamera::nWateTimeCnt;
float		CCamera::g_fAngleCamera;
D3DXVECTOR3 CCamera::RRot;
CScene2D *CCamera::scene2d;
D3DXVECTOR3 CCamera::billboardPos;
D3DXVECTOR3 CCamera::scenePos;
bool		CCamera::bRotateL;
bool		CCamera::bRotateR;
float		CCamera::fRotLast;
int			CCamera::cameraLevel;
float		CCamera::zeroCameraRot, CCamera::oneCameraRot, CCamera::twoCameraRot, CCamera::fVarSin;
/*******************************************************************************
* �֐���:HRESULT InitCamera()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �J�����̏���������
*
*******************************************************************************/
void CCamera::Init(){
	zeroCameraRot = D3DX_PI * 0.5f;
	oneCameraRot = D3DX_PI * 1.5f;
	twoCameraRot = 0.0f;
	fVarSin = 0.0f;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posV = D3DXVECTOR3(0.0f, 50.0f, 200.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	NowRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fRotLast = 0.0f;
	nWateTimeCnt = 0;
	bEdit = false;
	bRotateR = false;
	bRotateL = false;
	g_fAngleCamera = atan2f(posV.x - posR.x, posV.z - posR.z);
	fDistance = sqrtf((posV.x - posR.x) * (posV.x - posR.x) + (posV.z - posR.z) * (posV.z - posR.z));
	NowRot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	cameraLevel = 0;
};
/*******************************************************************************
* �֐���:void UninitCamera()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �J�����̏I������
*
*******************************************************************************/
void CCamera::Uninit(){
}
/*******************************************************************************
* �֐���:void UpdateCamera()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �J�����̍X�V����
*
*******************************************************************************/
void CCamera::Update(){
	switch (cameraLevel){
	case 0:
		if (LevelZeroCamera())	cameraLevel++;
		break;
	case 1:
		if (LevelOneCamera()){
			posV.y = 500.0f;
			posR.y = 500.0f;
			cameraLevel++;
		}
		break;
	case 2:
		if (LevelTwoCamera()){
			cameraLevel++;
		}
		break;
	case 3:
		ForrowPlayer(*CGame::player->GetPos(), *CGame::player->GetRot());

		break;
	}
}
/*******************************************************************************
* �֐���:void SetCamera(
* ���� �J�����̃Z�b�^�[
*)
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
*******************************************************************************/
void CCamera::Set(){
	//�f�o�C�X�̎擾
	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixIdentity(&mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixPerspectiveFovLH(&mtxProjection, (D3DX_PI) / 4, (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_Z, FAR_Z);
	CEffectManager::onResetDevice((D3DX_PI) / 4, (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_Z, FAR_Z);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	CEffectManager::SetProjectionMatrix(posV, posR, vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
/*******************************************************************************
* �֐���:void DrawCamera()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �J�������̕`��
*
*******************************************************************************/
void CCamera::Draw(){
}
/*******************************************************************************
* �֐���:void ControllCamera()
*
* ����:  �Ȃ�
* �߂�l:&g_Camera
* ���� �J�������̃R���g���[���[
*
*******************************************************************************/
void CCamera::ControllCamera(){

}
/*******************************************************************************
* �֐���:void ForrowPlayer()
*
* ����:  �Ȃ�
* �߂�l:&g_Camera
* ���� �J�������v���C���[�ɑ΂��ĒǏ]������֐�
*
*******************************************************************************/
void CCamera::ForrowPlayer(D3DXVECTOR3 playerPos, D3DXVECTOR3  playerRot){
	D3DXMATRIX *proj = getProj();
	D3DXMATRIX *view = getView();

	posV.y = playerPos.y + 15.0f + fDistance / 100.0f * sinf(g_fAngleCamera + rot.x);
	posV.x = playerPos.x + fDistance / 50.0f * sinf(g_fAngleCamera + rot.y);
	posV.z = playerPos.z + fDistance / 50.0f * cosf(g_fAngleCamera + rot.y);

	posR.x = posV.x - sinf(g_fAngleCamera + rot.y) * fDistance * 50.0f;
	posR.z = posV.z - cosf(g_fAngleCamera + rot.y) * fDistance * 50.0f;
	posR.y = posV.y + 60.0f;

	posV.y = playerPos.y + 60.0f;
	posV.x = playerPos.x + 200.0f * sinf(g_fAngleCamera + rot.y);
	posV.z = playerPos.z + 200.0f * cosf(g_fAngleCamera + rot.y);

	rot.y = playerRot.y;


	if (posV.x > 30) posV.x = 30;
	if (posV.x < -30) posV.x = -30;
	if (posV.y > 80) posV.y = 80;
}
// �X�N���[�����W�����[���h���W�ɕϊ�
D3DXVECTOR3* CCamera::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // �X�N���[��X���W
	int Sy,  // �X�N���[��Y���W
	float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	) {
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// �t�ϊ�
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3((float)Sx, (float)Sy, (float)fZ), &tmp);
	return pout;
}
// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
D3DXVECTOR3* CCamera::CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	) {
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld(&nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj);
	CalcScreenToWorld(&farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj);
	ray = farpos - nearpos;
	D3DXVec3Normalize(&ray, &ray);

	// ���Ƃ̌������N���Ă���ꍇ�͌�_��
	// �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
	if (ray.y <= billboardPos.y) {
		// ����_
		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		*pout = nearpos + (LP0 / Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}
bool CCamera::LevelTwoCamera(){
	CPlayer *player = CGame::player;
	posR = *player->GetPos();
	posR.x = player->GetPos()->x - sinf(player->GetRot()->y) *  BETWEEN_PLAYER_CAMERA_VIEW_X;
	posR.z = player->GetPos()->z - cosf(player->GetRot()->y) *  BETWEEN_PLAYER_CAMERA_VIEW_X;
	posR.y += 2.0f;
	posV.y -= 5.0f;
	posV.x = player->GetPos()->x + sinf(player->GetRot()->y) *  BETWEEN_PLAYER_CAMERA_VIEW_X;
	posV.z = player->GetPos()->z + cosf(player->GetRot()->y) *  BETWEEN_PLAYER_CAMERA_VIEW_X;
	if (posV.y < player->GetPos()->y + 100.0f)	return true;
	return false;
}
bool CCamera::LevelZeroCamera(){
	CPlayer *player = CGame::player;
	posR = *player->GetPos();
	posV.x = posR.x + sinf(zeroCameraRot) *  BETWEEN_PLAYER_CAMERA_VIEW_X;
	posV.z = posR.z + cosf(zeroCameraRot) *  BETWEEN_PLAYER_CAMERA_VIEW_X;
	posV.y = 50.0f;
	zeroCameraRot += 0.015f;
	if (zeroCameraRot > 1.0f * D3DX_PI)	return true;
	return false;
}
bool CCamera::LevelOneCamera(){
	CPlayer *player = CGame::player;
	posR = *player->GetPos();
	posV.x = posR.x + sinf(oneCameraRot) *  BETWEEN_PLAYER_CAMERA_VIEW_X;
	posV.z = posR.z + cosf(oneCameraRot) *  BETWEEN_PLAYER_CAMERA_VIEW_X;
	posV.y = 50.0f;
	oneCameraRot -= 0.015f;
	if (oneCameraRot < 1.0f * D3DX_PI)	{ return true; posV.y = 70.0f; }
	return false;
}