#include "Model.h"
#include "Shader.h"

Model::Model()
	:m_pBuffer(NULL)
{

}
Model::~Model()
{
	if (m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
	}
}

bool Model::LoadModel(const char* pFilePath)
{
	HRESULT hr;
	//モデルファイル読み込み
	hr = m_fbx.LoadModel(pFilePath);
	if (FAILED(hr)) { return false; }

	//モデルのメッシュの数だけ、
	//頂点バッファ作成
	int meshNum = m_fbx.GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; ++i)
	{
		//メッシュごとに頂点バッファ作成
		m_pBuffer[i].CreateVertexBuffer(
			m_fbx.GetVertexData(i),
			m_fbx.GetVertexSize(i),
			m_fbx.GetVertexCount(i)
		);
		//インデックスバッファ作成
		m_pBuffer[i].CreateIndexBuffer(
			m_fbx.GetIndexData(i),
			m_fbx.GetIndexCount(i)
		);
	}
	return true;
}

void Model::Draw()
{
	int meshNum = m_fbx.GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{
		SHADER->SetTexture(
			m_fbx.GetTexture(i)
		);
		m_pBuffer[i].Draw(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}