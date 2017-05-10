/****************************************************************************
* タイトル:  IrregularityFieldヘッダー
* ファイル名:IrregularityField.h
* 作成者：	 芳崎大地
* 作成日：   2016/05/23
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _IRREGULARITY_FIELD_H_
#define _IRREGULARITY_FIELD_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"main.h"
#include"scene.h"
/*******************************************************************************
* マクロ定義
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
		int Sx,  // スクリーンX座標
		int Sy,  // スクリーンY座標
		float fZ,  // 射影空間でのZ値（0～1）
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

	LPDIRECT3DVERTEXBUFFER9	m_pVtxBufferMeshField;		//フィールド用バッファー
	LPDIRECT3DINDEXBUFFER9	m_pIndexBufferField;		//インデックスバッファーへのポインタ

	D3DXVECTOR3				m_posMeshField;				//フィールドの位置
	D3DXVECTOR3				m_rotMeshField;				//フィールドの向き
	D3DXVECTOR3				m_sclMeshField;				//フィールドのスケール

	D3DXCOLOR m_choiceCol;

	float m_fHeightCopy;

	void EditField();
	float fEditRange;
	void SetEditGui();

	int m_nFieldNumX;								//横向きに対しての往復回数
	int m_nFieldNumZ;								//縦向きに対しての往復回数
	int m_nMeshFieldPolygonNum;						//ポリゴン数
	int m_nMeshFieldVerTexNum;                      //頂点数
	int m_nIdxMeshFieldNum;                         //インデックス数
	float m_fBlockSizeX;							//1ブロックの横向きの大きさ
	float m_fBlockSizeZ;							//1ブロックの縦向きの大きさ
	float m_fFieldSizeX;							//フィールドの横向きの大きさ
	float m_fFieldSizeZ;							//フィールドの縦向きの大きさ
	char *m_pFileName;
};
#endif