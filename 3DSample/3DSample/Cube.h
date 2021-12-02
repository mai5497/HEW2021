#ifndef __CUBE_H__
#define __CUBE_H__

#include "DrawBuffer.h"

class Cube
{
public:
	Cube();
	~Cube();

	void SetPos(float x, float y, float z);
	void SetSize(float w, float h, float d);
	void SetAngle(float ax, float ay, float az);	//äpìxä÷êî

	void Draw();

private:
	float m_posX, m_posY, m_posZ;
	float m_width, m_height, m_depth;
	float m_AngleX, m_AngleY, m_AngleZ;	//äpìx
	DrawBuffer m_buffer;
};

#endif