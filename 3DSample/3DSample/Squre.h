//====================================================================
//
// �l�p�|���S��[Squre.h]
// �쐬��:�g����
// 
// �X�V��:2022/01/23	�쐬
//====================================================================

/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"DrawBuffer.h"

//*******************************************************************************
// �N���X�錾
//*******************************************************************************
class Squre
{
public:
	Squre();
	~Squre();
	
	//---�֐�
	void Update();
	void Draw();

	//---Setter
	void SetPos(float x,float y,float z);				// ���W
	void SetSize(float w,float d);						// �傫��
	void SetAngle(float Ax, float Ay, float Az);		// �p�x
	void SetRGBA(float r, float g, float b, float a);	// �F

private:
	float m_posX, m_posY, m_posZ;			//�@���W
	float m_Width,m_Depth;					// �傫��
	float m_AngleX, m_AngleY, m_AngleZ;		//�p�x
	float m_R, m_G, m_B, m_A;				// �F
	DrawBuffer m_buffer;

};



