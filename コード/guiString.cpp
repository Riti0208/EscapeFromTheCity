/****************************************************************************
* �^�C�g��:  GUI�̏���
* �t�@�C����:guiString.cpp
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
#include"guiString.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
* �֐���:CGuiString::CGuiString(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName)
*
* ����: D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName
* �߂�l:	�Ȃ�
* ����	guiString�N���X�̃R���X�g���N�^
*
*******************************************************************************/
CGuiString::CGuiString(D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, char *pFileName, D3DXCOLOR col){
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_nFontSize = nFontSize;
	m_string = string;
	m_col = col;
	m_pFileName = pFileName;
	Init();
}
/*******************************************************************************
* �֐���:void CGuiString::Init()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	guiString�N���X�̏���������
*
*******************************************************************************/
void CGuiString::Init(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	m_pFont = NULL;
	D3DXCreateFont(pDevice,		//D3D�f�o�C�X�̃|�C���^
		m_nFontSize,						//�����̍���
		0,						//�����̕�
		3,						//�t�H���g�̑���
		3,						//�~�b�v�}�b�v�̃��x���̐�
		FALSE,					//�C�^���b�N�t�H���g�̏ꍇ��true,����ȊO��false
		SHIFTJIS_CHARSET,		//�t�H���g�̕����Z�b�g
		OUT_DEFAULT_PRECIS,		//Windows �ł́A���ۂ̃t�H���g�ƖړI�̃t�H���g�̃T�C�Y����ѓ����̈�v���@���w�肵�܂�(�悭�킩��Ȃ�)
		DEFAULT_QUALITY,		//Windows �ł́A���ۂ̃t�H���g�ƖړI�̃t�H���g�Ƃ̈�v���@���w�肵�܂�(�悭�킩��Ȃ�)
		DEFAULT_PITCH,			//�s�b�`�ƃt�@�~���C���f�b�N�X
		"Consolas",				//�t�H���g�̖��O��ێ����镶����
		&m_pFont);

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

	pVtx[0].col = COLOR_GRAY;
	pVtx[1].col = COLOR_GRAY;
	pVtx[2].col = COLOR_GRAY;
	pVtx[3].col = COLOR_GRAY;

	//UV���W�̐ݒ�

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	m_bufferPolygon->Unlock();
}
/*******************************************************************************
* �֐���:void CGuiString::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	guiString�N���X�̏I������
*
*******************************************************************************/
void CGuiString::Uninit(){
	if (m_pFont != NULL){
		m_pFont->Release();
		m_pFont = NULL;
	}
	if (m_bufferPolygon != NULL){
		m_bufferPolygon->Release();		//���
		m_bufferPolygon = NULL;
	}
}
/*******************************************************************************
* �֐���:void CGuiString::Update()
*WW
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	guiString�N���X�̍X�V����
*
*******************************************************************************/
void CGuiString::Update(){
}
/*******************************************************************************
* �֐���:void CGuiString::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	guiString�N���X�̕`�揈��
*
*******************************************************************************/
void CGuiString::Draw(){
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

	RECT rect = { (LONG)(m_pos.x - m_fWidth * 0.5f), (LONG)(m_pos.y - m_fHeight * 0.5f), (LONG)(m_pos.x + m_fWidth * 0.5f), (LONG)(m_pos.y + m_fHeight * 0.5f) };
	m_pFont->DrawText(NULL,	// �`��X�v���C�g�`���
		m_string.c_str(),	// �`�悷��e�L�X�g	
		-1,					// �e�L�X�g�̒����A�|�P�Ȃ�Ύ����Ő��l�����킳���
		&rect,				// �e�L�X�g��`�悷�钷���`�̈�
		DT_CENTER,			// �e�L�X�g�`��I�v�V����
		m_col				// �����J���[
		);
}
/*******************************************************************************
* �֐���:CGuiString *CGuiString::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, D3DXCOLOR col)
*
* ����:  D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, D3DXCOLOR col
* �߂�l:	CGuiString *
* ����	guiString�N���X�̐�������
*
*******************************************************************************/
CGuiString *CGuiString::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nFontSize, std::string string, char *pFileName, D3DXCOLOR col){
	CGuiString *scene;
	scene = new CGuiString(pos, fWidth, fHeight,nFontSize, string, pFileName, col);
	return scene;
}
