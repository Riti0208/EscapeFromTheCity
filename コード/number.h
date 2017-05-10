/****************************************************************************
* �^�C�g��:  number�w�b�_�[
* �t�@�C����:number.h
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/13
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _NUMBER_H_
#define _NUMBER_H_
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"gui.h"
#include"sceneRect.h"
#include"renderer.h"
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
class CNumberList : public CGui{
public:
	CNumberList(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nLineNum);
	~CNumberList(){ Uninit(); };
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetNum(int num){ m_nNum = num; };
	static CNumberList *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nLineNum);
private:
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;	//���_�o�b�t�@
	D3DXVECTOR3 m_pos;		//�|�W�V����
	float		m_fWidth;	//��
	float		m_fHeight;	//����
	char		*m_pFileName;	//�e�N�X�`���̖��O
	int			m_nNum;		//�`��p�̐��l
	int			m_nLineNum;
};
class CNumber : public CGui{	
public:
	CNumber(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber);
	~CNumber(){ Uninit(); };
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetNum(int num){ m_nNum = num; };
	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber);
private:
	LPDIRECT3DVERTEXBUFFER9	m_bufferPolygon;	//���_�o�b�t�@
	D3DXVECTOR3 m_pos;		//�|�W�V����
	float		m_fWidth;	//��
	float		m_fHeight;	//����
	char		*m_pFileName;	//�e�N�X�`���̖��O
	int			m_nNum;		//�`��p�̐��l
};

#endif