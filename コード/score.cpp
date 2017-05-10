/****************************************************************************
* タイトル:  GUIの処理
* ファイル名:score.cpp
* 作成者：	 芳崎大地
* 作成日：   2016/05/13
*******************************************************************************/
/*******************************************************************************
* 更新履歴：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include"manager.h"
#include"score.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* グローバル変数
*******************************************************************************/
/*******************************************************************************
* 関数名:CScore::CScore(D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName)
*
* 引数: D3DXVECTOR3 pos, float fWidth, float fHeight, char *pFileName
* 戻り値:	なし
* 説明	scoreクラスのコンストラクタ
*
*******************************************************************************/
CScore::CScore(D3DXVECTOR3 pos, float fWidth, float fHeight, int nNum, int nDigit, char* fileName){
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_nScore = nNum;
	m_nDigit = nDigit;
	for (int i = 0; i < m_nDigit; i++)	{
		int num = (int)m_nScore / (int)pow(10.0f, (m_nDigit - 1 - i));
		CNumber* number = CNumber::Create(D3DXVECTOR3(m_pos.x + (fWidth / m_nDigit) * (i + 1), m_pos.y, 0.0f), m_fWidth / m_nDigit, m_fHeight, fileName, num);
		m_vecNum.push_back(number);
	}
	Init();
}
/*******************************************************************************
* 関数名:void CScore::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	scoreクラスの初期化処理
*
*******************************************************************************/
void CScore::Init(){
}
/*******************************************************************************
* 関数名:void CScore::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	scoreクラスの終了処理
*
*******************************************************************************/
void CScore::Uninit(){
	std::for_each(m_vecNum.begin(), m_vecNum.end(), [&](CNumber *number){
		delete number;
		number = NULL;
	});
	m_vecNum.empty();
}
/*******************************************************************************
* 関数名:void CScore::Update()
*WW
* 引数:  void、なし
* 戻り値:void、なし
* 説明	scoreクラスの更新処理
*
*******************************************************************************/
void CScore::Update(){
	for (int i = 0; i < m_nDigit; i++)	{
		int num = (int)(m_nScore / pow(10.0f, (m_nDigit - 1 - i)));
		m_vecNum[i]->SetNum(num);
	}
}
/*******************************************************************************
* 関数名:void CScore::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	scoreクラスの描画処理
*
*******************************************************************************/
void CScore::Draw(){
}
CScore *CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nNum, int nDidit, char* fileName){
	CScore *scene;
	scene = new CScore(pos, fWidth, fHeight, nNum, nDidit, fileName);
	return scene;
}