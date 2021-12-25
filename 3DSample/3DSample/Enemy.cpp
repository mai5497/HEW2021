/**
 * @file Enemy.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/08	弾への追跡を削除
 *					追跡の速度を調整
 * @brief 敵に関する処理
 */
#include "Enemy.h"
#include "myVector.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"

#define ENEMY_SIZE (0.007f)

DrawBuffer *Enemy::m_pBuffer = NULL;
FBXPlayer *Enemy::m_pfbx = NULL;

Enemy::Enemy()
{
	LoadTextureFromFile("Assets/Texture/tyoutingazou.png", &m_pEnemyTex);


	m_pos.x = 11.0f;
	m_pos.y = 0.5f;
	m_pos.z = 3.0f;

	m_move.x = 0.0f;
	m_move.y = 0.0f;
	m_move.z = 0.0f;

	use = true;
}

Enemy::~Enemy()
{

}

bool Enemy::LoadEnemy(const char* pFilePath)
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

bool Enemy::Init()
{
	if (m_pBuffer == NULL)
	{
		Enemy::LoadEnemy("Assets/Model/tyoutinobake.fbx");
	}
	return true;
}

void Enemy::Uninit()
{
	if (m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pfbx;
		m_pfbx = NULL;
	}
}

void Enemy::Update()
{
	//----- 変数初期化 -----
	static int LifeCnt;

	//エネミの速度を調節するためにコメントアウトされていた部分を元に戻した
	// 追従するターゲットの座標
	DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&m_targetPos);

	// Enemyの座標
	DirectX::XMVECTOR vEnemyPos = DirectX::XMLoadFloat3(&m_pos);

	// 進行方向							　　↓ベクトルの引き算
	DirectX::XMVECTOR vDirection = DirectX::XMVectorSubtract(vTarget, vEnemyPos);

	// 一定の速度にするために正規化
	// 速度を変えるならvDirectonに速度をかける。
	vDirection = DirectX::XMVector3Normalize(vDirection);

	// かける関数								  ↓かける数
	vDirection = DirectX::XMVectorScale(vDirection, 1.0 / 60);

	// Float3型に変換
	DirectX::XMStoreFloat3(&m_move, vDirection);


	// アークタンジェント(逆正接)
	m_EnemyAngle = atan2(m_move.z, m_move.x);
	m_EnemyAngle -= DirectX::XM_PI * 0.5f;

	// 敵のアクション

	// 移動
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

}

void Enemy::Draw()
{

	// エネミーのテクスチャ
	int meshNum = m_pfbx->GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{

		SHADER->SetWorld(
			DirectX::XMMatrixScaling(ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE)
			*DirectX::XMMatrixRotationY(-m_EnemyAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pEnemyTex);
		/*SHADER->SetTexture(
		m_fbx.GetTexture(i)
		);*/

		m_pBuffer[i].Draw(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
	}
}

void Enemy::EnemyStop()
{
	m_move.x = 0.6f;
	m_move.y = 0.6f;
	m_move.z = 0.6f;
}