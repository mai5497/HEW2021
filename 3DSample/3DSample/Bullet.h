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
	
	// ---�֐�
	Bullet(DirectX::XMFLOAT3 size);
	virtual ~Bullet();
	bool Init();
	void Uninit();

	virtual void OnCollision(GameObject*);
	virtual void Update();
	void SetRB(bool flg);								// �������e���Ԃ����Z�b�g����
	bool GetRB(); 
	void SetColFlg(bool flg);
	void BulletCollision(bool Setflg);				// �t�B�[���h�Ƃ̓����蔻��

	// ---�ϐ�
	// ---���f���`��p�̒ǉ�
	ID3D11ShaderResourceView* m_pBulletTex;

private:
	// ---�֐�
	bool LoadBullet(const char* pFilePath);		// �@���f���ǂݍ���

	// ---�ϐ�
	int m_sleep;
	int m_sleep2;
	bool m_rbFlg;	// true�@���@��			false�@���@��
	bool m_ColFlg;	// true�@���@�ڂ��Ă���		false �� �ڂ��Ă��Ȃ�

	static DrawBuffer* m_pBuffer;					// �o�b�t�@�N���X
	static FBXPlayer* m_pFBX;						// FBX�t�@�C�����삭�炷
};


#endif