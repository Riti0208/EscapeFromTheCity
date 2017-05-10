/****************************************************************************
* タイトル:  numberヘッダー
* ファイル名:number.h
* 作成者：	 芳崎大地
* 作成日：   2016/05/13
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _NUMBER_H_
#define _NUMBER_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"gui.h"
#include"sceneRect.h"
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
class CNumberList : public CGui{
public:
	CNumberList(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nLineNum);
	~CNumberList(){ Uninit(); };
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetNum(int num){ m_nNum = num; };
	static CNumberList *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nLineNum);
private:
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;	//頂点バッファ
	D3DXVECTOR3 m_pos;		//ポジション
	float		m_fWidth;	//幅
	float		m_fHeight;	//高さ
	char		*m_pFileName;	//テクスチャの名前
	int			m_nNum;		//描画用の数値
	int			m_nLineNum;
};
class CNumber : public CGui{	
public:
	CNumber(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber);
	~CNumber(){ Uninit(); };
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetNum(int num){ m_nNum = num; };
	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber);
private:
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;	//頂点バッファ
	D3DXVECTOR3 m_pos;		//ポジション
	float		m_fWidth;	//幅
	float		m_fHeight;	//高さ
	char		*m_pFileName;	//テクスチャの名前
	int			m_nNum;		//描画用の数値
};

#endif