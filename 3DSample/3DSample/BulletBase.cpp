//====================================================================
//
// 弾のベース
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/03	作成
//		 :2022/01/11	サウンド追加
//		 :2022/01/16	着地SEうるせえから静かにした（伊地田）
//		 :2022/01/17	弾が地面に当たった瞬間をとるフラグの作成（伊地田）
//====================================================================

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"BulletBase.h"
#include	"Sound.h"

//========================= グローバル変数定義 ===========================
DrawBuffer* BulletBase::m_pBuffer[MAX_BULLET_COLOR] = { nullptr, nullptr };
FBXPlayer* BulletBase::m_pBulletModel[MAX_BULLET_COLOR] = { nullptr, nullptr };


//==============================================================
//
//	BulletBase::コンストラクタ
// 
//==============================================================
BulletBase::BulletBase() :
	m_rbFlg(true),
	m_ColFlg(false),
	m_LandingFlg(false)
{
	// ---変数初期化	
	m_pos.x = 1000.0f;						//初期座標x
	m_pos.y = 1000.0f;						//初期座標y
	m_pos.z = 1000.0f;						//初期座標z
	m_size.x = 2.0f;
	m_size.y = 2.0f;
	m_size.z = 2.0f;
	m_sleep = 0;
	m_sleep2 = 0;
	m_Radius = XMFLOAT3(10.0f, 0.1f, 10.0f);

	m_BulletAngle = 0.0f;					// 角度の初期化
	m_dir = XMFLOAT3(0.0f, 0.0f, 0.0f);		// 向き
	m_AliveTime = BULLET_DESTOROY_CNT;		// 生存時間

	//----- モデル・テクスチャ一括読込 -----
	LoadTextureFromFile("Assets/Texture/flowerblue.png", &m_pBulletTex[BLUE_BULLET]);
	LoadTextureFromFile("Assets/Texture/flowerred.png", &m_pBulletTex[RED_BULLET]);

	for (int i = 0; i < MAX_BULLET_COLOR; i++) {
		m_pBulletModel[i] = new FBXPlayer;
	}
	LoadModel("Assets/Model/flowerblue.fbx", BLUE_BULLET);
	m_flowerAnim[BLUE_BLAST] = m_pBulletModel[BLUE_BULLET]->LoadAnimation("Assets/Model/flowerblue_anime.fbx");
	LoadModel("Assets/Model/flowerred.fbx", RED_BULLET);
	m_flowerAnim[RED_BLAST] = m_pBulletModel[RED_BULLET]->LoadAnimation("Assets/Model/flowerred_anime.fbx");

}


//==============================================================
//
//	BulletBase::デストラクタ
//
//==============================================================
BulletBase::~BulletBase()
{
	for (int i = 0; i < MAX_BULLET_COLOR; i++) {
		SAFE_RELEASE(m_pBulletTex[i]);
	}
	for (int i = 0; i < MAX_BULLET_COLOR; i++) {
		delete m_pBulletModel[i];
		m_pBulletModel[i] = nullptr;
	}
	if (m_pBuffer != nullptr) {
		for (int i = 0; i < MAX_BULLET_COLOR; i++) {
			delete[] m_pBuffer[i];
			m_pBuffer[i] = nullptr;
		}
	}
}

