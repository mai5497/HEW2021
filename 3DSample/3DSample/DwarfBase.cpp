//****************************************************
//
//	小人ベース
//	作成者：伊地田真衣
//	
//	2021/12/03 : 作成(伊地田)
//	2021/12/11 : ターゲットの座標いれる関数を追加した気がする(伊地田)
//	2021/12/21 : ソース名を変更(伊地田)
//				 赤青小人判定用の変数追加(伊地田)
//	2021/12/22 : 追跡フラグお引越し(伊地田)
//				 移動許可フラグの追加(伊地田)
//	2022/01/20 : 徘徊フラグの追加（伊地田）
//
//****************************************************

//========================= インクルード部 ===========================
#include "DwarfBase.h"

//====================================================================
//
//		コンストラクタ
//
//====================================================================
DwarfBase::DwarfBase():
	m_aliveFlg(true),
	m_FollowFlg(false),
	m_runFlg(false),
	m_MoveFlg(false),
	m_colFlg(false),
	m_CollectionFlg(false),
	m_CircumferenceFlg(false),
	m_liftFlg(false)
{
	//----- 変数初期化 -----
	m_collisionType = COLLISION_DYNAMIC;	// 小人は動く物体
	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_size = XMFLOAT3(DWARF_SIZE, DWARF_SIZE, DWARF_SIZE);

	m_Radius = XMFLOAT3(DWARF_HITBOX_X, DWARF_HITBOX_Y, DWARF_HITBOX_Z);


}


//====================================================================
//
//		デストラクタ
//
//====================================================================
DwarfBase::~DwarfBase() 
{

}


//====================================================================
//
//		更新処理
//
//====================================================================
void DwarfBase::Update() {

}


//====================================================================
//
//		描画処理
//
//====================================================================
void DwarfBase::Draw() 
{
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(
			m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixTranslation(
			m_pos.x, m_pos.y, m_pos.z));

	m_pCube->Draw();	
}


//====================================================================
//
//		ターゲットの座標をいれる
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : ターゲットの座標
//
//====================================================================
void DwarfBase::TargetPos(XMFLOAT3 pos) 
{
	m_targetPos = pos;
}


//====================================================================
//
//		赤青フラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 赤小人か青小人かtrue：赤、false：青
//
//====================================================================
void DwarfBase::SetRBFlg(bool flg) 
{
	m_rbFlg = flg;
}


//====================================================================
//
//		赤青フラグ取得
//		作成者：伊地田真衣
//		戻り値 : 赤小人か青小人かtrue：赤、false：青
//		引数   : void
//
//====================================================================
bool DwarfBase::GetRBFlg()
{
	return m_rbFlg;
}

//====================================================================
//
//		生存フラグのセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 生死true：生、false：死
//
//====================================================================
void DwarfBase::SetAliveFlg(bool flg) 
{
	m_aliveFlg = flg;
}


//====================================================================
//
//		生存フラグの取得
//		作成者：伊地田真衣
//		戻り値 : 生死true：生、false：死
//		引数   : void
//
//====================================================================
bool DwarfBase::GetAliveFlg() 
{
	return m_aliveFlg;
}



//====================================================================
//
//		離れるフラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : セットしたいフラグ(trueで離れる)
//
//====================================================================
void DwarfBase::SetrunFlg(bool flg)
{
	m_runFlg = flg;
}


//====================================================================
//
//		離れるフラグ取得
//		作成者：伊地田真衣
//		戻り値 : 離れるフラグ(trueで離れる)
//		引数   : void
//
//====================================================================
bool DwarfBase::GetrunFlg() 
{
	return m_runFlg;
}


//====================================================================
//
//		追跡フラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : セットしたいフラグ(trueで追跡)
//
//====================================================================
void DwarfBase::SetFollowFlg(bool flg)
{
	m_FollowFlg = flg;
}


//====================================================================
//
//		追跡フラグ取得
//		作成者：伊地田真衣
//		戻り値 : 追跡フラグ(trueで追跡)
//		引数   : void
//
//====================================================================
bool DwarfBase::GetFollowFlg()
{
	return m_FollowFlg;
}


//====================================================================
//
//		移動許可フラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : セットしたいフラグ(trueで許可)
//
//====================================================================
void DwarfBase::SetMoveFlg(bool flg) 
{
	m_MoveFlg = flg;
}


//====================================================================
//
//		移動許可フラグ取得
//		作成者：伊地田真衣
//		戻り値 : 移動許可フラグ(trueで許可)
//		引数   : void
//
//====================================================================
bool DwarfBase::GetMoveFlg()
{
	return m_MoveFlg;
}


//====================================================================
//
//		当たり判定フラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 当たり判定フラグtrue:当たりfalse:当たってない
//
//====================================================================
void DwarfBase::SetColFlg(bool flg)
{
	m_colFlg = flg;
}


//====================================================================
//
//		当たり判定フラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 当たり判定フラグtrue:当たりfalse:当たってない
//
//====================================================================
bool DwarfBase::GetColFlg()
{
	return m_colFlg;
}


//====================================================================
//
//		過去の座標取得
//		作成者：伊地田真衣
//		戻り値 : 過去座標
//		引数   : void
//
//====================================================================
XMFLOAT3 DwarfBase::GetOldPos()
{
	return m_oldPos;
}


//====================================================================
//
//		現在の座標取得
//		作成者：伊地田真衣
//		戻り値 : 現在座標
//		引数   : void
//
//====================================================================
XMFLOAT3 DwarfBase::GetCurrentPos() 
{
	return m_currentPos;
}


//====================================================================
//
//		回収フラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 回収フラグtrue:回収された false:回収されていない
//
//====================================================================
void DwarfBase::SetCollectionFlg(bool flg)
{
	m_CollectionFlg = flg;
}


//====================================================================
//
//		回収フラグ取得
//		作成者：伊地田真衣
//		戻り値 : 回収フラグtrue:回収された false:回収されていない
//		引数   : void
//
//====================================================================
bool DwarfBase::GetCollectionFlg()
{
	return m_CollectionFlg;
}


//====================================================================
//
//		周回フラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 周回フラグtrue:周回する false:周回しない
//
//====================================================================
void DwarfBase::SetCircumferenceFlg(bool flg) {
	m_CircumferenceFlg = flg;
}

//====================================================================
//
//		周回フラグ取得
//		作成者：伊地田真衣
//		戻り値 : 回収フラグtrue:回収された false:回収されていない
//		引数   : void
//
//====================================================================
bool DwarfBase::GetCircumferenceFlg() {
	return m_CircumferenceFlg;
}


//====================================================================
//
//		浮くフラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 浮いてるtrue
//
//====================================================================
void DwarfBase::SetLiftFlg(bool flg) {
	m_liftFlg = flg;
}


//====================================================================
//
//		浮くフラグセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 浮いてるtrue
//
//====================================================================
bool DwarfBase::GetLiftFlg() {
	return m_liftFlg;
}


//====================================================================
//
//		弾の生存時間のセット
//		作成者：伊地田真衣
//		戻り値 : void
//		引数   : 弾の生存時間
//
//====================================================================
void DwarfBase::SetBulletAliveTimer(int time) {
	m_CircumferenceTimer = time;
}

