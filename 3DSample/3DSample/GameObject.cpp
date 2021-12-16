/**
 * @file GameObject.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/11 �ǐՃt���O�������o�ϐ��ɒǉ�
 *					�ǐՃt���O�擾�֐���ǉ�
 *					�ǐՃt���O�Z�b�g�֐���ǉ�
 * @brief �Q�[�����̃I�u�W�F�N�g�Ɋւ��鏈��
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
	//�L���[�u�̐���
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
	//3D�̍��W�Ԋ҂̊�{�͍s��Ōv�Z���s��
	//�Ⴆ�΃��f�����������������A��]��������
	//�ړ����������ꍇ�A���ꂼ���
	//�ϊ��s����쐬����K�v������
	//(����炷�ׂĂ���x�ɍs���ϊ���
	//�����ō�邵���Ȃ�
	//���ꂼ��̕ϊ��s����|�����킹��
	//�s�񂪍ŏI�I�ȃ��[���h�ϊ��s��ƂȂ�B
	//���̎��A�|���Z�̏��Ԃ��ӎ����Ȃ���
	//�Ӑ}���Ȃ����ʂɂȂ�̂Œ��ӂ��K�v
	//��{�I�ɂ͊g�k�~��]�~�ړ���
	//���ԂŌv�Z���s���Ƃ悢�BDirectX��
	//�����珇�Ԃɏ���������
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
