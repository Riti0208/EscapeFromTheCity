/****************************************************************************
* �^�C�g��:  scene2d�w�b�_�[
* �t�@�C����:scene2d.h
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/3
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _SCENE_2D_H_
#define _SCENE_2D_H_
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"scene.h"
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
class CScene2D : public CScene{
private:
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;	//���_�o�b�t�@
	LPDIRECT3DTEXTURE9		m_pTexture;
	char					*m_pFileName;		//�t�@�C����
	float					m_fWidth;
	float					m_fHeight;
	D3DXVECTOR3				m_oldPos;
	D3DXCOLOR				m_oldCol;
	bool					m_withoutLoadingMode;

public:
	CScene2D(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col, bool withoutLoadingMode){ m_bufferPolygon = NULL; m_pos = pos; m_fWidth = fWidth; m_fHeight = fHeight; m_pFileName = pFileName; m_col = col; m_withoutLoadingMode = withoutLoadingMode; Init(); }
	~CScene2D(){ Uninit(); }
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static CScene2D *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col, bool withoutLoadingMode = false);
};

#endif