/****************************************************************************
* タイトル:  GUIの処理
* ファイル名:number.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/05/13
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"manager.h"
#include"number.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
*関数名:CNumber::CNumber(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber){
*
* 引数 : D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName
* 戻り値 : なし
* 説明	numberクラスのコンストラクタ
*
*******************************************************************************/
CNumber::CNumber(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber){
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_pFileName = pFileName;
	m_nNum = nNumber;
	Init();
}
/*******************************************************************************
* 関数名:void CNumber::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	numberクラスの初期化処理
*
*******************************************************************************/
void CNumber::Init(){
	//デバイスのポインタを持ってくる
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
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//UV座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	m_bufferPolygon->Unlock();

}
/*******************************************************************************
* 関数名:void CNumber::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	numberクラスの終了処理
*
*******************************************************************************/
void CNumber::Uninit(){
}
/*******************************************************************************
* 関数名:void CNumber::Update()
*WW
* 引数:  void、なし
* 戻り値:void、なし
* 説明	numberクラスの更新処理
*
*******************************************************************************/
void CNumber::Update(){

	VERTEX_2D *pVtx;

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);
	//UV座標の設定

	pVtx[0].tex = D3DXVECTOR2(m_nNum * 0.1f, 0.0);
	pVtx[1].tex = D3DXVECTOR2(0.1f + m_nNum * 0.1f, 0.0);
	pVtx[2].tex = D3DXVECTOR2(m_nNum * 0.1f, 1.0);
	pVtx[3].tex = D3DXVECTOR2(0.1f + m_nNum * 0.1f, 1.0);

	m_bufferPolygon->Unlock();
}
/*******************************************************************************
* 関数名:void CNumber::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	numberクラスの描画処理
*
*******************************************************************************/
void CNumber::Draw(){
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->SetStreamSource(0, m_bufferPolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

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
* 関数名:CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nLineNum)
*
* 引数: D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nLineNum
* 戻り値:	*CNumber型
* 説明	numberクラスの描画処理
*
*******************************************************************************/
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber){
	CNumber *scene;
	scene = new CNumber(pos, fWidth, fHeight, pFileName, nNumber);
	return scene;
}
