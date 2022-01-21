/**
 * @file Input.h
 * @Author 園田翔大
 * @date 2020/08/07 作成
 * @brief キー、マウス、ジョイパッド入力を扱う
 */
#pragma once
#define NOMINMAX
#include <Windows.h>
#include <DirectXMath.h>
#include <Xinput.h>


enum class JPadButton {
	DPAD_UP			= 0x1,
	DPAD_DOWN		= 0x2,
	DPAD_LEFT		= 0x4,
	DPAD_RIGHT		= 0x8,
	START			= 0x10,
	BACK			= 0x20,
	L_THUMB			= 0x40,
	R_THUMB			= 0x80,
	L_SHOULDER		= 0x100,
	R_SHOULDER		= 0x200,
	L_TRIGGER		= 0x400,
	R_TRIGGER		= 0x800,
	A				= 0x1000,
	B				= 0x2000,
	X				= 0x4000,
	Y				= 0x8000,
	L_THUMB_UP		= 0x10000,
	L_THUMB_DOWN	= 0x20000,
	L_THUMB_LEFT	= 0x40000,
	L_THUMB_RIGHT	= 0x80000,
	R_THUMB_UP		= 0x100000,
	R_THUMB_DOWN	= 0x200000,
	R_THUMB_LEFT	= 0x400000,
	R_THUMB_RIGHT	= 0x800000
};

// @brief 入力情報の取得・更新
void UpdateInput(HWND&, float);

// @brief キーを押しているかを取得
// @param[in] key	VK_SPACE 等で指定
// @return bool
bool IsPress(unsigned char key);

// @brief キーを押した瞬間を取得
// @param[in] key	VK_SPACE 等で指定
// @return bool
bool IsTrigger(unsigned char key);

// @brief キーを離した瞬間を取得
// @param[in] key	VK_SPACE 等で指定
// @return bool
bool IsRelease(unsigned char key);

// @brief キーを押している間一定間隔でtrueを返す
// @param[in] key	VK_SPACE 等で指定
// @param[in] cycle	trueを返す周期
// @return bool
bool IsRepeat(unsigned char key, unsigned int cycle);
// @brief キーを離した瞬間を取得
// @param[in] key	VK_SPACE 等で指定
// @return uint	押し込み継続時間
unsigned int HoldTime(unsigned char key);
// @brief ボタンを押しているかを取得
// @param[in] button	JPadButton::A等で指定
// @return bool
bool IsPress(JPadButton button);
// @brief ボタンを押した瞬間を取得
// @param[in] button	JPadButton::A等で指定
// @return bool
bool IsTrigger(JPadButton button);
// @brief ボタンを離した瞬間を取得
// @param[in] button	JPadButton::A等で指定
// @return bool
bool IsRelease(JPadButton button);
// @brief ボタンを押している間一定間隔でtrueを返す
// @param[in] button	JPadButton::A等で指定
// @param[in] cycle	trueを返す周期
// @return bool
bool IsRepeat(JPadButton button, unsigned int cycle);
// @brief ボタンを離した瞬間を取得
// @param[in] button	JPadButton::A等で指定
// @return uint	押し込み継続時間
unsigned int HoldTime(JPadButton button);
// @brief カーソル座標の取得
// @return DirectX::XMFLOAT2	位置
DirectX::XMFLOAT2 CursorPosition();
// @brief カーソル加速度の取得
// @return DirectX::XMFLOAT2	加速度
DirectX::XMFLOAT2 CursorAcceleration();
// @brief マウスホイール回転速度の取得
// @return float	回転速度	
float MouseWheelDelta();
// @brief 左スティック位置の取得
// @return DirectX::XMFLOAT2	位置(正規化済み)
DirectX::XMFLOAT2 LeftThumbPosition();
// @brief 右スティック位置の取得
// @return DirectX::XMFLOAT2	位置(正規化済み)
DirectX::XMFLOAT2 RightThumbPosition();
// @brief 左スティック加速度の取得
// @return DirectX::XMFLOAT2	加速度(正規化済み)
DirectX::XMFLOAT2 LeftThumbAcceleration();
// @brief 右スティック加速度の取得
// @return DirectX::XMFLOAT2	加速度(正規化済み)
DirectX::XMFLOAT2 RightThumbAcceleration();
// @brief 左トリガー押し込み強度の取得
// @return DirectX::XMFLOAT2	強度(0.0f~1.0f)
float LeftTriggerStrength();
// @brief 右トリガー押し込み強度の取得
// @return DirectX::XMFLOAT2	強度(0.0f~1.0f)
float RightTriggerStrength();
// @brief 左トリガー押し込み加速度の取得
// @return DirectX::XMFLOAT2	加速度(0.0f~1.0f)
float LeftTriggerAcceleration();
// @brief 右トリガー押し込み加速度の取得
// @return DirectX::XMFLOAT2	加速度(0.0f~1.0f)
float RightTriggerAcceleration();
// @brief 左モーターの振動を設定
// @param[in] power	振動強度(0.0f~1.0f)
// @param[in] frame 振動フレーム
void LeftVibration(float power, unsigned int frame);
// @brief 右モーターの振動を設定
// @param[in] power	振動強度(0.0f~1.0f)
// @param[in] frame 振動フレーム
void RightVibration(float power, unsigned int frame);
// @brief コントローラーの接続状況
// @return bool	true : 接続中
bool IsJoyPadConnection();