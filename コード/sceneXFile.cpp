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
#include"sceneXFile.h"
#include"model.h"
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
void CSceneXFile::Init(){
	m_modelInfo = CModel::Get(m_pFileName);
	m_mesh = m_modelInfo.m_mesh;
	m_defaultModelInfo = m_modelInfo;
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
/*******************************************************************************
* �֐���:void CScene::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̏I������
*
*******************************************************************************/
void CSceneXFile::Uninit(){
}
/*******************************************************************************
* �֐���:void CScene::Update()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̍X�V����
*
*******************************************************************************/
void CSceneXFile::Update(){
}
/*******************************************************************************
* �֐���:void CScene::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̕`�揈��
*
*******************************************************************************/
void CSceneXFile::Draw(){
	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	D3DXMATRIX	mtxScl, mtxRot, mtxTrans;	//�g�k�A��]�A�ړ��p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_world);
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

	//�����O���[�v�̐�����DrawSubset���Ă�
	for (unsigned int i = 0; i < (int)m_modelInfo.m_numMaterial; i++) {
		pDevice->SetMaterial(&m_modelInfo.m_mat[i]);
		pDevice->SetTexture(0, CTexture::Get(m_modelInfo.m_textureName[i]));
		m_modelInfo.m_mesh->DrawSubset(i);
	}
}
CSceneXFile *CSceneXFile::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName){
	CSceneXFile *scene;
	scene = new CSceneXFile(pos, rot, pFileName);
	return scene;
}