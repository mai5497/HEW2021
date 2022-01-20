//====================================================================
//
// 弾の落下地点[BulletTarget.cpp]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/15	作成
//====================================================================

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	<math.h>
#include	"MyMath.h"

#include	"BulletTarget.h"
#include	"Input.h"
#include	"Controller.h"



 //*******************************************************************************
 // 定数・マクロ定義
 //*******************************************************************************
#define TARGET_POS_X		(0.0f)
#define TARGET_POS_Y		(1.2f)
#define TARGET_POS_Z		(0.0f)

#define TARGET_SIZE_X	(1.0f)
#define TARGET_SIZE_Y		(0.0f)
#define TARGET_SIZE_Z		(1.0f)

#define L_PI			(3.1415926f)		// π
#define L_H_DEG			(180.0f)			// 角度
#define	TRANS_RADIAN	(L_PI / L_H_DEG)	// ラジアンに変換

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
//DrawBuffer* BulletTarget::m_pBuffer = NULL;
//FBXPlayer* BulletTarget::m_pFBX = NULL;
Camera* g_pBulletTargetCamera;

//==============================================================
//
//	BulletTargetクラス::コンストラクタ
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
BulletTarget::BulletTarget() : m_pCamera(nullptr)
{

}

//==============================================================
//
//	BulletTargetクラス::デストラクタ
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
BulletTarget::~BulletTarget()
{

}

//==============================================================
//
//	BulletTargetクラス::初期化
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
bool BulletTarget::Init()
{
	LoadTextureFromFile("Assets/Model/Target.png", &m_pBulletTargetTex);

	GameObject::Init();

	// カメラインスタンスの初期化
	//m_pCamera = new Camera;
	//m_pCamera->Init();
	g_pBulletTargetCamera = new Camera;
	g_pBulletTargetCamera->Init();

	//---テクスチャ読み込み

	//---変数初期化
	m_pos = XMFLOAT3(TARGET_POS_X, TARGET_POS_Y, TARGET_POS_Z);
	m_size = XMFLOAT3(TARGET_SIZE_X, TARGET_SIZE_Y, TARGET_SIZE_Z);
	m_Angle = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_collisionType = COLLISION_DYNAMIC;			// 当たり判定を取るときのオブジェクトの種類の設定



	return true;

}


//==============================================================
//
//	BulletTargetクラス::終了
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void BulletTarget::Uninit()
{
	//if (m_pBuffer != NULL) {
	//	delete[] m_pBuffer;
	//	m_pBuffer = NULL;
	//}

	//if (m_pFBX != NULL) {
	//	delete[] m_pFBX;
	//	m_pFBX = NULL;
	//}

	//---テクスチャ解放
	SAFE_RELEASE(m_pBulletTargetTex);

	//// カメラインスタンス解放
	m_pCamera->Uninit();
	delete m_pCamera;
	//g_pBulletTargetCamera->Uninit();
	//delete g_pBulletTargetCamera;

	GameObject::Uninit();
}

//==============================================================
//
//	BulletTargetクラス::更新
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void BulletTarget::Update()
{
	//---変数初期化
	XMFLOAT2 Axis = XMFLOAT2(0.0f, 0.0f);
	Axis = LeftThumbPosition();
	bool moveFlg = false;					// 移動フラグ

	const float Move = (10.0f / FPS) * 4;	// 1秒間で4M進む

	m_move = XMFLOAT3(Axis.x, m_move.y, Axis.y);

	//---カメラの向きを取得(ラジアンに変換)
	//float CameraRad = m_pCamera->GetxzAngle() * TRANS_RADIAN;
	
	// ターゲットオブジェクト移動
	//if (m_move.x != 0.0f && m_move.y != 0.0f) {
		if (IsPress(VK_LEFT)) {			// 左
			moveFlg = true;
			m_move.x -= Move;
		}
		if (IsPress(VK_RIGHT)) {		// 右
			moveFlg = true;
			m_move.x += Move;
		}
		if (IsPress(VK_UP)) {			// 上
			moveFlg = true;
			m_move.z += Move;
		}
		if (IsPress(VK_DOWN)) {			// 下
			moveFlg = true;
			m_move.z -= Move;
		}
	//}
	//MyVector2 Direction(0.0f, 0.0f);

	// 極座標を使ったTPS視点
	//Direction.x = m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//Direction.y = m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);
	//Direction = Direction.GetNormalize();
	//Direction.x = m_move.x - m_move.z;
	//Direction.y = m_move.x + m_move.z;

	// 描画用角度変更だよ
	// atan ... アークタンジェントの関数
	if (moveFlg == true) {
		m_DrawAngle  = atan2(m_move.z, m_move.x);
		m_DrawAngle -= XM_PI * 0.5f;
	}

	//m_move.x = Direction.x * Move;
	//m_move.z = Direction.y * Move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
 }

//==============================================================
//
//	BulletTargetクラス::描画
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void BulletTarget::Draw()
{
	SHADER->Bind(VS_WORLD, PS_PHONG);
	//m_pCamera->Bind();

	//int MeshNum = m_pFBX->GetMeshNum();
	//for (int i = 0; i < MeshNum; ++i){
	SHADER->SetTexture(m_pBulletTargetTex);

	SHADER->SetWorld
	(
		XMMatrixScaling(m_size.x, m_size.y, m_size.z)*
		XMMatrixRotationY(-m_DrawAngle)*
		XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);

	GameObject::Draw();

	SHADER->SetTexture(NULL);

	//	m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//}

}


//==============================================================
//
//	BulletTargetクラス::座標取得
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
XMFLOAT3 BulletTarget::GetBulletTargetPos()
{
	return m_pos;
}