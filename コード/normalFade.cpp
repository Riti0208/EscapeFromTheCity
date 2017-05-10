/****************************************************************************
* タイトル:  フェードの処理
* ファイル名:fade.cpp
* 作成者：	 芳崎大地
* 作成日：   2015/07/06
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"fade.h"
#include"normalFade.h"
#include"mode.h"
#include"input.h"
#include"debugProc.h"
#include"scene2D.h"
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:CNormalFade::CNormalFade()
*
* 引数:  なし
* 戻り値:なし
* 説明 ノーマルフェードのコンストラクタ
*
*******************************************************************************/
CNormalFade::CNormalFade(){
}
/*******************************************************************************
* 関数名:CNormalFade::CNormalFade()
*
* 引数:  なし
* 戻り値:なし
* 説明 ノーマルフェードのデストラクタ
*
*******************************************************************************/
CNormalFade::~CNormalFade(){
	Uninit();
}
/*******************************************************************************
* 関数名:void CNormalFade::Init()
*
* 引数:  なし
* 戻り値:なし
* 説明 ノーマルフェードの初期化処理
*
*******************************************************************************/
void CNormalFade::Init(){
	m_currentFadeState = FADE_OUT;
	m_nVertexNum = 4;
	m_bFinish = false;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_buffer,
			NULL
			);

		VERTEX_2D *pVtx;

		m_buffer->Lock(0, 0, (void **)&pVtx, 0);

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
			pVtx[3].col = m_col;

		//UV座標の設定

		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

		m_buffer->Unlock();
	}
/*******************************************************************************
* 関数名:void CNormalFade::Uninit()
*
* 引数:  なし
* 戻り値:なし
* 説明 ノーマルフェードの終了処理
*
*******************************************************************************/
void CNormalFade::Uninit(){
}
/*******************************************************************************
* 関数名:void CNormalFade::Update()
*
* 引数:  なし
* 戻り値:なし
* 説明 ノーマルフェードの更新処理
*
*******************************************************************************/
void CNormalFade::Update(){
	m_col;
	if (m_currentFadeState == FADE_OUT){
		m_col.a += 0.1f * m_fFadeSpeed;
		if (m_col.a >= 1.0f){
			m_col.a = 1.0f;
			m_currentFadeState = FADE_IN;
			m_bChangeMode = true;
		}
	}
	else if (m_currentFadeState == FADE_IN){
		m_bChangeMode = false;
		m_col.a -= 0.1f * m_fFadeSpeed;
		if (m_col.a <= 0.0f){
			m_col.a = 0.0f;
			m_bFinish = true;
		}
	}

	VERTEX_2D *pVtx;

	m_buffer->Lock(0, 0, (void **)&pVtx, 0);

	//頂点色の設定

	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_col;

	m_buffer->Unlock();

}
/*******************************************************************************
* 関数名:void CNormalFade::Draw()
*
* 引数:  なし
* 戻り値:なし
* 説明 ノーマルフェードの描画処理
*
*******************************************************************************/
void CNormalFade::Draw(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->SetStreamSource(0, m_buffer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTexture::Get(""));

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);
}