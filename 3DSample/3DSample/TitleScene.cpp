
#include "TitleScene.h"
#include "Input.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"

typedef enum
{
	TITLE_BG = 0,
	TITLE_LOGO,

	TITLE_BUTTON,

	TITLE_MAX,
}Title;

ID3D11ShaderResourceView*	g_pTitleTex[TITLE_MAX];
Camera*		g_pTitleCamera;
GameObject	g_pTitleObject[TITLE_MAX];

const char* g_pTitleTexFName[TITLE_MAX] = {
	"Assets/Texture/Scene/Select_BG.png",
	"Assets/Texture/Scene/Title_Logo.png",
	"Assets/Texture/Scene/Press_A.png",
};


TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{

}

void TitleScene::Init()
{
	for (int i = 0; i < TITLE_MAX; i++) {
		LoadTextureFromFile(g_pTitleTexFName[i], &g_pTitleTex[i]);
		g_pTitleObject[i].Init();
	}

	g_pTitleObject[TITLE_BG].SetPos(XMFLOAT3(0.0f,0.0f,1.1f));
	g_pTitleObject[TITLE_BG].SetSize(XMFLOAT3(1.0f,0.6f,0.0f));
	
	g_pTitleObject[TITLE_LOGO].SetPos(XMFLOAT3(0.0f,0.1f,1.0f));
	g_pTitleObject[TITLE_LOGO].SetSize(XMFLOAT3(0.6f,0.38f,0.0f));

	g_pTitleObject[TITLE_BUTTON].SetPos(XMFLOAT3(0.0f,-0.15f,1.0f));
	g_pTitleObject[TITLE_BUTTON].SetSize(XMFLOAT3(0.5f,0.1f,0.0f));

	
	g_pTitleCamera = new Camera;
	g_pTitleCamera->Init();

	// BGMçƒê∂
	CSound::Play(TITLE_BGM);
}

void TitleScene::Uninit()
{
	for (int i = 0; i < TITLE_MAX; i++) {
		SAFE_RELEASE(g_pTitleTex[i]);
		g_pTitleObject[i].Uninit();
	}
	g_pTitleCamera->Uninit();
	delete g_pTitleCamera;

	CSound::Stop(TITLE_BGM);
}

SCENE TitleScene::Update()
{
	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {
		CSound::Play(SE_ENTER_1);
		return SCENE_SELECT;
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

	SHADER->Bind(VS_WORLD, PS_UNLIT);

	g_pTitleCamera->Bind2D();
	
	for (int i = 0; i < TITLE_MAX; i++) {
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