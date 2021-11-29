#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "DirectX.h"

HRESULT LoadTextureFromFile(const char *pszFileName, ID3D11ShaderResourceView **ppTexture);

#endif // __TEXTURE_H__