#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <DirectXMath.h>
#include "Cube.h"
#include "Shader.h"
using namespace DirectX;

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
	virtual void CreateObject(XMFLOAT3 pos, XMFLOAT3 dir,XMFLOAT3 move);

	//値取得
	XMFLOAT3 GetPos();
	XMFLOAT3 GetSize();
	XMFLOAT3 GetMove();
	XMFLOAT3 GetRadius();
	ObjectCollisionType GetCollisionType();
	bool GetFollowFlg();

	//値設定
	void SetMove(XMFLOAT3 move);
	void SetPos(XMFLOAT3 pos);
	void SetSize(XMFLOAT3 size);
	void SetAngle(XMFLOAT3 angle);
	void SetFollowFlg(bool flg);

	bool use;

private:
protected:
	XMFLOAT3 m_pos;
	XMFLOAT3 m_size;
	XMFLOAT3 m_move;
	XMFLOAT3 m_Radius;
	XMFLOAT3 m_Angle;
	Cube* m_pCube;
	ObjectCollisionType m_collisionType;

	bool m_FollowFlg; // ついていくべき時がtrue初期値はfalse
};



#endif	//__GAME_OBJECT_H__
