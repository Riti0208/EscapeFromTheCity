/****************************************************************************
* �^�C�g��:  Billboard�|���S���֌W�̏���
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
#include"sceneBillboard.h"
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
void CSceneBillboard::Init(){
	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	m_rot.z = 0.0f;

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_bufferPolygon,
		NULL
		);

	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	VERTEX_3D *pVtx;

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);

	//�|�W�V�����̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth * 0.5f, m_fHeight * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth * 0.5f, m_fHeight * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth * 0.5f, -m_fHeight * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth * 0.5f, -m_fHeight * 0.5f, 0.0f);
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//�J���[�ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_bufferPolygon->Unlock();
}
/*******************************************************************************
* �֐���:void CScene::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̏I������
*
*******************************************************************************/
void CSceneBillboard::Uninit(){
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
void CSceneBillboard::Update(){
}
/*******************************************************************************
* �֐���:void CScene::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̕`�揈��
*
*******************************************************************************/
void CSceneBillboard::Draw(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMATRIX	mtxView;

	D3DXMatrixIdentity(&m_world);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	D3DXMatrixInverse(&m_world, NULL, &mtxView);

	m_world._41 = 0.0f;
	m_world._42 = 0.0f;
	m_world._43 = 0.0f;
	m_world._44 = 1.0f;

	//�X�P�[���̔��f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxScl);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxTrans);

	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_world);

	pDevice->SetStreamSource(0, m_bufferPolygon, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::Get(m_pFileName));

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

}
CSceneBillboard *CSceneBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, char *pFileName, D3DXCOLOR col){
	CSceneBillboard *scene;
	scene = new CSceneBillboard(pos, rot, fWidth, fHeight, pFileName, col);
	return scene;
}