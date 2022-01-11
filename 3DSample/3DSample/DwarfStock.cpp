#include "DwarfStock.h"
#include "Camera.h"
#include "Texture.h"
#include "Input.h"
#include "DrawBuffer.h"
#include "Shader.h"
#include "GameObject.h"
#include "Defines.h"

ID3D11ShaderResourceView* g_pMakiTex;
Camera* g_pMakiCamera;
GameObject* g_pMakiObj;

DwarfStock::DwarfStock()
{

}
DwarfStock::~DwarfStock()
{

}

void DwarfStock::Init()
{
	LoadTextureFromFile("Assets/Model/UI_2.png", &g_pMakiTex);
	g_pMakiObj = new GameObject;
	g_pMakiObj->Init();
	g_pMakiObj->SetPos(DirectX::XMFLOAT3(-0.34f, -0.17f, 1));
	g_pMakiObj->SetSize(DirectX::XMFLOAT3(0.28f, 0.18f/*(float)SCREEN_HEIGHT / SCREEN_WIDTH*/, 1.0f));

}
void DwarfStock::Uninit()
{
	SAFE_RELEASE(g_pMakiTex);
}
void DwarfStock::Update()
{

}
void DwarfStock::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	g_pMakiCamera->Bind2D();
	SHADER->SetTexture(g_pMakiTex);
	//g_pMakiObj->SetPos(DirectX::XMFLOAT3(-0.4f, 0.35f, 1));
	g_pMakiObj->Draw();

	SHADER->SetTexture(NULL);
}