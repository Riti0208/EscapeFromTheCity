/****************************************************************************
* タイトル:  GUIの処理
* ファイル名:guiString.cpp
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
#include"guiString.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:CGuiString::CGuiString(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName)
*
* 引数: D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName
* 戻り値:	なし
* 説明	guiStringクラスのコンストラクタ
*
*******************************************************************************/
CGuiString::CGuiString(D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, char *pFileName, D3DXCOLOR col){
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_nFontSize = nFontSize;
	m_string = string;
	m_col = col;
	m_pFileName = pFileName;
	Init();
}
/*******************************************************************************
* 関数名:void CGuiString::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	guiStringクラスの初期化処理
*
*******************************************************************************/
void CGuiString::Init(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	m_pFont = NULL;
	D3DXCreateFont(pDevice,		//D3Dデバイスのポインタ
		m_nFontSize,						//文字の高さ
		0,						//文字の幅
		3,						//フォントの太さ
		3,						//ミップマップのレベルの数
		FALSE,					//イタリックフォントの場合はtrue,それ以外はfalse
		SHIFTJIS_CHARSET,		//フォントの文字セット
		OUT_DEFAULT_PRECIS,		//Windows での、実際のフォントと目的のフォントのサイズおよび特性の一致方法を指定します(よくわからない)
		DEFAULT_QUALITY,		//Windows での、実際のフォントと目的のフォントとの一致方法を指定します(よくわからない)
		DEFAULT_PITCH,			//ピッチとファミリインデックス
		"Consolas",				//フォントの名前を保持する文字列
		&m_pFont);

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

	pVtx[0].col = COLOR_GRAY;
	pVtx[1].col = COLOR_GRAY;
	pVtx[2].col = COLOR_GRAY;
	pVtx[3].col = COLOR_GRAY;

	//UV座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	m_bufferPolygon->Unlock();
}
/*******************************************************************************
* 関数名:void CGuiString::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	guiStringクラスの終了処理
*
*******************************************************************************/
void CGuiString::Uninit(){
	if (m_pFont != NULL){
		m_pFont->Release();
		m_pFont = NULL;
	}
	if (m_bufferPolygon != NULL){
		m_bufferPolygon->Release();		//解放
		m_bufferPolygon = NULL;
	}
}
/*******************************************************************************
* 関数名:void CGuiString::Update()
*WW
* 引数:  void、なし
* 戻り値:void、なし
* 説明	guiStringクラスの更新処理
*
*******************************************************************************/
void CGuiString::Update(){
}
/*******************************************************************************
* 関数名:void CGuiString::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	guiStringクラスの描画処理
*
*******************************************************************************/
void CGuiString::Draw(){
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

	RECT rect = { (LONG)(m_pos.x - m_fWidth * 0.5f), (LONG)(m_pos.y - m_fHeight * 0.5f), (LONG)(m_pos.x + m_fWidth * 0.5f), (LONG)(m_pos.y + m_fHeight * 0.5f) };
	m_pFont->DrawText(NULL,	// 描画スプライト描画先
		m_string.c_str(),	// 描画するテキスト	
		-1,					// テキストの長さ、－１ならば自動で数値が合わされる
		&rect,				// テキストを描画する長方形領域
		DT_CENTER,			// テキスト描画オプション
		m_col				// 文字カラー
		);
}
/*******************************************************************************
* 関数名:CGuiString *CGuiString::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, D3DXCOLOR col)
*
* 引数:  D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, D3DXCOLOR col
* 戻り値:	CGuiString *
* 説明	guiStringクラスの生成処理
*
*******************************************************************************/
CGuiString *CGuiString::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, char *pFileName, D3DXCOLOR col){
	CGuiString *scene;
	scene = new CGuiString(pos, fWidth, fHeight,nFontSize, string, pFileName, col);
	return scene;
}
