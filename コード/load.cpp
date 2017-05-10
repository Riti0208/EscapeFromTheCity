
/****************************************************************************
* タイトル:  ロードの処理
* ファイル名:laod.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/12/8
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"load.h"
#include"debugProc.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:void load::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	loadクラスの初期化処理
*
*******************************************************************************/
void load::Init(){
	//	bg = new CScene2DwL(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, "data/TEXTURE/loadingBG.png", COLOR_WHITE);
	loadStringImage = new CScene2DwL(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, "data/TEXTURE/loadingImage00.png", COLOR_WHITE);
	loadingImage = new CScene2DwLAnimation(D3DXVECTOR3(SCREEN_WIDTH * 0.925f, SCREEN_HEIGHT * 0.875f, 0.0f), SCREEN_WIDTH * 0.1f, SCREEN_WIDTH * 0.1f, "data/TEXTURE/loadingImage.png", COLOR_WHITE, 12, 5);
	loadStringImageAlpha = 0.0f;
}
/*******************************************************************************
* 関数名:void load::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	loadクラスの終了処理
*
*******************************************************************************/
void load::Uninit(){
	//SAFE_DELETE(bg);
	SAFE_DELETE(loadStringImage);
	SAFE_DELETE(loadingImage);
}
/*******************************************************************************
* 関数名:void load::Update()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	loadクラスの更新処理
*
*******************************************************************************/
void load::Update(){
	loadStringImageAlpha += 0.1f;
	if (loadStringImage){
		loadStringImage->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, sinf((loadStringImageAlpha)+1) / 2 + 0.5f));
		loadStringImage->Update();
	}
	if (loadingImage){
		loadingImage->Update();
	}
}
/*******************************************************************************
* 関数名:void load::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	loadクラスの描画処理
*
*******************************************************************************/
void load::Draw(){
//	if (bg != NULL)					bg->Draw();
	if (loadStringImage != NULL)	loadStringImage->Draw();
	if (loadingImage != NULL)		loadingImage->Draw();
}