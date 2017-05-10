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
#include"input.h"
#include"IrregularityField.h"
#include"camera.h"
#include"sceneBillboard.h"
#include"collision.h"
#include<fstream>
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
* �֐���:void COrregularityField::Init()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̏���������
*
*******************************************************************************/
void CIrregularityField::Init(){
	m_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_sclMeshField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_nFieldNumX = 100;
	m_nFieldNumZ = 100;
	m_fFieldSizeX = 6000.0f;
	m_fFieldSizeZ = 6000.0f;
	fEditRange = 0.0f;

	m_fHeightCopy = 0.0f;

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
		sizeof(VERTEX_3D) * m_nMeshFieldVerTexNum * 2,
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
		pVtx[nCnt].pos = D3DXVECTOR3((m_fFieldSizeX - (m_fBlockSizeX * m_nFieldNumX / 2)) + m_fBlockSizeX * (nCnt % (m_nFieldNumX + 1)) - m_fFieldSizeX, 
			sinf(nCnt) * cosf(nCnt) * 50.0f ,
			(m_fFieldSizeZ + (m_fBlockSizeZ * m_nFieldNumZ / 2)) - m_fBlockSizeZ * (nCnt / (m_nFieldNumX + 1)) - m_fFieldSizeZ);
	}
	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].col = COLOR_RED;
	}
	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	int incrimentCnt = 0;

	int nFieldX = m_nFieldNumX;

	nFieldX = m_nFieldNumX;

	incrimentCnt = 0;

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum - 1; nCnt++){
		incrimentCnt++;
		if (incrimentCnt == nFieldX + 1)	incrimentCnt = 1, nCnt += 1;

		D3DXVECTOR3 V12(pVtx[0 + nCnt].pos.x - pVtx[m_nFieldNumX + 1 + nCnt].pos.x, pVtx[0 + nCnt].pos.y - pVtx[m_nFieldNumX + 1 + nCnt].pos.y, pVtx[0 + nCnt].pos.z - pVtx[m_nFieldNumX + 1 + nCnt].pos.z);
		D3DXVECTOR3 V13(pVtx[m_nFieldNumX + 2 + nCnt].pos.x - pVtx[m_nFieldNumX + 1 + nCnt].pos.x, pVtx[m_nFieldNumX + 2 + nCnt].pos.y - pVtx[m_nFieldNumX + 1 + nCnt].pos.y, pVtx[m_nFieldNumX + 2 + nCnt].pos.z - pVtx[m_nFieldNumX + 1 + nCnt].pos.z);

		D3DXVECTOR3 out;
		D3DXVec3Cross(&out, &V12, &V13);
		D3DXVECTOR3 N1;
		D3DXVec3Normalize(&N1, &out);

		D3DXVECTOR3 V22(pVtx[0 + nCnt].pos.x - pVtx[1 + nCnt].pos.x, pVtx[0 + nCnt].pos.y - pVtx[1 + nCnt].pos.y, pVtx[0 + nCnt].pos.z - pVtx[1 + nCnt].pos.z);
		D3DXVECTOR3 V23(pVtx[m_nFieldNumX + 2 + nCnt].pos.x - pVtx[1 + nCnt].pos.x, pVtx[m_nFieldNumX + 2 + nCnt].pos.y - pVtx[1 + nCnt].pos.y, pVtx[m_nFieldNumX + 2 + nCnt].pos.z - pVtx[1 + nCnt].pos.z);

		D3DXVec3Cross(&out, &V22, &V23);
		D3DXVECTOR3 N4;
		D3DXVec3Normalize(&N4, &out);

		D3DXVECTOR3 N2;
		D3DXVec3Normalize(&N2, &(N1 + N2));

		D3DXVECTOR3 N3;
		D3DXVec3Normalize(&N3, &(N1 + N2));

		pVtx[nCnt].nor = N1;
		pVtx[nCnt + 1].nor = N2;
		pVtx[nCnt + 2].nor = N3;
		pVtx[nCnt + 3].nor = N4;

	}

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].col = m_col;
	}

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].tex = D3DXVECTOR2((float)(nCnt % (m_nFieldNumX + 1)), (float)(nCnt / (m_nFieldNumX + 1)));
	}

	m_pIndexBufferField->Unlock();

