

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include "TitleScene.h"
#include "Input.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
typedef enum
{
	TITLE_BG = 0,
	TITLE_LOGO,

	TITLE_START,
	TITLE_END,

	TITLE_BUTTON,

	TITLE_MAX,
}Title;

#define MAX_TITLE_TEX			(TITLE_MAX)			// �g�p����e�N�X�`���̐�
#define TITLE_SELECT_SIZE	(1.3f)					// �I�𒆂�1.3�{��

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
const char* g_pTitleTexFName[MAX_TITLE_TEX] = {
	"Assets/Texture/Scene/Select_BG.png",			// �w�i
	"Assets/Texture/Scene/Title_Logo.png",			// �^�C�g�����S
	"Assets/Texture/Title/GameStart.png",				// �Q�[�����͂��߂�
	"Assets/Texture/Title/GameEnd.png",				// ���[�ނ����
	"Assets/Texture/Scene/Press_A.png",				// Press A
};

ID3D11ShaderResourceView* g_pTitleTex[MAX_TITLE_TEX];
Camera* g_pTitleCamera;
GameObject	g_pTitleObject[TITLE_MAX];


TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{

}

void TitleScene::Init()
{

	//---�Ă�������E���Ԃ������Ɠǂݍ���
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		LoadTextureFromFile(g_pTitleTexFName[i], &g_pTitleTex[i]);
		g_pTitleObject[i].Init();
	}

	//---�w�i
	g_pTitleObject[TITLE_BG].SetPos(XMFLOAT3(0.0f,0.0f,1.5f));
	g_pTitleObject[TITLE_BG].SetSize(XMFLOAT3(1.0f,0.6f,0.0f));
	
	//---�����Ƃ�낲
	g_pTitleObject[TITLE_LOGO].SetPos(XMFLOAT3(0.0f,0.1f,1.1f));
	g_pTitleObject[TITLE_LOGO].SetSize(XMFLOAT3(0.45f,0.3f,0.0f));

	//--���[�ނ͂��߂�
	g_pTitleObject[TITLE_START].SetPos(XMFLOAT3(0.0f, -0.1f, 1.2f));
	g_pTitleObject[TITLE_START].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));

	//---���[�ނ����
	g_pTitleObject[TITLE_END].SetPos(XMFLOAT3(0.0f, -0.2f, 1.13f));
	g_pTitleObject[TITLE_END].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));

	//---PressA
	g_pTitleObject[TITLE_BUTTON].SetPos(XMFLOAT3(0.0f,-0.5f,1.0f));
	g_pTitleObject[TITLE_BUTTON].SetSize(XMFLOAT3(0.5f,0.1f,0.0f));

	//---���߂炢�񂷂���
	g_pTitleCamera = new Camera;
	g_pTitleCamera->Init();

	//---�ϐ�������
	m_SelectState = SCENE_SELECT;

	// BGM�Đ�
	CSound::Play(TITLE_BGM);
}

void TitleScene::Uninit()
{
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		SAFE_RELEASE(g_pTitleTex[i]);
		g_pTitleObject[i].Uninit();
	}
	g_pTitleCamera->Uninit();
	delete g_pTitleCamera;

	CSound::Stop(TITLE_BGM);
}

SCENE TitleScene::Update()
{
	//---�J�[�\���ړ�
	if (IsRelease(VK_DOWN) || IsRelease(JPadButton::DPAD_DOWN)) {			// ���ړ�
		CSound::Play(SE_SELECT_1);
		m_SelectState += 3;

		if (m_SelectState > 5) {
			m_SelectState = SCENE_END;
		}
	}
	if (IsRelease(VK_UP) || IsRelease(JPadButton::DPAD_UP)) {					// ��ړ�
		CSound::Play(SE_SELECT_1);
		m_SelectState -= 3;

		if (m_SelectState < 2) {
			m_SelectState = SCENE_SELECT;
		}
	}

	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {					// ���肫�[
		CSound::Play(SE_ENTER_1);

		if (m_SelectState == 2) {
			return SCENE_SELECT;
		}
		if(m_SelectState == 5) {
			PostQuitMessage(0);
		}
	}

	switch (m_SelectState)
	{
	case 2:
		g_pTitleObject[TITLE_START].SetSize(XMFLOAT3(0.45f * TITLE_SELECT_SIZE, 0.3f * TITLE_SELECT_SIZE, 0.0f));
		g_pTitleObject[TITLE_END].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));
		break;

	case 5:
		g_pTitleObject[TITLE_END].SetSize(XMFLOAT3(0.45f * TITLE_SELECT_SIZE, 0.3f * TITLE_SELECT_SIZE, 0.0f));
		g_pTitleObject[TITLE_START].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));
		break;

	default:
		break;
	}
	//return SCENE_SELECT;

#ifdef _DEBUG
		if (IsRelease(JPadButton::L_SHOULDER) && IsRelease(JPadButton::R_SHOULDER)) {
			CSound::Play(SE_ENTER_1);
			return SCENE_GAME;
		}

#endif // _DEBUG

		return SCENE_TITLE;

}
void TitleScene::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	g_pTitleCamera->Bind2D();
	
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		SHADER->SetTexture(g_pTitleTex[i]);
		g_pTitleObject[i].Draw();
	}

	SHADER->SetTexture(NULL);
}	