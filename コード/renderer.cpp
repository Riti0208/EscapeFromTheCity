/****************************************************************************
* �^�C�g��:  DirectX�֌W�̏���
* �t�@�C����:renderer.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/04/18
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"renderer.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
LPDIRECT3DDEVICE9 CRenderer::m_pD3DDevice;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
/*******************************************************************************
* �֐���:HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd)
*
* ����:  HINSTANCE hInstance, HWND hWnd
* �߂�l:S_OK, E_FAILE
* ����	DirectX�֌W�̏���������
*
*******************************************************************************/
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd){
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);			//Direct3D�I�u�W�F�N�g�̐���
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		return E_FAIL;
	}

	//----------------------------------------------------------------------------------------------
	//D3DPRESENT_PARAMETERS�\���� d3dpp�̐ݒ�
	//----------------------------------------------------------------------------------------------
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;						//��ʂ̕�
	d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;						//��ʂ̍���
	d3dpp.BackBufferFormat = d3ddm.Format;						//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//�o�b�t�@�̐؂�ւ����@�̒��
	d3dpp.EnableAutoDepthStencil = TRUE;						//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@�̐���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					//�f�v�X�o�b�t�@�Ƃ���16�r�b�g���g�p
	d3dpp.Windowed = true;									//�E�B���h�E���[�h�ƃX�N���[�����[�h�̎w��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//�t���X�N���[���ł̃��t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�X���b�v(�o�b�t�@�̐؂�ւ�)�̏��������^�C�~���O

	//------------------------------------------------------------------------
	//Direct3D�f�o�C�X�̐���(�`�揈���F�n�[�h�E�F�A�A���_�����F�n�[�h�E�F�A)
	//------------------------------------------------------------------------
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,									//�`�揈�����n�[�h�E�F�A�ɏ���������
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,			//���_�������n�[�h�E�F�A�ɏ���������
		&d3dpp,
		&m_pD3DDevice))){
		//------------------------------------------------------------------------
		//Direct3D�f�o�C�X�̐���(�`�揈���F�n�[�h�E�F�A�A���_�����F�\�t�g�E�F�A)
		//------------------------------------------------------------------------
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,								//�`�揈�����n�[�h�E�F�A�ɏ���������
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,		//���_�������\�t�g�E�F�A�ɏ���������
			&d3dpp,
			&m_pD3DDevice))){
			//------------------------------------------------------------------------
			//Direct3D�f�o�C�X�̐���(�`�揈���F�\�t�g�E�F�A�A���_�����F�\�t�g�E�F�A)
			//------------------------------------------------------------------------
			if (FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,							//�`�揈�����\�t�g�E�F�A�ɏ���������
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//���_�������\�t�g�E�F�A�ɏ���������
				&d3dpp,
				&m_pD3DDevice))){
				return E_FAIL;//���s�����ꍇ
			}
		}
	}
	//----------------------------------------------------------------------------------------------
	//�����_�[�X�e�[�g�̐ݒ�
	//----------------------------------------------------------------------------------------------
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//�J�����O�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//�������̕s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�]�����̃u�����f�B���O�W���̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�]����̃u�����f�B�����W���̐ݒ�

	//----------------------------------------------------------------------------------------------
	//�T���v���[�X�e�[�g�̐ݒ�
	//----------------------------------------------------------------------------------------------
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);

	//----------------------------------------------------------------------------------------------
	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//----------------------------------------------------------------------------------------------

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//----------------------------------------------------------------------------------------------
	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//----------------------------------------------------------------------------------------------
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	return S_OK;
}
/*******************************************************************************
* �֐���:void CRenderer::Uninit()
*
* ����:  void,�Ȃ�
* �߂�l:void,�Ȃ�
* ���� DirectX�֌W�̏I������
*
*******************************************************************************/
void CRenderer::Uninit(){
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
}
/*******************************************************************************
* �֐���:void CRenderer::Update()
*
* ����:  void,�Ȃ�
* �߂�l:void,�Ȃ�
* ���� DirectX�֌W�̍X�V����
*
*******************************************************************************/
void CRenderer::Update(){
}
void CRenderer::DrawBegin(){
	//�w�i�F���w�肵�ăN���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(256, 256, 256, 256), 1.0f, 0);
	//�`��J�n
	m_pD3DDevice->BeginScene();
}
void CRenderer::DrawEnd(){
	//�`��I��
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
/*******************************************************************************
* �֐���:void CRenderer::Draw()
*
* ����:  void,�Ȃ�
* �߂�l:void,�Ȃ�
* ���� DirectX�֌W�̕`�揈��
*
*******************************************************************************/
void CRenderer::Draw(){
}
/*******************************************************************************
* �֐���:LPDIRECT3DDEVICE9 GetDevice()
*
* ����:  void,�Ȃ�
* �߂�l:g_pD3DDevice
* ���� g_pD3DDevice�̃Q�b�^�[
*
*******************************************************************************/
LPDIRECT3DDEVICE9 CRenderer::GetDevice(){
	return m_pD3DDevice;//�|�C���^��n��
}