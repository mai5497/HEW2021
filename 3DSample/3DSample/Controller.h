//
// 
//  _(._.)_
//
//


#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <DirectXMath.h>
#include <map>
#pragma comment(lib, "Xinput.lib")

using namespace std;
using namespace DirectX;

struct Stick {
	float direction;
	float length;
};

/**
 * @class Input
 * @brief インプットクラス
 */
class Input {
private:
	const float STICK_MAX_INPUT = 32767.0f;
	const float TRIGGER_MAX_INPUT = 255.0f;
	const float MAX_VIBRATION = 65535.0f;

	BYTE  m_key[256];					//!< キーボード情報
	map<UINT, UINT> m_keyCount;			//!< キーの入力継続時間
	POINT m_cursorPos;					//!< カーソル座標
	POINT m_prevCursorPos;				//!< 前フレームのカーソル座標
	XINPUT_STATE m_controller;			//!< コントローラー情報
	map<UINT, UINT> m_buttonCount;		//!< ボタンの入力継続時間
	Stick m_rightStick;					//!< 右スティックの情報
	Stick m_prevRightStick;				//!< 前フレームの右スティックの情報
	Stick m_leftStick;					//!< 左スティックの情報
	Stick m_prevLeftStick;				//!< 前フレームの左スティックの情報
	float m_rightTrigger;				//!< 右トリガーの入力値
	float m_leftTrigger;				//!< 左トリガーの入力値
	map<float, int> m_rightVibration;	//!< 高周波振動データを保持するコンテナ
	map<float, int> m_leftVibration;	//!< 低周波振動データを保持するコンテナ
	bool m_connection;					//!< コントローラーの接続状況(true:接続中/false:接続不可)

