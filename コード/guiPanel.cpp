/****************************************************************************
* �^�C�g��:  GUI�̏���
* �t�@�C����:guiPanel.cpp
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
#include"guiPanel.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
* �֐���:CGuiPanel::CGuiPanel(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName)
*
* ����: D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName
* �߂�l:	�Ȃ�
* ����	guiPanel�N���X�̃R���X�g���N�^
*
*******************************************************************************/
CGuiPanel::CGuiPanel(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col){
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_col = col;
	m_pFileName = pFileName;
	Init();
}
/*******************************************************************************
* �֐���:void CGuiPanel::Init()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	guiPanel�N���X�̏���������
*
*******************************************************************************/
void CGuiPanel::Init(){
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
	pVtx[3].col = m_col;

	//UV���W�̐ݒ�

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	m_bufferPolygon->Unlock();
}
/*******************************************************************************
* �֐���:void CGuiPanel::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	guiPanel�N���X�̏I������
*
*******************************************************************************/
void CGuiPanel::Uninit(){
	SAFE_RELEASE(m_bufferPolygon)
}
/*******************************************************************************
* �֐���:void CGuiPanel::Update()
*WW
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	guiPanel�N���X�̍X�V����
*
*******************************************************************************/
void CGuiPanel::Update(){
}
/*******************************************************************************
* �֐���:void CGuiPanel::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	guiPanel�N���X�̕`�揈��
*
*******************************************************************************/
void CGuiPanel::Draw(){
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
* �֐���:CGuiPanel *CGuiPanel::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, D3DXCOLOR col)
*
* ����:  D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, D3DXCOLOR col
* �߂�l:	CGuiPanel *
* ����	guiPanel�N���X�̐�������
*
*******************************************************************************/
CGuiPanel *CGuiPanel::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, char* fileName, D3DXCOLOR col){
	CGuiPanel *scene;
	scene = new CGuiPanel(pos, fWidth, fHeight, fileName, col);
	return scene;
}
