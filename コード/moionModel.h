/****************************************************************************
* �^�C�g��:  texture.cpp�̃w�b�_�[
* �t�@�C����:texture.h
* �쐬�ҁF	 �F���n
* �쐬���F   2015/2/18
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _PlAYER_MODEL_H_
#define _PlAYER_MODEL_H_
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include"renderer.h"
#include"scene.h"
#include"model.h"
#include<vector>
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �񋓑̂̒�`
*******************************************************************************/
enum MOTIONTYPE{
	MOTION_TYPE_NEUTRAL = 0,
	MOTION_TYPE_RUN
};
/*******************************************************************************
* �\���̂̒�`
*******************************************************************************/
class KEY{
public:
float PositionX;
float PositionY;
float PositionZ;
float RotationX;
float RotationY;
float RotationZ;
KEY(){
}
	KEY(float posX, float posY, float posZ, float rotX, float rotY, float rotZ){
		PositionX = posX;
		PositionY = posY;
		PositionZ = posZ;
		RotationX = rotX;
		RotationY = rotY;
		RotationZ = rotZ;
	}
	void SetPositon(float posX, float posY, float posZ){
		PositionX = posX;
		PositionY = posY;
		PositionZ = posZ;
	}
	void SetRotation(float rotX, float rotY, float rotZ){
		RotationX = rotX;
		RotationY = rotY;
		RotationZ = rotZ;
	}
};

typedef struct{
	int Frame;
	std::vector<KEY> keyVec;
}KEY_INFO;
typedef struct{
	std::vector <KEY_INFO> kiVec;
	bool isLoop;
	int  numKey;
}MOTION_INFO;
/*******************************************************************************
* �N���X�̒�`
*******************************************************************************/
class CMotionModel{
public:
	CMotionModel::CMotionModel(char *modelName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotionModel *parent);
	~CMotionModel(){};
	void Init();
	void Uninit();
	void Draw();
	void Update();
	D3DXMATRIX GetWorldMatrix(){ return m_worldMatrix; }
	static CMotionModel *Create(char *modelName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotionModel *parent){
		CMotionModel *model = new CMotionModel(modelName, pos, rot, parent);
		return model;
	};
	void SetParent(CMotionModel *parent){ m_Parent = parent; }
	void SetPosition(D3DXVECTOR3 position){ m_Position = position; }
	void SetRotation(D3DXVECTOR3 rotation){ m_Rotation = rotation; }
private:
	LPD3DXMESH m_Mesh;
	D3DXMATRIX m_worldMatrix;
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	MODEL_INFO m_modelInfo;
	MODEL_INFO m_defaultModelInfo;
	CMotionModel *m_Parent;

};

class CPlayerModel : public CScene{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetMotion(int motionIndex);
	void UpdateMotion();
	CPlayerModel(char *fileName, int motionIndex, D3DXVECTOR3 pos);
	~CPlayerModel(){};
	static CPlayerModel *Create(char *fileName, int motionIndex, D3DXVECTOR3 pos);

private:
	std::vector<CMotionModel*> m_modelVec;
	D3DXMATRIX	m_worldMatrix;
	MOTIONTYPE	m_motionType;
	int			m_motionIndex;
	KEY_INFO	*m_KeyInfo;
	int			m_NumKey;
	int			m_Key;
	int			m_Frame;						//�����t���[���ڂ����Ǘ�
	char		*m_motionFileName;
	std::vector<MOTION_INFO> miVec;
};

#endif