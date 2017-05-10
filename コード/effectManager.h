#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

#define _NOT_CPP14_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include"renderer.h"
#include<vector>
#include<map>
#include<algorithm>

class CEffectManager{
private:
	static ::Effekseer::Manager					*m_manager;
	static ::EffekseerRenderer::Renderer		*m_renderer;
	static std::map<std::string, ::Effekseer::Effect*>		effectMap;
	static std::vector<std::string> get_file_path_in_dir(const std::string& dir_name);
public:
	static void Init(LPDIRECT3DDEVICE9 device, int instanceMax);
	static void Uninit();
	static void Update();
	static void Draw();
	static ::Effekseer::Handle CreateEffect(char *fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static void StopEffect(::Effekseer::Handle handle);
	static void SetPos(::Effekseer::Handle handle, D3DXVECTOR3 pos){ m_manager->SetLocation(handle, pos.x, pos.y, pos.z); }
	static void SetRot(::Effekseer::Handle handle, D3DXVECTOR3 rot){ m_manager->SetRotation(handle, rot.x, rot.y, rot.z); }
	static D3DXVECTOR3 GetPos(::Effekseer::Handle handle){ ::Effekseer::Vector3D pos = m_manager->GetLocation(handle); return D3DXVECTOR3(pos.X, pos.Y, pos.Z); };
	static void SleepEffect(){ ::SleepEx(1000, true); }
	static void onLostDevice(){ m_renderer->OnLostDevice(); }
	static void onResetDevice(float fob, float aspect, float nz, float fz){ 	// 投影行列を設定
		m_renderer->SetProjectionMatrix(
			::Effekseer::Matrix44().PerspectiveFovLH(fob, aspect, nz, fz));
	}
	static void SetProjectionMatrix(D3DXVECTOR3 eye, D3DXVECTOR3 at, D3DXVECTOR3 up){	// カメラ行列を設定
		m_renderer->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(eye.x, eye.y, eye.z), ::Effekseer::Vector3D(at.x, at.y, at.z), ::Effekseer::Vector3D(up.x, up.y, up.z)));
	};
};

#endif