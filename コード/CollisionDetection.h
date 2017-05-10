/****************************************************************************
* �^�C�g��:  CollisionDetection.cpp�̃w�b�_�[
* �t�@�C����:CollisionDetection.h
* �쐬�ҁF	 �F���n
* �쐬���F   2016/07/03
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _COLLISION_DETECTION_H_
#define _COLLISION_DETECTION_H_
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"renderer.h"
/*******************************************************************************
* �N���X�̒�`
*******************************************************************************/
class CCollisionDetection {
private:
	static void GetVertex(LPD3DXMESH pMesh, unsigned long index, D3DXVECTOR3* vertex);
	static bool GetIntersectionPoint(D3DXVECTOR3 rayStart, D3DXVECTOR3 rayDirection, LPD3DXMESH pMesh, D3DXVECTOR3* intersectionPoint, D3DXVECTOR3* normalVector);

public:
	static bool LayToMesh(D3DXVECTOR3 rayStart, D3DXVECTOR3 rayDirection, LPD3DXMESH pMesh, D3DXVECTOR3 meshPosition, D3DXMATRIX meshRotation, D3DXVECTOR3* intersectionPoint = 0, D3DXVECTOR3* normalVector = 0);
};
#endif