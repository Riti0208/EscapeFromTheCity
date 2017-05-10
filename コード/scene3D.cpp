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
#include"scene3D.h"
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
void CScene3D::Init(){
	m_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_sclMeshField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);;
	m_nFieldNumX = 10;
	m_nFieldNumZ = 10;
	m_fFieldSizeX = 1500.0f;
	m_fFieldSizeZ = 1500.0f;
	m_posMeshField.x -= 1500;
	m_posMeshField.z -= 1500;

	m_pVtxBufferMeshField = NULL;

	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	m_sclMeshField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_nIdxMeshFieldNum = (m_nFieldNumX * 2 + 2) * m_nFieldNumZ + (m_nFieldNumZ - 1) * 2;

	m_nMeshFieldPolygonNum = m_nIdxMeshFieldNum - 2;

	m_nMeshFieldVerTexNum = (m_nFieldNumX + 1) * (m_nFieldNumZ + 1);

	m_fBlockSizeX = m_fFieldSizeX / m_nFieldNumX;
	m_fBlockSizeZ = m_fFieldSizeZ / m_nFieldNumZ;

	//���_�o�b�t�@�[�̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nMeshFieldVerTexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBufferMeshField,
		NULL
		);
	//�C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nIdxMeshFieldNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndexBufferField,
		NULL
		);

	//�C���f�b�N�X���̐ݒ�
	WORD *pIdx;
	m_pIndexBufferField->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X���W�ݒ�
	int nX = 0, nY = 0;
	int nIdx = 0;
	while (nIdx < m_nIdxMeshFieldNum){
		while (nIdx < (nY + 1) * (m_nFieldNumX * 2 + 4) - 2){
			if (nIdx % 2 == 0){
				pIdx[nIdx] = (m_nFieldNumX + 1) * (nY + 1) + nX;
			}
			else{
				pIdx[nIdx] = (m_nFieldNumX + 1) * nY + nX;
				nX++;
			}
			nIdx++;
		}
		nY++;
		nX = 0;
		nIdx += 2;
	}

	nIdx = m_nFieldNumX * 2 + 2;

	for (nY = 0; nY < m_nFieldNumZ - 1; nY++){
		pIdx[nIdx] = pIdx[nIdx - 1];
		pIdx[nIdx + 1] = pIdx[nIdx + 2];
		nIdx += m_nFieldNumX * 2 + 4;
	}

	m_pIndexBufferField->Unlock();

	//���_���̐ݒ�
	VERTEX_3D *pVtx;
	m_pVtxBufferMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].pos = D3DXVECTOR3((m_fFieldSizeX - (m_fBlockSizeX * m_nFieldNumX / 2)) + m_fBlockSizeX * (nCnt % (m_nFieldNumX + 1)), 0.0f, (m_fFieldSizeZ + (m_fBlockSizeZ * m_nFieldNumZ / 2)) - m_fBlockSizeZ * (nCnt / (m_nFieldNumX + 1)));
	}
	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].col = m_col;
	}

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].tex = D3DXVECTOR2((float)(nCnt % (m_nFieldNumX + 1)), (float)(nCnt / (m_nFieldNumX + 1)));
	}

	m_pIndexBufferField->Unlock();

}
/*******************************************************************************
* �֐���:void CScene::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̏I������
*
*******************************************************************************/
void CScene3D::Uninit(){
	if (m_pVtxBufferMeshField != NULL){
		m_pVtxBufferMeshField->Release();
		m_pVtxBufferMeshField = NULL;
	}
	if (m_pIndexBufferField != NULL){
		m_pIndexBufferField->Release();
		m_pIndexBufferField = NULL;
	}
}
/*******************************************************************************
* �֐���:void CScene::Update()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̍X�V����
*
*******************************************************************************/
void CScene3D::Update(){
}
/*******************************************************************************
* �֐���:void CScene::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̕`�揈��
*
*******************************************************************************/
void CScene3D::Draw(){
	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_world);
	//�X�P�[���̔��f
	D3DXMatrixScaling(&mtxScl, m_sclMeshField.x, m_sclMeshField.y, m_sclMeshField.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxScl);
	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotMeshField.y, m_rotMeshField.x, m_rotMeshField.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posMeshField.x, m_posMeshField.y, m_posMeshField.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxTrans);
	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_world);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetStreamSource(0, m_pVtxBufferMeshField, 0, sizeof(VERTEX_3D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::Get(m_pFileName));

	//�C���f�b�N�X�o�b�t�@���o�C���h
	pDevice->SetIndices(m_pIndexBufferField);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMeshFieldVerTexNum, 0, m_nMeshFieldPolygonNum);
}
/*******************************************************************************
* �֐���:CScene3D Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col)
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	CScene3D�N���X�̐�������
*
*******************************************************************************/
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col){
	CScene3D *scene;
	scene = new CScene3D(pos, rot, pFileName, col);
	return scene;
}
