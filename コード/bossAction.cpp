/****************************************************************************
* �^�C�g��: �{�XAI�̏���
* �t�@�C����:scene.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2017/02/12
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"bossAction.h"
#include"bullet.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
/*******************************************************************************
* �֐���:void spreadAttack:update()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	spreadAttack�̍X�V����
*
*******************************************************************************/
bool spreadAttack::update(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot) {
	attackTime++;
	sinCnt++;
	if (attackTime >= 360) {
		attackTime = 0;
		return true;

	}
	for (int i = 0; i < 10; i++) {
		if (180 < attackTime && 360 > attackTime) {
			if (attackTime % 30== 0) {
				auto leftPos = D3DXVECTOR3(pos->x + 40.0f, pos->y, pos->z - 10.0f);
				auto rightPos = D3DXVECTOR3(pos->x - 40.0f, pos->y, pos->z - 10.0f);
				auto leftUpPos = D3DXVECTOR3(pos->x + 30.0f, pos->y + 30.0f, pos->z - 10.0f);
				auto rightUpPos = D3DXVECTOR3(pos->x - 30.0f, pos->y + 30.0f, pos->z - 10.0f);

				CMissileBoss::Create(leftPos, D3DXVECTOR3(D3DX_PI, D3DX_PI * 0.25f, 0.0f + D3DX_PI * 0.5f));
				CMissileBoss::Create(rightPos, D3DXVECTOR3(D3DX_PI, -D3DX_PI * 0.25f, 0.0f + D3DX_PI * 0.5f));
				CMissileBoss::Create(leftUpPos, D3DXVECTOR3(D3DX_PI, D3DX_PI * 0.25f, 0.0f + D3DX_PI * 0.5f));
				CMissileBoss::Create(rightUpPos, D3DXVECTOR3(D3DX_PI, -D3DX_PI * 0.25f, 0.0f + D3DX_PI * 0.5f));

			}
			return false;
		}
		else {
			pos->x = sinf((float)sinCnt / 10) * 75.0f;
			return false;
		}
	}


}
/*******************************************************************************
* �֐���:void concentrationAttack:update()
*
* ����:  void�A�Ȃ�
* �߂�l:void�A�Ȃ�
* ����	concentrationAttack�̍X�V����
*
*******************************************************************************/
bool concentrationAttack::update(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot) {
	attackTime++;
	sinCnt++;
	if (attackTime >= 360) {
		attackTime = 0;
		return true;
	}
	for (int i = 0; i < 10; i++) {
		if (180 < attackTime && 360 > attackTime) {
			if (attackTime % 10 == 0) {
				D3DXVECTOR3 RIGHT_CANON_START(pos->x - sinf(rot->y + (0.3f * D3DX_PI)) * 15.0f, pos->y - 2.5f,pos->z + cosf(rot->y + (0.14f * D3DX_PI)) * 15.0f);
				D3DXVECTOR3 LEFT_CANON_START(pos->x - sinf(rot->y - (0.3f * D3DX_PI)) * 15.0f, pos->y - 2.5f, pos->z + cosf(rot->y - (0.14f * D3DX_PI)) * 15.0f);

				CBulletBoss::Create(RIGHT_CANON_START, *rot);
				CBulletBoss::Create(LEFT_CANON_START, *rot);
			}

			return false;
		}
		else {
			pos->x = sinf((float)sinCnt / 10) * 75.0f;
			return false;
		}
	}
}
/*******************************************************************************
* �֐���:void newtral : update()
*
* ���� : void�A�Ȃ�
* �߂�l : void�A�Ȃ�
* ����	concentrationAttack�̍X�V����
*
*******************************************************************************/
bool newtral::update(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot) {
	attackTime++;
	if (attackTime >= 2000) {
		attackTime = 0;
		return true;
	}
}