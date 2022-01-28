#ifndef __SHADER_H__
#define __SHADER_H__

#include "DirectX.h"
#include <DirectXMath.h>

//----------------------------------------
// マクロ
//----------------------------------------
#define SHADER GetShader()

//----------------------------------------
// 定数
//----------------------------------------
// 頂点シェーダ
enum VertexShaderKind
{
	VS_WORLD,
	VS_ANIMATION,

	VS_KIND_MAX
};
// ピクセルシェーダ
enum PixelShaderKind
{
	PS_UNLIT,
	PS_TOON,
	PS_LAMBERT,
	PS_PHONG,

	PS_KIND_MAX
};

//----------------------------------------
// クラス/構造体
//----------------------------------------
/// @brief カメラ変換行列
struct VSBufferCamera
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 proj;
};
/// @brief マテリアル
struct PSBufferMaterial
{
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 specular;
	DirectX::XMFLOAT4 emissive;
};
/// @brief ライト
struct PSBufferLight
{
	DirectX::XMFLOAT4 dir;
	PSBufferMaterial material;
};
/// @brief カメラ
struct PSBufferCamera
{
	DirectX::XMFLOAT4 pos;
};

/// @brief シェーダ
class Shader
{
public:
	Shader();
	~Shader();

	HRESULT Init();
	void Uninit();
	void Bind(VertexShaderKind vs, PixelShaderKind ps);

	//---
	void SetWorld(const DirectX::XMMATRIX& world);
	void SetView(const DirectX::XMMATRIX& view);
	void SetProjection(const DirectX::XMMATRIX& proj);
	void SetTexture(ID3D11ShaderResourceView* pTexture);
	void SetDiffuse(const DirectX::XMFLOAT4& diffuse);
	void SetAmbient(const DirectX::XMFLOAT4& ambient);
	void SetSpecular(const DirectX::XMFLOAT4& specular);
	void SetEmissive(const DirectX::XMFLOAT4& emissive);
	void SetLightDir(const DirectX::XMFLOAT4& dir);
	void SetLightDiffuse(const DirectX::XMFLOAT4& diffuse);
	void SetLightAmbient(const DirectX::XMFLOAT4& ambient);
	void SetLightSpecular(const DirectX::XMFLOAT4& specular, float exp);
	void SetPSCameraPos(const DirectX::XMFLOAT3& pos);

private:
	ID3D11InputLayout * m_pInputLayout[VS_KIND_MAX];
	ID3D11VertexShader* m_pVertexShader[VS_KIND_MAX];
	ID3D11PixelShader* m_pPixelShader[PS_KIND_MAX];
	ID3D11Buffer* m_pBuffers[6];

	ID3D11ShaderResourceView* m_pTexture;

	DirectX::XMFLOAT4X4 m_world;		// b0
	VSBufferCamera		m_vsCamera;		// b1
	DirectX::XMFLOAT4X4 m_anime[150];	// b2
	PSBufferMaterial	m_material;		// b0
	PSBufferLight		m_light;		// b1
	PSBufferCamera		m_psCamera;		// b2
};

//----------------------------------------
// 関数
//----------------------------------------
Shader* GetShader();

#endif // __SHADER_H_