/****************************************************************************
* タイトル:  Billboardポリゴン関係の処理
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
#include"sceneBillboard.h"
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
void CSceneBillboard::Init(){
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	m_rot.z = 0.0f;

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_bufferPolygon,
		NULL
		);

	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	VERTEX_3D *pVtx;

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);

	//ポジションの設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth * 0.5f, m_fHeight * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth * 0.5f, m_fHeight * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth * 0.5f, -m_fHeight * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth * 0.5f, -m_fHeight * 0.5f, 0.0f);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//カラー設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

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
void CSceneBillboard::Uninit(){
	SAFE_RELEASE(m_bufferPolygon)
}
/*******************************************************************************
* 関数名:void CScene::Update()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの更新処理
*
*******************************************************************************/
void CSceneBillboard::Update(){
}
/*******************************************************************************
* 関数名:void CScene::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの描画処理
*
*******************************************************************************/
void CSceneBillboard::Draw(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//ワールドマトリックスの初期化
	D3DXMATRIX	mtxView;

	D3DXMatrixIdentity(&m_world);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	D3DXMatrixInverse(&m_world, NULL, &mtxView);

	m_world._41 = 0.0f;
	m_world._42 = 0.0f;
	m_world._43 = 0.0f;
	m_world._44 = 1.0f;

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
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

}
CSceneBillboard *CSceneBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col){
	CSceneBillboard *scene;
	scene = new CSceneBillboard(pos, rot, fWidth, fHeight, pFileName, col);
	return scene;
}