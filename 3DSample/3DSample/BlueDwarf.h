#ifndef __BLUEDWARF_H__
#define __BLUEDWARF_H__

//========================= �C���N���[�h�� ===========================
#include "DwarfBase.h"
#include "FBX/FBXPlayer.h"

//========================= �N���X��` ===========================
class BlueDwarf : public DwarfBase
{
public:
	//---�֐�
	BlueDwarf();
	virtual ~BlueDwarf();
	bool Init();
	virtual void Uninit();
	virtual void Update();
	void Draw();


	//---�ϐ�
	ID3D11ShaderResourceView *m_pBlueDwarfTex;

private:
	//---�֐�
	bool LoadDwarf(const char *pFilePath);

	//---�ϐ�
	float m_DwarfAngle;
	XMFLOAT3 m_dir;
	static DrawBuffer *m_pBuffer;
	static FBXPlayer *m_pFBX;		// FBX�t�@�C������N���X
};


#endif