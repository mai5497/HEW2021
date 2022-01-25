//====================================================================
//
// �|���S��[GamePolygon.h]
// �쐬��:�g����
// 
// �X�V��:2022/01/23	�쐬
//====================================================================

/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	<DirectXMath.h>
#include	"Squre.h"
#include	"Shader.h"

//*******************************************************************************
// ���O���
//*******************************************************************************
using namespace DirectX;


//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************	

enum PolygonCollisionType {
	POLYGON_COLLSION_STATIC,			
	POLYGON_COLLSION_DYNAMIC,
	POLYGON_COLLISIOM_OVERLAP,
};

//*******************************************************************************
// �N���X��`
//*******************************************************************************
class GamePolygon
{
public:
	GamePolygon();
	virtual ~GamePolygon();

	//---�֐�
	virtual bool Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void OnCollision(GamePolygon*) {}
	virtual void CreatPolygon(XMFLOAT3 pos, XMFLOAT3 dir, XMFLOAT3 move);

	//---�l�ݒ�
	void SetPos(XMFLOAT3 pos);
	void SetSize(XMFLOAT3 size);
	void SetMove(XMFLOAT3 move);
	void SetAngle(XMFLOAT3 angle);
	void SeColor(XMFLOAT4 color);

	//---�l�擾
	XMFLOAT3 GetPos();
	XMFLOAT3 GetSize();
	XMFLOAT3 GetMove();
	XMFLOAT3 GetRadius();
	XMFLOAT3 GetAngle();
	XMFLOAT4 GetColor();
	PolygonCollisionType GetCollisionType();
	

private:
	//---�ϐ�
	XMFLOAT3 m_pos;			// ���W
	XMFLOAT3 m_size;		// �T�C�Y
	XMFLOAT3 m_move;		// ���x
	XMFLOAT3 m_Angle;		// �p�x
	XMFLOAT4 m_Color;		// �F
	XMFLOAT3 m_Radius;		// ���a

	Squre *m_pSqure;									// �X�N�G�A�̃|�C���^���
	PolygonCollisionType m_CollisionType;		// �����蔻��̎��

};