#ifdef _DEBUG
	SetEditGui();
#endif

	load();
}
/*******************************************************************************
* �֐���:void COrregularityField::Uninit()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̏I������
*
*******************************************************************************/
void CIrregularityField::Uninit(){
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
* �֐���:void CIrregularityField::SetEditGui()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	�t�B�[���h�̕ҏW�pGUI�ݒu
*
*******************************************************************************/
void CIrregularityField::SetEditGui(){

}
/*******************************************************************************
* �֐���:void CIrregularityField::EditField()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	�t�B�[���h�̕ҏW
*
*******************************************************************************/
void CIrregularityField::EditField(){
#ifdef _DEBUG
	D3DXMATRIX *proj = CCamera::getProj();
	D3DXMATRIX *view = CCamera::getView();
	MOUSE_POINT mp = CInput::GetMousePointer();

	//���_���̐ݒ�3
	VERTEX_3D *pVtx = NULL;
	m_pVtxBufferMeshField->Lock(0, 0, (void**)&pVtx, 0);

	fEditRange += mp.lZ / 10;

	m_pVtxBufferMeshField->Unlock();
#endif
}
/*******************************************************************************
* �֐���:void CIrregularityField::playerColl()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̏I������
*
*******************************************************************************/
float *CIrregularityField::GetHeight(D3DXVECTOR3 *pos){
	int nFieldX = m_nFieldNumX;

	int incrimentCnt = 0;

	//���_���̐ݒ�
	VERTEX_3D *pVtx = NULL;
	m_pVtxBufferMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < (m_nFieldNumX)* (m_nFieldNumZ); nCnt++){
		incrimentCnt++;
		if (incrimentCnt == nFieldX + 1)	incrimentCnt = 1, nCnt += 1;

		float fRadius = sqrt((pVtx[nCnt + 1].pos.x - pVtx[nCnt + 0].pos.x) * (pVtx[nCnt + 1].pos.x - pVtx[nCnt + 0].pos.x) + (pVtx[nCnt + 0].pos.z - pVtx[m_nFieldNumX + 1 + nCnt].pos.z) * (pVtx[nCnt + 0].pos.z - pVtx[m_nFieldNumX + 1 + nCnt].pos.z));

		bool C1 = CCollision::CircleCollision(&pVtx[nCnt + 0].pos, pos, fRadius);
		bool C2 = CCollision::CircleCollision(&pVtx[nCnt + 1].pos, pos, fRadius);
		bool C3 = CCollision::CircleCollision(&pVtx[m_nFieldNumX + nCnt + 1].pos, pos, fRadius);
		bool C4 = CCollision::CircleCollision(&pVtx[m_nFieldNumX + nCnt + 2].pos, pos, fRadius);

		if (C1 && C2 && C3 && C4){

			D3DXVECTOR3 PA1(pVtx[m_nFieldNumX + 1 + nCnt].pos.x - pVtx[0 + nCnt].pos.x, 0, pVtx[m_nFieldNumX + 1 + nCnt].pos.z - pVtx[0 + nCnt].pos.z);
			D3DXVECTOR3 PB1(pos->x - pVtx[0 + nCnt].pos.x, 0, pos->z - pVtx[0 + nCnt].pos.z);

			D3DXVECTOR3 out;
			D3DXVec3Cross(&out, &PB1, &PA1);
			D3DXVECTOR3 N1;
			D3DXVec3Normalize(&N1, &out);

			D3DXVECTOR3 PA2(pVtx[m_nFieldNumX + 2 + nCnt].pos.x - pVtx[m_nFieldNumX + 1 + nCnt].pos.x, 0, pVtx[m_nFieldNumX + 2 + nCnt].pos.z - pVtx[m_nFieldNumX + 1 + nCnt].pos.z);
			D3DXVECTOR3 PB2(pos->x - pVtx[m_nFieldNumX + 1 + nCnt].pos.x, 0, pos->z - pVtx[m_nFieldNumX + 1 + nCnt].pos.z);

			D3DXVec3Cross(&out, &PB2, &PA2);
			D3DXVECTOR3 N2;
			D3DXVec3Normalize(&N2, &out);

			D3DXVECTOR3 PA3(pVtx[0 + nCnt].pos.x - pVtx[m_nFieldNumX + 2 + nCnt].pos.x, 0, pVtx[0 + nCnt].pos.z - pVtx[m_nFieldNumX + 2 + nCnt].pos.z);
			D3DXVECTOR3 PB3(pos->x - pVtx[m_nFieldNumX + 2 + nCnt].pos.x, 0, pos->z - pVtx[m_nFieldNumX + 2 + nCnt].pos.z);

			D3DXVec3Cross(&out, &PB3, &PA3);
			D3DXVECTOR3 N3;
			D3DXVec3Normalize(&N3, &out);


			D3DXVECTOR3 PA4(pVtx[1 + nCnt].pos.x - pVtx[m_nFieldNumX + 2 + nCnt].pos.x, 0, pVtx[1 + nCnt].pos.z - pVtx[m_nFieldNumX + 2 + nCnt].pos.z);
			D3DXVECTOR3 PB4(pos->x - pVtx[m_nFieldNumX + 2 + nCnt].pos.x, 0, pos->z - pVtx[m_nFieldNumX + 2 + nCnt].pos.z);

			D3DXVec3Cross(&out, &PA4, &PB4);
			D3DXVECTOR3 N4;
			D3DXVec3Normalize(&N4, &out);

			D3DXVECTOR3 PA5(pVtx[0 + nCnt].pos.x - pVtx[1 + nCnt].pos.x, 0, pVtx[0 + nCnt].pos.z - pVtx[1 + nCnt].pos.z);
			D3DXVECTOR3 PB5(pos->x - pVtx[1 + nCnt].pos.x, 0, pos->z - pVtx[1 + nCnt].pos.z);

			D3DXVec3Cross(&out, &PA5, &PB5);
			D3DXVECTOR3 N5;
			D3DXVec3Normalize(&N5, &out);

			D3DXVECTOR3 PA6(pVtx[m_nFieldNumX + 2 + nCnt].pos.x - pVtx[0 + nCnt].pos.x, 0, pVtx[m_nFieldNumX + 2 + nCnt].pos.z - pVtx[0 + nCnt].pos.z);
			D3DXVECTOR3 PB6(pos->x - pVtx[0 + nCnt].pos.x, 0, pos->z - pVtx[0 + nCnt].pos.z);

			D3DXVec3Cross(&out, &PA6, &PB6);
			D3DXVECTOR3 N6;
			D3DXVec3Normalize(&N6, &out);

			D3DXVECTOR3 faceVec1 = pVtx[m_nFieldNumX + 1 + nCnt].pos - pVtx[0 + nCnt].pos;
			D3DXVECTOR3 faceVec2 = pVtx[m_nFieldNumX + 2 + nCnt].pos - pVtx[0 + nCnt].pos;

			D3DXVECTOR3 faceVec3 = pVtx[0 + nCnt].pos - pVtx[m_nFieldNumX + 2 + nCnt].pos;
			D3DXVECTOR3 faceVec4 = pVtx[m_nFieldNumX + 1 + nCnt].pos - pVtx[m_nFieldNumX + 2 + nCnt].pos;

			D3DXVECTOR3 out2;

			D3DXVec3Cross(&out, &faceVec1, &faceVec2);
			D3DXVec3Cross(&out2, &faceVec3, &faceVec4);

			out = out + out2;

			D3DXVECTOR3 faceN1;

			D3DXVec3Normalize(&faceN1, &out);

			D3DXVECTOR3 faceVec5 = pVtx[0 + nCnt].pos - pVtx[m_nFieldNumX + 2 + nCnt].pos;
			D3DXVECTOR3 faceVec6 = pVtx[1 + nCnt].pos - pVtx[m_nFieldNumX + 2 + nCnt].pos;

			D3DXVECTOR3 faceVec7 = pVtx[m_nFieldNumX + 2 + nCnt].pos - pVtx[1 + nCnt].pos;
			D3DXVECTOR3 faceVec8 = pVtx[0 + nCnt].pos - pVtx[1 + nCnt].pos;

			D3DXVec3Cross(&out, &faceVec5, &faceVec6);
			D3DXVec3Cross(&out2, &faceVec7, &faceVec8);

			out = out + out2;

			D3DXVECTOR3 faceN2;
			D3DXVec3Normalize(&faceN2, &out);

			if ((N1.y > 0) && (N2.y > 0) && (N3.y > 0)){

				pos->y = playerYPosUpdate(pos, D3DXVECTOR3(pVtx[0 + nCnt].pos.x, pVtx[0 + nCnt].pos.y, pVtx[0 + nCnt].pos.z), faceN1);

			}
			else if ((N4.y <= 0) && (N5.y <= 0) && (N6.y <= 0)){

				pos->y = playerYPosUpdate(pos, D3DXVECTOR3(pVtx[1 + nCnt].pos.x, pVtx[1 + nCnt].pos.y, pVtx[1 + nCnt].pos.z), faceN2);

			}

		}
	}
	m_pVtxBufferMeshField->Unlock();

	return &pos->y;
}
/*******************************************************************************
* �֐���:void COrregularityField::playerHeight
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̍X�V����
*
*******************************************************************************/
float CIrregularityField::playerYPosUpdate(D3DXVECTOR3 *pos, D3DXVECTOR3 _pos, D3DXVECTOR3 _nor){
	pos->y = _pos.y/*P0*/ - (_nor.x/*N*/ * ( pos->x/*P*/ - _pos.x) + _nor.z * (pos->z - _pos.z)) / _nor.y;
	return pos->y;
}
/*******************************************************************************
* �֐���:void save()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	field�N���X�̃Z�[�u����
*
*******************************************************************************/
void CIrregularityField::save(){
	std::ofstream ofs("data/MAP/map.txt", std::ios::out | std::ios::trunc);
	//���_���̐ݒ�
	VERTEX_3D *pVtx = NULL;
	m_pVtxBufferMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		ofs << pVtx[nCnt].pos.y << std::endl;
	}

	m_pVtxBufferMeshField->Unlock();
}
/*******************************************************************************
* �֐���:void save()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	field�N���X�̃Z�[�u����
*
*******************************************************************************/
void CIrregularityField::load(){
	//std::ifstream ifs("data/MAP/map.txt");
	//int nLineCnt = 0;
	//std::string str;
	////���_���̐ݒ�
	//VERTEX_3D *pVtx = NULL;
	//m_pVtxBufferMeshField->Lock(0, 0, (void**)&pVtx, 0);
	//while (getline(ifs, str)) {
	//	pVtx[nLineCnt].pos.y = std::stof(str);
	//	nLineCnt++;
	//}
	//

	//m_pVtxBufferMeshField->Unlock();
}

