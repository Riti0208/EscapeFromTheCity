/****************************************************************************
* タイトル:  カメラの処理
* ファイル名:camera.cpp
* 作成者：	 芳崎大地
* 作成日：   2015/10/20
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
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
* マクロ定義
*******************************************************************************/
#define NEAR_Z	(10)					//カメラの描画開始距離
#define FAR_Z	(10000)					//カメラの描画終了距離
#define MOVE_SPEED	(4.0f)				//カメラの１Fあたりの移動量
#define ROT_VALUE	(0.2f)			//カメラの１Fあたりの回転量
#define DISNTANCE_TRANS_PER_FRAME (1.0f)//視点と注視点の間の距離の１Fあたりの変化量

#define BETWEEN_PLAYER_CAMERA_Z (300.0f)	//プレイヤーとカメラのＺ軸での距離
#define BETWEEN_PLAYER_CAMERA_VIEW_X (200.0f)	//プレイヤーとカメラの視点のX軸での距離
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
D3DXVECTOR3 CCamera::posV;			//視点
D3DXVECTOR3 CCamera::posR;			//注視点
D3DXVECTOR3 CCamera::vecU;			//上方向ベクトル
D3DXVECTOR3	CCamera::moveV;			//移動量}
D3DXVECTOR3	CCamera::moveR;			//移動量
D3DXVECTOR3 CCamera::rot;			//カメラの向き
D3DXMATRIX	CCamera::mtxProjection;	//プロジェクションマトリックス
D3DXMATRIX	CCamera::mtxView;			//ビューマトリックス
float		CCamera::fDistance;			//視点と注視点の距離
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
* 関数名:HRESULT InitCamera()
*
* 引数:  なし
* 戻り値:なし
* 説明 カメラの初期化処理
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
* 関数名:void UninitCamera()
*
* 引数:  なし
* 戻り値:なし
* 説明 カメラの終了処理
*
*******************************************************************************/
void CCamera::Uninit(){
}
/*******************************************************************************
* 関数名:void UpdateCamera()
*
* 引数:  なし
* 戻り値:なし
* 説明 カメラの更新処理
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
* 関数名:void SetCamera(
* 説明 カメラのセッター
*)
*
* 引数:  なし
* 戻り値:なし
*******************************************************************************/
void CCamera::Set(){
	//デバイスの取得
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	//プロジェクションマトリックスの作成
	D3DXMatrixIdentity(&mtxProjection);
	//プロジェクションマトリックスの初期化
	D3DXMatrixPerspectiveFovLH(&mtxProjection, (D3DX_PI) / 4, (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_Z, FAR_Z);
	CEffectManager::onResetDevice((D3DX_PI) / 4, (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_Z, FAR_Z);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	CEffectManager::SetProjectionMatrix(posV, posR, vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
/*******************************************************************************
* 関数名:void DrawCamera()
*
* 引数:  なし
* 戻り値:なし
* 説明 カメラ情報の描画
*
*******************************************************************************/
void CCamera::Draw(){
}
/*******************************************************************************
* 関数名:void ControllCamera()
*
* 引数:  なし
* 戻り値:&g_Camera
* 説明 カメラ情報のコントローラー
*
*******************************************************************************/
void CCamera::ControllCamera(){

}
/*******************************************************************************
* 関数名:void ForrowPlayer()
*
* 引数:  なし
* 戻り値:&g_Camera
* 説明 カメラをプレイヤーに対して追従させる関数
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
// スクリーン座標をワールド座標に変換
D3DXVECTOR3* CCamera::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // スクリーンX座標
	int Sy,  // スクリーンY座標
	float fZ,  // 射影空間でのZ値（0～1）
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	) {
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// 逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3((float)Sx, (float)Sy, (float)fZ), &tmp);
	return pout;
}
// XZ平面とスクリーン座標の交点算出関数
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

	// 床との交差が起きている場合は交点を
	// 起きていない場合は遠くの壁との交点を出力
	if (ray.y <= billboardPos.y) {
		// 床交点
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