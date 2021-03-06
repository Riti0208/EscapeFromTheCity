/****************************************************************************
* タイトル:  debugProc.cppのヘッダー
* ファイル名:debugProc.h
* 作成者：	 芳崎大地
* 作成日：   2016/05/13
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"manager.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MAX_CHAR 1020
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
/*******************************************************************************
* クラスの定義
*******************************************************************************/
class CDebugProc{
public:
	CDebugProc(){}
	~CDebugProc(){}
	static void print(const char* fmt, ...);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
private:
	static LPD3DXFONT m_pFont;	//フォントのワーク
	static char m_aStrDebug[MAX_CHAR];	//描画用文字列
};
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/

#endif