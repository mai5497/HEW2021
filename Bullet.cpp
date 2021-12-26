/**
 * @file Bullet.cpp
 * @Author	園田翔大
 * @Edit	吉原(2021/12/19)
 * @date 2021/11/29 作成
 *		 2021/12/19 赤青玉を判別する変数を追加
 *					赤青玉判別変数のゲッターセッターを追加
					フィールドと弾の当たり判定の処理を追加(吉原)
 * @brief			プレイヤーから発射される弾に関する処理
 */

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include "Bullet.h"
#include <math.h>
#include "Texture.h"


//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define FPS (60)					//フレーム数
#define WAIT_TIME (1.0 * FPS)		//遅延のための時間
#define WAIT_TIME2 (0.8f * FPS)		//遅延のための時間
#define BULLET_GRAVITY (0.1f)		// 弾にかかる重力

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
DrawBuffer* Bullet::m_pBuffer = NULL;			
FBXPlayer* Bullet::m_pFBX = NULL;				

//====================================================================
//
//		コンストラクタ
//
//====================================================================
Bullet::Bullet(DirectX::XMFLOAT3 size):m_rbFlg(true),m_ColFlg(false)
{
	// テクスチャ読み込み
	LoadTextureFromFile("Assets/Model/flowerred.png", &m_pBulletTex);

	// ---変数初期化	m_pos.y = 1000.0f;						//初期座標x
	m_pos.z = 1000.0f;						//初期座標y
	m_pos.x = 1000.0f;						//初期座標z
	m_size.x = 0.25f;				
	m_size.y = 0.25f;
	m_size.z = 0.25f;
	m_sleep = 0;
	m_sleep2 = 0;

}

//====================================================================
//
//		デストラクタ
//
//====================================================================
Bullet::~Bullet()
{
	Uninit();
}

//====================================================================
//
//		初期化
//
//====================================================================
bool Bullet::Init()
{
	// ---モデル読み込み
	if (m_pBuffer) {
		Bullet::LoadBullet("Assets/Model/flowerred.fbx");
	}

	GameObject::Init();
	return true;
}

//====================================================================
//
//		終了処理
//
//====================================================================
void Bullet::Uninit()
{
	// ---テクスチャ解放
	SAFE_RELEASE(m_pBulletTex);

	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;

		delete m_pFBX;
		m_pFBX = NULL;
	}

	// ---キューブの解放
	GameObject::Uninit();
}

//====================================================================
//
//		更新処理
//
//====================================================================
void Bullet::Update()
{
	//毎フレーム初期化
//	m_move = DirectX::XMFLOAT3(0, m_move.y, 0);

	//一定時間後に重力をかける
	//if (m_sleep > WAIT_TIME)
	//{
	//	//このコメントアウト↓外すと一定時間後に弾がゆっくり落下します
	//	//m_move.y -= 3.0f / FPS;
	//	m_move.x = 0;
	//	m_move.y = 0;
	//	m_move.z = 0;
	//	m_sleep = 0;
	//}
	
	//if (m_sleep2 > WAIT_TIME2)
	//{
	//	if (m_pos.y > 0.1f)
	//		m_move.y -= 1.5f / FPS;

	//	m_sleep2 = 0;
	//}

	//m_sleep++;
	//m_sleep2++;

	//if (use == true && m_pos.y > 0.5f) {
	//	
	//	m_move.y -= BULLET_GRAVITY / FPS;			// 重力追加
	//}

	// 重力追加
	m_move.y -= BULLET_GRAVITY;

	//if (m_ColFlg) {
	if (m_pos.y < 1.0f) {							// 今は高さで判定
		m_move.x = 0.0f;
		m_move.y = 0.0f;
		m_move.z = 0.0f;

		SetMove(m_move);
	}

	//座標更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	// オブジェクトの更新(弾の更新)
	GameObject::Update();
}


//====================================================================
//
//		描画処理
//
//====================================================================
void Bullet::Draw()
{
	// 弾のテクスチャ
	int meshNum = m_pFBX->GetMeshNum();
	for (int  i = 0; i < meshNum; ++i){
		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			* DirectX::XMMatrixRotationY(-m_BulletAngle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		SHADER->SetTexture(m_pBulletTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	}
}

//=============================================================
//
//	弾の当たり判定処理
//	作成者	： 園田翔大
//	戻り値	： オブジェクト情報
//　引数		： なし 
//
//=============================================================
void Bullet::OnCollision(GameObject* pObj)
{
	// 弾が使われてないときは終了する
	if (use == false) { return; }

	DirectX::XMFLOAT3 m_Enemypos = pObj->GetPos();		//敵の座標取得
	DirectX::XMFLOAT3 Target = m_pos;							//弾の座標を取得（敵との当たり判定でつかう

	DirectX::XMFLOAT3 dir;
	/*
	dir.x = m_pos.x - m_Enemypos.x;
	dir.y = m_pos.y - m_Enemypos.y;
	dir.z = m_pos.z - m_Enemypos.z;

	float l;
	l = sqrtf(powf(dir.x, 2) + powf(dir.y, 2) + powf(dir.z, 2));
	dir.x = dir.x / l;
	dir.y = dir.y / l;
	dir.z = dir.z / l;

	dir.x = dir.x * 0.025f;
	dir.y = dir.y * 0.025f;
	dir.z = dir.z * 0.025f;
	*/

	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = 0.0f;

	pObj->SetMove(dir);
}


//=============================================================
//
//	当たり判定のセット
//	作成者	： 園田翔大
//	戻り値	： フラグ
//　引数		： なし 
//
//=============================================================
void Bullet::SetColFlg(bool flg) {
	m_ColFlg = flg;
}


//=============================================================
//
//	投げた弾が赤か青かセットする
//	作成者	： 伊地田真衣
//	戻り値	： void
//　引数	： 赤か青かセットtrueが赤falseが青
//
//=============================================================
void Bullet::SetRB(bool flg)
{
	m_rbFlg = flg;
}





//=============================================================
//
//	弾が赤か青か取得
//	作成者	： 伊地田真衣
//	戻り値	： 赤か青かtrueが赤falseが青
//　引数	： void
//
//=============================================================
bool Bullet::GetRB()
{
	return m_rbFlg;
}



//=============================================================
//
//	モデル読み込み
//	作成者	： bool型
//	戻り値	： void
//　引数		： ファイルパス 
//
//=============================================================
bool Bullet::LoadBullet(const char* pFilePath)
{
	/* 以下はモデルが来たら使用 */
	HRESULT hr;
	m_pFBX = new FBXPlayer;
	hr = m_pFBX->LoadModel(pFilePath);
	if (FAILED(hr))
	{
		return false;
	}

	//モデルのメッシュの数だけ頂点バッファ作成
	int meshNum = m_pFBX->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++)
	{
		//メッシュごとに頂点バッファ作成
		m_pBuffer[i].CreateVertexBuffer(
			m_pFBX->GetVertexData(i),
			m_pFBX->GetVertexSize(i),
			m_pFBX->GetVertexCount(i)
		);
		//インデックスバッファ作成
		m_pBuffer[i].CreateIndexBuffer(
			m_pFBX->GetIndexData(i),
			m_pFBX->GetIndexCount(i)
		);

	}
	return true;
}


