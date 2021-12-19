#ifndef __BULLET_H__
#define __BULLET_H__


#include "CharacterBase.h"


class Bullet : public CharacterBase
{
public:
	Bullet(DirectX::XMFLOAT3 size);
	virtual ~Bullet();


	virtual void OnCollision(GameObject*);
	

	virtual void Update();

	void SetRB(bool flg);	// �������e���Ԃ����Z�b�g����
	bool GetRB();
private:

	int m_sleep;
	int m_sleep2;

	bool m_rbFlg;	// true�Ȃ��false�Ȃ��
};


#endif