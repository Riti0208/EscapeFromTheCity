/****************************************************************************
* �^�C�g��:  2D�|���S���֌W�̏���
* �t�@�C����:scene.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/04/19
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"scene2DwLAnimation.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
* �֐���:void CScene::Init()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̏���������
*
*******************************************************************************/
void CScene2DwLAnimation::Init(){
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

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,					//�f�o�C�X
		m_pFileName,			//�t�@�C����
		&m_pTexture					//�e�N�X�`���̃|�C���^
		);

	m_bufferPolygon->Unlock();

	m_currentAnimtionFrame = 0;

	m_currentAnimtionSpriteCnt = 0;
}
/*******************************************************************************
* �֐���:void CScene::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̏I������
*
*******************************************************************************/
void CScene2DwLAnimation::Uninit(){
	SAFE_RELEASE(m_bufferPolygon)
}
/*******************************************************************************
* �֐���:void CScene::Update()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̍X�V����
*
*******************************************************************************/
void CScene2DwLAnimation::Update(){

	VERTEX_2D *pVtx;



	if (m_currentAnimtionSpriteCnt > m_animationChangeFrame){
		m_currentAnimtionSpriteCnt = 0;
		m_currentAnimtionFrame++;
	}

	m_currentAnimtionSpriteCnt++;

	//�ʒu���̐ݒ�

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth / 2, m_pos.y - m_fHeight / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth / 2, m_pos.y - m_fHeight / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth / 2, m_pos.y + m_fHeight / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth / 2, m_pos.y + m_fHeight / 2, 0.0f);

	//���_�F�̐ݒ�

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =

		pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(1.0f / m_animationNum * m_currentAnimtionFrame, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / m_animationNum * (m_currentAnimtionFrame + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / m_animationNum * m_currentAnimtionFrame, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / m_animationNum * (m_currentAnimtionFrame + 1), 1.0f);

	m_bufferPolygon->Unlock();

}
/*******************************************************************************
* �֐���:void CScene::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̕`�揈��
*
*******************************************************************************/
void CScene2DwLAnimation::Draw(){
	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->SetStreamSource(0, m_bufferPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);
}