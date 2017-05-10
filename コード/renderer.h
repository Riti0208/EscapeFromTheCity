/****************************************************************************
* タイトル:  rendererヘッダー
* ファイル名:rendere.h
* 作成者：	 芳崎大地
* 作成日：   2016/04/18
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _RENDERER_H_
#define _RENDERER_H_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "xaudio2.h"
#include "d3dx9.h"//描画処理用
#include "texture.h"
/*******************************************************************************
* ライブラリのリンク
*******************************************************************************/
#pragma comment(lib, "d3d9.lib")//描画処理に必要
#pragma comment(lib, "d3dx9.lib")//上記の拡張ライブラリ
#pragma comment(lib, "dxguid.lib")//DirectXコンポーネント使用時に必要
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D_TEX2	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2)
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
typedef struct{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;
typedef struct{
	D3DXVECTOR3 pos;//頂点座標
	D3DXVECTOR3 nor;//法線座標
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
	D3DXVECTOR2 tex2;//テクスチャ座標
}VERTEX_3D_TEX2;
typedef struct {
	D3DXVECTOR3 pos;//頂点座標
	D3DXVECTOR3 nor;//法線座標
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_3D;
/*******************************************************************************
* クラスの定義
*******************************************************************************/
class CScene;
//レンダラークラス
class CRenderer{
public:
	CRenderer(){};
	~CRenderer(){};										//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化
	void	Uninit();									//終了
	void	Update();									//更新
	void	Draw();										//描画
	static	LPDIRECT3DDEVICE9		GetDevice();		//デバイスの取得
	void							DrawBegin();
	void							DrawEnd();
private:
	LPDIRECT3D9						m_pD3D;				//Direct3Dオブジェクトへのポインタ
	static	LPDIRECT3DDEVICE9		m_pD3DDevice;		//Direct3Dデバイスへのポインタ
	void							RecoverDevice(IDirect3DDevice9 *g_pD3DDev, D3DPRESENT_PARAMETERS &d3dpp);
};
#endif