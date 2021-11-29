#include "Texture.h"
#include "DirectXTex/DirectXTex.h"

#ifdef _X86_
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/Win32/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/Win32/Release/DirectXTex.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/x64/Release/DirectXTex.lib")
#endif
#endif

HRESULT LoadTextureFromFile(const char *pszFileName, ID3D11ShaderResourceView **ppTexture)
{
	HRESULT hr;
	ID3D11Device *pDevice = GetDevice();
	ID3D11DeviceContext *pContext = GetContext();
	DirectX::TexMetadata mdata;
	DirectX::ScratchImage image;
	wchar_t wPath[MAX_PATH];
	size_t wLen = 0;

	// 文字変換
	MultiByteToWideChar(0, 0, pszFileName, -1, wPath, MAX_PATH);
	// ファイル別読み込み
	if (strstr(pszFileName, ".tga"))
	{
		hr = DirectX::LoadFromTGAFile(wPath, &mdata, image);
	}
	else
	{
		hr = DirectX::LoadFromWICFile(wPath, DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &mdata, image);
	}
	if (FAILED(hr))
	{
		MessageBox(NULL, pszFileName, "Failed to load texture.", MB_OK);
		return hr;
	}

	// シェーダリソースビュー作成
	hr = CreateShaderResourceView(
		pDevice,
		image.GetImages(), image.GetImageCount(),
		mdata, ppTexture);

	return hr;
}