#ifndef __DIRECT_X_H__
#define __DIRECT_X_H__

#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

#define SAFE_RELEASE(p) if(p){p->Release(); p = NULL;}

enum BlendMode
{
	BLEND_ALPHA,
	BLEND_ADD,
	BLEND_MAX
};

HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen);
void UninitDX();
void BeginDrawDX();
void EndDrawDX();

ID3D11Device *GetDevice();
ID3D11DeviceContext *GetContext();

void SetBlendMode(BlendMode blend);
//“Á’è‚Ì–Ê‚ğ‰f‚ç‚È‚¢‚æ‚¤‚É‚·‚éˆ—‚ğ
//ƒJƒŠƒ“ƒO(Culling)‚Á‚Ä‚¢‚¤
void EnableCulling(bool enable);

#endif // __DIRECT_X_H__