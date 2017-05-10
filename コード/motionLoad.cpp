#include"moionModel.h"
#include"model.h"
#include"input.h"
#include"eraceString.h"
#include <fstream>
#include <list>
#include"split.h"
#include"constCharToChar.h"
KEY_INFO g_KeyWalk[] = {
	{ 300,														//FRAME
	{
		{ 0.0f, 50.0f, 0.0f, -0.13f, 0.0f, 0.0f },
		{ -5.0f, 5.0f, 0.0f, 0.88f, 0.0f, D3DX_PI * 0.5f },
		{ 5.0f, 5.0f, 0.0f, 0.88f, 0.0f, -D3DX_PI * 0.5f },
		{ -5.0f, 4.0f, 0.0f, 0.0f, -0.44f, 0.0f },
		{ 5.0f, 4.0f, 0.0f, 0.0f, 1.04f, 0.0f },
		{ -6.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 6.0f, 1.0f, 0.0f, D3DX_PI, 0.0f, 0.0f },
		{ -3.0f, -5.0f, 2.0f, -0.88f, 0.09f, 0.0f },
		{ 3.0f, -5.0f, 2.0f, 0.88f, 0.0f, 0.0f },
		{ -2.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.0f },
		{ 2.0f, -7.0f, -1.0f, -0.66f, 0.0f, 0.0f },
		{ -1.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 1.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 8.0f, 0.0f, 0.28f, 0.0f, 0.0f }
	}

	},
	{ 300,														//FRAME
	{
		{ 0.0f, 50.8f, 0.0f, -0.03f, 0.0f, 0.0f },
		{ -5.0f, 5.0f, 0.0f, -0.88f, 0.0f, D3DX_PI * 0.5f },
		{ 5.0f, 5.0f, 0.0f, 0.88f, -0.26f, -D3DX_PI * 0.5f },
		{ -5.0f, 4.0f, 0.0f, 0.0f, -0.44f, 0.0f },
		{ 5.0f, 4.0f, 0.0f, 0.0f, 1.04f, 0.0f },
		{ -6.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 6.0f, 1.0f, 0.0f, D3DX_PI, 0.0f, 0.0f },
		{ -3.0f, -5.0f, 2.0f, 0.9f, 0.09f, 0.0f },
		{ 3.0f, -5.0f, 2.0f, -0.41f, 0.0f, 0.0f },
		{ -2.0f, -7.0f, -1.0f, 0.25f, 0.0f, 0.0f },
		{ 2.0f, -7.0f, -1.0f, -0.66f, 0.0f, 0.0f },
		{ -1.0f, -5.0f, 0.0f, -0.41f, 0.0f, 0.0f },
		{ 1.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 8.0f, 0.0f, -0.03f, 0.0f, 0.0f }
	}
	}
};
KEY_INFO g_KeyNewtlal[] = {
	{ 100,														//FRAME
	{
		{ 0.0f, 50.0f, 0.0f, -D3DX_PI * 0.15f, 0.0f, 0.0f },
		{ -5.0f, 5.0f, 0.0f, 0.0f, 0.0f, D3DX_PI * 0.5f },
		{ 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, -D3DX_PI * 0.5f },
		{ -5.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 5.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ -6.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 6.0f, 1.0f, 0.0f, D3DX_PI, 0.0f, 0.0f },
		{ -3.0f, -5.0f, 2.0f, 0.0f, 0.0f, 0.0f },
		{ 3.0f, -5.0f, 2.0f, 0.0f, 0.0f, 0.0f },
		{ -2.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.0f },
		{ 2.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.0f },
		{ -1.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 1.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f }
	}
	}
};
KEY_INFO g_KeyShot[] = {
	{ 100,
	{
		{ 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ -5.0f, 5.0f, 0.0f, 0.0f, 0.0f, D3DX_PI * 0.5f },
		{ 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, -D3DX_PI * 0.5f },
		{ -5.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 5.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ -6.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 6.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ -3.0f, -5.0f, 2.0f, 0.0f, 0.0f, 0.0f },
		{ 3.0f, -5.0f, 2.0f, 0.0f, 0.0f, 0.0f },
		{ -2.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.0f },
		{ 2.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.0f },
		{ -1.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 1.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f }
	}
	}
};

