#include"stensilShadow.h"
stensilShadow::stensilShadow(D3DXVECTOR3 pos){
	m_pos = pos; 
	Init();
}
stensilShadow::~stensilShadow(){
	SAFE_RELEASE(m_bufferPolygon)
}
void stensilShadow::Init(){

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

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�������W�ݒ�

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�F�̐ݒ�

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =

		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);


	//UV���W�̐ݒ�

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	m_bufferPolygon->Unlock();

	m_modelInfo = CModel::Get("data\\MODEL\\cylinder.x");
	m_mesh = m_modelInfo.m_mesh;
	m_defaultModelInfo = m_modelInfo;
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
void stensilShadow::Uninit(){}
void stensilShadow::Update(){
	VERTEX_2D *pVtx;

	//�ʒu���̐ݒ�

	m_bufferPolygon->Lock(0, 0, (void **)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//���_�F�̐ݒ�

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =

		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	m_bufferPolygon->Unlock();
}
void stensilShadow::Draw(){
	auto device = CRenderer::GetDevice();
	device->SetTexture(0, NULL);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	device->SetRenderState(D3DRS_STENCILREF, 1);
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	device->SetRenderState(D3DRS_FOGENABLE, false);

	//�f�o�C�X�̃|�C���^�������Ă���
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	D3DXMATRIX	mtxScl, mtxRot, mtxTrans;	//�g�k�A��]�A�ړ��p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_world);
	//�X�P�[���̔��f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxScl);
	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0, 0, 0);
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

	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//�����O���[�v�̐�����DrawSubset���Ă�
	for (unsigned int i = 0; i < (int)m_modelInfo.m_numMaterial; i++) {
		pDevice->SetMaterial(&m_modelInfo.m_mat[i]);
		pDevice->SetTexture(0, CTexture::Get(m_modelInfo.m_textureName[i]));
		m_modelInfo.m_mesh->DrawSubset(i);
	}

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);

	device->SetStreamSource(0, m_bufferPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	device->SetTexture(0, CTexture::Get(""));

	//�|���S���̕`��
	device->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);

	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	float FogStart = 900.0f, FogEnd = 3000.0f;

	device->SetRenderState(D3DRS_FOGENABLE, TRUE); // �t�H�O�L��
	device->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f)); // �t�H�O�F
	device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR); // �o�[�e�b�N�X�t�H�O
	device->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE); // �͈̓x�[�X�̃t�H�O
	device->SetRenderState(D3DRS_FOGSTART, *((DWORD*)(&FogStart))); // �t�H�O�J�n�_
	device->SetRenderState(D3DRS_FOGEND, *((DWORD*)(&FogEnd))); // �t�H�O�I���_
}
stensilShadow *Create(D3DXVECTOR3 pos){
	stensilShadow *scene;
	scene = new stensilShadow(pos); 
	return scene;
}