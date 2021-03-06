/****************************************************************************
* タイトル:  scene2dヘッダー
* ファイル名:scene2d.h
* 作成者：	 芳崎大地
* 作成日：   2016/05/3
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _SCENE_3D_H_
#define _SCENE_3D_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"manager.h"
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
class CScene3D : public CScene{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBufferMeshField;		//フィールド用バッファー
	LPDIRECT3DINDEXBUFFER9	m_pIndexBufferField;		//インデックスバッファーへのポインタ

	D3DXVECTOR3				m_posMeshField;				//フィールドの位置
	D3DXVECTOR3				m_rotMeshField;				//フィールドの向き
	D3DXVECTOR3				m_sclMeshField;				//フィールドのスケール

	int m_nFieldNumX;								//横向きに対しての往復回数
	int m_nFieldNumZ;								//縦向きに対しての往復回数
	int m_nMeshFieldPolygonNum;						//ポリゴン数
	int m_nMeshFieldVerTexNum;                      //頂点数
	int m_nIdxMeshFieldNum;                         //インデックス数
	float m_fBlockSizeX;							//1ブロックの横向きの大きさ
	float m_fBlockSizeZ;							//1ブロックの縦向きの大きさ
	float m_fFieldSizeX;							//フィールドの横向きの大きさ
	float m_fFieldSizeZ;							//フィールドの縦向きの大きさ

	char *m_pFileName;

public:
	CScene3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col){ m_pos = pos; m_rot = rot; m_pFileName = pFileName; m_col = col; Init(); };
	~CScene3D(){ Uninit(); };
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col);
};

#endif