/****************************************************************************
* タイトル:  2Dポリゴン関係の処理
* ファイル名:scene.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/04/19
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"sceneXFile.h"
#include"model.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:void CScene::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの初期化処理
*
*******************************************************************************/
void CSceneXFile::Init(){
	m_modelInfo = CModel::Get(m_pFileName);
	m_mesh = m_modelInfo.m_mesh;
	m_defaultModelInfo = m_modelInfo;
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
/*******************************************************************************
* 関数名:void CScene::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの終了処理
*
*******************************************************************************/
void CSceneXFile::Uninit(){
}
/*******************************************************************************
* 関数名:void CScene::Update()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの更新処理
*
*******************************************************************************/
void CSceneXFile::Update(){
}
/*******************************************************************************
* 関数名:void CScene::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの描画処理
*
*******************************************************************************/
void CSceneXFile::Draw(){
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	D3DXMATRIX	mtxScl, mtxRot, mtxTrans;	//拡縮、回転、移動用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_world);
	//スケールの反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxScl);
	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxTrans);
	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &m_world);

	//属性グループの数だけDrawSubsetを呼ぶ
	for (unsigned int i = 0; i < (int)m_modelInfo.m_numMaterial; i++) {
		pDevice->SetMaterial(&m_modelInfo.m_mat[i]);
		pDevice->SetTexture(0, CTexture::Get(m_modelInfo.m_textureName[i]));
		m_modelInfo.m_mesh->DrawSubset(i);
	}
}
CSceneXFile *CSceneXFile::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName){
	CSceneXFile *scene;
	scene = new CSceneXFile(pos, rot, pFileName);
	return scene;
}