/*******************************************************************************
* 関数名:void CMotionModel::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスの初期化処理
*
*******************************************************************************/
void CMotionModel::Init(){
}
/*******************************************************************************
* 関数名:void CMotionModel::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスの終了処理
*
*******************************************************************************/
void CMotionModel::Uninit(){
}
/*******************************************************************************
* 関数名:void CMotionModel::Update()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスの更新処理
*
*******************************************************************************/
void CMotionModel::Update(){
}
/*******************************************************************************
* 関数名:void CMotionModel::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスの描画処理
*
*******************************************************************************/
void CMotionModel::Draw(){

	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	D3DXMATRIX	mtxScl, mtxRot, mtxTrans;	//拡縮、回転、移動用マトリックス

	D3DXMATRIX parentMatrix;

	if (m_Parent != NULL){
		parentMatrix = m_Parent->GetWorldMatrix();
	}
	else{
		pDevice->GetTransform(D3DTS_WORLD, &parentMatrix);
	}

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_worldMatrix);
	//スケールの反映
	D3DXMatrixScaling(&mtxScl, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxScl);
	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxTrans);

	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &parentMatrix);

	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &m_worldMatrix);

	//属性グループの数だけDrawSubsetを呼ぶ
	for (unsigned int i = 0; i < (int)m_modelInfo.m_numMaterial; i++) {
		pDevice->SetMaterial(&m_modelInfo.m_mat[i]);
		pDevice->SetTexture(0, CTexture::Get(m_modelInfo.m_textureName[i]));
		m_modelInfo.m_mesh->DrawSubset(i);
	}
}

