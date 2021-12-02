/**
 * @file ResultScene.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 * @brief リザルトシーンに関する処理
 */
#include "ResultScene.h"
#include "Input.h"
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"

ID3D11ShaderResourceView* g_pResultTex;
//DrawBuffer g_pResultBuffer;
//TPSCamera* g_pResultTPSCamera;
Camera* g_pResultCamera;
GameObject* g_pResultObject;

ResultScene::ResultScene(void)
{

}

ResultScene::~ResultScene(void)
{

}

void ResultScene::Init()
{
	LoadTextureFromFile("Result.png", &g_pResultTex);

	//g_pResultTPSCamera = new TPSCamera();
	//g_pResultTPSCamera->Init();
	//g_pResultTPSCamera->SetTargetObj(g_pResultBG);
	g_pResultObject = new GameObject;
	g_pResultObject->Init();
	g_pResultObject->SetPos(DirectX::XMFLOAT3(0, 0, 300));
	g_pResultObject->SetSize(DirectX::XMFLOAT3(1, (float)SCREEN_HEIGHT / SCREEN_WIDTH, 1));
	g_pResultCamera = new Camera;
	g_pResultCamera->Init();
}

void ResultScene::Uninit()
{
	SAFE_RELEASE(g_pResultTex);
	g_pResultCamera->Uninit();
	//delete g_pResultTPSCamera;
	delete g_pResultCamera;
	g_pResultObject->Uninit();
	delete g_pResultObject;

}
SCENE ResultScene::Update()
{
	if (IsTrigger('1')) { return SCENE_TITLE; }
	return SCENE_RESULT;
}
void ResultScene::Draw()
{
	SHADER->Bind(VS_WORLD, PS_PHONG);
	g_pResultCamera->Bind2D();
	SHADER->SetTexture(g_pResultTex);

	//g_pBuffer.Draw(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	g_pResultObject->Draw();

	SHADER->SetTexture(NULL);

}