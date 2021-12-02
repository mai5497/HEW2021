#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <DirectXMath.h>
#include "Cube.h"
#include "Shader.h"

//当たり判定を実施するときの
//オブジェクトの種類
enum ObjectCollisionType
{
	COLLISION_STATIC,	//静止している物体
	COLLISION_DYNAMIC,	//動いている物体
	COLLISION_OVERLAP,	//貫通する物体
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

	//値取得
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetSize();
	DirectX::XMFLOAT3 GetMove();
	DirectX::XMFLOAT3 GetRadius();
	ObjectCollisionType GetCollisionType();

	//値設定
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
