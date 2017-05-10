/****************************************************************************
* �^�C�g��:  sceneXFile�w�b�_�[
* �t�@�C����:sceneXFile.h
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/3
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _SCENE_X_H_
#define _SCENE_X_H_
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"scene.h"
#include"model.h"
/*******************************************************************************
* ���C�u�����̃����N
*******************************************************************************/
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �\���̂̒�`
*******************************************************************************/
/*******************************************************************************
* �N���X�̒�`
*******************************************************************************/
//�V�[���N���X
class CSceneXFile : public CScene{
private:
	LPDIRECT3DTEXTURE9 	m_texture;	//�e�N�X�`�����
	LPD3DXMESH 			m_mesh;		//���b�V�����
	LPD3DXBUFFER	 	m_bufferMaterial;	//�}�e���A�����
	DWORD				m_numMaterial;		//�}�e���A���̐�
	char				*m_pFileName;			//�t�@�C����
	MODEL_INFO			m_modelInfo;
	MODEL_INFO			m_defaultModelInfo;
public:
	CSceneXFile(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName){m_mesh = NULL;m_texture = NULL;m_bufferMaterial = NULL;m_pos = pos;m_rot = rot;m_pFileName = pFileName;Init();}
	~CSceneXFile(){ Uninit(); };
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static CSceneXFile *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName);
	LPD3DXMESH GetMesh(){ return m_mesh; };
	MODEL_INFO *GetModelInfo(){ return &m_modelInfo; }
	MODEL_INFO *GetDefaultModelInfo(){ return &m_defaultModelInfo; }
};

#endif