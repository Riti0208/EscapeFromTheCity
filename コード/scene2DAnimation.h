/****************************************************************************
* �^�C�g��:  scene2d�w�b�_�[
* �t�@�C����:scene2d.h
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/3
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _SCENE_2D_ANIMATION_H_
#define _SCENE_2D_ANIMATION_H_
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
class CScene2DAnimation : public CScene{
private:
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;	//���_�o�b�t�@
	LPDIRECT3DTEXTURE9		m_pTexture;
	char					*m_pFileName;		//�t�@�C����
	float					m_fWidth;
	float					m_fHeight;
	D3DXVECTOR3				m_oldPos;
	D3DXCOLOR				m_oldCol;
	bool					m_withoutLoadingMode;
	int						m_animationNum;
	int						m_currentAnimtionFrame;
	int						m_currentAnimtionSpriteCnt;
	int						m_animationChangeFrame;
public:
	CScene2DAnimation(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col, int animationNum, int animationChangeFrame, bool withoutLoadingMode){ m_bufferPolygon = NULL; m_pos = pos; m_fWidth = fWidth; m_fHeight = fHeight; m_pFileName = pFileName; m_col = col; m_animationNum = animationNum; m_animationChangeFrame = animationChangeFrame; m_withoutLoadingMode = withoutLoadingMode; Init(); }
	~CScene2DAnimation(){ Uninit(); }
	void Init();
	void Uninit();
	void Draw();
	void Update();
	static CScene2DAnimation *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col, int animationNum, int animationChangeFrame, bool withoutLoadingMode = false);
};

#endif