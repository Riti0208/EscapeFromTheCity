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
#include"scene2DwLAnimation.h"
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
void CScene2DwLAnimation::Init(){
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

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth / 2, m_pos.y - m_fHeight / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth / 2, m_pos.y - m_fHeight / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth / 2, m_pos.y + m_fHeight / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth / 2, m_pos.y + m_fHeight / 2, 0.0f);

	//同次座標設定

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点色の設定

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_col;

	//UV座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,					//デバイス
		m_pFileName,			//ファイル名
		&m_pTexture					//テクスチャのポインタ
		);

	m_bufferPolygon->Unlock();

	m_currentAnimtionFrame = 0;

	m_currentAnimtionSpriteCnt = 0;
}
/*******************************************************************************
* 関数名:void CScene::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの終了処理
*
*******************************************************************************/
void CScene2DwLAnimation::Uninit(){
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
void CScene2DwLAnimation::Update(){

	VERTEX_2D *pVtx;



	if (m_currentAnimtionSpriteCnt > m_animationChangeFrame){
		m_currentAnimtionSpriteCnt = 0;
		m_currentAnimtionFrame++;
	}

	m_currentAnimtionSpriteCnt++;

	//位置情報の設定

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth / 2, m_pos.y - m_fHeight / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth / 2, m_pos.y - m_fHeight / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth / 2, m_pos.y + m_fHeight / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth / 2, m_pos.y + m_fHeight / 2, 0.0f);

	//頂点色の設定

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =

		pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(1.0f / m_animationNum * m_currentAnimtionFrame, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / m_animationNum * (m_currentAnimtionFrame + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / m_animationNum * m_currentAnimtionFrame, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / m_animationNum * (m_currentAnimtionFrame + 1), 1.0f);

	m_bufferPolygon->Unlock();

}
/*******************************************************************************
* 関数名:void CScene::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	sceneクラスの描画処理
*
*******************************************************************************/
void CScene2DwLAnimation::Draw(){
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->SetStreamSource(0, m_bufferPolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);
}