//==============================================================
//
//	更新処理
//
//==============================================================
void BulletBase::Update()
{
	// 重力追加
	//m_move.y -= BULLET_GRAVITY;

	//---放物線をベジェ曲線の計算で処理を行う
	// ベジェ曲線で算出した値を各座標に格納
	// CurrentPos = m_pos となる 

	// 弾の投擲時間を進める(定数で投げ終わる時間を決めれる)
	m_ThrowTimer += 1.3f / BULLET_THROW_CNT;


	if (m_ThrowTimer <= 1.0f) {

	m_pos.x = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.x + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.x + m_ThrowTimer * m_ThrowTimer * m_EndPos.x;

	m_pos.y = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.y + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.y + m_ThrowTimer * m_ThrowTimer * m_EndPos.y;

	m_pos.z = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.z + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.z + m_ThrowTimer * m_ThrowTimer * m_EndPos.z;
	}
	else {

		//if (m_ColFlg) {
		//if (m_pos.y < 1.7f) {							// 今は高さで判定
		//if(m_ThrowTimer > 1.0f){
			m_ColFlg = true;
			//m_move.x = 0.0f;
			//m_move.y = 0.0f;
			//m_move.z = 0.0f;

			//SetMove(m_move);

			//use = false;
		//}
	}
	if (m_ColFlg) {
		if (m_AliveTime == BULLET_DESTOROY_CNT) {
			// サウンド
			CSound::Play(SE_BULLET_2);
			m_LandingFlg = true;	// 弾が地面についた瞬間
		} else {
			m_LandingFlg = false;
		}


		// 弾の時間経過での破壊処理
		m_AliveTime--;					// 生存時間のカウントダウン
		if (m_AliveTime < 0) {			// 0以下になったら
			use = false;					// 使用フラグを変更
			Uninit();
		}
	}

}

//==============================================================
//
//	描画処理
//
//==============================================================
void BulletBase::Draw()
{
	/* テクスチャ描画 */
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * 
					DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

	m_pCube->Draw();
}

//====================================================================
//
//		モデル読み込み
//
//====================================================================
bool BulletBase::LoadModel(const char* pFilePath,int index) {
	/* 以下はモデルが来たら使用 */
	HRESULT hr;
	hr = m_pBulletModel[index]->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//モデルのメッシュの数だけ頂点バッファ作成
	int meshNum = m_pBulletModel[index]->GetMeshNum();
	m_pBuffer[index] = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
		//メッシュごとに頂点バッファ作成
		m_pBuffer[index][i].CreateVertexBuffer(
			m_pBulletModel[index]->GetVertexData(i),
			m_pBulletModel[index]->GetVertexSize(i),
			m_pBulletModel[index]->GetVertexCount(i)
		);
		//インデックスバッファ作成
		m_pBuffer[index][i].CreateIndexBuffer(
			m_pBulletModel[index]->GetIndexData(i),
			m_pBulletModel[index]->GetIndexCount(i)
		);

	}
	return true;
}

//=============================================================
//
//	投げた弾が赤か青かセットする
//	作成者	： 伊地田真衣
//	戻り値	： void
//　引数	： 赤か青かセットtrueが赤falseが青
//
//=============================================================
void BulletBase::SetRBFlg(bool flg)
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
bool BulletBase::GetRBFlg()
{
	return m_rbFlg;
}

//=============================================================
//
//	当たり判定のセット
//	作成者	： 伊地田真衣
//	戻り値	： なし
//　引数		： セットしたいフラグ 
//
//=============================================================
void BulletBase::SetColFlg(bool flg) {
	m_ColFlg = flg;
}

//=============================================================
//
//	当たり判定フラグ（地面に当たった瞬間）のセット
//	作成者	： 伊地田真衣
//	戻り値	： フラグ
//　引数		： なし 
//
//=============================================================
bool BulletBase::GetLandingFlg() {
	return m_LandingFlg;
}


//=============================================================
//
//	ベジェ曲線による算出を行うための座標を取得
//	作成者	： 吉原飛鳥
//	戻り値	： なし
//　引数		： XMFLOAT3型で3つの座標を取得 
//
//=============================================================
void BulletBase::SetBezierInfo(XMFLOAT3 startPos, XMFLOAT3 endPos, XMFLOAT3 centerPos,float ThrowTimer)		
{
	m_StarPos = startPos;
	m_EndPos = endPos;
	m_CenterPos = centerPos;
	m_ThrowTimer = ThrowTimer;
}


//=============================================================
//
//	着地フラグの取得
//	作成者	： 伊地田真衣
//	戻り値	： 着地フラグ
//　引数	： なし 
//
//=============================================================
bool BulletBase::GetColFlg() {
	return m_ColFlg;
}


//=============================================================
//
//	弾の生存時間の取得
//	作成者	： 伊地田真衣
//	戻り値	： 弾の生存時間
//　引数	： なし
//
//=============================================================
int BulletBase::GetAliveTime() {
	return m_AliveTime;
}