/*******************************************************************************
* �֐���:void COrregularityField::Update()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̍X�V����
*
*******************************************************************************/
void CIrregularityField::Update(){

	VERTEX_3D *pVtx = NULL;
	m_pVtxBufferMeshField->Lock(0, 0, (void**)&pVtx, 0);

	int incrimentCnt = 0;

	int nFieldX = m_nFieldNumX;

	nFieldX = m_nFieldNumX;

	incrimentCnt = 0;

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum - 1; nCnt++){
		incrimentCnt++;
		if (incrimentCnt == nFieldX + 1)	incrimentCnt = 1, nCnt += 1;

		D3DXVECTOR3 V12(pVtx[0 + nCnt].pos.x - pVtx[m_nFieldNumX + 1 + nCnt].pos.x, pVtx[0 + nCnt].pos.y - pVtx[m_nFieldNumX + 1 + nCnt].pos.y, pVtx[0 + nCnt].pos.z - pVtx[m_nFieldNumX + 1 + nCnt].pos.z);
		D3DXVECTOR3 V13(pVtx[m_nFieldNumX + 2 + nCnt].pos.x - pVtx[m_nFieldNumX + 1 + nCnt].pos.x, pVtx[m_nFieldNumX + 2 + nCnt].pos.y - pVtx[m_nFieldNumX + 1 + nCnt].pos.y, pVtx[m_nFieldNumX + 2 + nCnt].pos.z - pVtx[m_nFieldNumX + 1 + nCnt].pos.z);

		D3DXVECTOR3 out;
		D3DXVec3Cross(&out, &V12, &V13);
		D3DXVECTOR3 N1;
		D3DXVec3Normalize(&N1, &out);

		D3DXVECTOR3 V22(pVtx[0 + nCnt].pos.x - pVtx[1 + nCnt].pos.x, pVtx[0 + nCnt].pos.y - pVtx[1 + nCnt].pos.y, pVtx[0 + nCnt].pos.z - pVtx[1 + nCnt].pos.z);
		D3DXVECTOR3 V23(pVtx[m_nFieldNumX + 2 + nCnt].pos.x - pVtx[1 + nCnt].pos.x, pVtx[m_nFieldNumX + 2 + nCnt].pos.y - pVtx[1 + nCnt].pos.y, pVtx[m_nFieldNumX + 2 + nCnt].pos.z - pVtx[1 + nCnt].pos.z);

		D3DXVec3Cross(&out, &V22, &V23);
		D3DXVECTOR3 N4;
		D3DXVec3Normalize(&N4, &out);

		D3DXVECTOR3 N2;
		D3DXVec3Normalize(&N2, &(N1 + N2));

		D3DXVECTOR3 N3;
		D3DXVec3Normalize(&N3, &(N1 + N2));

		pVtx[nCnt].nor = N1;
		pVtx[nCnt + 1].nor = N2;
		pVtx[nCnt + 2].nor = N3;
		pVtx[nCnt + 3].nor = N4;

	}

	for (int nCnt = 0; nCnt < m_nMeshFieldVerTexNum; nCnt++){
		pVtx[nCnt].col = COLOR_WHITE;
	}

	m_pVtxBufferMeshField->Unlock();

	EditField();
}
/*******************************************************************************
* �֐���:void COrregularityField::Draw()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	scene�N���X�̕`�揈��
*
*************************************S******************************************/
void CIrregularityField::Draw(){
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
	pDevice->SetTexture(0, CTexture::Get("data\\TEXTURE\\sand.jpg"));

	//�C���f�b�N�X�o�b�t�@���o�C���h
	pDevice->SetIndices(m_pIndexBufferField);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMeshFieldVerTexNum, 0, m_nMeshFieldPolygonNum);
}
/*******************************************************************************
* �֐���:CIrregularityField Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col)
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	CIrregularityField�N���X�̐�������
*
*******************************************************************************/
CIrregularityField *CIrregularityField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col){
	CIrregularityField *scene;
	scene = new CIrregularityField(pos, rot, pFileName, col);
	return scene;
}

// �X�N���[�����W�����[���h���W�ɕϊ�
D3DXVECTOR3* CIrregularityField::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // �X�N���[��X���W
	int Sy,  // �X�N���[��Y���W
	float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	) {
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// �t�ϊ�
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3(Sx, Sy, fZ), &tmp);

	return pout;
}
// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
D3DXVECTOR3* CIrregularityField::CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	) {
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld(&nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj);
	CalcScreenToWorld(&farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj);
	ray = farpos - nearpos;
	D3DXVec3Normalize(&ray, &ray);


	return pout;
}
