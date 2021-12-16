/**
 * @file GameObject.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/11 追跡フラグをメンバ変数に追加
 *					追跡フラグ取得関数を追加
 *					追跡フラグセット関数を追加
 * @brief ゲーム内のオブジェクトに関する処理
 */
#include "GameObject.h"
#include "Shader.h"


GameObject::GameObject()
	:m_pCube(nullptr)
	,m_pos(0,0,0)
	,m_size(1,1,1)
	,m_move(0,0,0)
	,m_Radius(5,5,5)
	,m_Angle(0, 0, 0)
	,m_collisionType(COLLISION_STATIC)
	,use(false)
	,m_FollowFlg(false)
{

}
GameObject::~GameObject()
{
	Uninit();
}

bool GameObject::Init()
{
	//キューブの生成
	m_pCube = new Cube();
	m_pCube->SetSize(
		m_size.x, m_size.y, m_size.z
	);
	m_pCube->SetPos(
		m_pos.x, m_pos.y, m_pos.z
	);
	m_pCube->SetAngle(
		m_Angle.x, m_Angle.y, m_Angle.z
	);

	return true;
}
void GameObject::Uninit()
{
	if (m_pCube != NULL)
	{
		delete m_pCube;
		m_pCube = NULL;
	}

}
void GameObject::Update()
{

}
void GameObject::Draw()
{
	//3Dの座標返還の基本は行列で計算を行う
	//例えばモデルを小さくしたい、回転させたい
	//移動させたい場合、それぞれの
	//変換行列を作成する必要がある
	//(これらすべてを一度に行う変換は
	//自分で作るしかない
	//それぞれの変換行列を掛け合わせた
	//行列が最終的なワールド変換行列となる。
	//この時、掛け算の順番を意識しないと
	//意図しない結果になるので注意が必要
	//基本的には拡縮×回転×移動の
	//順番で計算を行うとよい。DirectXは
	//左から順番に処理をする
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(
			m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixRotationY(m_Angle.y)
		* DirectX::XMMatrixTranslation(
			m_pos.x, m_pos.y, m_pos.z));

	m_pCube->Draw();
}
void GameObject::CreateObject(DirectX::XMFLOAT3 pos,
	DirectX::XMFLOAT3 dir, DirectX::XMFLOAT3 move)
{

}
DirectX::XMFLOAT3 GameObject::GetPos()
{
	return m_pos;
}
DirectX::XMFLOAT3 GameObject::GetSize()
{
	return m_size;
}
DirectX::XMFLOAT3 GameObject::GetMove()
{
	return m_move;
}
DirectX::XMFLOAT3 GameObject::GetRadius()
{
	return m_Radius;
}
ObjectCollisionType GameObject::GetCollisionType()
{
	return m_collisionType;
}

bool GameObject::GetFollowFlg() {
	return m_FollowFlg;
}

void GameObject::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}
void GameObject::SetSize(DirectX::XMFLOAT3 size)
{
	m_size = size;
}
void GameObject::SetMove(DirectX::XMFLOAT3 move)
{
	m_move = move;
}
void GameObject::SetAngle(DirectX::XMFLOAT3 angle)
{
	m_Angle = angle;
}

void GameObject::SetFollowFlg(bool flg) {
	m_FollowFlg = flg;
}
