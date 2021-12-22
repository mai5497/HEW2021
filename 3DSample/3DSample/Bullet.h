#ifndef __BULLET_H__
#define __BULLET_H__


#include "CharacterBase.h"
#include "Collision.h"

class Bullet : public CharacterBase
{
public:
	Bullet(DirectX::XMFLOAT3 size);
	virtual ~Bullet();


	virtual void OnCollision(GameObject*);
	

	virtual void Update();

	void SetRB(bool flg);	// �������e���Ԃ����Z�b�g����
	bool GetRB();
	void SetColFlg(bool flg);	// �����蔻��t���O�Z�b�g
	bool GetColFlg();


private:
	
	int m_sleep;
	int m_sleep2;

	bool m_rbFlg;	// true�@���@��			false�@���@��
	bool m_ColFlg;	// true�@���@�ڂ��Ă���		false �� �ڂ��Ă��Ȃ�

	Collision *m_pCollision;
};


#endif