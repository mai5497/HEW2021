#include "CollectionPoint.h"

CollectionPoint::CollectionPoint()
{
	m_pos.y = 1.0f;
	m_Angle = XMFLOAT3(0, 0, 0);
	m_collisionType = COLLISION_STATIC;
}

CollectionPoint::~CollectionPoint()
{
	Uninit();

}

bool CollectionPoint::Init()
{
	GameObject::Init();
	return true;
}
void CollectionPoint::Uninit()
{
	GameObject::Uninit();

}
void CollectionPoint::Update()
{


}
void CollectionPoint::Draw()
{
	//ƒ[ƒ‹ƒhÀ•W•ÏŠ·
	SHADER->SetWorld
	(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* XMMatrixRotationY(m_Angle.y) * XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pCube->Draw();
}



