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
#include"scene3D.h"
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
void CScene3D::Init(){
	m_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_sclMeshField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);;
	m_nFieldNumX = 10;
	m_nFieldNumZ = 10;
	m_fFieldSizeX = 1500.0f;
	m_fFieldSizeZ = 1500.0f;
	m_posMeshField.x -= 1500;
	m_posMeshField.z -= 1500;

	m_pVtxBufferMeshField = NULL;

	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	m_sclMeshField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_nIdxMeshFieldNum = (m_nFieldNumX * 2 + 2) * m_nFieldNumZ + (m_nFieldNumZ - 1) * 2;

	m_nMeshFieldPolygonNum = m_nIdxMeshFieldNum - 2;

	m_nMeshFieldVerTexNum = (m_nFieldNumX + 1) * (m_nFieldNumZ + 1);

	m_fBlockSizeX = m_fFieldSizeX / m_nFieldNumX;
	m_fBlockSizeZ = m_fFieldSizeZ / m_nFieldNumZ;

	//頂点バッファーの作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nMeshFieldVerTexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBufferMeshField,
		NULL
		);
	//インデックスバッファの作成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nIdxMeshFieldNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndexBufferField,
		NULL
		);

	//インデックス情報の設定
	WORD *pIdx;
	m_pIndexBufferField->Lock(0, 0, (void**)&pIdx, 0);

	// インデックス座標設定
	int nX = 0, nY = 0;
	int nIdx = 0;
	while (nIdx < m_nIdxMeshFieldNum){
		while (nIdx < (nY + 1) * (m_nFieldNumX * 2 + 4) - 2){
			if (nIdx % 2 == 0){
				pIdx[nIdx] = (m_nFieldNumX + 1) * (nY + 1) + nX;
			}
			else{
				pIdx[nIdx] = (m_nFieldNumX + 1) * nY + nX;
				nX++;
			}
			nIdx++;
		}
		nY++;
		nX = 0;
		nIdx += 2;
	}

	nIdx = m_nFieldNumX * 2 + 2;

	for (nY = 0; nY < m_nFieldNumZ - 1; nY++){
		pIdx[nIdx] = pIdx[nIdx - 1];
		pIdx[nIdx + 1] = pIdx[nIdx + 2];
		nIdx += m_nFieldNumX * 2 + 4;
	}

	m_pIndexBufferField->Unlock();

	//頂点情報の設定
	VERTEX_3D *pVtx;
	m_pVtxBufferMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].pos = D3DXVECTOR3((m_fFieldSizeX - (m_fBlockSizeX * m_nFieldNumX / 2)) + m_fBlockSizeX * (nCnt % (m_nFieldNumX + 1)), 0.0f, (m_fFieldSizeZ + (m_fBlockSizeZ * m_nFieldNumZ / 2)) - m_fBlockSizeZ * (nCnt / (m_nFieldNumX + 1)));
	}
	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].col = m_col;
	}

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].tex = D3DXVECTOR2((float)(nCnt % (m_nFieldNumX + 1)), (float)(nCnt / (m_nFieldNumX + 1)));
	}

	m_pIndexBufferField->Unlock();

}
/*******************************************************************************
* 関数名:void CScene::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの終了処理
*
*******************************************************************************/
void CScene3D::Uninit(){
	if (m_pVtxBufferMeshField != NULL){
		m_pVtxBufferMeshField->Release();
		m_pVtxBufferMeshField = NULL;
	}
	if (m_pIndexBufferField != NULL){
		m_pIndexBufferField->Release();
		m_pIndexBufferField = NULL;
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
void CScene3D::Update(){
}
/*******************************************************************************
* 関数名:void CScene::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの描画処理
*
*******************************************************************************/
void CScene3D::Draw(){
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_world);
	//スケールの反映
	D3DXMatrixScaling(&mtxScl, m_sclMeshField.x, m_sclMeshField.y, m_sclMeshField.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxScl);
	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotMeshField.y, m_rotMeshField.x, m_rotMeshField.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_posMeshField.x, m_posMeshField.y, m_posMeshField.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxTrans);
	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &m_world);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetStreamSource(0, m_pVtxBufferMeshField, 0, sizeof(VERTEX_3D));

	//テクスチャの設定
	pDevice->SetTexture(0, CTexture::Get(m_pFileName));

	//インデックスバッファをバインド
	pDevice->SetIndices(m_pIndexBufferField);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMeshFieldVerTexNum, 0, m_nMeshFieldPolygonNum);
}
/*******************************************************************************
* 関数名:CScene3D Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col)
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	CScene3Dクラスの生成処理
*
*******************************************************************************/
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col){
	CScene3D *scene;
	scene = new CScene3D(pos, rot, pFileName, col);
	return scene;
}
