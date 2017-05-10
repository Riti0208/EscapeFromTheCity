#ifndef _RULE_H_
#define _RULE_H_

#include"manager.h"
class CPlayer;
class CScore;
class ruleManager{
private:
	static CPlayer *onep;
	static CPlayer *twop;
	static int nTime;
	static CScore *timeScore;
	static int nTimeCnt;
public:

	static void Init();
	static void Uninit();
	static void Update();
};
#endif