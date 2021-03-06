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
#include	"Input.h"
#include	"Controller.h"
#include	"Camera.h"
#include	"Shader.h"

#include	"BulletTarget.h"



 //*******************************************************************************
 // 定数・マクロ定義
 //*******************************************************************************

//---座標系
#define TARGET_POS_X		(0.0f)			
#define TARGET_POS_Y		(2.0f)
#define TARGET_POS_Z		(-20.0f)

//---サイズ系
#define TARGET_SIZE_X		(3.0f)
#define TARGET_SIZE_Y		(0.0f)
#define TARGET_SIZE_Z		(3.0f)

//---数学系
#define L_PI				(3.1415926f)			// π
#define L_H_DEG				(180.0f)				// 角度
#define	TRANS_RADIAN		(L_PI / L_H_DEG)		// ラジアンに変換

//---弾の調整値
#define	BULLET_THROEWPOWER	((1.0f / FPS) * 40.0f)	// 弾の飛距離の速度

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
DrawBuffer* BulletTarget::m_pBTBuffer = NULL;
FBXPlayer* BulletTarget::m_pBTFBX = NULL;
Camera* g_pBulletTargetCamera;
GameObject* g_pBulletTarget;

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

	// カメラインスタンスの初期化
	//m_pCamera = new Camera;
	//m_pCamera->Init();
	//g_pBulletTargetCamera = new Camera;
	//g_pBulletTargetCamera->Init();

	//---テクスチャ読み込み
	LoadTextureFromFile("Assets/Model/Target2.png", &m_pBulletTargetTex);

	//g_pBulletTarget = new GameObject;
	//g_pBulletTarget->Init();

	GameObject::Init();

	//---変数初期化
	//g_pBulletTarget->SetPos((XMFLOAT3(TARGET_POS_X, TARGET_POS_Y, TARGET_POS_Z)));
	//g_pBulletTarget->SetSize(XMFLOAT3(TARGET_SIZE_X, TARGET_SIZE_Y, TARGET_SIZE_Z));
	//g_pBulletTarget->SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//g_pBulletTarget->SetAngle(XMFLOAT3(XM_PI / 2, 0.0f, 0.0f));

	m_pos = (XMFLOAT3(TARGET_POS_X, TARGET_POS_Y, TARGET_POS_Z));
	m_size = (XMFLOAT3(TARGET_SIZE_X, TARGET_SIZE_Y, TARGET_SIZE_Z));
	m_Color = (XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f));
	m_Angle = (XMFLOAT3(XM_PI / 2, 0.0, 0.0f));

	m_ThrowDir = 1.0f;


	//m_MoveSpeed = (1.0f / FPS) * 100.0f;
	//m_MoveSpeed = atan2(m_move.z, m_move.x);
	//m_MoveSpeed = BULLET_THROEWPOWER;				// 弾の飛距離の速度
	 
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
	//m_pCamera->Uninit();
	//delete m_pCamera;
	//g_pBulletTargetCamera->Uninit();
	//delete g_pBulletTargetCamera;

	//g_pBulletTarget->Uninit();
	//delete g_pBulletTarget;

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

	 float Move = (10.0f / FPS) * 4;	// 1秒間で2M進む

	m_move = XMFLOAT3(Axis.x, 0.0f, 0.0f);


	// ターゲットオブジェクト移動
	//if (m_move.x != 0.0f && m_move.y != 0.0f) {
	if (IsPress('A') || IsPress(VK_LEFT)) {			// 左
		m_move.x -= Move;
		
		if (m_pos.x < -40.0f){
			m_pos.x = -40.0f;
		}
	}
	if (IsPress('D') || IsPress(VK_RIGHT)) {		// 右
		m_move.x += Move;
		
		if (m_pos.x > 40.0f) {
			m_pos.x = 40.0f;
		}
	}

	m_MoveSpeed.x = 0.0f;
	m_MoveSpeed.z = 0.0f;
	
	if (IsRepeat(('Q'),1) || IsRepeat((JPadButton::X),1)|| 
		IsRepeat(('E'),1) || IsRepeat((JPadButton::A),1)){			// 変更後ー上
		/* 
			キーはなしたら帰ってきた！！！なんで！！！！わあ！！！！	(2022/01/21時点)
			できた！！まんじ！！								(2022/01/22時点)
		*/
		

		// 距離の計算(ターゲットとプレイヤーの距離)
		// 三平方の定理によって算出
		m_Distance = sqrt((m_pos.x - m_PlayerPos.x) * (m_pos.x - m_PlayerPos.x) + (m_pos.z - m_PlayerPos.z) * (m_pos.z - m_PlayerPos.z));

		
		if (m_Distance > 50.0f) {		// 一定の奥まで
			// 距離の離れた大きさによって位置フレーム前の座標に再配置
			m_Distance = 50.0f;
			m_ThrowDir = -1.0f;			// 反転
		}

		if (m_Distance < 10.0f) {		// 一定の手前まで
			// 距離の離れた大きさによって位置フレーム前の座標に再配置
			m_Distance = 10.0f;
			m_ThrowDir = 1.0f;			// 反転


		}
		

		m_RotAngle.x = cos(m_ThrowAngle + XM_PI / 2.0f);
		m_RotAngle.z = sin(m_ThrowAngle + XM_PI / 2.0f);

		m_MoveSpeed.x = m_RotAngle.x * BULLET_THROEWPOWER * m_ThrowDir;
		m_MoveSpeed.z = m_RotAngle.z * BULLET_THROEWPOWER * m_ThrowDir;

		//m_move.z = m_MoveSpeed;		// 移動方向反転

	}


	m_pos.x += m_move.x + m_MoveSpeed.x;
	//m_pos.y += m_move.y;
	m_pos.z += m_move.z + m_MoveSpeed.z;
 }

//============================================================
//
//	BulletTargetクラス::描画
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void BulletTarget::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	//m_pCamera->Bind2D();

	//g_pBulletTargetCamera->Bind2D();

	//int MeshNum = m_pBTFBX->GetMeshNum();

	//for (int i = 0; i < MeshNum; ++i){
	SHADER->SetTexture(m_pBulletTargetTex);

	SHADER->SetWorld
	(
		XMMatrixScaling(m_size.x, m_size.y, m_size.z)*
		XMMatrixRotationX(XM_PI / 2) * 
		XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);

	//g_pBulletTarget->Draw();


	GameObject::Draw();

	SHADER->SetTexture(NULL);

		//m_pBTBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//}

}

//==============================================================
//
//	BulletTargetクラス::座標設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： XMFLOAT3
//
//==============================================================
void BulletTarget::SetBulletTargetPos(XMFLOAT3 pos) 
{
	m_pos = pos;
}

//==============================================================
//
//	BulletTargetクラス::プレイヤーの座標を設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： XMFLOAT3
//
//==============================================================
void BulletTarget::SetPlayerPos(XMFLOAT3  pos)
{
	m_PlayerPos = pos;
}

//==============================================================
//
//	BulletTargetクラス::プレイヤーの向く角度を設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： XMFLOAT3
//
//==============================================================
void BulletTarget::SetPlayerDrawAngle(float  PlayerAngle)
{
	m_ThrowAngle = PlayerAngle;
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