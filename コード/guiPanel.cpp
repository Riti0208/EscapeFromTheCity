/****************************************************************************
* タイトル:  GUIの処理
* ファイル名:guiPanel.cpp
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
#include"guiPanel.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:CGuiPanel::CGuiPanel(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName)
*
* 引数: D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName
* 戻り値:	なし
* 説明	guiPanelクラスのコンストラクタ
*
*******************************************************************************/
CGuiPanel::CGuiPanel(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col){
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_col = col;
	m_pFileName = pFileName;
	Init();
}
/*******************************************************************************
* 関数名:void CGuiPanel::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	guiPanelクラスの初期化処理
*
*******************************************************************************/
void CGuiPanel::Init(){
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

	m_bufferPolygon->Unlock();
}
/*******************************************************************************
* 関数名:void CGuiPanel::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	guiPanelクラスの終了処理
*
*******************************************************************************/
void CGuiPanel::Uninit(){
	SAFE_RELEASE(m_bufferPolygon)
}
/*******************************************************************************
* 関数名:void CGuiPanel::Update()
*WW
* 引数:  void、なし
* 戻り値:void、なし
* 説明	guiPanelクラスの更新処理
*
*******************************************************************************/
void CGuiPanel::Update(){
}
/*******************************************************************************
* 関数名:void CGuiPanel::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	guiPanelクラスの描画処理
*
*******************************************************************************/
void CGuiPanel::Draw(){
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
* 関数名:CGuiPanel *CGuiPanel::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, D3DXCOLOR col)
*
* 引数:  D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, D3DXCOLOR col
* 戻り値:	CGuiPanel *
* 説明	guiPanelクラスの生成処理
*
*******************************************************************************/
CGuiPanel *CGuiPanel::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char* fileName, D3DXCOLOR col){
	CGuiPanel *scene;
	scene = new CGuiPanel(pos, fWidth, fHeight, fileName, col);
	return scene;
}
