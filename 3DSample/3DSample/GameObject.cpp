/**
 * @file GameObject.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/11 追跡フラグをメンバ変数に追加（いちだ）
 *					追跡フラグ取得関数を追加（いちだ）
 *					追跡フラグセット関数を追加（いちだ）
 *		 2021/12/20 色情報をいれる変数を追加（いちだ）
 *					色情報用の変数のセットゲット関数を追加（いちだ）
 *		 2021/12/22 追跡フラグをdwarfbaseに移動した（伊地田）
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
	//,m_FollowFlg(false)
	,m_Color(1.0f, 1.0f, 1.0f, 1.0f)
	,m_BulletFlg(false)
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
	m_pCube->SetSize(m_size.x, m_size.y, m_size.z);			// 初期サイズ
	m_pCube->SetPos(m_pos.x, m_pos.y, m_pos.z);				// 初期位置
	m_pCube->SetAngle(m_Angle.x, m_Angle.y, m_Angle.z);		// 初期角度

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
void GameObject::Update() {
	if (m_Color.w != 1.0f || m_Color.x != 1.0f || m_Color.y != 1.0f || m_Color.z != 1.0f) {		// 色の変更がかかっている場合更新する
		m_pCube->SetRGBA(m_Color.x,m_Color.y,m_Color.z,m_Color.w);
		m_pCube->Update();
	}
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
		DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixRotationY(m_Angle.y)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pCube->Draw();
}
void GameObject::CreateObject(XMFLOAT3 pos,XMFLOAT3 dir,XMFLOAT3 move)
{

}


//--------------------- ゲット関数 ----------------------
//=======================================================
//
//		座標取得
//
//=======================================================
XMFLOAT3 GameObject::GetPos()
{
	return m_pos;
}

//=======================================================
//
//		サイズ取得
//
//=======================================================
XMFLOAT3 GameObject::GetSize()
{
	return m_size;
}

//=======================================================
//
//		移動量取得
//
//=======================================================
XMFLOAT3 GameObject::GetMove()
{
	return m_move;
}

//=======================================================
//
//		境界球半径取得
//
//=======================================================
XMFLOAT3 GameObject::GetRadius()
{
	return m_Radius;
}

//=======================================================
//
//		オブジェクトの種類取得
//
//=======================================================
ObjectCollisionType GameObject::GetCollisionType()
{
	return m_collisionType;
}

//=======================================================
//
//		追跡フラグ取得
//
//=======================================================
//bool GameObject::GetFollowFlg() 
//{
//	return m_FollowFlg;
//}

//=======================================================
//
//		カラー取得
//
//=======================================================
XMFLOAT4 GameObject::GetColor() 
{
	return m_Color;
}


//--------------------- セット関数 ----------------------
//=======================================================
//
//		座標のセット
//
//=======================================================
void GameObject::SetPos(XMFLOAT3 pos)
{
	m_pos = pos;
	
}

//=======================================================
//
//		サイズのセット
//
//=======================================================
void GameObject::SetSize(XMFLOAT3 size)
{
	m_size = size;
}

//=======================================================
//
//		移動距離のセット
//
//=======================================================
void GameObject::SetMove(XMFLOAT3 move)
{
	m_move = move;
}

//=======================================================
//
//		角度のセット
//
//=======================================================
void GameObject::SetAngle(XMFLOAT3 angle)
{
	m_Angle = angle;
}

//=======================================================
//
//		追跡フラグのセット
//	
//=======================================================
//void GameObject::SetFollowFlg(bool flg) 
//{
//	m_FollowFlg = flg;
//}

//=======================================================
//
//		色のセット
//
//=======================================================
void GameObject::SetCollor(XMFLOAT4 color) {
	m_Color = color;
}
