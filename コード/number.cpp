/****************************************************************************
* �^�C�g��:  GUI�̏���
* �t�@�C����:number.cpp
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
#include"number.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
*�֐���:CNumber::CNumber(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber){
*
* ���� : D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName
* �߂�l : �Ȃ�
* ����	number�N���X�̃R���X�g���N�^
*
*******************************************************************************/
CNumber::CNumber(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber){
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_pFileName = pFileName;
	m_nNum = nNumber;
	Init();
}
/*******************************************************************************
* �֐���:void CNumber::Init()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	number�N���X�̏���������
*
*******************************************************************************/
void CNumber::Init(){
	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_bufferPolygon,
		NULL
		);

	VERTEX_2D *pVtx;

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth / 2, m_pos.y - m_fHeight / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth / 2, m_pos.y - m_fHeight / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth / 2, m_pos.y + m_fHeight / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth / 2, m_pos.y + m_fHeight / 2, 0.0f);

	//�������W�ݒ�

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�F�̐ݒ�

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//UV���W�̐ݒ�

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	m_bufferPolygon->Unlock();

}
/*******************************************************************************
* �֐���:void CNumber::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	number�N���X�̏I������
*
*******************************************************************************/
void CNumber::Uninit(){
}
/*******************************************************************************
* �֐���:void CNumber::Update()
*WW
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	number�N���X�̍X�V����
*
*******************************************************************************/
void CNumber::Update(){

	VERTEX_2D *pVtx;

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);
	//UV���W�̐ݒ�

	pVtx[0].tex = D3DXVECTOR2(m_nNum * 0.1f, 0.0);
	pVtx[1].tex = D3DXVECTOR2(0.1f + m_nNum * 0.1f, 0.0);
	pVtx[2].tex = D3DXVECTOR2(m_nNum * 0.1f, 1.0);
	pVtx[3].tex = D3DXVECTOR2(0.1f + m_nNum * 0.1f, 1.0);

	m_bufferPolygon->Unlock();
}
/*******************************************************************************
* �֐���:void CNumber::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	number�N���X�̕`�揈��
*
*******************************************************************************/
void CNumber::Draw(){
	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->SetStreamSource(0, m_bufferPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::Get(m_pFileName));

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);
}
/*******************************************************************************
* �֐���:CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nLineNum)
*
* ����: D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nLineNum
* �߂�l:	*CNumber�^
* ����	number�N���X�̕`�揈��
*
*******************************************************************************/
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, int nNumber){
	CNumber *scene;
	scene = new CNumber(pos, fWidth, fHeight, pFileName, nNumber);
	return scene;
}
