/****************************************************************************
* タイトル:  scene2dヘッダー
* ファイル名:scene2d.h
* 作成者：	 芳崎大地
* 作成日：   2016/05/3
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _SCENE_2D_ANIMATION_WL_H_
#define _SCENE_2D_ANIMATION_WL_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"renderer.h"
/*******************************************************************************
* ライブラリのリンク
*******************************************************************************/
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
/*******************************************************************************
* クラスの定義
*******************************************************************************/
//シーンクラス
class CScene2DwLAnimation{
private:
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;	//頂点バッファ
	LPDIRECT3DTEXTURE9		m_pTexture;
	char					*m_pFileName;		//ファイル名
	float					m_fWidth;
	float					m_fHeight;
	int						m_animationNum;
	int						m_currentAnimtionFrame;
	int						m_currentAnimtionSpriteCnt;
	int						m_animationChangeFrame;
	D3DXVECTOR3				m_pos;
	D3DXCOLOR				m_col;
public:
	CScene2DwLAnimation(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col, int animationNum, int animationChangeFrame){ m_bufferPolygon = NULL; m_pos = pos; m_fWidth = fWidth; m_fHeight = fHeight; m_pFileName = pFileName; m_col = col; m_animationNum = animationNum; m_animationChangeFrame = animationChangeFrame; Init(); }
	~CScene2DwLAnimation(){ Uninit(); }
	void Init();
	void Uninit();
	void Draw();
	void Update();
};

#endif