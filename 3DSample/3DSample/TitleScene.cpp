

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


ID3D11ShaderResourceView*	g_pTitleTex[MAX_TITLE_TEX];
Camera*		g_pTitleCamera;
GameObject	g_pTitleObject[TITLE_MAX];

const char* g_pTitleTexFName[TITLE_MAX] = {
	"Assets/Texture/Scene/Select_BG.png",			// �w�i
	"Assets/Texture/Scene/Title_Logo.png",			// �^�C�g�����S
	"Assets/Texture/Title/GameStart.png",			// �Q�[�����͂��߂�
	"Assets/Texture/Title/GameEnd.png",				// ���[�ނ����
	"Assets/Texture/Scene/Press_A.png",				// Press A
};



TitleScene::TitleScene(void)
{
	m_pTitleBuffer = nullptr;
	m_pTitleFBX = nullptr;
}

TitleScene::~TitleScene(void)
{

}

void TitleScene::Init()
{
	if (m_pTitleBuffer == nullptr) {
		LoadTitleModel("Assets/Model/Title/title.fbx");
	}
	m_pTitleFBX->LoadAnimation("Assets/Model/Title/title_anime.fbx");

	//---�Ă�������E���Ԃ������Ɠǂݍ���
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		LoadTextureFromFile(g_pTitleTexFName[i], &g_pTitleTex[i]);
		g_pTitleObject[i].Init();
	}

	//---�w�i
	g_pTitleObject[TITLE_BG].SetPos(XMFLOAT3(0.0f, 0.0f, 1.5f));
	g_pTitleObject[TITLE_BG].SetSize(XMFLOAT3(1.0f, 0.6f, 0.0f));

	//---�����Ƃ�낲
	g_pTitleObject[TITLE_LOGO].SetPos(XMFLOAT3(0.0f, 0.1f, 1.1f));
	g_pTitleObject[TITLE_LOGO].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));

	//--���[�ނ͂��߂�
	g_pTitleObject[TITLE_START].SetPos(XMFLOAT3(0.0f, -0.1f, 1.2f));
	g_pTitleObject[TITLE_START].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));

	//---���[�ނ����
	g_pTitleObject[TITLE_END].SetPos(XMFLOAT3(0.0f, -0.2f, 1.13f));
	g_pTitleObject[TITLE_END].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));

	//---PressA
	g_pTitleObject[TITLE_BUTTON].SetPos(XMFLOAT3(0.0f, -0.5f, 1.0f));
	g_pTitleObject[TITLE_BUTTON].SetSize(XMFLOAT3(0.5f, 0.1f, 0.0f));
	
	g_pTitleCamera = new Camera;
	g_pTitleCamera->Init();

	//---�ϐ�������
	m_SelectState = SCENE_SELECT;


	// BGM�Đ�
	CSound::Play(TITLE_BGM);
}

void TitleScene::Uninit()
{
	if (m_pTitleBuffer != nullptr) {
		delete[] m_pTitleBuffer;
		m_pTitleBuffer = nullptr;

		delete m_pTitleFBX;
		m_pTitleFBX = nullptr;
	}

	for (int i = 0; i < TITLE_MAX; i++) {
		SAFE_RELEASE(g_pTitleTex[i]);
		g_pTitleObject[i].Uninit();
	}
	g_pTitleCamera->Uninit();
	delete g_pTitleCamera;

	CSound::Stop(TITLE_BGM);
}

bool TitleScene::LoadTitleModel(const char *pFilePath) {
	HRESULT hr;
	m_pTitleFBX = new FBXPlayer;
	hr = m_pTitleFBX->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pTitleFBX->GetMeshNum();
	m_pTitleBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
		m_pTitleBuffer[i].CreateVertexBuffer(
			m_pTitleFBX->GetVertexData(i),
			m_pTitleFBX->GetVertexSize(i),
			m_pTitleFBX->GetVertexCount(i)
		);
		//�C���f�b�N�X�o�b�t�@�쐬
		m_pTitleBuffer[i].CreateIndexBuffer(
			m_pTitleFBX->GetIndexData(i),
			m_pTitleFBX->GetIndexCount(i)
		);

	}
	return true;

}


SCENE TitleScene::Update()
{
	if (!m_pTitleFBX->IsPlay()) {
		m_pTitleFBX->Play(0);
	}
	//m_pTitleFBX->Step();
	
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
		if (m_SelectState == 5) {
			PostQuitMessage(0);
		}
	}

	switch (m_SelectState) {
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
	SHADER->Bind(VS_ANIMATION, PS_UNLIT);
	g_pTitleCamera->Bind();

	int meshNum = m_pTitleFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(1.0f,1.0f,1.0f)
			* DirectX::XMMatrixRotationRollPitchYaw(
				XMConvertToRadians(-90.0f),
				XMConvertToRadians(180.0f),
				XMConvertToRadians(0.0f))
			*DirectX::XMMatrixTranslation(0.0f,0.0f,-20.0f));
		SHADER->SetAnimation(m_pTitleFBX->GetAnimeMatrix(i), m_pTitleFBX->GetAnimeMatrixNum(i));
		SHADER->SetTexture(m_pTitleFBX->GetTexture(i));

		m_pTitleBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}


	SHADER->Bind(VS_WORLD, PS_UNLIT);
	g_pTitleCamera->Bind2D();
	
	for (int i = 1; i < TITLE_MAX; i++) {
		//SHADER->SetWorld(
		//	XMMatrixScaling(
		//		g_pTitleObject[i].GetSize().x,
		//		g_pTitleObject[i].GetSize().y,
		//		g_pTitleObject[i].GetSize().z)
		//	* XMMatrixTranslation(
		//		g_pTitleObject[i].GetPos().x,
		//		g_pTitleObject[i].GetPos().y,
		//		g_pTitleObject[i].GetPos().z));


		SHADER->SetTexture(g_pTitleTex[i]);
		g_pTitleObject[i].Draw();
	}

	SHADER->SetTexture(NULL);
}	