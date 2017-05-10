/****************************************************************************
* �^�C�g��:  stageLoader
* �t�@�C����:stageLoader.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/11/4
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include <fstream>
#include <algorithm>
#include"stage.h"
#include"split.h"
#include"sceneXFile.h"
#include"enemy.h"
#include"sound.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
std::list<int> CStage::objectList[3];
float CStage::goalPosition;

bool CStage::load(std::string fileName){
	std::ifstream ifs(fileName);
	std::string str;
	int nInfoCnt = 0;
	while (std::getline(ifs, str)){
		// split�����s���܂��B
		std::list<std::string> strList = split(str, ",");

		// �C�e���[�^���擾���܂��B
		std::list<std::string>::iterator iter = strList.begin();

		std::stoi(*iter);

		objectList[0].push_back(std::stoi(*iter));

		// �P����ɐi��
		++iter;

		objectList[1].push_back(std::stoi(*iter));

		// �P����ɐi��
		++iter;

		objectList[2].push_back(std::stoi(*iter));

		nInfoCnt++;
	}
	return true;
}
void CStage::create(){
	CSceneXFile::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\field.x");
	for (int i = 0; i < 3; i++){
		auto iter = objectList[i].begin();
		for (int j = 0; j < objectList[i].size(); j++){
			if (*iter == 1){
				CEnemyStandard *enemy = CEnemyStandard::Create(D3DXVECTOR3(-60.0f + i * 60, 0.0f, -j * 500.0f - 800.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));
				CEnemy::enemyList.push_back(enemy);
			}
			if (*iter == 2){
				CEnemyLv1*enemy = CEnemyLv1::Create(D3DXVECTOR3(-60.0f + i * 60, 0.0f, -j * 500.0f - 800.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));
				CEnemy::enemyList.push_back(enemy);
			}
			if (*iter == 3){
				CEnemyFly*enemy = CEnemyFly::Create(D3DXVECTOR3(-60.0f + i * 60, 75.0f, -j * 500.0f - 800.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));
				CEnemy::enemyList.push_back(enemy);
			}
			if (*iter == 4){
				CEnemyBoss*enemy = CEnemyBoss::Create(D3DXVECTOR3(-60.0f + i * 60, 300.0f, -j * 500.0f - 800.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));
				CEnemy::enemyList.push_back(enemy);
			}
			iter++;
		}
	}
}