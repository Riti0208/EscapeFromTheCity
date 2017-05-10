/****************************************************************************
* タイトル:  camera.cppのヘッダー
* ファイル名:camera.h
* 作成者：	 芳崎大地
* 作成日：   2015/07/06
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _CAMERA_H_
#define _CAMERA_H_
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"renderer.h"
#include"player.h"
#include<list>
/*******************************************************************************
* クラスの定義
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
	static D3DXVECTOR3 posV;			//視点
	static D3DXVECTOR3 posR;			//注視点
	static D3DXVECTOR3 vecU;			//上方向ベクトル
	static D3DXVECTOR3	moveV;			//移動量}
	static D3DXVECTOR3	moveR;			//移動量
	static D3DXVECTOR3 rot;			//カメラの向き
	static D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	static D3DXMATRIX mtxView;			//ビューマトリックス
	static float fDistance;			//視点と注視点の距離
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
		int Sx,  // スクリーンX座標
		int Sy,  // スクリーンY座標
		float fZ,  // 射影空間でのZ値（0～1）
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
* プロトタイプ宣言
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/

#endif