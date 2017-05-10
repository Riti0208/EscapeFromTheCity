/****************************************************************************
* タイトル:  シーンの処理
* ファイル名:scene.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/05/16
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"scene.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
std::list<CScene*> CScene::sceneList;
bool			   CScene::isFog;
/*******************************************************************************
* 関数名:CScene::CScene()
*
* 引数:		なし
* 戻り値:	なし
* 説明		sceneのコンストラクタ
*
*******************************************************************************/
CScene::CScene(){
	m_bDelete = false;
	m_bDraw = true;
	m_curItr = sceneList.end();
	sceneList.push_back(this);
	name = "";
}
CScene::CScene(std::string  _name = ""){

	m_bDelete = false;
	m_bDraw = true;
	m_curItr = sceneList.end();
	sceneList.push_back(this);
	name = _name;
}
/*******************************************************************************
* 関数名:void CScene::UpdateAll();
*
* 引数:	なし
* 戻り値:	なし
* 説明		sceneの更新処理
*
*******************************************************************************/
void CScene::UpdateAll(){
	std::for_each(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		scene->Update();
	});
	
	auto iter = std::find_if(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		return scene->m_bDelete;
	});
	if (iter != sceneList.end()){
		delete *iter;
		sceneList.erase(iter);
	}

}
/*******************************************************************************
* 関数名:void CScene::DrawAll();
*
* 引数:		なし
* 戻り値:	なし
* 説明		sceneの描画処理
*
*******************************************************************************/
void CScene::DrawAll(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (isFog){
		float FogStart = 900.0f, FogEnd = 3000.0f;

		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); // フォグ有効
		pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f)); // フォグ色
		pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR); // バーテックスフォグ
		pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE); // 範囲ベースのフォグ
		pDevice->SetRenderState(D3DRS_FOGSTART, *((DWORD*)(&FogStart))); // フォグ開始点
		pDevice->SetRenderState(D3DRS_FOGEND, *((DWORD*)(&FogEnd))); // フォグ終了点
	}
	std::for_each(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		if (scene->m_bDraw)	scene->Draw();
	});
	if (isFog){
		pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	}
}
/*******************************************************************************
* 関数名:void CScene::ReleaseAll();
*
* 引数:		なし
* 戻り値:	なし
* 説明		sceneの全体削除
*
*******************************************************************************/
void CScene::ReleaseAll(){
	std::for_each(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		SAFE_DELETE(scene);
		scene = NULL;
	});
	sceneList.erase(sceneList.begin(), sceneList.end());
}
/*******************************************************************************
* 関数名:void CScene::Release();
*
* 引数:		なし
* 戻り値:	なし
* 説明		sceneの単体削除
*
*******************************************************************************/
void CScene::Release(){
	m_bDelete = true;
}
CScene *CScene::Find(std::string string){
	auto scene = std::find_if(sceneList.begin(), sceneList.end(), [=](CScene *scene){
		if (string == scene->name)	return true;
		return false;
	});
	if (scene != sceneList.end())
	return *scene;
	return NULL;
}
static void SetFog(){
}