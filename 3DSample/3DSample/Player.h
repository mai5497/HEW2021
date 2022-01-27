#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "CharacterBase.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "DwarfManager.h"
#include "Collision.h"
#include "Stage.h"

// ���f���`��p
#include	"Texture.h"
#include	"FBX//FBXPlayer.h"
#include	"DrawBuffer.h"

enum PLAYERANIME {
	STAND = 0,
	THROW,
	MAX_ANIME
};

class DwarfManager;

class Player : public CharacterBase
{
public:
	// ---�R���X�g���N�^/�f�X�g���N�^
	Player();
	virtual ~Player();

	// ---4�又��
	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();

	// ---�G�l�~�[�ǐՏ���
	virtual void PlayerToEnemy(GameObject*);

	// ---�J�����֘A
	void SetControllCamera(Camera *pCamera);
	void GetCameraPos(TPSCamera*);

	// ---�v���C���[�֘A
	ID3D11ShaderResourceView *m_pPlayerTex;			
	XMFLOAT3 GetPlayerPos();
	XMFLOAT3 GetPlayerAngle();
	float GetPlayerDrawAngle();							// �v���C���[�̌����p�x���擾

	void SetBulletTargetPos(XMFLOAT3 pos);
	
	void SetThrowFlg(bool flg);

private:
	bool LoadPlayer(const char *pFilePath);

	Camera * m_pControllCamera;				// �J�������W����
	static DrawBuffer *m_pBuffer;			// �o�b�t�@��񑀍�
	static FBXPlayer *m_pFBX;				// FBX�t�@�C������N���X
	float m_DrawAngle;						// �`��p�x
	XMFLOAT3 m_BulletTargetPos;
	ANIME_INDEX m_playerAnim[MAX_ANIME];
	bool m_throwFlg;
};

#endif // !_PLAYER_H_
