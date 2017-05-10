/****************************************************************************
* タイトル:  フェードの処理
* ファイル名:fade.cpp
* 作成者：	 芳崎大地
* 作成日：   2015/07/11
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"fade.h"
#include"mode.h"
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:CFade::CFade()
*
* 引数:  なし
* 戻り値:なし
* 説明 フェードクラスのコンストラクタ
*
*******************************************************************************/
CFade::CFade(){
	m_nVertexNum = 0;
	m_buffer = NULL;
	m_bChangeMode = false;
	m_currentFadeState = FADE_NONE;
	m_bFinish = false;
}
/*******************************************************************************
* 関数名:CFade::~CFade()
*
* 引数:  なし
* 戻り値:なし
* 説明 フェードクラスのデストラクタ
*
*******************************************************************************/
CFade::~CFade(){
	SAFE_RELEASE(m_buffer);
}