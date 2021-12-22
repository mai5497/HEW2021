#include "Collector.h"
#include "Texture.h"

#define ENEMY_SIZE (0.007f)

DrawBuffer *Collector::m_pBuffer = NULL;
FBXPlayer *Collector::m_pfbx = NULL;

#define FPS			(60)					//フレーム数
#define WAIT_TIME	(10)

Collector::Collector()
{
	LoadTextureFromFile("Assets/Model/tyoutingazou.png", &m_pCollectorTex);


	m_pos.x = 10.0f;
	m_pos.y = 20.0f;
	m_pos.z = 0.0f;

	m_move.x = 0.0f;
	m_move.y = 0.0f;
	m_move.z = 0.0f;

	m_bTimeFlg = true;
	m_Timer = WAIT_TIME * FPS + 59;

	use = true;
}
Collector::~Collector()
{

}

bool Collector::LoadFBX(const char* pFilePath)
{
	HRESULT hr;
	m_pfbx = new FBXPlayer;
	hr = m_pfbx->LoadModel(pFilePath);
	if (FAILED(hr)) { return false; }

	//モデルのメッシュの数だけ頂点バッファ作成
	int meshNum = m_pfbx->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++)
	{
		//メッシュごとに頂点バッファ作成
		m_pBuffer[i].CreateVertexBuffer(
			m_pfbx->GetVertexData(i),
			m_pfbx->GetVertexSize(i),
			m_pfbx->GetVertexCount(i)
		);
		//インデックスバッファ作成
		m_pBuffer[i].CreateIndexBuffer(
			m_pfbx->GetIndexData(i),
			m_pfbx->GetIndexCount(i)
		);

	}
	return true;
}

bool Collector::Init()
{
	if (m_pBuffer == NULL)
	{
		Collector::LoadFBX("Assets/Model/tyoutinobake.fbx");
	}
	return true;
}
void Collector::Uninit()
{
	if (m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pfbx;
		m_pfbx = NULL;
	}
}

void Collector::Update()
{
	// アークタンジェント(逆正接)
	m_Angle = atan2(m_move.z, m_move.x);
	m_Angle -= DirectX::XM_PI * 0.5f;

	if (m_bTimeFlg)
	{
		if (m_Timer > 0)
		{
			m_Timer--;
		}
		else
		{
			m_move.x = -(1.5f / FPS);
		}

		if (m_pos.x < 0)
		{
			m_move.x = 0;
			if (m_pos.y > 0)
			{
				m_move.y = -(1.5f / FPS);
			}
			else
			{
				m_move.y = 0;
				m_bTimeFlg = false;
				m_Timer = WAIT_TIME * FPS + 59;
			}
		}
	}
	if (!m_bTimeFlg)
	{
		if (m_Timer > 0)
		{
			m_Timer--;
		}
		else
		{
			m_move.y = (1.5f / FPS);
		}

		if (m_pos.y > 20)
		{
			m_move.y = 0;
			if (m_pos.x < 10)
			{
				m_move.x = (1.5f / FPS);
			}
			else
			{
				m_move.x = 0;
			}
		}
	}

// 移動
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
}

void Collector::Draw()
{
	// のテクスチャ
	int meshNum = m_pfbx->GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE)
			*DirectX::XMMatrixRotationY(-m_Angle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pCollectorTex);


		m_pBuffer[i].Draw(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
	}
}
