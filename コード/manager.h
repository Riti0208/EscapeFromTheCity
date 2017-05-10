/****************************************************************************
* タイトル:  マネージャクラスヘッダー
* ファイル名:manager.h
* 作成者：芳崎大地
* 作成日：2016/05/9
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _MANAGER_H_
#define _MANAGER_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"main.h"
#include"sound.h"
#include"scene.h"
#include"scene2D.h"
#include"scene3D.h"
#include"sceneXFile.h"
#include"input.h"
#include"mode.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"gameOver.h"
#include"fadeController.h"
#include"fade.h"
#include"normalFade.h"
#include"camera.h"
#include"light.h"
#include"debugProc.h"
#include"texture.h"
#include"sceneBillboard.h"
#include"sky.h"
#include"score.h"
#include"gui.h"
#include"guiPanel.h"
#include"model.h"
#include"moionModel.h"
#include"debugProc.h"
#include"effectManager.h"
#include"load.h"
/*******************************************************************************
* ライブラリのリンク
*******************************************************************************/
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define GRAVITY 0.98f
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
/*******************************************************************************
* クラスの定義
*******************************************************************************/
class CManager{
private:
	CRenderer m_renderer;
	std::vector<CScene *>			m_sceneVec;			//シーンクラス配列
	std::vector<CGui *>				m_guiVec;
	bool m_bWireFrame;
	unsigned int  loadId;
	bool		isInit;
	load		*loadScene;
public:
	CManager(){}
	~CManager(){}
	void Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Draw();
	void Update();
};
#endif