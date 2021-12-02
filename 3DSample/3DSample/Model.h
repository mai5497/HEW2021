#ifndef __MODEL_H__
#define __MODEL_H__

#include "DrawBuffer.h"
#include "FBX/FBXPlayer.h"

class Model
{
public:
	Model();
	~Model();

	bool LoadModel(const char* pFilePath);
	void Draw();

private:
	//�Q�[���̃L�����N�^�[�͕����̃p�[�c�Ő��藧���Ă���B
	//���̃p�[�c�������b�V���ƌĂԁB
	//��{�I�Ɉ�̃��b�V���ň�̒��_�o�b�t�@������
	//���f�����ƂɃ��b�V���̐����قȂ邽�߁A
	//���_�o�b�t�@�𓮓I�Ɋm�ۂ���
	DrawBuffer* m_pBuffer;

	FBXPlayer m_fbx;	//FBX�t�@�C������N���X
};

#endif	//__MODEL_H__