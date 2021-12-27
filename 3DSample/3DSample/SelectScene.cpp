#include "SelectScene.h"
#include "Input.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"

ID3D11ShaderResourceView* g_pSelectTex;
//DrawBuffer g_pBuffer;
//TPSCamera* g_pSelectTPSCamera;
Camera* g_pSelectCamera;
GameObject* g_pSelectObject;

SelectScene::SelectScene(void)
{

}

SelectScene::~SelectScene(void)
{

}

void SelectScene::Init()
{
	LoadTextureFromFile("Assets/Model/Select.png", &g_pSelectTex);

	//g_pSelectTPSCamera = new TPSCamera();
	//g_pSelectTPSCamera->Init();
	//g_pSelectTPSCamera->SetTargetObj(g_pSelectBG);
	g_pSelectObject = new GameObject;
	g_pSelectObject->Init();
	g_pSelectObject->SetPos(DirectX::XMFLOAT3(0, 0, 300));
	g_pSelectObject->SetSize(DirectX::XMFLOAT3(1, (float)SCREEN_HEIGHT / SCREEN_WIDTH, 1));

	g_pSelectCamera = new Camera;
	g_pSelectCamera->Init();

}

void SelectScene::Uninit()
{
	SAFE_RELEASE(g_pSelectTex);
	g_pSelectCamera->Uninit();
	//delete g_pSelectTPSCamera;
	delete g_pSelectCamera;
	g_pSelectObject->Uninit();
	delete g_pSelectObject;


}
SCENE SelectScene::Update()
{

	//g_pSelectTPSCamera->Update();

	if (IsTrigger('1')) { return SCENE_GAME; }
	return SCENE_SELECT;
}
void SelectScene::Draw()
{
	SHADER->Bind(VS_WORLD, PS_PHONG);

	g_pSelectCamera->Bind2D();

	SHADER->SetTexture(g_pSelectTex);

	//g_pBuffer.Draw(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	g_pSelectObject->Draw();

	SHADER->SetTexture(NULL);

}