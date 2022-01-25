/**
 * @file GameObject.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/11 �ǐՃt���O�������o�ϐ��ɒǉ��i�������j
 *					�ǐՃt���O�擾�֐���ǉ��i�������j
 *					�ǐՃt���O�Z�b�g�֐���ǉ��i�������j
 *		 2021/12/20 �F���������ϐ���ǉ��i�������j
 *					�F���p�̕ϐ��̃Z�b�g�Q�b�g�֐���ǉ��i�������j
 *		 2021/12/22 �ǐՃt���O��dwarfbase�Ɉړ������i�ɒn�c�j
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
	//�L���[�u�̐���
	m_pCube = new Cube();
	m_pCube->SetSize(m_size.x, m_size.y, m_size.z);			// �����T�C�Y
	m_pCube->SetPos(m_pos.x, m_pos.y, m_pos.z);				// �����ʒu
	m_pCube->SetAngle(m_Angle.x, m_Angle.y, m_Angle.z);		// �����p�x

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
	if (m_Color.w != 1.0f || m_Color.x != 1.0f || m_Color.y != 1.0f || m_Color.z != 1.0f) {		// �F�̕ύX���������Ă���ꍇ�X�V����
		m_pCube->SetRGBA(m_Color.x,m_Color.y,m_Color.z,m_Color.w);
		m_pCube->Update();
	}
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
		DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixRotationY(m_Angle.y)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pCube->Draw();
}
void GameObject::CreateObject(XMFLOAT3 pos,XMFLOAT3 dir,XMFLOAT3 move)
{

}


//--------------------- �Q�b�g�֐� ----------------------
//=======================================================
//
//		���W�擾
//
//=======================================================
XMFLOAT3 GameObject::GetPos()
{
	return m_pos;
}

//=======================================================
//
//		�T�C�Y�擾
//
//=======================================================
XMFLOAT3 GameObject::GetSize()
{
	return m_size;
}

//=======================================================
//
//		�ړ��ʎ擾
//
//=======================================================
XMFLOAT3 GameObject::GetMove()
{
	return m_move;
}

//=======================================================
//
//		���E�����a�擾
//
//=======================================================
XMFLOAT3 GameObject::GetRadius()
{
	return m_Radius;
}

//=======================================================
//
//		�I�u�W�F�N�g�̎�ގ擾
//
//=======================================================
ObjectCollisionType GameObject::GetCollisionType()
{
	return m_collisionType;
}

//=======================================================
//
//		�ǐՃt���O�擾
//
//=======================================================
//bool GameObject::GetFollowFlg() 
//{
//	return m_FollowFlg;
//}

//=======================================================
//
//		�J���[�擾
//
//=======================================================
XMFLOAT4 GameObject::GetColor() 
{
	return m_Color;
}


//--------------------- �Z�b�g�֐� ----------------------
//=======================================================
//
//		���W�̃Z�b�g
//
//=======================================================
void GameObject::SetPos(XMFLOAT3 pos)
{
	m_pos = pos;
	
}

//=======================================================
//
//		�T�C�Y�̃Z�b�g
//
//=======================================================
void GameObject::SetSize(XMFLOAT3 size)
{
	m_size = size;
}

//=======================================================
//
//		�ړ������̃Z�b�g
//
//=======================================================
void GameObject::SetMove(XMFLOAT3 move)
{
	m_move = move;
}

//=======================================================
//
//		�p�x�̃Z�b�g
//
//=======================================================
void GameObject::SetAngle(XMFLOAT3 angle)
{
	m_Angle = angle;
}

//=======================================================
//
//		�ǐՃt���O�̃Z�b�g
//	
//=======================================================
//void GameObject::SetFollowFlg(bool flg) 
//{
//	m_FollowFlg = flg;
//}

//=======================================================
//
//		�F�̃Z�b�g
//
//=======================================================
void GameObject::SetCollor(XMFLOAT4 color) {
	m_Color = color;
}
