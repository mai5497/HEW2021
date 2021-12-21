/**
 * @file CharacterBase.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 * @brief プレイヤーの座標に関する処理
 */
#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
	//キャラクターは動くオブジェクト
	m_collisionType = COLLISION_DYNAMIC;
}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Draw()
{
	//ワールド座標変換
	SHADER->SetWorld
	(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
	* XMMatrixRotationY(m_Angle.y) * XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pCube->Draw();
}