	/**
	 * @brief コンストラクタ
	 */
	Input() = default;
	/**
	 * @brief デストラクタ
	 */
	~Input() = default;
	/**
	 * @brief コピーコンストラクタ
	 * @details 複製を禁止に
	 */
	Input(const Input&) = delete;
	/**
	 * @brief =演算子のオーバーロード
	 * @details 代入を禁止に
	 */
	void operator=(const Input&) = delete;
public:
	/**
	 * @brief シングルトンインスタンスの取得
	 * @return static Input& インスタンス
	 */
	static Input& instance();
	/**
	 * @brief 初期化処理
	 * @details ウィンドウハンドルの初期化
	 */
	void update(HWND& hWnd);
	/**
	 * @brief キー入力の取得
	 * @param[in] unsigned int キーコード
	 * @return bool キーが押されていたらtrueを返す
	 */
	bool getKeyPress(UINT key);
	/**
	 * @brief キーが押された瞬間の取得
	 * @param[in] unsigned int キーコード
	 * @return bool キーが押された最初のフレームだけtrueを返す
	 */
	bool getKeyTrigger(UINT key);
	/**
	 * @brief キーが離された瞬間の取得
	 * @param[in] unsigned int キーコード
	 * @return bool キーが離された最初のフレームだけtrueを返す
	 */
	bool getKeyRelease(UINT key);
	/**
	 * @brief キー入力を一定間隔で取得
	 * @param[in] unsigned int キーコード
	 * @param[in] unsigned int リピート間隔
	 * @return bool キーが入力されていたら一定間隔ごとにtrueを返す
	 */
	bool getKeyRepeat(UINT key, UINT interval);
	/**
	 * @brief キー入力継続時間の取得
	 * @param[in] unsigned int キーコード
	 * @return unsigned int 入力継続時間
	 */
	UINT getKeyHoldTime(UINT key);
	/**
	 * @brief マウスカーソルのクライアントx座標の取得
	 * @return float カーソルx座標
	 */
	float getCursorPosX();
	/**
	 * @brief マウスカーソルのクライアントy座標の取得
	 * @return float カーソルy座標
	 */
	float getCursorPosY();
	/**
	 * @brief マウスカーソルのx軸速度の取得
	 * @return float カーソルx軸速度
	 */
	float getCursorSpeedX();
	/**
	 * @brief マウスカーソルのy軸速度の取得
	 * @return float カーソルy軸速度
	 */
	float getCursorSpeedY();
	/**
	 * @brief コントローラーの接続状況の取得
	 * @return bool コントローラー接続があればtrueを返す
	 */
	bool getControllerConnection();
	/**
	 * @brief コントローラーのボタン入力の取得
	 * @param[in] unsigned int ボタンコード
	 * @return bool ボタンが押されていたらtrueを返す
	 */
	bool getButtonPress(UINT button);
	/**
	 * @brief コントローラーのボタンが押された瞬間の取得
	 * @param[in] unsigned int ボタンコード
	 * @return bool ボタンが押された最初のフレームだけtrueを返す
	 */
	bool getButtonTrigger(UINT button);
	/**
	 * @brief コントローラーのボタンが離された瞬間の取得
	 * @param[in] unsigned int ボタンコード
	 * @return bool ボタンが離された最初のフレームだけtrueを返す
	 */
	bool getButtonRelease(UINT button);
	/**
	 * @brief ボタン入力を一定間隔で取得
	 * @param[in] unsigned int ボタンコード
	 * @param[in] unsigned int リピート間隔
	 * @return bool ボタンが入力されていたら一定間隔ごとにtrueを返す
	 */
	bool getButtonRepeat(UINT button, UINT interval);
	/**
	 * @brief ボタン入力継続時間の取得
	 * @param[in] unsigned int ボタンコード
	 * @return unsigned int 入力継続時間
	 */
	UINT getButtonHoldTime(UINT button);
	/**
	 * @brief コントローラーの右スティックx軸入力の取得
	 * @return float 右スティックx軸入力(-1.0~1.0)
	 */
	float getRightStickX();
	/**
	 * @brief コントローラーの右スティックy軸入力の取得
	 * @return float 右スティックy軸入力(-1.0~1.0)
	 */
	float getRightStickY();
	/**
	 * @brief コントローラーの左スティックx軸入力の取得
	 * @return float 左スティックx軸入力(-1.0~1.0)
	 */
	float getLeftStickX();
	/**
	 * @brief コントローラーの左スティックy軸入力の取得
	 * @return float 左スティックy軸入力(-1.0~1.0)
	 */
	float getLeftStickY();
	/**
	 * @brief コントローラーの右スティックの入力強度の取得
	 * @return float 右スティック入力強度(-1.0~1.0)
	 */
	float getRightStickMagnitude();
	/**
	 * @brief コントローラーの左スティックの入力強度の取得
	 * @return float 左スティック入力強度(-1.0~1.0)
	 */
	float getLeftStickMagnitude();
	/**
	 * @brief コントローラーの右スティックx軸速度の取得
	 * @return float 右スティックx軸速度(-1.0~1.0)
	 */
	float getRightStickSpeedX();
	/**
	 * @brief コントローラーの右スティックy軸速度の取得
	 * @return float 右スティックy軸速度(-1.0~1.0)
	 */
	float getRightStickSpeedY();
	/**
	 * @brief コントローラーの左スティックy軸速度の取得
	 * @return float 左スティックy軸速度(-1.0~1.0)
	 */
	float getLeftStickSpeedX();
	/**
	 * @brief コントローラーの左スティックy軸速度の取得
	 * @return float 左スティックy軸速度(-1.0~1.0)
	 */
	float getLeftStickSpeedY();
	/**
	 * @brief コントローラーの右スティック入力角度の取得
	 * @return float 右スティック入力角度(0.0~360.0)
	 */
	float getRightStickDirection();
	/**
	 * @brief コントローラーの左スティック入力角度の取得
	 * @return float 左スティック入力角度(0.0~360.0)
	 */
	float getLeftStickDirection();
	/**
	 * @brief コントローラーの右トリガー入力の取得
	 * @return float 右トリガー入力(0.0~1.0)
	 */
	float getRightTrigger();
	/**
	 * @brief コントローラーの左トリガー入力の取得
	 * @return float 左トリガー入力(0.0~1.0)
	 */
	float getLeftTrigger();
	/**
	 * @brief コントローラーの高周波振動の設定
	 * @param[in] float 振動強度(0.0~1.0)
	 * @param[in] unsigned int 振動フレーム数
	 * @return bool true:成功
	 */
	bool setRightVibration(float power, UINT frame);
	/**
	 * @brief コントローラーの低周波振動の設定
	 * @param[in] float 振動強度(0.0~1.0)
	 * @param[in] unsigned int 振動フレーム数
	 * @return bool true:成功
	 */
	bool setLeftVibration(float power, UINT frame);
};