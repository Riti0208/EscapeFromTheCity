/****************************************************************************
* タイトル:  CollisionDetection.cppのヘッダー
* ファイル名:CollisionDetection.h
* 作成者：	 芳崎大地
* 作成日：   2016/07/03
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _COLLISION_DETECTION_H_
#define _COLLISION_DETECTION_H_
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"renderer.h"
/*******************************************************************************
* クラスの定義
*******************************************************************************/
class CCollisionDetection {
private:
	static void GetVertex(LPD3DXMESH pMesh, unsigned long index, D3DXVECTOR3* vertex);
	static bool GetIntersectionPoint(D3DXVECTOR3 rayStart, D3DXVECTOR3 rayDirection, LPD3DXMESH pMesh, D3DXVECTOR3* intersectionPoint, D3DXVECTOR3* normalVector);

public:
	static bool LayToMesh(D3DXVECTOR3 rayStart, D3DXVECTOR3 rayDirection, LPD3DXMESH pMesh, D3DXVECTOR3 meshPosition, D3DXMATRIX meshRotation, D3DXVECTOR3* intersectionPoint = 0, D3DXVECTOR3* normalVector = 0);
};
#endif