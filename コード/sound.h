//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include <xaudio2.h>
//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_FOOT_SOUND_0 = 0,		//足音
	SOUND_LABEL_FOOT_SOUND_1,		//足音
	SOUND_LABEL_EXPLOSION_SOUND_0,		//爆発
	SOUND_LABEL_MISSILE_SOUND_0,
	BGM_LABEL_TITLE_0,
	BGM_LABEL_BATTLE_0,
	BGM_LABEL_BOSS_0,
	BGM_LABEL_RESULT_0,
	SOUND_LABEL_BEAM_SOUND_0,
	SOUND_LABEL_KEIHOU_SOUND_0,
	SOUND_LABEL_BOOST_SOUND_0,
	SOUND_LABEL_MAX,
} SOUND_LABEL;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
