/****************************************************************************
* タイトル:  モデル管理クラスの処理
* ファイル名:model.cpp
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

#include"model.h"
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
/*******************************************************************************
* グローバル変数
*******************************************************************************/
std::vector<MODEL_INFO>		CModel::vecModelInfo;
std::vector<std::string>	CModel::modelName;
void backEraseString(std::string &str ,const char word){
	int i = 0;
	for (; i < (int)str.size(); ++i) {
		if (str[i] == word) break;
	}
	if (i < (int)str.size()) {
		str.erase(0, i);
	}
}
/*******************************************************************************
* 関数名:HRESULT CModel::Create()
*
* 引数:  なし
* 戻り値:なし
* 説明	指定ディレクトリにある全ての画像からテクスチャの一括生成
*
*******************************************************************************/
HRESULT CModel::Create(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	std::vector<std::string> file_list;

#ifndef _NOT_CPP14_

	// カレントディレクトリ以下のファイル名を取得する
	// 再帰的にファイル名を取得する場合は、std::tr2::sys::recursive_directory_iteratorを使う
	for (std::tr2::sys::directory_iterator it("data/MODEL"), end; it != end; ++it) {
		file_list.push_back(it->path());
	}
#endif

	file_list = get_file_path_in_dir("data/MODEL");

	for (auto itr = file_list.begin(); itr != file_list.end(); ++itr) {
		std::string fileName = *itr;

		fileName = "data\\MODEL\\" + fileName;

		MODEL_INFO modelInfo = {0};

		modelInfo.m_fileName = fileName;

		if (FAILED(D3DXLoadMeshFromX(
			fileName.c_str(), 
			D3DXMESH_SYSTEMMEM, 
			pDevice, 
			NULL, 
			&modelInfo.m_bufferMaterial, 
			NULL, 
			&modelInfo.m_numMaterial, 
			&modelInfo.m_mesh))){
			return E_FAIL;
		}

		D3DXMATERIAL* d3dxmatrs = (D3DXMATERIAL*)modelInfo.m_bufferMaterial->GetBufferPointer();

		int nNumMaterial = (int)modelInfo.m_numMaterial;
		for (int i = 0; i < nNumMaterial; i++) {
			//マテリアル複写
			modelInfo.m_mat.push_back(d3dxmatrs[i].MatD3D);
			modelInfo.m_mat[i].Ambient = d3dxmatrs[i].MatD3D.Diffuse;

			if (d3dxmatrs[i].pTextureFilename != NULL){
				std::string textureName = d3dxmatrs[i].pTextureFilename;

				backEraseString(textureName, '\\');
				backEraseString(textureName, '/');

				textureName = "data\\TEXTURE\\" + textureName;
				modelInfo.m_textureName.push_back(textureName);
			}
			else{
				modelInfo.m_textureName.push_back("");
			}
		}

		modelInfo.m_bufferMaterial->Release();

		vecModelInfo.push_back(modelInfo);
		modelName.push_back(fileName);

		fileName = "";
	}

	return S_OK;
}
/*******************************************************************************
* 関数名:LPDIRECT3DTEXTURE9 CModel::Get(std::string fileName)
*
* 引数:  なし
* 戻り値:なし
* 説明	MODEL_INFOの取得
*
*******************************************************************************/
MODEL_INFO  CModel::Get(std::string fileName){
	auto iter = std::find(modelName.begin(), modelName.end(), fileName);
	if (iter != modelName.end()){
		std::string a = *iter;
		int index = std::distance(modelName.begin(), iter);
		return vecModelInfo[index];
	}
	MODEL_INFO modelInfo = {0};
	return modelInfo;
}
/*******************************************************************************
* 関数名:std::vector<std::string> CModel::get_file_path_in_dir(const std::string& dir_name)
*
* 引数:  フォルダ名の指定
* 戻り値:なし
* 説明	指定したディレクトリからファイル名をすべて取得
*
*******************************************************************************/
std::vector<std::string> CModel::get_file_path_in_dir(const std::string& dir_name){
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