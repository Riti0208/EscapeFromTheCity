/****************************************************************************
* タイトル:  sceneXFileヘッダー
* ファイル名:sceneXFile.h
* 作成者：	 芳崎大地
* 作成日：   2016/05/3
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _SCENE_X_H_
#define _SCENE_X_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"scene.h"
#include"model.h"
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
class CSceneXFile : public CScene{
private:
	LPDIRECT3DTEXTURE9 	m_texture;	//テクスチャ情報
	LPD3DXMESH 			m_mesh;		//メッシュ情報
	LPD3DXBUFFER	 	m_bufferMaterial;	//マテリアル情報
	DWORD				m_numMaterial;		//マテリアルの数
	char				*m_pFileName;			//ファイル名
	MODEL_INFO			m_modelInfo;
	MODEL_INFO			m_defaultModelInfo;
public:
	CSceneXFile(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName){m_mesh = NULL;m_texture = NULL;m_bufferMaterial = NULL;m_pos = pos;m_rot = rot;m_pFileName = pFileName;Init();}
	~CSceneXFile(){ Uninit(); };
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static CSceneXFile *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName);
	LPD3DXMESH GetMesh(){ return m_mesh; };
	MODEL_INFO *GetModelInfo(){ return &m_modelInfo; }
	MODEL_INFO *GetDefaultModelInfo(){ return &m_defaultModelInfo; }
};

#endif