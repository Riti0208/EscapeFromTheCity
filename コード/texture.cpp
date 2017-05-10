/****************************************************************************
* タイトル:  テクスチャ管理クラスの処理
* ファイル名:texture.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/04/11
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/

#define _NOT_CPP14_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/

#include"texture.h"
#ifndef _NOT_CPP14_
#include <filesystem>
#endif
#ifndef _CPP14_
#include<stdexcept>
#endif
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* 構造体の定義
*******************************************************************************/
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
std::vector<std::string> get_file_path_in_dir(const std::string& dir_name);
/*******************************************************************************
* グローバル変数
*******************************************************************************/
std::vector<LPDIRECT3DTEXTURE9> CTexture::vecTexture;
std::vector<std::string>		CTexture::textureName;
int								CTexture::textureCnt;
/*******************************************************************************
* 関数名:HRESULT CTexture::Create()
*
* 引数:  なし
* 戻り値:なし
* 説明	指定ディレクトリにある全ての画像からテクスチャの一括生成
*
*******************************************************************************/
HRESULT CTexture::Create(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	LPDIRECT3DTEXTURE9 texture;

	std::vector<std::string> file_list = get_file_path_in_dir("data/TEXTURE");

#ifndef _NOT_CPP14_

	// カレントディレクトリ以下のファイル名を取得する
	// 再帰的にファイル名を取得する場合は、std::tr2::sys::recursive_directory_iteratorを使う
	for (std::tr2::sys::directory_iterator it("data/TEXTURE"), end; it != end; ++it) {
		file_list.push_back(it->path());
	}
#endif

	for (auto itr = file_list.begin(); itr != file_list.end(); ++itr) {
		std::string fileName = *itr;

		fileName = "data\\TEXTURE\\" + fileName;

		//テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice,					//デバイス
			fileName.c_str(),			//ファイル名
			&texture					//テクスチャのポインタ
			))){
			return E_FAIL;
		}

		vecTexture.push_back(texture);
		textureName.push_back(fileName);

		texture = NULL;
		fileName = "";
	}

	return S_OK;
}
/*******************************************************************************
* 関数名:LPDIRECT3DTEXTURE9 CTexture::Get(std::string fileName)
*
* 引数:  なし
* 戻り値:なし
* 説明	テクスチャの取得
*
*******************************************************************************/
LPDIRECT3DTEXTURE9 CTexture::Get(std::string fileName){
	auto iter = std::find(textureName.begin(), textureName.end(), fileName);
	if (iter != textureName.end()){
		std::string a = *iter;
		int index = std::distance(textureName.begin(), iter);
		return vecTexture[index];
	}
	return NULL;
}
/*******************************************************************************
* 関数名:LPDIRECT3DTEXTURE9 CTexture::Get(std::string fileName)
*
* 引数:  なし
* 戻り値:なし
* 説明	テクスチャの取得
*
*******************************************************************************/
LPDIRECT3DTEXTURE9 CTexture::Get(int null){
	return NULL;
}
/*******************************************************************************
* 関数名:void CTexture::Release()
*
* 引数:  なし
* 戻り値:なし
* 説明	テクスチャの開放
*
*******************************************************************************/
void CTexture::Release(){
	for (auto iter = vecTexture.begin(); iter != vecTexture.end(); ++iter){
		size_t index = std::distance(vecTexture.begin(), iter);
		if (vecTexture[index] != NULL){
			vecTexture[index]->Release();
			vecTexture[index] = NULL;
		}
	}
}
/*******************************************************************************
* 関数名:std::vector<std::string> get_file_path_in_dir(const std::string& dir_name)
*
* 引数:  フォルダ名の指定
* 戻り値:なし
* 説明	指定したディレクトリからファイル名をすべて取得
*
*******************************************************************************/
std::vector<std::string> get_file_path_in_dir(const std::string& dir_name){
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;//defined at Windwos.h
	std::vector<std::string> file_names;

	//拡張子の設定
	std::string search_name = dir_name + "\\*";

	hFind = FindFirstFile(search_name.c_str(), &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file not found");
	}

	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			file_names.push_back(win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);

	return file_names;
}