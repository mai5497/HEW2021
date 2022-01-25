#ifndef __CUBE_H__
#define __CUBE_H__

#include "DrawBuffer.h"

class Cube
{
public:
	Cube();
	~Cube();
	void Update();

	void SetPos(float x, float y, float z);
	void SetSize(float w, float h ,float d);
	void SetAngle(float ax, float ay, float az);		//角度関数
	void SetRGBA(float r, float g, float b,float a);	// 色変更

	void Draw();

private:

	float m_posX, m_posY, m_posZ;
	float m_width, m_height,m_depth;
	float m_AngleX, m_AngleY, m_AngleZ;	//角度
	float m_R, m_G, m_B, m_A;
	DrawBuffer m_buffer;
};

#endif