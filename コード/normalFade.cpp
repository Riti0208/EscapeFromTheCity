/****************************************************************************
* �^�C�g��:  �t�F�[�h�̏���
* �t�@�C����:fade.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2015/07/06
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"fade.h"
#include"normalFade.h"
#include"mode.h"
#include"input.h"
#include"debugProc.h"
#include"scene2D.h"
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
* �֐���:CNormalFade::CNormalFade()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �m�[�}���t�F�[�h�̃R���X�g���N�^
*
*******************************************************************************/
CNormalFade::CNormalFade(){
}
/*******************************************************************************
* �֐���:CNormalFade::CNormalFade()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �m�[�}���t�F�[�h�̃f�X�g���N�^
*
*******************************************************************************/
CNormalFade::~CNormalFade(){
	Uninit();
}
/*******************************************************************************
* �֐���:void CNormalFade::Init()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �m�[�}���t�F�[�h�̏���������
*
*******************************************************************************/
void CNormalFade::Init(){
	m_currentFadeState = FADE_OUT;
	m_nVertexNum = 4;
	m_bFinish = false;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_buffer,
			NULL
			);

		VERTEX_2D *pVtx;

		m_buffer->Lock(0, 0, (void **)&pVtx, 0);

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
			pVtx[3].col = m_col;

		//UV���W�̐ݒ�

		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

		m_buffer->Unlock();
	}
/*******************************************************************************
* �֐���:void CNormalFade::Uninit()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �m�[�}���t�F�[�h�̏I������
*
*******************************************************************************/
void CNormalFade::Uninit(){
}
/*******************************************************************************
* �֐���:void CNormalFade::Update()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �m�[�}���t�F�[�h�̍X�V����
*
*******************************************************************************/
void CNormalFade::Update(){
	m_col;
	if (m_currentFadeState == FADE_OUT){
		m_col.a += 0.1f * m_fFadeSpeed;
		if (m_col.a >= 1.0f){
			m_col.a = 1.0f;
			m_currentFadeState = FADE_IN;
			m_bChangeMode = true;
		}
	}
	else if (m_currentFadeState == FADE_IN){
		m_bChangeMode = false;
		m_col.a -= 0.1f * m_fFadeSpeed;
		if (m_col.a <= 0.0f){
			m_col.a = 0.0f;
			m_bFinish = true;
		}
	}

	VERTEX_2D *pVtx;

	m_buffer->Lock(0, 0, (void **)&pVtx, 0);

	//���_�F�̐ݒ�

	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_col;

	m_buffer->Unlock();

}
/*******************************************************************************
* �֐���:void CNormalFade::Draw()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ���� �m�[�}���t�F�[�h�̕`�揈��
*
*******************************************************************************/
void CNormalFade::Draw(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	pDevice->SetStreamSource(0, m_buffer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::Get(""));

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2
		);
}