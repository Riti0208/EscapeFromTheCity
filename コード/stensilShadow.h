#ifndef _STENCIL_SHADOW_H_
#define _STENCIL_SHADOW_H_
#include"renderer.h"
#include"scene2D.h"
#include"sceneXFile.h"
class stensilShadow : public CScene{
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;

	LPDIRECT3DTEXTURE9 	m_texture;	//�e�N�X�`�����
	LPD3DXMESH 			m_mesh;		//���b�V�����
	LPD3DXBUFFER	 	m_bufferMaterial;	//�}�e���A�����
	DWORD				m_numMaterial;		//�}�e���A���̐�
	char				*m_pFileName;			//�t�@�C����
	MODEL_INFO			m_modelInfo;
	MODEL_INFO			m_defaultModelInfo;
public:
	stensilShadow(D3DXVECTOR3 pos);
	~stensilShadow();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static stensilShadow *Create(D3DXVECTOR3 pos){
		stensilShadow *ss;
		ss = new stensilShadow(pos);
		return ss;
	}
};
#endif