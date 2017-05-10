/****************************************************************************
* �^�C�g��:  �e�N�X�`���Ǘ��N���X�̏���
* �t�@�C����:texture.cpp
* �쐬�ҁF	 �F���n
* �쐬���F   2016/04/11
*******************************************************************************/
/*******************************************************************************
* �X�V�����F
*
*******************************************************************************/

#define _NOT_CPP14_

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/

#include"texture.h"
#ifndef _NOT_CPP14_
#include <filesystem>
#endif
#ifndef _CPP14_
#include<stdexcept>
#endif
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �\���̂̒�`
*******************************************************************************/
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
std::vector<std::string> get_file_path_in_dir(const std::string& dir_name);
/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
std::vector<LPDIRECT3DTEXTURE9> CTexture::vecTexture;
std::vector<std::string>		CTexture::textureName;
int								CTexture::textureCnt;
/*******************************************************************************
* �֐���:HRESULT CTexture::Create()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ����	�w��f�B���N�g���ɂ���S�Ẳ摜����e�N�X�`���̈ꊇ����
*
*******************************************************************************/
HRESULT CTexture::Create(){
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	LPDIRECT3DTEXTURE9 texture;

	std::vector<std::string> file_list = get_file_path_in_dir("data/TEXTURE");

#ifndef _NOT_CPP14_

	// �J�����g�f�B���N�g���ȉ��̃t�@�C�������擾����
	// �ċA�I�Ƀt�@�C�������擾����ꍇ�́Astd::tr2::sys::recursive_directory_iterator���g��
	for (std::tr2::sys::directory_iterator it("data/TEXTURE"), end; it != end; ++it) {
		file_list.push_back(it->path());
	}
#endif

	for (auto itr = file_list.begin(); itr != file_list.end(); ++itr) {
		std::string fileName = *itr;

		fileName = "data\\TEXTURE\\" + fileName;

		//�e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice,					//�f�o�C�X
			fileName.c_str(),			//�t�@�C����
			&texture					//�e�N�X�`���̃|�C���^
			))){
			return E_FAIL;
		}

		vecTexture.push_back(texture);
		textureName.push_back(fileName);

		texture = NULL;
		fileName = "";
	}

	return S_OK;
}
/*******************************************************************************
* �֐���:LPDIRECT3DTEXTURE9 CTexture::Get(std::string fileName)
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ����	�e�N�X�`���̎擾
*
*******************************************************************************/
LPDIRECT3DTEXTURE9 CTexture::Get(std::string fileName){
	auto iter = std::find(textureName.begin(), textureName.end(), fileName);
	if (iter != textureName.end()){
		std::string a = *iter;
		int index = std::distance(textureName.begin(), iter);
		return vecTexture[index];
	}
	return NULL;
}
/*******************************************************************************
* �֐���:LPDIRECT3DTEXTURE9 CTexture::Get(std::string fileName)
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ����	�e�N�X�`���̎擾
*
*******************************************************************************/
LPDIRECT3DTEXTURE9 CTexture::Get(int null){
	return NULL;
}
/*******************************************************************************
* �֐���:void CTexture::Release()
*
* ����:  �Ȃ�
* �߂�l:�Ȃ�
* ����	�e�N�X�`���̊J��
*
*******************************************************************************/
void CTexture::Release(){
	for (auto iter = vecTexture.begin(); iter != vecTexture.end(); ++iter){
		size_t index = std::distance(vecTexture.begin(), iter);
		if (vecTexture[index] != NULL){
			vecTexture[index]->Release();
			vecTexture[index] = NULL;
		}
	}
}
/*******************************************************************************
* �֐���:std::vector<std::string> get_file_path_in_dir(const std::string& dir_name)
*
* ����:  �t�H���_���̎w��
* �߂�l:�Ȃ�
* ����	�w�肵���f�B���N�g������t�@�C���������ׂĎ擾
*
*******************************************************************************/
std::vector<std::string> get_file_path_in_dir(const std::string& dir_name){
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;//defined at Windwos.h
	std::vector<std::string> file_names;

	//�g���q�̐ݒ�
	std::string search_name = dir_name + "\\*";

	hFind = FindFirstFile(search_name.c_str(), &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file not found");
	}

	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			file_names.push_back(win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);

	return file_names;
}