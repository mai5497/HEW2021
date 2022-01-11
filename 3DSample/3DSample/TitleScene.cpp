#include "TitleScene.h"
#include "Input.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"
#include "Sound.h"

ID3D11ShaderResourceView* g_pTitleTex;
DrawBuffer g_pBuffer;
//TPSCamera* g_pTitleTPSCamera;
Camera* g_pTitleCamera;
GameObject* g_pTitleObject;

TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{

}

void TitleScene::Init()
{
	LoadTextureFromFile("Assets/Texture/Title.png", &g_pTitleTex);

	//g_pTitleTPSCamera = new TPSCamera();
	//g_pTitleTPSCamera->Init();
	//g_pTitleTPSCamera->SetTargetObj(g_pTitleBG);
	g_pTitleObject = new GameObject;
	g_pTitleObject->Init();
	g_pTitleObject->SetPos(DirectX::XMFLOAT3(0, 0, 300));
	g_pTitleObject->SetSize(DirectX::XMFLOAT3(1, (float)SCREEN_HEIGHT / SCREEN_WIDTH, 1));
	g_pTitleCamera = new Camera;
	g_pTitleCamera->Init();

	// BGMÄ¶
	CSound::Play(TITLE_BGM);
}

void TitleScene::Uninit()
{
	SAFE_RELEASE(g_pTitleTex);
	g_pTitleCamera->Uninit();
	//delete g_pTitleTPSCamera;
	delete g_pTitleCamera;
	g_pTitleObject->Uninit();
	delete g_pTitleObject;

	CSound::Stop(TITLE_BGM);
}
SCENE TitleScene::Update()
{

	//g_pTitleTPSCamera->Update();

	if (IsTrigger('1')) { return SCENE_SELECT; }
	return SCENE_TITLE;
}
void TitleScene::Draw()
{

	SHADER->Bind(VS_WORLD, PS_PHONG);

	g_pTitleCamera->Bind2D();
	
	SHADER->SetTexture(g_pTitleTex);
	
	//g_pBuffer.Draw(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	g_pTitleObject->Draw();

	SHADER->SetTexture(NULL);

}	