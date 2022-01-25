#include "Shader.h"
#include "DirectX.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

Shader g_shader;

//----------------------------------------
// 頂点レイアウト
//----------------------------------------
const D3D11_INPUT_ELEMENT_DESC LayoutWorld[] =
{
{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
{ "COLOR",			0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
const D3D11_INPUT_ELEMENT_DESC LayoutAnime[] =
{
	{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
{ "COLOR",			0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
{ "BLENDINDICES",	0, DXGI_FORMAT_R32G32B32A32_UINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

//----------------------------------------
// 頂点シェーダ
//----------------------------------------
//----- 通常の変換 -----
const char VSCodeWorld[] = "\
struct VS_IN {\
	float3 pos : POSITION0;\
	float4 color : COLOR0;\
	float2 uv : TEXCOORD0;\
	float3 normal : NORMAL0;\
};\
struct VS_OUT {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
	float3 wPos : TEXCOORD3;\
};\
cbuffer ConstantBuffer : register(b0) {\
	float4x4 World;\
};\
cbuffer ConstantBuffer : register(b1) {\
	float4x4 View;\
	float4x4 Proj;\
};\
VS_OUT main(VS_IN VIN) {\
	VS_OUT VOUT;\
	VOUT.pos = float4(VIN.pos, 1);\
	VOUT.pos = mul(VOUT.pos, World);\
	VOUT.wPos = VOUT.pos;\
	VOUT.pos = mul(VOUT.pos, View);\
	VOUT.pos = mul(VOUT.pos, Proj);\
	VOUT.uv = VIN.uv;\
	VOUT.color = VIN.color;\
	VOUT.normal = mul(VIN.normal, (float3x3)World);\
	return VOUT;\
}";
//----- アニメーション -----
const char VSCodeAnime[] = "\
struct VS_IN {\
	float3 pos : POSITION0;\
	float4 color : COLOR0;\
	float2 uv : TEXCOORD0;\
	float3 normal : NORMAL0;\
	float4 weight : BLENDWEIGHT0;\
	uint4 index : BLENDINDICES0;\
};\
struct VS_OUT {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
	float3 wPos : TEXCOORD3;\
};\
cbuffer ConstantBuffer : register(b0) {\
	float4x4 World;\
};\
cbuffer ConstantBuffer : register(b1) {\
	float4x4 View;\
	float4x4 Proj;\
};\
cbuffer ConstantBuffer : register(b2) {\
	float4x4 Bone[150];\
};\
VS_OUT main(VS_IN VIN) {\
	float4x4 mat = 0;\
	mat += Bone[VIN.index.x] * VIN.weight.x;\
	mat += Bone[VIN.index.y] * VIN.weight.y;\
	mat += Bone[VIN.index.z] * VIN.weight.z;\
	mat += Bone[VIN.index.w] * VIN.weight.w;\
	VS_OUT VOUT;\
	VOUT.pos = float4(VIN.pos, 1);\
	VOUT.pos = mul(VOUT.pos, mat);\
	VOUT.pos = mul(VOUT.pos, World);\
	VOUT.pos = mul(VOUT.pos, View);\
	VOUT.pos = mul(VOUT.pos, Proj);\
	VOUT.uv = VIN.uv;\
	VOUT.color = VIN.color;\
	VOUT.normal = VIN.normal;\
	VOUT.normal = mul(VOUT.normal, (float3x3)mat);\
	VOUT.normal = mul(VOUT.normal, (float3x3)World);\
	return VOUT;\
}";
//----------------------------------------
// ピクセルシェーダ
//----------------------------------------
//----- Unlit -----
const char PSCodeUnlit[] = "\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
};\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
float4 main(PS_IN PIN) : SV_Target {\
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;\
	return color;\
}";
//----- Toon -----
const char PSCodeToon[] = "\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
};\
struct Material {\
	float4 diffuse;\
	float4 ambient;\
	float4 specular;\
	float4 emissive;\
};\
cbuffer ConstantBuffer : register(b0) {\
	Material objMat;\
};\
cbuffer ConstantBuffer : register(b1) {\
	float3 lightDir;\
	Material lightMat;\
};\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
float4 main(PS_IN PIN) : SV_Target {\
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;\
	float4 diffuse = objMat.diffuse * lightMat.diffuse *\
					 max(dot(normalize(PIN.normal), -lightDir), 0);\
	float4 ambient = objMat.ambient * lightMat.ambient;\
	color.rgb *= step(0.01f, diffuse + ambient);\
	return color;\
}";
//----- Lambert -----
const char PSCodeLambert[] = "\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
};\
struct Material {\
	float4 diffuse;\
	float4 ambient;\
	float4 specular;\
	float4 emissive;\
};\
cbuffer ConstantBuffer : register(b0) {\
	Material objMat;\
};\
cbuffer ConstantBuffer : register(b1) {\
	float3 lightDir;\
	Material lightMat;\
};\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
float4 main(PS_IN PIN) : SV_Target {\
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;\
	float4 diffuse = objMat.diffuse * lightMat.diffuse *\
					 max(dot(normalize(PIN.normal), -lightDir), 0);\
	float4 ambient = objMat.ambient * lightMat.ambient;\
	color.rgb *= diffuse + ambient;\
	return color;\
}";
//----- Phong -----
const char PSCodePhong[] = "\
struct PS_IN {\
	float4 pos : SV_POSITION;\
	float4 color : TEXCOORD0;\
	float2 uv : TEXCOORD1;\
	float3 normal : TEXCOORD2;\
	float3 wPos : TEXCOORD3;\
};\
struct Material {\
	float4 diffuse;\
	float4 ambient;\
	float4 specular;\
	float4 emissive;\
};\
cbuffer ConstantBuffer : register(b0) {\
	Material objMat;\
};\
cbuffer ConstantBuffer : register(b1) {\
	float3 lightDir;\
	Material lightMat;\
};\
cbuffer ConstantBuffer : register(b2) {\
	float3 cameraPos;\
};\
Texture2D tex : register(t0);\
SamplerState samp : register(s0);\
float4 main(PS_IN PIN) : SV_Target {\
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;\
	float3 N = normalize(PIN.normal);\
	float3 L = normalize(-lightDir);\
	float3 V = normalize(cameraPos - PIN.wPos);\
	float4 diffuse = objMat.diffuse * lightMat.diffuse *\
					 max(dot(N, L), 0);\
	float4 ambient = objMat.ambient * lightMat.ambient;\
	float4 specular = objMat.specular * lightMat.specular *\
					  pow(max(dot(N, normalize(L + V)), 0), lightMat.specular.a);\
	color.rgb *= diffuse + ambient + specular;\
	return color;\
}";

Shader::Shader()
{
	ZeroMemory(m_pInputLayout, sizeof(m_pInputLayout));
	ZeroMemory(m_pVertexShader, sizeof(m_pVertexShader));
	ZeroMemory(m_pPixelShader, sizeof(m_pPixelShader));
	ZeroMemory(m_pBuffers, sizeof(m_pBuffers));

	m_pTexture = nullptr;
	m_world._11 = m_vsCamera.view._11 = m_vsCamera.proj._11 = 1.0f;
	m_world._22 = m_vsCamera.view._22 = m_vsCamera.proj._22 = 1.0f;
	m_world._33 = m_vsCamera.view._33 = m_vsCamera.proj._33 = 1.0f;
	m_world._44 = m_vsCamera.view._44 = m_vsCamera.proj._44 = 1.0f;
	m_material.diffuse = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_material.ambient = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_material.specular = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_material.emissive = DirectX::XMFLOAT4(0, 0, 0, 0);
	m_light.dir = DirectX::XMFLOAT4(-1, -1, 1, 0);
	DirectX::XMStoreFloat4(
		&m_light.dir,
		DirectX::XMVector3Normalize(DirectX::XMLoadFloat4(&m_light.dir)));
	m_light.material.diffuse = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_light.material.ambient = DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.f);
	m_light.material.specular = DirectX::XMFLOAT4(1, 1, 1, 10);
	m_light.material.emissive = DirectX::XMFLOAT4(0, 0, 0, 0);
	m_psCamera.pos = DirectX::XMFLOAT4(0, 0, -1, 0);
}
Shader::~Shader()
{
}

HRESULT Shader::Init()
{
	HRESULT hr;
	ID3DBlob *pBlob;
	ID3DBlob *error;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pContext = GetContext();

	//--- 頂点シェーダ作成
	const char* pVSCode[] = { VSCodeWorld, VSCodeAnime };
	const D3D11_INPUT_ELEMENT_DESC* pLayout[] = { LayoutWorld, LayoutAnime };
	UINT pLayoutNum[] = { _countof(LayoutWorld), _countof(LayoutAnime) };
	for (int i = 0; i < VS_KIND_MAX; ++i)
	{
		// シェーダコンパイル
		hr = D3DCompile(pVSCode[i], strlen(pVSCode[i]),
			NULL, NULL, NULL, "main", "vs_5_0", 0, 0, &pBlob, &error);
		if (FAILED(hr)) { return hr; }
		//頂点レイアウト作成
		hr = pDevice->CreateInputLayout(pLayout[i], pLayoutNum[i],
			pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_pInputLayout[i]);
		if (FAILED(hr)) { return hr; }
		//頂点シェーダー生成
		hr = pDevice->CreateVertexShader(
			pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pVertexShader[i]);
		if (FAILED(hr)) { return hr; }
		SAFE_RELEASE(pBlob);
	}

	//--- ピクセルシェーダ作成
	const char* pPSCode[] = { PSCodeUnlit, PSCodeToon, PSCodeLambert, PSCodePhong };
	for (int i = 0; i < PS_KIND_MAX; ++i)
	{
		// シェーダコンパイル
		hr = D3DCompile(pPSCode[i], strlen(pPSCode[i]),
			NULL, NULL, NULL, "main", "ps_5_0", 0, 0, &pBlob, &error);
		if (FAILED(hr)) { return hr; }
		//ピクセルシェーダー生成
		hr = pDevice->CreatePixelShader(
			pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pPixelShader[i]);
		if (FAILED(hr)) { return hr; }
		SAFE_RELEASE(pBlob);
	}

	//--- 縞々テクスチャ生成
	// テクスチャ情報
	const int TexSize = 10;
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = texDesc.Height = TexSize;
	texDesc.MipLevels = texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	 //テクスチャデータ
	BYTE color[TexSize * TexSize][4] = {};
	for (int j = 0; j < TexSize; ++j)
	{
		for (int i = 0; i < TexSize; ++i)
		{
			int idx = (TexSize * j) + i;
			color[idx][0] = color[idx][1] = color[idx][2] = 0xff * ((i + j) % 2);
			color[idx][3] = 0xff;
		}
	}
	D3D11_SUBRESOURCE_DATA texSubResource = {};
	texSubResource.SysMemPitch = sizeof(color) / TexSize;
	texSubResource.pSysMem = color;
	// データ生成
	ID3D11Texture2D *pTex = NULL;
	hr = pDevice->CreateTexture2D(&texDesc, &texSubResource, &pTex);
	if (FAILED(hr)) { return hr; }
	// シェーダリソースビュー設定
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderViewDesc = {};
	shaderViewDesc.Format = texDesc.Format;
	shaderViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderViewDesc.Texture2D.MipLevels = texDesc.MipLevels;
	// シェーダリソースビュー作成
	hr = pDevice->CreateShaderResourceView(pTex, &shaderViewDesc, &m_pTexture);
	if (FAILED(hr)) { return hr; }
	SetTexture(nullptr);

	//--- 定数バッファ生成
	D3D11_BUFFER_DESC shaderBufDesc = {};
	D3D11_SUBRESOURCE_DATA shaderSubResource = {};
	shaderBufDesc.Usage = D3D11_USAGE_DEFAULT;
	shaderBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	UINT BufferSize[] = {
		sizeof(m_world), sizeof(m_vsCamera), sizeof(m_anime),
		sizeof(m_material), sizeof(m_light), sizeof(m_psCamera)
	};
	void* BufferData[] = {
		&m_world, &m_vsCamera, m_anime,
		&m_material, &m_light, &m_psCamera
	};
	for (int i = 0; i < 6; ++i)
	{
		shaderBufDesc.ByteWidth = BufferSize[i];
		shaderSubResource.pSysMem = BufferData[i];
		hr = pDevice->CreateBuffer(&shaderBufDesc, &shaderSubResource, &m_pBuffers[i]);
		if (FAILED(hr)) { return hr; }
	}

	return hr;
}

void Shader::Uninit()
{
	SAFE_RELEASE(m_pTexture);
	for (int i = 0; i < 6; ++i)
		SAFE_RELEASE(m_pBuffers[i]);
	for (int i = 0; i < PS_KIND_MAX; ++i)
		SAFE_RELEASE(m_pPixelShader[i]);
	for (int i = 0; i < VS_KIND_MAX; ++i)
	{
		SAFE_RELEASE(m_pVertexShader[i]);
		SAFE_RELEASE(m_pInputLayout[i]);
	}
}

void Shader::Bind(VertexShaderKind vs, PixelShaderKind ps)
{
	ID3D11DeviceContext* pContext = GetContext();
	pContext->IASetInputLayout(m_pInputLayout[vs]);
	pContext->VSSetShader(m_pVertexShader[vs], nullptr, 0);
	pContext->PSSetShader(m_pPixelShader[ps], nullptr, 0);
	pContext->VSSetConstantBuffers(0, 3, &m_pBuffers[0]);
	pContext->PSSetConstantBuffers(0, 3, &m_pBuffers[3]);
}

void Shader::SetWorld(const DirectX::XMMATRIX& world)
{
	DirectX::XMStoreFloat4x4(&m_world, DirectX::XMMatrixTranspose(world));
	GetContext()->UpdateSubresource(m_pBuffers[0], 0, NULL, &m_world, 0, 0);
}
void Shader::SetView(const DirectX::XMMATRIX& view)
{
	DirectX::XMStoreFloat4x4(&m_vsCamera.view, DirectX::XMMatrixTranspose(view));
	GetContext()->UpdateSubresource(m_pBuffers[1], 0, NULL, &m_vsCamera, 0, 0);
}
void Shader::SetProjection(const DirectX::XMMATRIX& proj)
{
	DirectX::XMStoreFloat4x4(&m_vsCamera.proj, DirectX::XMMatrixTranspose(proj));
	GetContext()->UpdateSubresource(m_pBuffers[1], 0, NULL, &m_vsCamera, 0, 0);
}
void Shader::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	ID3D11DeviceContext* pContext = GetContext();
	if (pTexture == nullptr) { pTexture = m_pTexture; }
	pContext->PSSetShaderResources(0, 1, &pTexture);
}
void Shader::SetDiffuse(const DirectX::XMFLOAT4& diffuse)
{
	m_material.diffuse = diffuse;
	GetContext()->UpdateSubresource(m_pBuffers[3], 0, NULL, &m_material, 0, 0);
}
void Shader::SetAmbient(const DirectX::XMFLOAT4& ambient)
{
	m_material.ambient = ambient;
	GetContext()->UpdateSubresource(m_pBuffers[3], 0, NULL, &m_material, 0, 0);
}
void Shader::SetSpecular(const DirectX::XMFLOAT4& specular)
{
	m_material.specular = specular;
	GetContext()->UpdateSubresource(m_pBuffers[3], 0, NULL, &m_material, 0, 0);
}
void Shader::SetEmissive(const DirectX::XMFLOAT4& emissive)
{
	m_material.emissive = emissive;
	GetContext()->UpdateSubresource(m_pBuffers[3], 0, NULL, &m_material, 0, 0);
}
void Shader::SetLightDir(const DirectX::XMFLOAT4& dir)
{
	DirectX::XMStoreFloat4(
		&m_light.dir,
		DirectX::XMVector3Normalize(DirectX::XMLoadFloat4(&dir)));
	GetContext()->UpdateSubresource(m_pBuffers[4], 0, NULL, &m_light, 0, 0);
}
void Shader::SetLightDiffuse(const DirectX::XMFLOAT4& diffuse)
{
	m_light.material.diffuse = diffuse;
	GetContext()->UpdateSubresource(m_pBuffers[4], 0, NULL, &m_light, 0, 0);
}
void Shader::SetLightAmbient(const DirectX::XMFLOAT4& ambient)
{
	m_light.material.ambient = ambient;
	GetContext()->UpdateSubresource(m_pBuffers[4], 0, NULL, &m_light, 0, 0);
}
void Shader::SetLightSpecular(const DirectX::XMFLOAT4& specular, float exp)
{
	m_light.material.specular = specular;
	m_light.material.specular.w = exp;
	GetContext()->UpdateSubresource(m_pBuffers[4], 0, NULL, &m_light, 0, 0);
}
void Shader::SetPSCameraPos(const DirectX::XMFLOAT3& pos)
{
	m_psCamera.pos = DirectX::XMFLOAT4(pos.x, pos.y, pos.z, 1);
	GetContext()->UpdateSubresource(m_pBuffers[5], 0, NULL, &m_psCamera, 0, 0);
}

Shader* GetShader()
{
	return &g_shader;
}