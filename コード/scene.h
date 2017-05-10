/****************************************************************************
* タイトル:  sceneヘッダー
* ファイル名:scene.h
* 作成者：	 芳崎大地
* 作成日：   2016/04/19
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _SCENE_H_
#define _SCENE_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"renderer.h"
#include<list>
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
class CScene{
protected:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scl;
	D3DXMATRIX	m_world;
	D3DXCOLOR	m_col;
	bool m_bDraw;
	int			m_nPriority;
	std::list<CScene*>::iterator m_curItr;
	bool m_bDelete;
	std::string name;
private:
	static bool isFog;
public:
	static std::list<CScene*> sceneList;

	static void SetFog(bool tf){ isFog = tf; };

	static CScene *CScene::Find(std::string string);

	CScene();
	CScene(std::string);
	~CScene(){};

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void UpdateAll();
	static void DrawAll();
	static void ReleaseAll();
	void Release();

	void SetPos(float x, float y, float z){
		m_pos.x = x;
		m_pos.y = y;
		m_pos.z = z;
	}
	void SetPosY(float y){
		m_pos.y = y;
	}
	void SetPos(D3DXVECTOR3 pos){
		m_pos = pos;
	}
	void SetRot(float x, float y, float z)
		{
		m_rot.x = x;
		m_rot.y = y;
		m_rot.z = z;
	}
	void SetRot(D3DXVECTOR3 rot){
		m_rot = rot;
	}
	void SetCanDraw(bool bDraw){
		m_bDraw = bDraw;
	}
	void SetScl(float x, float y, float z)
	{
		m_scl.x = x;
		m_scl.y = y;
		m_scl.z = z;
	}
	void SetScl(D3DXVECTOR3 scl){
		m_scl = scl;
	}
	void SetCol(D3DXCOLOR col){
		m_col = col;
	}
	D3DXCOLOR GetCol(){
		return m_col;
	}
	D3DXVECTOR3 *GetPos(){
		return &m_pos;
	}
	D3DXVECTOR3 *GetRot(){
		return &m_rot;
	}
	D3DXVECTOR3 *GetScl(){
		return &m_scl;
	}
	bool GetCanDraw(){
		return m_bDraw;
	}
};
#endif