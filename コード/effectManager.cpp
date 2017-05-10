#include"effectManager.h"
#include"camera.h"
#include <iostream>
#include <locale> 
#include <codecvt> 
#ifndef _NOT_CPP14_
#include <filesystem>
#endif
#ifndef _CPP14_
#include<stdexcept>
#endif


#define NEAR_Z	(10)					//カメラの描画開始距離
#define FAR_Z	(100)					//カメラの描画終了距離
::Effekseer::Manager				*CEffectManager::m_manager;
::EffekseerRenderer::Renderer		*CEffectManager::m_renderer;	static std::map<char*, ::Effekseer::Effect*>		effectMap;
std::map<std::string, ::Effekseer::Effect*>	CEffectManager::effectMap;

void CEffectManager::Init(LPDIRECT3DDEVICE9 device, int instanceMax){
	m_renderer = ::EffekseerRendererDX9::Renderer::Create(device, instanceMax);
	m_manager = ::Effekseer::Manager::Create(instanceMax);
	// 描画用インスタンスから描画機能を設定
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());
	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());

	std::vector<std::string> file_list = get_file_path_in_dir("data/EFFECT");

#ifndef _NOT_CPP14_

	// カレントディレクトリ以下のファイル名を取得する
	// 再帰的にファイル名を取得する場合は、std::tr2::sys::recursive_directory_iteratorを使う
	for (std::tr2::sys::directory_iterator it("data/EFFECT"), end; it != end; ++it) {
		file_list.push_back(it->path());
	}
#endif
	for (auto itr = file_list.begin(); itr != file_list.end(); ++itr) {
		std::string fileName = *itr;
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;

		::Effekseer::Effect *effect = NULL;

		std::wstring ws = cv.from_bytes(fileName);
		
		ws = L"data\\EFFECT\\" + ws;

		effect = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)ws.c_str());

		fileName = "data\\EFFECT\\" + fileName;

		effectMap.insert(std::make_pair(fileName, effect));

		fileName = "";
	}
}
void CEffectManager::Uninit(){
	m_manager->Destroy();
	m_renderer->Destory();
}
void CEffectManager::Update(){

	CEffectManager::onResetDevice((D3DX_PI) / 4, (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_Z, FAR_Z);
	CEffectManager::SetProjectionMatrix(CCamera::GetPosEye(), CCamera::GetPosLookAt(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	// 投影行列の更新
	m_manager->Update();
}
void CEffectManager::Draw(){
	auto device = CRenderer::GetDevice();
	device->SetRenderState(D3DRS_ZENABLE, true);
	// エフェクトの描画開始処理を行う。
	m_renderer->BeginRendering();

	// エフェクトの描画を行う。
	m_manager->Draw();

	// エフェクトの描画終了処理を行う。
	m_renderer->EndRendering();

}
::Effekseer::Handle CEffectManager::CreateEffect(char *fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot){
	// エフェクトの読込
	::Effekseer::Handle handle;

	std::string string = "data\\EFFECT\\";
	string += fileName;


	// エフェクトの再生
	handle = m_manager->Play(effectMap.at(string), pos.x, pos.y, pos.z);
	m_manager->SetRotation(handle, rot.x, rot.y, rot.z);
	m_manager->SetScale(handle, 10, 10, 10);

	return handle;
}

void CEffectManager::StopEffect(::Effekseer::Handle handle){
	m_manager->StopEffect(handle);
}
/*******************************************************************************
* 関数名:std::vector<std::string> get_file_path_in_dir(const std::string& dir_name)
*
* 引数:  フォルダ名の指定
* 戻り値:なし
* 説明	指定したディレクトリからファイル名をすべて取得
*
*******************************************************************************/
std::vector<std::string> CEffectManager::get_file_path_in_dir(const std::string& dir_name){
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