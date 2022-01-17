#include "TitleScene.h"
#include "Input.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"

#define MAX_TITLE_TEX	(3)

ID3D11ShaderResourceView* g_pTitleTex[MAX_TITLE_TEX];
Camera* g_pTitleCamera;
GameObject g_pTitleObject[MAX_TITLE_TEX];

const char* g_pTitleTexFName[MAX_TITLE_TEX] = {
	"Assets/Texture/SceneTexture/Title_BG.png",
	"Assets/Texture/SceneTexture/Title_Logo.png",
	"Assets/Texture/SceneTexture/Press_A.png",
};


TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{

}

void TitleScene::Init()
{
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		LoadTextureFromFile(g_pTitleTexFName[i], &g_pTitleTex[i]);
	}
	g_pTitleObject[0].Init();
	g_pTitleObject[0].SetPos(XMFLOAT3(0, 0, -18));
	g_pTitleObject[0].SetSize(XMFLOAT3(1, (float)SCREEN_HEIGHT / SCREEN_WIDTH, 0));
	
	g_pTitleObject[1].Init();
	g_pTitleObject[1].SetPos(XMFLOAT3(0, 11, -18));
	g_pTitleObject[1].SetSize(XMFLOAT3(4, 2, 0));

	g_pTitleObject[2].Init();
	g_pTitleObject[2].SetPos(XMFLOAT3(0, 8, -18));
	g_pTitleObject[2].SetSize(XMFLOAT3(2, 1, 0));

	
	
	g_pTitleCamera = new Camera;
	g_pTitleCamera->Init(XMFLOAT3(0.0f, 0.0f, -5.0f));

	// BGMçƒê∂
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

	//g_pTitleTPSCamera->Update();

	if (IsRelease('1') || IsRelease(JPadButton::B)) {
		CSound::Play(SE_ENTER_1);
		return SCENE_SELECT;
	}
	return SCENE_TITLE;
}
void TitleScene::Draw()
{

	SHADER->Bind(VS_WORLD, PS_PHONG);

	g_pTitleCamera->Bind();
	
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		SHADER->SetTexture(g_pTitleTex[i]);
		g_pTitleObject[i].Draw();
	}
	
	SHADER->SetTexture(NULL);
}	