#include"stensilShadow.h"
stensilShadow::stensilShadow(D3DXVECTOR3 pos){
	m_pos = pos; 
	Init();
}
stensilShadow::~stensilShadow(){
	SAFE_RELEASE(m_bufferPolygon)
}
void stensilShadow::Init(){

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_bufferPolygon,
		NULL
		);

	VERTEX_2D *pVtx;

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//同次座標設定

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点色の設定

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =

		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);


	//UV座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	m_bufferPolygon->Unlock();

	m_modelInfo = CModel::Get("data\\MODEL\\cylinder.x");
	m_mesh = m_modelInfo.m_mesh;
	m_defaultModelInfo = m_modelInfo;
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
void stensilShadow::Uninit(){}
void stensilShadow::Update(){
	VERTEX_2D *pVtx;

	//位置情報の設定

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//頂点色の設定

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =

		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	m_bufferPolygon->Unlock();
}
void stensilShadow::Draw(){
	auto device = CRenderer::GetDevice();
	device->SetTexture(0, NULL);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	device->SetRenderState(D3DRS_STENCILREF, 1);
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	device->SetRenderState(D3DRS_FOGENABLE, false);

	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	D3DXMATRIX	mtxScl, mtxRot, mtxTrans;	//拡縮、回転、移動用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_world);
	//スケールの反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxScl);
	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0, 0, 0);
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

	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//属性グループの数だけDrawSubsetを呼ぶ
	for (unsigned int i = 0; i < (int)m_modelInfo.m_numMaterial; i++) {
		pDevice->SetMaterial(&m_modelInfo.m_mat[i]);
		pDevice->SetTexture(0, CTexture::Get(m_modelInfo.m_textureName[i]));
		m_modelInfo.m_mesh->DrawSubset(i);
	}

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);

	device->SetStreamSource(0, m_bufferPolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	device->SetTexture(0, CTexture::Get(""));

	//ポリゴンの描画
	device->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);

	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	float FogStart = 900.0f, FogEnd = 3000.0f;

	device->SetRenderState(D3DRS_FOGENABLE, TRUE); // フォグ有効
	device->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f)); // フォグ色
	device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR); // バーテックスフォグ
	device->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE); // 範囲ベースのフォグ
	device->SetRenderState(D3DRS_FOGSTART, *((DWORD*)(&FogStart))); // フォグ開始点
	device->SetRenderState(D3DRS_FOGEND, *((DWORD*)(&FogEnd))); // フォグ終了点
}
stensilShadow *Create(D3DXVECTOR3 pos){
	stensilShadow *scene;
	scene = new stensilShadow(pos); 
	return scene;
}