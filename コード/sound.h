//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include <xaudio2.h>
//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_FOOT_SOUND_0 = 0,		//����
	SOUND_LABEL_FOOT_SOUND_1,		//����
	SOUND_LABEL_EXPLOSION_SOUND_0,		//����
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
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
