#include"ruleManager.h"
#include"player.h"
#include"effectManager.h"
#include<time.h>
#include<math.h>
CPlayer *ruleManager::onep;
CPlayer *ruleManager::twop;
int		ruleManager::nTime;
int		ruleManager::nTimeCnt;
CScore  *ruleManager::timeScore;
void ruleManager::Init(){
	onep = CPlayer::Create(0);
	twop = CPlayer::Create(1);
	nTime = 300;
}
void ruleManager::Update(){
	nTimeCnt++;
	if (nTimeCnt % 60 == 0)	nTime--;
	if (nTime % 5 == 0){
		//CEffectManager::CreateEffect(L"data\\EFFECT\\stome.efk", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}
void ruleManager::Uninit(){}