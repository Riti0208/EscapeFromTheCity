/****************************************************************************
* タイトル:  DirectX関係の処理
* ファイル名:renderer.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/04/18
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"renderer.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
LPDIRECT3DDEVICE9 CRenderer::m_pD3DDevice;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/*******************************************************************************
* 関数名:HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd)
*
* 引数:  HINSTANCE hInstance, HWND hWnd
* 戻り値:S_OK, E_FAILE
* 説明	DirectX関係の初期化処理
*
*******************************************************************************/
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd){
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);			//Direct3Dオブジェクトの生成
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		return E_FAIL;
	}

	//----------------------------------------------------------------------------------------------
	//D3DPRESENT_PARAMETERS構造体 d3dppの設定
	//----------------------------------------------------------------------------------------------
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;						//画面の幅
	d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;						//画面の高さ
	d3dpp.BackBufferFormat = d3ddm.Format;						//バックバッファの形式
	d3dpp.BackBufferCount = 1;									//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//バッファの切り替え方法の廷費
	d3dpp.EnableAutoDepthStencil = TRUE;						//デプスバッファとステンシルバッファの生成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					//デプスバッファとして16ビットを使用
	d3dpp.Windowed = true;									//ウィンドウモードとスクリーンモードの指定
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//フルスクリーンでのリフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//スワップ(バッファの切り替え)の書き換えタイミング

	//------------------------------------------------------------------------
	//Direct3Dデバイスの生成(描画処理：ハードウェア、頂点処理：ハードウェア)
	//------------------------------------------------------------------------
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,									//描画処理をハードウェアに処理させる
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,			//頂点処理をハードウェアに処理させる
		&d3dpp,
		&m_pD3DDevice))){
		//------------------------------------------------------------------------
		//Direct3Dデバイスの生成(描画処理：ハードウェア、頂点処理：ソフトウェア)
		//------------------------------------------------------------------------
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,								//描画処理をハードウェアに処理させる
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,		//頂点処理をソフトウェアに処理させる
			&d3dpp,
			&m_pD3DDevice))){
			//------------------------------------------------------------------------
			//Direct3Dデバイスの生成(描画処理：ソフトウェア、頂点処理：ソフトウェア)
			//------------------------------------------------------------------------
			if (FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,							//描画処理をソフトウェアに処理させる
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//頂点処理をソフトウェアに処理させる
				&d3dpp,
				&m_pD3DDevice))){
				return E_FAIL;//失敗した場合
			}
		}
	}
	//----------------------------------------------------------------------------------------------
	//レンダーステートの設定
	//----------------------------------------------------------------------------------------------
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//カリングの設定
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//透明化の不可
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//転送元のブレンディング係数の設定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//転送先のブレンディンぐ係数の設定

	//----------------------------------------------------------------------------------------------
	//サンプラーステートの設定
	//----------------------------------------------------------------------------------------------
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);

	//----------------------------------------------------------------------------------------------
	//テクスチャステージステートの設定
	//----------------------------------------------------------------------------------------------

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//----------------------------------------------------------------------------------------------
	//テクスチャステージステートの設定
	//----------------------------------------------------------------------------------------------
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	return S_OK;
}
/*******************************************************************************
* 関数名:void CRenderer::Uninit()
*
* 引数:  void,なし
* 戻り値:void,なし
* 説明 DirectX関係の終了処理
*
*******************************************************************************/
void CRenderer::Uninit(){
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
}
/*******************************************************************************
* 関数名:void CRenderer::Update()
*
* 引数:  void,なし
* 戻り値:void,なし
* 説明 DirectX関係の更新処理
*
*******************************************************************************/
void CRenderer::Update(){
}
void CRenderer::DrawBegin(){
	//背景色を指定してクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(256, 256, 256, 256), 1.0f, 0);
	//描画開始
	m_pD3DDevice->BeginScene();
}
void CRenderer::DrawEnd(){
	//描画終了
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
/*******************************************************************************
* 関数名:void CRenderer::Draw()
*
* 引数:  void,なし
* 戻り値:void,なし
* 説明 DirectX関係の描画処理
*
*******************************************************************************/
void CRenderer::Draw(){
}
/*******************************************************************************
* 関数名:LPDIRECT3DDEVICE9 GetDevice()
*
* 引数:  void,なし
* 戻り値:g_pD3DDevice
* 説明 g_pD3DDeviceのゲッター
*
*******************************************************************************/
LPDIRECT3DDEVICE9 CRenderer::GetDevice(){
	return m_pD3DDevice;//ポインタを渡す
}