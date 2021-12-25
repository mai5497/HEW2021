#ifndef __REDDWARF_H__
#define __REDDWARF_H__

//========================= インクルード部 ===========================
#include "DwarfBase.h"
#include "FBX/FBXPlayer.h"

//========================= クラス定義 ===========================
class RedDwarf : public DwarfBase
{
public:
	//---関数
	RedDwarf();
	virtual ~RedDwarf();
	bool Init();
	virtual void Uninit();
	virtual void Update();
	void Draw();


	//---変数
	ID3D11ShaderResourceView *m_pRedDwarfTex;

private:
	//---関数
	void Attack();
	bool LoadDwarf(const char *pFilePath);

	//---変数
	float m_DwarfAngle;
	XMFLOAT3 m_dir;
	static DrawBuffer *m_pBuffer;
	static FBXPlayer *m_pFBX;		// FBXファイル操作クラス
};


#endif