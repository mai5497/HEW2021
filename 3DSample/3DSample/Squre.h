//====================================================================
//
// 四角ポリゴン[Squre.h]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/23	作成
//====================================================================

/* -----------------インクルードガード------------------ */
#pragma once

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"DrawBuffer.h"

//*******************************************************************************
// クラス宣言
//*******************************************************************************
class Squre
{
public:
	Squre();
	~Squre();
	
	//---関数
	void Update();
	void Draw();

	//---Setter
	void SetPos(float x,float y,float z);				// 座標
	void SetSize(float w,float d);						// 大きさ
	void SetAngle(float Ax, float Ay, float Az);		// 角度
	void SetRGBA(float r, float g, float b, float a);	// 色

private:
	float m_posX, m_posY, m_posZ;			//　座標
	float m_Width,m_Depth;					// 大きさ
	float m_AngleX, m_AngleY, m_AngleZ;		//角度
	float m_R, m_G, m_B, m_A;				// 色
	DrawBuffer m_buffer;

};



