/****************************************************************************
* タイトル:  空の処理
* ファイル名:Sky.cpp
* 作成者：	 芳崎大地
* 作成日：   2015/10/26
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"sky.h"
#include"camera.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* 構造体の定義
*******************************************************************************/

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************//*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:void InitSky()
*
* 引数:  なし
* 戻り値:なし
* 説明 空の初期化処理
*
*******************************************************************************/
void CSky::Init(){
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 24,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_bufferPolygon,
		NULL
		);

	VERTEX_3D *pVtx;

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-6000.0f, -6000.0f, 6000.0f);
	pVtx[1].pos = D3DXVECTOR3(6000.0f, -6000.0f,  6000.0f);
	pVtx[2].pos = D3DXVECTOR3(-6000.0f, -6000.0f, -6000.0f);
	pVtx[3].pos = D3DXVECTOR3(6000.0f, -6000.0f,  -6000.0f);

	pVtx[4].pos = D3DXVECTOR3(-6000.0f, 6000.0f, -6000.0f);
	pVtx[5].pos = D3DXVECTOR3(6000.0f, 6000.0f, -6000.0f);
	pVtx[6].pos = D3DXVECTOR3(-6000.0f, 6000.0f, 6000.0f);
	pVtx[7].pos = D3DXVECTOR3(6000.0f, 6000.0f, 6000.0f);

		
	pVtx[8].pos = D3DXVECTOR3(-6000.0f, 6000.0f, -6000.0f);
	pVtx[9].pos = D3DXVECTOR3(-6000.0f, 6000.0f, 6000.0f);
	pVtx[10].pos = D3DXVECTOR3(-6000.0f, -6000.0f, -6000.0f);
	pVtx[11].pos = D3DXVECTOR3(-6000.0f, -600000.0, 6000.0f);

	pVtx[12].pos = D3DXVECTOR3(6000.0f, 6000.0f, 6000.0f);
	pVtx[13].pos = D3DXVECTOR3(6000.0f, 6000.0f, -6000.0f);
	pVtx[14].pos = D3DXVECTOR3(6000.0f, -6000.0f, 6000.0f);
	pVtx[15].pos = D3DXVECTOR3(6000.0f, -6000.0f, -6000.0f);


	pVtx[16].pos = D3DXVECTOR3(-6000.0f, 6000.0f, 6000.0f);
	pVtx[17].pos = D3DXVECTOR3(6000.0f, 6000.0f, 6000.0f);
	pVtx[18].pos = D3DXVECTOR3(-6000.0f, -6000.0f, 6000.0f);
	pVtx[19].pos = D3DXVECTOR3(6000.0f, -6000.0f, 6000.0f);

	pVtx[20].pos = D3DXVECTOR3(6000.0f, 6000.0f, -6000.0f);
	pVtx[21].pos = D3DXVECTOR3(-6000.0f, 6000.0f, -6000.0f);
	pVtx[22].pos = D3DXVECTOR3(6000.0f, -6000.0f, -6000.0f);
	pVtx[23].pos = D3DXVECTOR3(-6000.0f, -6000.0f, -6000.0f);

	//頂点色の設定

	pVtx[0].col = COLOR_WHITE;
	pVtx[1].col = COLOR_WHITE;
	pVtx[2].col = COLOR_WHITE;
	pVtx[3].col = COLOR_WHITE;

	//UV座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.52f, 0.66f);
	pVtx[1].tex = D3DXVECTOR2(0.73f, 0.66f);
	pVtx[2].tex = D3DXVECTOR2(0.52f, 0.9f);
	pVtx[3].tex = D3DXVECTOR2(0.73f, 0.9f);

	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.1f);
	pVtx[5].tex = D3DXVECTOR2(0.75f, 0.1f);
	pVtx[6].tex = D3DXVECTOR2(0.5f, 0.33f);
	pVtx[7].tex = D3DXVECTOR2(0.75f, 0.33f);

	pVtx[8].tex = D3DXVECTOR2(0.25f, 0.34f);
	pVtx[9].tex = D3DXVECTOR2(0.5f, 0.34f);
	pVtx[10].tex = D3DXVECTOR2(0.25f, 0.66f);
	pVtx[11].tex = D3DXVECTOR2(0.5f,0.66f);

	pVtx[12].tex = D3DXVECTOR2(0.75f, 0.34f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.34f);
	pVtx[14].tex = D3DXVECTOR2(0.75f, 0.66f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 0.66f);

	pVtx[16].tex = D3DXVECTOR2(0.5f, 0.34f);
	pVtx[17].tex = D3DXVECTOR2(0.75f, 0.34f);
	pVtx[18].tex = D3DXVECTOR2(0.5f, 0.66f);
	pVtx[19].tex = D3DXVECTOR2(0.75f, 0.66f);

	pVtx[20].tex = D3DXVECTOR2(0.0f, 0.34f);
	pVtx[21].tex = D3DXVECTOR2(0.25f, 0.34f);
	pVtx[22].tex = D3DXVECTOR2(0.0f, 0.66f);
	pVtx[23].tex = D3DXVECTOR2(0.25f, 0.66f);

	for (int i = 0; i < 24; i++){
		//カラー設定
		pVtx[i].col = COLOR_WHITE;
		//法線設定
		pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_bufferPolygon->Unlock();

}
/*******************************************************************************
* 関数名:void UninitSky()
*
* 引数:  なし
* 戻り値:なし
* 説明 空の終了処理
*
*******************************************************************************/
void CSky::Uninit(){
	SAFE_RELEASE(m_bufferPolygon)
}
/*******************************************************************************
* 関数名:void UpdateSky()
*
* 引数:  なし
* 戻り値:なし
* 説明 空の更新処理
*
*******************************************************************************/
void CSky::Update(){
	m_pos = CCamera::GetPosEye();
}
/*******************************************************************************
* 関数名:void DrawSky()
*
* 引数:  なし
* 戻り値:なし
* 説明 空の描画処理
*
*******************************************************************************/
void CSky::Draw(){

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING,false);

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMATRIX	mtxView;

	D3DXMatrixIdentity(&m_world);

	//スケールの反映
	D3DXMatrixScaling(&mtxScl, 0.5f, 0.5f, 0.5f);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxScl);
	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
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
	pDevice->SetTexture(0, CTexture::Get("data\\TEXTURE\\sky.png"));
	for (int i = 0; i < 6; i++){
		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,
			i * 4,
			2
			);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
/*******************************************************************************
* 関数名:CSky *CSky::Create()
*
* 引数:  なし
* 戻り値:なし
* 説明 空の作成
*
*******************************************************************************/
CSky *CSky::Create(){
	CSky *scene;
	scene = new CSky;
	return scene;
}