/*******************************************************************************
* 関数名:CMotionModel::CMotionModel()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスのコンストラクタ
*
*******************************************************************************/
CMotionModel::CMotionModel(char *modelName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotionModel *parent){
	m_modelInfo = CModel::Get(modelName);
	m_Mesh = m_modelInfo.m_mesh;
	m_defaultModelInfo = m_modelInfo;
	m_Position = pos;
	m_Rotation = rot;
	m_Parent = parent;
}
/*******************************************************************************
* 関数名:void CPlayerModel::Init()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスの初期化処理
*
************************************* ******************************************/
void CPlayerModel::Init(){
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	std::vector<std::string>	modelNameVec;
	std::vector<int>			modelIndex;
	std::vector<D3DXVECTOR3>	modelPos;
	std::vector<D3DXVECTOR3>	modelRot;
	std::vector<int>			parentIndex;

	std::ifstream ifs(m_motionFileName);
	std::string str;
	bool						isPartsSet = false;
	bool						isMotionSet = false;
	bool						isKeySet = false;
	int							keyCnt = 0;
	MOTION_INFO					mi;
	KEY_INFO					ki;

	int nInfoCnt = 0;

	while (std::getline(ifs, str)){
		if (str.find("PARTSSET") != str.npos){
			isPartsSet = true;
		}
		if (str.find("END_PARTSSET") != str.npos){
			isPartsSet = false;
		}
		if (str.find("MODEL_FILENAME = ") != str.npos){
			eraseString(str, "MODEL_FILENAME = ");
			backEraseString(str, "	");
			modelNameVec.push_back(str);
		}
		if (isPartsSet){
			if (str.find("INDEX = ") != str.npos){
				eraseString(str, "		");
				eraseString(str, "INDEX = ");
				backEraseString(str, "	");
				modelIndex.push_back(std::stoi(str));
			}
			if (str.find("PARENT = ") != str.npos){
				eraseString(str, "		");
				eraseString(str, "PARENT = ");
				backEraseString(str, "	");
				parentIndex.push_back(std::stoi(str));
			}
			if (str.find("POS = ") != str.npos){
				eraseString(str, "		");
				eraseString(str, "POS = ");
				backEraseString(str, "	");
				std::list<std::string> strList = split(str, " ");
				auto iter = strList.begin();

				float x = std::stof(*iter);
				iter++;
				float y = std::stof(*iter);
				iter++;
				float z = std::stof(*iter);

				D3DXVECTOR3 vec = D3DXVECTOR3(x, y, z);
				modelPos.push_back(vec);
			}
			if (str.find("ROT = ") != str.npos){
				eraseString(str, "		");
				eraseString(str, "ROT = ");
				backEraseString(str, "	");
				std::list<std::string> strList = split(str, " ");
				auto iter = strList.begin();

				float x = std::stof(*iter);
				iter++;
				float y = std::stof(*iter);
				iter++;
				float z = std::stof(*iter);

				D3DXVECTOR3 vec = D3DXVECTOR3(x, y, z);
				modelRot.push_back(vec);
			}
		}

		if (str.find("MOTIONSET") != str.npos){
			isMotionSet = true;
		}
		if (str.find("END_MOTIONSET") != str.npos){
			isMotionSet = false;
		}
		if (str.find("LOOP = ") != str.npos){
			eraseString(str, "	");
			eraseString(str, "LOOP = ");
			backEraseString(str, "#");
			if (std::stoi(str) == 1){
				mi.isLoop = true;
			}
			else{
				mi.isLoop = false;
			}
		}
		if (str.find("NUM_KEY =") != str.npos){
			eraseString(str, "	");
			eraseString(str, "NUM_KEY =");
			backEraseString(str, "#");
			mi.numKey = std::stoi(str);
		}

		if (str.find("KEYSET") != str.npos){
			isKeySet = true;
			ki.keyVec.resize(modelNameVec.size());
		}
		if (str.find("END_KEYSET") != str.npos){
			isKeySet = false;
			mi.kiVec.push_back(ki);
			if (mi.kiVec.size() == mi.numKey){
				miVec.push_back(mi);
				mi.kiVec.clear();
			}
			keyCnt = 0;
		}
		if (str.find("FRAME = ") != str.npos){
			eraseString(str, "		");
			eraseString(str, "FRAME = ");
			backEraseString(str, "	");
			ki.Frame = std::stoi(str);
		}
		if (str.find("POS = ") != str.npos){
			eraseString(str, "			");
			eraseString(str, "POS = ");
			std::list<std::string> wordList = split(str, " ");
			auto iter = wordList.begin();
			float x, y, z;
			x = std::stof(*iter);
			iter++;
			y = std::stof(*iter);
			iter++;
			z = std::stof(*iter);
			ki.keyVec[keyCnt].SetPositon(x, y, z);
		}
		if (str.find("ROT = ") != str.npos){
			eraseString(str, "			");
			eraseString(str, "ROT = ");
			std::list<std::string> wordList = split(str, " ");
			auto iter = wordList.begin();
			float x, y, z;
			x = std::stof(*iter);
			iter++;
			y = std::stof(*iter);
			iter++;
			z = std::stof(*iter);
			ki.keyVec[keyCnt].SetRotation(x, y, z);
			keyCnt++;
		}
	}

	m_modelVec.resize(modelNameVec.size());

	for (int i = 0; i < modelNameVec.size(); i++){
		if (parentIndex[i] == -1)	parentIndex[i] = NULL;
		m_modelVec[i] = new CMotionModel(ccToc(modelNameVec[i].c_str()), modelPos[i], modelRot[i], m_modelVec[parentIndex[i]]);
	}

	ifs.close();

	SetMotion(MOTION_TYPE_NEUTRAL);

}
/*******************************************************************************
* 関数名:void CPlayerModel::Uninit()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスの終了処理
*
*******************************************************************************/
void CPlayerModel::Uninit(){
	std::for_each(m_modelVec.begin(), m_modelVec.end(), [&](CMotionModel *model){SAFE_DELETE(model)});
	m_modelVec.empty();
}
/*******************************************************************************
* 関数名:void CPlayerModel::Update()d
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスの更新処理
*
*******************************************************************************/
void CPlayerModel::Update(){
	UpdateMotion();
}
/*******************************************************************************
* 関数名:void CPlayerModel::UpdateMotion()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスのモーション更新
*
*******************************************************************************/
void CPlayerModel::UpdateMotion(){
	for (int i = 0; i < m_modelVec.size(); i++){
		KEY *key, *keyNext;
		float rate;
		D3DXVECTOR3 pos, rot;
		key = &m_KeyInfo[m_Key].keyVec[i];
		keyNext = &m_KeyInfo[(m_Key + 1) % m_NumKey].keyVec[i];
		rate = (float)m_Frame / m_KeyInfo[m_Key].Frame;
		pos.x = key->PositionX * (1.0f - rate) + keyNext->PositionX * rate;
		pos.y = key->PositionY * (1.0f - rate) + keyNext->PositionY * rate;
		pos.z = key->PositionZ * (1.0f - rate) + keyNext->PositionZ * rate;

		//回転処理
		rot.x = key->RotationX * (1.0f - rate) + keyNext->RotationX * rate;
		float rotDif = keyNext->RotationX - key->RotationX;
		if (rotDif > D3DX_PI){
			rotDif = 0.0f;
		}
		rot.x = key->RotationX + rotDif * rate;

		rot.y = key->RotationY * (1.0f - rate) + keyNext->RotationY * rate;
		rotDif = keyNext->RotationY - key->RotationY;
		if (rotDif > D3DX_PI){
			rotDif = 0.0f;
		}
		rot.y = key->RotationY + rotDif * rate;
		rot.z = key->RotationZ * (1.0f - rate) + keyNext->RotationZ * rate;
		rotDif = keyNext->RotationZ - key->RotationZ;
		if (rotDif > D3DX_PI){
			rotDif = 0.0f;
		}
		rot.z = key->RotationZ + rotDif * rate;
		m_modelVec[i]->SetPosition(pos);
		m_modelVec[i]->SetRotation(rot);

		m_Frame++;
		if (m_Frame >= m_KeyInfo[m_Key].Frame)
		{
			m_Key = (m_Key + 1) % m_NumKey;			//ループに対応
			m_Frame = 0;
		}
	}
}
/*******************************************************************************
* 関数名:void CPlayerModel::Draw()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスの描画処理
*
*******************************************************************************/
void CPlayerModel::Draw(){
	//デバイスのポインタを持ってくる
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	D3DXMATRIX	mtxScl, mtxRot, mtxTrans;	//拡縮、回転、移動用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_world);
	//スケールの反映
	D3DXMatrixScaling(&mtxScl, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxScl);
	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.z, m_rot.x);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_world, &m_world, &mtxTrans);
	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &m_world);

	std::for_each(m_modelVec.begin(), m_modelVec.end(), [&](CMotionModel *model){ model->Draw(); });
}
/*******************************************************************************
* 関数名:CPlayerModel::CPlayerModel()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスのコンストラクタ
*
*******************************************************************************/
CPlayerModel::CPlayerModel(char *fileName, int motionIndex, D3DXVECTOR3 pos){
	m_pos = pos;
	m_motionIndex = motionIndex;
	m_motionFileName = fileName;
	Init();
}
/*******************************************************************************
* 関数名:CPlayerModel::Create()
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスのコンストラクタ
*
*******************************************************************************/
CPlayerModel *CPlayerModel::Create(char *fileName, int motionIndex, D3DXVECTOR3 pos){
	CPlayerModel *model;
	model = new CPlayerModel(fileName, motionIndex, pos);
	return model;

}
/*******************************************************************************
* 関数名:void CPlayerModel::SetMotion(MOTIONTYPE motionType)
*
* 引数:  void、なし
* 戻り値:void、なし
* 説明	モデルクラスのモーション読み込み
*
*******************************************************************************/
void CPlayerModel::SetMotion(int motionIndex){
	switch (motionIndex){
	case MOTION_TYPE_NEUTRAL:
		m_KeyInfo = g_KeyNewtlal;
		m_NumKey = 1;
		break;

	case MOTION_TYPE_RUN:
		m_KeyInfo = g_KeyWalk;
		m_NumKey = 2;
		break;
	}
	m_Key = 0;
	m_Frame = 0;
	m_motionIndex = motionIndex;
}