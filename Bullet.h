#ifndef __BULLET_H__
#define __BULLET_H__


#include "CharacterBase.h"
#include "Collision.h"

// ---���f���`��p�̒ǉ�
#include	"FBX/FBXPlayer.h"
#include	"DrawBuffer.h"


class Bullet : public CharacterBase
{
public:
	
	// ---4�又���֐�
	Bullet(DirectX::XMFLOAT3 size);
	virtual ~Bullet();
	bool Init();
	virtual void Uninit();
	virtual void Update();
	//virtual void Draw();
	void Draw();

	// ---�����蔻�菈��
	virtual void OnCollision(GameObject*);
	void SetColFlg(bool flg);
	//void BulletCollision(bool Setflg);		// �t�B�[���h�Ƃ̓����蔻��

	// ---2�F�̒e�̏���
	void SetRB(bool flg);						// �������e���Ԃ����Z�b�g����
	bool GetRB(); 

	// ---���f���`��p�̒ǉ�
	ID3D11ShaderResourceView* m_pBulletTex;


private:
	// ---�֐�
	bool LoadBullet(const char* pFilePath);		// �@���f���ǂݍ���

	// ---�ϐ�
	int m_sleep;
	int m_sleep2;
	float m_BulletAngle;						// �p�x
	XMFLOAT3 m_dir;								// ����

	bool m_rbFlg;								// true�@���@��			false�@���@��
	bool m_ColFlg;								// true�@���@�ڂ��Ă���		false �� �ڂ��Ă��Ȃ�

	// ---���f���`��֘A
	static DrawBuffer* m_pBuffer;				// �o�b�t�@�N���X
	static FBXPlayer* m_pFBX;					// FBX�t�@�C�����삭�炷
};


#endif