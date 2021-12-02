#include <DirectXMath.h>
#include <stdexcept>
#include <climits>
#include "Controller.h"

/**
 * @brief シングルトンインスタンスの取得
 */
Input& Input::instance() {

	static Input instance;
	return instance;
}
/**
 * @brief 更新処理
 */
void Input::update(HWND& hWnd) {

	//=== キーボード入力状態更新
	GetKeyboardState(m_key);
	for (auto& it : m_keyCount) {
		if (getKeyPress(it.first)) {
			it.second++;
		}
		else if (it.second == UINT_MAX) {
			it.second = 0;
		}
		else if (it.second != 0) {
			it.second = UINT_MAX;
		}
	}

	//=== マウスカーソル座標更新
	m_prevCursorPos = m_cursorPos;
	GetCursorPos(&m_cursorPos);
	ScreenToClient(hWnd, &m_cursorPos);

	//=== コントローラー状態更新
	ZeroMemory(&m_controller, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &m_controller);
	if (dwResult == ERROR_SUCCESS) {
		m_prevRightStick = m_rightStick;
		m_prevLeftStick = m_leftStick;
		m_connection = true;

		//=== ボタン入力状態更新
		for (auto& it : m_buttonCount) {
			if (getButtonPress(it.first)) {
				it.second++;
			}
			else if (it.second == UINT_MAX) {
				it.second = 0;
			}
			else if (it.second != 0) {
				it.second = UINT_MAX;
			}
		}

		//=== 右スティックの補正
		float rx = m_controller.Gamepad.sThumbRX;
		float ry = m_controller.Gamepad.sThumbRY;
		float rLength = sqrtf(rx * rx + ry * ry);

		// デッドゾーンを適応
		if (rLength > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
			if (rLength > STICK_MAX_INPUT) rLength = STICK_MAX_INPUT;
			// 正規化
			m_rightStick.length = (rLength - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) /
				(STICK_MAX_INPUT - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
			m_rightStick.direction = atan2f(ry, rx);
		}
		else {
			m_rightStick.length = 0.0f;
		}

		//=== 左スティックの補正
		float lx = m_controller.Gamepad.sThumbLX;
		float ly = m_controller.Gamepad.sThumbLY;
		float lLength = sqrtf(lx * lx + ly * ly);
		// デッドゾーンを適応
		if (lLength > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			if (lLength > STICK_MAX_INPUT) lLength = STICK_MAX_INPUT;
			// 正規化
			m_leftStick.length = (lLength - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) /
				(STICK_MAX_INPUT - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
			m_leftStick.direction = atan2f(ly, lx);
		}
		else {
			m_leftStick.length = 0.0f;
		}

		//=== 右トリガーの補正
		// デッドゾーンを適応
		if (m_controller.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			m_rightTrigger = (m_controller.Gamepad.bRightTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
				(TRIGGER_MAX_INPUT - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else {
			m_rightTrigger = 0.0f;
		}

		//=== 左トリガーの補正
		// デッドゾーンを適応
		if (m_controller.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			m_leftTrigger = (m_controller.Gamepad.bLeftTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
				(TRIGGER_MAX_INPUT - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else {
			m_leftTrigger = 0.0f;
		}

		//=== 振動処理
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		XInputSetState(0, &vibration);

		float power = 0.0f;
		for (auto e = m_rightVibration.begin(); e != m_rightVibration.end();) {
			e->second--;
			if (e->second < 0) {
				e = m_rightVibration.erase(e);
			}
			else {
				if (e->first > power) {
					power = e->first;
				}
				++e;
			}
		}
		if (power > 0.0f) {
			vibration.wRightMotorSpeed = power * MAX_VIBRATION;
			XInputSetState(0, &vibration);
		}
		power = 0.0f;
		for (auto e = m_leftVibration.begin(); e != m_leftVibration.end();) {
			e->second--;
			if (e->second < 0) {
				e = m_leftVibration.erase(e);
			}
			else {
				if (e->first > power) {
					power = e->first;
				}
				++e;
			}
		}
		if (power > 0.0f) {
			vibration.wLeftMotorSpeed = power * MAX_VIBRATION;
			XInputSetState(0, &vibration);
		}
	}
	else {
		if (!m_connection) {
			m_rightStick.direction = 0.0f;
			m_rightStick.length = 0.0f;
			m_prevRightStick.direction = 0.0f;
			m_prevRightStick.length = 0.0f;
			m_leftStick.direction = 0.0f;
			m_leftStick.length = 0.0f;
			m_prevLeftStick.direction = 0.0f;
			m_prevLeftStick.length = 0.0f;
			m_rightTrigger = 0.0f;
			m_leftTrigger = 0.0f;
			m_buttonCount.clear();
			m_rightVibration.clear();
			m_leftVibration.clear();
		}
		m_connection = false;
	}
}

/**
 * @brief キー入力の取得
 * @param[in] unsigned int キーコード
 * @return bool キーが押されていたらtrueを返す
 */
bool Input::getKeyPress(UINT key) {

	return m_key[key] & 0x80;
}

/**
 * @brief キーボードが押された瞬間を取得
 * @param[in] unsigned int キーコード
 * @return bool キーが押された最初のフレームだけtrueを返す
 */
bool Input::getKeyTrigger(UINT key) {

	return m_keyCount[key] == 1;
}

/**
 * @brief キーが押された瞬間の取得
 * @param[in] unsigned int キーコード
 * @return bool キーが押された最初のフレームだけtrueを返す
 */
bool Input::getKeyRelease(UINT key) {

	return m_keyCount[key] == UINT_MAX;
}

/**
 * @brief キー入力を一定間隔で取得
 * @param[in] unsigned int キーコード
 * @param[in] unsigned int リピート間隔
 * @return bool キーが入力されていたら一定間隔ごとにtrueを返す
 */
bool Input::getKeyRepeat(UINT key, UINT interval) {

	if (interval <= 1) {
		return getKeyPress(key);
	}
	return getKeyHoldTime(key) % interval == 1;
}

/**
 * @brief キー入力継続時間の取得
 * @param[in] unsigned int キーコード
 * @return unsigned int 入力継続時間
 */
UINT Input::getKeyHoldTime(UINT key) {

	m_keyCount.try_emplace(key, getKeyPress(key) ? 1 : 0);
	if (m_keyCount[key] == UINT_MAX) {
		return 0;
	}
	return m_keyCount[key];
}

/**
 * @brief マウスカーソルのクライアントx座標の取得
 * @return float カーソルx座標
 */
float Input::getCursorPosX() {

	return static_cast<float>(m_cursorPos.x);
}

/**
 * @brief マウスカーソルのクライアントy座標の取得
 * @return float カーソルy座標
 */
float Input::getCursorPosY() {

	return static_cast<float>(m_cursorPos.y);
}

/**
 * @brief マウスカーソルのx軸速度の取得
 * @return float カーソルx軸速度
 */
float Input::getCursorSpeedX() {

	return static_cast<float>(m_cursorPos.x - m_prevCursorPos.x);
}

/**
 * @brief マウスカーソルのy軸速度の取得
 * @return float カーソルy軸速度
 */
float Input::getCursorSpeedY() {

	return static_cast<float>(m_cursorPos.y - m_prevCursorPos.y);
}

/**
 * @brief コントローラーの接続状況の取得
 * @return bool コントローラー接続があればtrueを返す
 */
bool Input::getControllerConnection() {

	return m_connection;
}

/**
 * @brief コントローラーのボタン入力の取得
 * @param[in] unsigned int ボタンコード
 * @return bool ボタンが押されていたらtrueを返す
 */
bool Input::getButtonPress(UINT button) {

	if (!getControllerConnection()) {
		return false;
	}
	return m_controller.Gamepad.wButtons & button;
}

/**
 * @brief コントローラーのボタンが押された瞬間の取得
 * @param[in] unsigned int ボタンコード
 * @return bool ボタンが押された最初のフレームだけtrueを返す
 */
bool Input::getButtonTrigger(UINT button) {

	if (!getControllerConnection()) {
		return false;
	}
	return m_buttonCount[button] == 1;
}

/**
 * @brief コントローラーのボタンが離された瞬間の取得
 * @param[in] unsigned int ボタンコード
 * @return bool ボタンが離された最初のフレームだけtrueを返す
 */
bool Input::getButtonRelease(UINT button) {

	if (!getControllerConnection()) {
		return false;
	}
	return m_buttonCount[button] == UINT_MAX;
}

/**
 * @brief ボタン入力を一定間隔で取得
 * @param[in] unsigned int ボタンコード
 * @param[in] unsigned int リピート間隔
 * @return bool ボタンが入力されていたら一定間隔ごとにtrueを返す
 */
bool Input::getButtonRepeat(UINT button, UINT interval) {

	if (!getControllerConnection()) {
		return false;
	}
	if (interval <= 1) {
		return getButtonPress(button);
	}
	return getButtonHoldTime(button) % interval == 1;
}

/**
 * @brief ボタン入力継続時間の取得
 * @param[in] unsigned int ボタンコード
 * @return unsigned int 入力継続時間
 */
UINT Input::getButtonHoldTime(UINT button) {

	if (!getControllerConnection()) {
		return 0;
	}
	m_buttonCount.try_emplace(button, getButtonPress(button) ? 1 : 0);
	if (m_buttonCount[button] == UINT_MAX) {
		return 0;
	}
	return m_buttonCount[button];
}

/**
 * @brief コントローラーの右スティックx軸入力の取得
 * @return float 右スティックx軸入力(-1.0~1.0)
 */
float Input::getRightStickX() {

	return cos(m_rightStick.direction) * m_rightStick.length;
}

/**
 * @brief コントローラーの右スティックy軸入力の取得
 * @return float 右スティックy軸入力(-1.0~1.0)
 */
float Input::getRightStickY() {

	return sin(m_rightStick.direction) * m_rightStick.length;
}

/**
 * @brief コントローラーの左スティックx軸入力の取得
 * @return float 左スティックx軸入力(-1.0~1.0)
 */
float Input::getLeftStickX() {

	return cos(m_leftStick.direction) * m_leftStick.length;
}

/**
 * @brief コントローラーの左スティックy軸入力の取得
 * @return float 左スティックy軸入力(-1.0~1.0)
 */
float Input::getLeftStickY() {

	return sin(m_leftStick.direction) * m_leftStick.length;
}

/**
 * @brief コントローラーの右スティックの入力強度の取得
 * @return float 右スティック入力強度(-1.0~1.0)
 */
float Input::getRightStickMagnitude() {

	return m_rightStick.length;
}

/**
 * @brief コントローラーの左スティックの入力強度の取得
 * @return float 左スティック入力強度(-1.0~1.0)
 */
float Input::getLeftStickMagnitude() {

	return m_leftStick.length;
}

/**
 * @brief コントローラーの右スティックx軸速度の取得
 * @return float 右スティックx軸速度(-1.0~1.0)
 */
float Input::getRightStickSpeedX() {

	return getRightStickX() -
		cos(m_prevRightStick.direction) * m_prevRightStick.length;
}

/**
 * @brief コントローラーの右スティックy軸速度の取得
 * @return float 右スティックy軸速度(-1.0~1.0)
 */
float Input::getRightStickSpeedY() {

	return getRightStickY() -
		sin(m_prevRightStick.direction) * m_prevRightStick.length;
}

/**
 * @brief コントローラーの左スティックy軸速度の取得
 * @return float 左スティックy軸速度(-1.0~1.0)
 */
float Input::getLeftStickSpeedX() {

	return getLeftStickX() -
		cos(m_prevLeftStick.direction) * m_prevLeftStick.length;
}

/**
 * @brief コントローラーの左スティックy軸速度の取得
 * @return float 左スティックy軸速度(-1.0~1.0)
 */
float Input::getLeftStickSpeedY() {

	return getLeftStickY() -
		sin(m_prevLeftStick.direction) * m_prevLeftStick.length;
}

/**
 * @brief コントローラーの右スティック入力角度の取得
 * @return float 右スティック入力角度(0.0~360.0)
 */
float Input::getRightStickDirection() {

	return fmodf((m_rightStick.direction + XM_2PI) * 180 / XM_PI, 360.0f);
}

/**
 * @brief コントローラーの左スティック入力角度の取得
 * @return float 左スティック入力角度(0.0~360.0)
 */
float Input::getLeftStickDirection() {

	return fmodf((m_leftStick.direction + XM_2PI) * 180 / XM_PI, 360.0f);
}

/**
 * @brief コントローラーの右トリガー入力の取得
 * @return float 右トリガー入力(0.0~1.0)
 */
float Input::getRightTrigger() {

	return m_rightTrigger;
}

/**
 * @brief コントローラーの左トリガー入力の取得
 * @return float 左トリガー入力(0.0~1.0)
 */
float Input::getLeftTrigger() {

	return m_leftTrigger;
}

/**
 * @brief コントローラーの高周波振動の設定
 * @param[in] float 振動強度(0.0~1.0)
 * @param[in] unsigned int 振動フレーム数
 * @return bool true:成功
 */
bool Input::setRightVibration(float power, UINT frame) {

	if (!getControllerConnection()) {
		return false;
	}
	if (m_rightVibration.count(power)) {
		auto it = m_rightVibration.find(power);
		if (it->second < frame) {
			it->second = frame;
		}
	}
	else {
		m_rightVibration.insert(std::make_pair(power, frame));
	}
	return true;
}

/**
 * @brief コントローラーの低周波振動の設定
 * @param[in] float 振動強度(0.0~1.0)
 * @param[in] unsigned int 振動フレーム数
 * @return bool true:成功
 */
bool Input::setLeftVibration(float power, UINT frame) {

	if (!getControllerConnection()) {
		return false;
	}
	if (m_leftVibration.count(power)) {
		auto it = m_leftVibration.find(power);
		if (it->second < frame) {
			it->second = frame;
		}
	}
	else {
		m_leftVibration.insert(std::make_pair(power, frame));
	}
	return true;
}