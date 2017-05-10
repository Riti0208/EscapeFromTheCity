/****************************************************************************
* �^�C�g��:  scene2d�w�b�_�[
* �t�@�C����:scene2d.h
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/3
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _SCENE_3D_H_
#define _SCENE_3D_H_
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"manager.h"
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
class CScene3D : public CScene{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBufferMeshField;		//�t�B�[���h�p�o�b�t�@�[
	LPDIRECT3DINDEXBUFFER9	m_pIndexBufferField;		//�C���f�b�N�X�o�b�t�@�[�ւ̃|�C���^

	D3DXVECTOR3				m_posMeshField;				//�t�B�[���h�̈ʒu
	D3DXVECTOR3				m_rotMeshField;				//�t�B�[���h�̌���
	D3DXVECTOR3				m_sclMeshField;				//�t�B�[���h�̃X�P�[��

	int m_nFieldNumX;								//�������ɑ΂��Ẳ�����
	int m_nFieldNumZ;								//�c�����ɑ΂��Ẳ�����
	int m_nMeshFieldPolygonNum;						//�|���S����
	int m_nMeshFieldVerTexNum;                      //���_��
	int m_nIdxMeshFieldNum;                         //�C���f�b�N�X��
	float m_fBlockSizeX;							//1�u���b�N�̉������̑傫��
	float m_fBlockSizeZ;							//1�u���b�N�̏c�����̑傫��
	float m_fFieldSizeX;							//�t�B�[���h�̉������̑傫��
	float m_fFieldSizeZ;							//�t�B�[���h�̏c�����̑傫��

	char *m_pFileName;

public:
	CScene3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col){ m_pos = pos; m_rot = rot; m_pFileName = pFileName; m_col = col; Init(); };
	~CScene3D(){ Uninit(); };
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col);
};

#endif