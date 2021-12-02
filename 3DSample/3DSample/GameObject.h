#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <DirectXMath.h>
#include "Cube.h"
#include "Shader.h"

//�����蔻������{����Ƃ���
//�I�u�W�F�N�g�̎��
enum ObjectCollisionType
{
	COLLISION_STATIC,	//�Î~���Ă��镨��
	COLLISION_DYNAMIC,	//�����Ă��镨��
	COLLISION_OVERLAP,	//�ђʂ��镨��
	COLLISION_ENEMY,
	COLLISION_PLAYER
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual bool Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void OnCollision(GameObject*) {}
	virtual void PlayerToEnemy(GameObject*) {}
	virtual void CreateObject(DirectX::XMFLOAT3 pos, 
		DirectX::XMFLOAT3 dir, DirectX::XMFLOAT3 move);

	//�l�擾
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetSize();
	DirectX::XMFLOAT3 GetMove();
	DirectX::XMFLOAT3 GetRadius();
	ObjectCollisionType GetCollisionType();

	//�l�ݒ�
	void SetMove(DirectX::XMFLOAT3 move);
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetSize(DirectX::XMFLOAT3 size);
	void SetAngle(DirectX::XMFLOAT3 angle);

	bool use;

private:
protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_size;
	DirectX::XMFLOAT3 m_move;
	DirectX::XMFLOAT3 m_Radius;
	DirectX::XMFLOAT3 m_Angle;
	Cube* m_pCube;
	ObjectCollisionType m_collisionType;

};



#endif	//__GAME_OBJECT_H__
