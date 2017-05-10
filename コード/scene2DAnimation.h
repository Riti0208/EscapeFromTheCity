/****************************************************************************
* タイトル:  scene2dヘッダー
* ファイル名:scene2d.h
* 作成者：	 芳崎大地
* 作成日：   2016/05/3
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _SCENE_2D_ANIMATION_H_
#define _SCENE_2D_ANIMATION_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"scene.h"
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
class CScene2DAnimation : public CScene{
private:
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;	//頂点バッファ
	LPDIRECT3DTEXTURE9		m_pTexture;
	char					*m_pFileName;		//ファイル名
	float					m_fWidth;
	float					m_fHeight;
	D3DXVECTOR3				m_oldPos;
	D3DXCOLOR				m_oldCol;
	bool					m_withoutLoadingMode;
	int						m_animationNum;
	int						m_currentAnimtionFrame;
	int						m_currentAnimtionSpriteCnt;
	int						m_animationChangeFrame;
public:
	CScene2DAnimation(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col, int animationNum, int animationChangeFrame, bool withoutLoadingMode){ m_bufferPolygon = NULL; m_pos = pos; m_fWidth = fWidth; m_fHeight = fHeight; m_pFileName = pFileName; m_col = col; m_animationNum = animationNum; m_animationChangeFrame = animationChangeFrame; m_withoutLoadingMode = withoutLoadingMode; Init(); }
	~CScene2DAnimation(){ Uninit(); }
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static CScene2DAnimation *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col, int animationNum, int animationChangeFrame, bool withoutLoadingMode = false);
};

#endif