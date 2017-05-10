/****************************************************************************
* タイトル:  Rectポリゴン関係の処理
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
#include"sceneRect.h"
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
void CSceneRect::Init(){
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_bufferPolygon,
		NULL
		);

	VERTEX_3D *pVtx;

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, 0.0f);

	//頂点色の設定

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//UV座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_bufferPolygon->Unlock();
}
/*******************************************************************************
* 関数名:void CScene::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの終了処理
*
*******************************************************************************/
void CSceneRect::Uninit(){
	if (m_bufferPolygon != NULL){
		m_bufferPolygon->Release();		//解放
		m_bufferPolygon = NULL;
	}
}
/*******************************************************************************
* 関数名:void CScene::Update()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの更新処理
*
*******************************************************************************/
void CSceneRect::Update(){
}
/*******************************************************************************
* 関数名:void CScene::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの描画処理
*
*******************************************************************************/
void CSceneRect::Draw(){

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;


	//ワールドマトリックスの初期化
	D3DXMATRIX	mtxView;

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

	pDevice->SetStreamSource(0, m_bufferPolygon, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTexture::Get(m_pFileName));

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);

}
/*******************************************************************************
* 関数名:CSceneRect *CSceneRect::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col)
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの描画処理
*
*******************************************************************************/
CSceneRect *CSceneRect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col){
	CSceneRect *scene;
	scene = new CSceneRect(pos, rot, scl, fWidth, fHeight, pFileName, col);
	return scene;
}