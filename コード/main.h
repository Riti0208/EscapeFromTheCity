/****************************************************************************
* タイトル:  メインヘッダー
* ファイル名:main.h
* 作成者：	 芳崎大地
* 作成日：   2015/05/29
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS


#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <Vector>
#include <list>
#include <algorithm>
#include <functional>
/*******************************************************************************
* ライブラリのリンク
*******************************************************************************/
#pragma comment(lib, "winmm.lib")
/*******************************************************************************
* マクロ定義
*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#define SCREEN_WIDTH	(1920.0f)//ウィンドウの幅
#define SCREEN_HEIGHT	(1080.0f)//ウィンドウの高さ

#define COLOR_BLACK		(D3DCOLOR_RGBA(	0,		0,		0,		0))
#define COLOR_WHITE		(D3DCOLOR_RGBA(	255,	255,	255,	255))

#define COLOR_RED		(D3DCOLOR_RGBA(	204,	0,		0,		255))
#define COLOR_BLUE		(D3DCOLOR_RGBA(	15,		82,		188,	255))
#define COLOR_YELLOW	(D3DCOLOR_RGBA(	255,	255,	0,		255))
#define COLOR_GREEN		(D3DCOLOR_RGBA(	0,		255,	65,		255))
#define COLOR_PINK		(D3DCOLOR_RGBA(	239,	143,	255,	255))
#define COLOR_MAGENTA	(D3DCOLOR_RGBA(	229,	0,		118,	255))
#define COLOR_PURPLE	(D3DCOLOR_RGBA(	196,	0,		204,	255))
#define COLOR_CYAN		(D3DCOLOR_RGBA(	15,		82,		118,	255))
#define	COLOR_GRAY		(D3DCOLOR_RGBA(	126,	126,	126,	255))
#define COLOR_BROWN		(D3DCOLOR_RGBA(	165,	89,		27,		255))

#define COLOR_RGREEN	(D3DCOLOR_RGBA(	116,	156,	54,		255))
#define	COLOR_RGRAY		(D3DCOLOR_RGBA(	189,	189,	189,	255))
#define COLOR_RBROWN	(D3DCOLOR_RGBA(	216,	117,	35,		255))

#define COLOR_DGREEN	(D3DCOLOR_RGBA(	48,		63,		22,		255))
#define	COLOR_DGRAY		(D3DCOLOR_RGBA(	63,		63,		63,		255))
#define COLOR_DBROWN	(D3DCOLOR_RGBA(	91,		49,		15,		255))

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HWND GetHWnd(void);
int GetFPS();
/*******************************************************************************
* インクルードガード
*******************************************************************************/

#endif