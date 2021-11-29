#ifndef __FBX_PLAYER_H__
#define __FBX_PLAYER_H__

#include <d3d11.h>

class FBXPlayer
{
public:
	FBXPlayer();
	~FBXPlayer();

	HRESULT LoadModel(const char* model);

	int GetMeshNum();
	void* GetVertexData(int mesh);
	UINT GetVertexSize(int mesh);
	UINT GetVertexCount(int mesh);
	const long* GetIndexData(int mesh);
	UINT GetIndexCount(int mesh);
	ID3D11ShaderResourceView* GetTexture(int mesh);

private:
	int m_modelID;
	void* m_pVertex;
	float m_frame;
};




#endif // __FBX_PLAYER_H__