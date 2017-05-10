/****************************************************************************
* �^�C�g��:  GUI�̏���
* �t�@�C����:score.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/13
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"manager.h"
#include"score.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
* �֐���:CScore::CScore(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName)
*
* ����: D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName
* �߂�l:	�Ȃ�
* ����	score�N���X�̃R���X�g���N�^
*
*******************************************************************************/
CScore::CScore(D3DXVECTOR3 pos, float fWidth, float fHeight, int nNum, int nDigit, char* fileName){
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_nScore = nNum;
	m_nDigit = nDigit;
	for (int i = 0; i < m_nDigit; i++)	{
		int num = (int)m_nScore / (int)pow(10.0f, (m_nDigit - 1 - i));
		CNumber* number = CNumber::Create(D3DXVECTOR3(m_pos.x + (fWidth / m_nDigit) * (i + 1), m_pos.y, 0.0f), m_fWidth / m_nDigit, m_fHeight, fileName, num);
		m_vecNum.push_back(number);
	}
	Init();
}
/*******************************************************************************
* �֐���:void CScore::Init()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	score�N���X�̏���������
*
*******************************************************************************/
void CScore::Init(){
}
/*******************************************************************************
* �֐���:void CScore::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	score�N���X�̏I������
*
*******************************************************************************/
void CScore::Uninit(){
	std::for_each(m_vecNum.begin(), m_vecNum.end(), [&](CNumber *number){
		delete number;
		number = NULL;
	});
	m_vecNum.empty();
}
/*******************************************************************************
* �֐���:void CScore::Update()
*WW
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	score�N���X�̍X�V����
*
*******************************************************************************/
void CScore::Update(){
	for (int i = 0; i < m_nDigit; i++)	{
		int num = (int)(m_nScore / pow(10.0f, (m_nDigit - 1 - i)));
		m_vecNum[i]->SetNum(num);
	}
}
/*******************************************************************************
* �֐���:void CScore::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	score�N���X�̕`�揈��
*
*******************************************************************************/
void CScore::Draw(){
}
CScore *CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nNum, int nDidit, char* fileName){
	CScore *scene;
	scene = new CScore(pos, fWidth, fHeight, nNum, nDidit, fileName);
	return scene;
}