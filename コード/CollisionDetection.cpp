/****************************************************************************
* タイトル:  メッシュとのあたり判定処理
* ファイル名:CollisionDetection.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/07/03
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "CollisionDetection.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/****************************************1**************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:void CCollisionDetection::GetVertex(LPD3DXMESH pMesh, unsigned long index, D3DXVECTOR3* vertex)
*
* 引数:  なし
* 戻り値:なし
* 説明 あたり判定時の頂点の取得
*
*******************************************************************************/
void CCollisionDetection::GetVertex(LPD3DXMESH pMesh, unsigned long index, D3DXVECTOR3* vertex) {
	unsigned long stride = pMesh->GetNumBytesPerVertex();
	unsigned short *indexBuffer = 0;									// 頂点番号配列
	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&indexBuffer);
	byte* vertices = 0;													// 頂点データの先頭アドレス
	if (SUCCEEDED (pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&vertices))){
		vertex[0] = *((D3DXVECTOR3*)(vertices + stride*indexBuffer[index*3]));		// indexで指定したポリゴンの頂点データをキャストで切り取ってvertexにコピー
		vertex[1] = *((D3DXVECTOR3*)(vertices + stride*indexBuffer[index*3 + 1]));
		vertex[2] = *((D3DXVECTOR3*)(vertices + stride*indexBuffer[index*3 + 2]));
		pMesh->UnlockVertexBuffer();
	}
	pMesh->UnlockIndexBuffer();
}
/*******************************************************************************
* 関数名:bool CCollisionDetection::GetIntersectionPoint(D3DXVECTOR3 rayStart, D3DXVECTOR3 rayDirection, LPD3DXMESH pMesh, D3DXVECTOR3* intersectionPoint, D3DXVECTOR3* normalVector)
*
* 引数:  なし
* 戻り値:なし
* 説明	メッシュにあったたか
*
*******************************************************************************/
bool CCollisionDetection::GetIntersectionPoint(D3DXVECTOR3 rayStart, D3DXVECTOR3 rayDirection, LPD3DXMESH pMesh, D3DXVECTOR3* intersectionPoint, D3DXVECTOR3* normalVector) {
	// 交差をチェック
	unsigned long index;	// 交差するポリゴンのindex
	float U, V, d;		// ポリゴン上の交差点のUV座標, レイの始点から交点までの距離
	BOOL hit;			// 交差したか否か
	D3DXIntersect(pMesh, &rayStart, &rayDirection, &hit, &index, &U, &V, &d, 0, 0);
	if (!hit) return false;

	// 交点を取得
	if (!intersectionPoint) return true;
	D3DXVECTOR3 vertex[3];	// 交差するポリゴンの頂点
	GetVertex(pMesh, index, vertex);
	*intersectionPoint = vertex[0] + U*(vertex[1] - vertex[0]) + V*(vertex[2] - vertex[0]);

	// 法線ベクトルを取得
	if (!normalVector) return true;
	D3DXPLANE plane;		// 交差するポリゴンの作る平面
	D3DXPlaneFromPoints(&plane, &vertex[0], &vertex[1], &vertex[2]);
	D3DXPlaneNormalize(&plane, &plane);
	*normalVector = D3DXVECTOR3(plane[0], plane[1], plane[2]);
	return true;
}
/*******************************************************************************
* 関数名:bool CCollisionDetection::LayToMesh(D3DXVECTOR3 rayStart, D3DXVECTOR3 rayDirection, LPD3DXMESH pMesh, D3DXVECTOR3 meshPosition, D3DXMATRIX meshRotation, D3DXVECTOR3* intersectionPoint, D3DXVECTOR3* normalVector
*
* 引数:  なし
* 戻り値:なし
* 説明	メッシュにあったたか
*
*******************************************************************************/
bool CCollisionDetection::LayToMesh(D3DXVECTOR3 rayStart, D3DXVECTOR3 rayDirection, LPD3DXMESH pMesh, D3DXVECTOR3 meshPosition, D3DXMATRIX meshRotation, D3DXVECTOR3* intersectionPoint, D3DXVECTOR3* normalVector) {
	// ローカル座標系に変換
	D3DXMATRIX trans, world, invWorld, invRotation;
	D3DXMatrixTranslation(&trans, meshPosition.x, meshPosition.y, meshPosition.z);
	world = meshRotation*trans;
	D3DXMatrixInverse(&invWorld, 0, &world);
	D3DXMatrixInverse(&invRotation, 0, &meshRotation);
	D3DXVec3TransformCoord(&rayStart, &rayStart, &invWorld);
	D3DXVec3TransformCoord(&rayDirection, &rayDirection, &invRotation);

	// ローカル座標系で交点を取得
	if (!GetIntersectionPoint(rayStart, rayDirection, pMesh, intersectionPoint, normalVector)) return false;

	// ワールド座標系に変換
	if (intersectionPoint) D3DXVec3TransformCoord(intersectionPoint, intersectionPoint, &world);
	if (normalVector) D3DXVec3TransformCoord(normalVector, normalVector, &meshRotation);
	return true;
}