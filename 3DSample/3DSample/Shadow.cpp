//====================================================================
//
// 影[Shadow.h]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/24	作成
//====================================================================

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"Shadow.h"

//==============================================================
// 
//	Shadowクラス::コンストラクタ
// 
//==============================================================
Shadow::Shadow()
{

}

//==============================================================
// 
//	Shadowクラス::デストラクタ
// 
//==============================================================
Shadow::~Shadow()
{

}

//==============================================================
// 
//	Shadowクラス::初期化
// 
//==============================================================
bool Shadow::Init()
{
	
	//---テクスチャ読み込み
	LoadTextureFromFile("Assets/Model/shadow000.jpg", &m_pShadowTex);

	//---オブジェクトインスタンス
	//m_pPolygonShadow = new GameObject;
	//m_pPolygonShadow->Init();
	//m_pPolygonShadow->SetPos(XMFLOAT3(0.0f, 5.0f, 0.0f));
	//m_pPolygonShadow->SetSize(XMFLOAT3(10.0f, 10.0f, 10.0f));
	GameObject::Init();

	m_pos = XMFLOAT3(0.0f, 1.6f, 0.0f);
	m_size = XMFLOAT3(3.0f, 0.0f, 3.0f);
	m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f,1.0f);
	m_Angle = XMFLOAT3(0.0f, 0.0f, 0.0f);

	
	//---カメラインスタンス
	//m_pCameraShadow = new Camera;
	//m_pCameraShadow->Init(XMFLOAT3(0.0f, 3.0f, 0.0f));

	return true;

}

//==============================================================
// 
//	Shadowクラス::終了
// 
//==============================================================
void Shadow::Uninit()
{
	SAFE_RELEASE(m_pShadowTex);

	//---オブジェクトインスタンス解放
	//m_pPolygonShadow->Uninit();
	//delete m_pPolygonShadow;
	GameObject::Uninit();

	//---カメラインスタンス解放
	//m_pCameraShadow->Uninit();
	//delete m_pCameraShadow;
}

//==============================================================
// 
//	Shadowクラス::更新
// 
//==============================================================
void Shadow::Update()
{

}

//==============================================================
// 
//	Shadowクラス::描画
// 
//==============================================================
void Shadow::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	//m_pCameraShadow->Bind();

	SHADER->SetTexture(m_pShadowTex);

	SHADER->SetWorld
	(
		XMMatrixScaling(m_size.x, m_size.y, m_size.z) *
		XMMatrixRotationY(m_Angle.y) *
		XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);

	GameObject::Draw();


	SHADER->SetTexture(NULL);
}

//==============================================================
// 
//	Shadowクラス::座標の設定
// 
//==============================================================
void Shadow::SetShadow(XMFLOAT3 pos)
{
	
}