/****************************************************************************
* �^�C�g��:  renderer�w�b�_�[
* �t�@�C����:rendere.h
* �쐬�ҁF	 �F���n
* �쐬���F   2016/04/18
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _RENDERER_H_
#define _RENDERER_H_

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "xaudio2.h"
#include "d3dx9.h"//�`�揈���p
#include "texture.h"
/*******************************************************************************
* ���C�u�����̃����N
*******************************************************************************/
#pragma comment(lib, "d3d9.lib")//�`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")//��L�̊g�����C�u����
#pragma comment(lib, "dxguid.lib")//DirectX�R���|�[�l���g�g�p���ɕK�v
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D_TEX2	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2)
/*******************************************************************************
* �\���̂̒�`
*******************************************************************************/
typedef struct{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p�W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;
typedef struct{
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 nor;//�@�����W
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
	D3DXVECTOR2 tex2;//�e�N�X�`�����W
}VERTEX_3D_TEX2;
typedef struct {
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 nor;//�@�����W
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_3D;
/*******************************************************************************
* �N���X�̒�`
*******************************************************************************/
class CScene;
//�����_���[�N���X
class CRenderer{
public:
	CRenderer(){};
	~CRenderer(){};										//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//������
	void	Uninit();									//�I��
	void	Update();									//�X�V
	void	Draw();										//�`��
	static	LPDIRECT3DDEVICE9		GetDevice();		//�f�o�C�X�̎擾
	void							DrawBegin();
	void							DrawEnd();
private:
	LPDIRECT3D9						m_pD3D;				//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	static	LPDIRECT3DDEVICE9		m_pD3DDevice;		//Direct3D�f�o�C�X�ւ̃|�C���^
	void							RecoverDevice(IDirect3DDevice9 *g_pD3DDev, D3DPRESENT_PARAMETERS &d3dpp);
};
#endif