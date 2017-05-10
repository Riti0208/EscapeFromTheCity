/****************************************************************************
* タイトル:  fade.cppのヘッダー
* ファイル名:title.h
* 作成者：	 芳崎大地
* 作成日：   2016/06/26
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _FADE_CONTROLLER_H_
#define _FADE_CONTROLLER_H_
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "renderer.h"
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
class CFade;
class CMode;
//フェードコントローラクラス
class CFadeController{
private:
	CFadeController();
	static CMode *m_nextMode;
	static CFade *m_currentFade;
public:
	static void SetFade(CFade *fade, CMode *nextMode, float nFadeSpeed = 1.0f);
	
	static CFade *GetFade(){ return m_currentFade; };
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};
#endif
