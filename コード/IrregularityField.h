/****************************************************************************
* �^�C�g��:  IrregularityField�w�b�_�[
* �t�@�C����:IrregularityField.h
* �쐬�ҁF	 �F���n
* �쐬���F   2016/05/23
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _IRREGULARITY_FIELD_H_
#define _IRREGULARITY_FIELD_

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"main.h"
#include"scene.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
class CSceneBillboard;
class CButton;
class CGui;
class CNumAndArrow;
class CIrregularityField : CScene{
public:
	CIrregularityField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col){ m_pos = pos, m_rot = rot, m_pFileName = pFileName, m_col = col, Init(); };
	~CIrregularityField(){ Uninit(); };
	void Init();
	void Uninit();
	void Update();
	void Draw();
	float *GetHeight(D3DXVECTOR3 *pos);
	float playerYPosUpdate(D3DXVECTOR3 *pos, D3DXVECTOR3 _pos, D3DXVECTOR3 nor);
	D3DXVECTOR3 *CalcScreenToWorld(D3DXVECTOR3* pout,
		int Sx,  // �X�N���[��X���W
		int Sy,  // �X�N���[��Y���W
		float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj);
	D3DXVECTOR3 *CalcScreenToXZ(D3DXVECTOR3* pout,
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj);
	static CIrregularityField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXCOLOR col);
private:

	void save();
	void load();

	LPDIRECT3DVERTEXBUFFER9	m_pVtxBufferMeshField;		//�t�B�[���h�p�o�b�t�@�[
	LPDIRECT3DINDEXBUFFER9	m_pIndexBufferField;		//�C���f�b�N�X�o�b�t�@�[�ւ̃|�C���^

	D3DXVECTOR3				m_posMeshField;				//�t�B�[���h�̈ʒu
	D3DXVECTOR3				m_rotMeshField;				//�t�B�[���h�̌���
	D3DXVECTOR3				m_sclMeshField;				//�t�B�[���h�̃X�P�[��

	D3DXCOLOR m_choiceCol;

	float m_fHeightCopy;

	void EditField();
	float fEditRange;
	void SetEditGui();

	int m_nFieldNumX;								//�������ɑ΂��Ẳ�����
	int m_nFieldNumZ;								//�c�����ɑ΂��Ẳ�����
	int m_nMeshFieldPolygonNum;						//�|���S����
	int m_nMeshFieldVerTexNum;                      //���_��
	int m_nIdxMeshFieldNum;                         //�C���f�b�N�X��
	float m_fBlockSizeX;							//1�u���b�N�̉������̑傫��
	float m_fBlockSizeZ;							//1�u���b�N�̏c�����̑傫��
	float m_fFieldSizeX;							//�t�B�[���h�̉������̑傫��
	float m_fFieldSizeZ;							//�t�B�[���h�̏c�����̑傫��
	char *m_pFileName;
};
#endif