#include <DirectXMath.h>
#include <stdexcept>
#include <climits>
#include "Controller.h"

/**
 * @brief �V���O���g���C���X�^���X�̎擾
 */
Input& Input::instance() {

	static Input instance;
	return instance;
}
/**
 * @brief �X�V����
 */
void Input::update(HWND& hWnd) {

	//=== �L�[�{�[�h���͏�ԍX�V
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

	//=== �}�E�X�J�[�\�����W�X�V
	m_prevCursorPos = m_cursorPos;
	GetCursorPos(&m_cursorPos);
	ScreenToClient(hWnd, &m_cursorPos);

	//=== �R���g���[���[��ԍX�V
	ZeroMemory(&m_controller, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &m_controller);
	if (dwResult == ERROR_SUCCESS) {
		m_prevRightStick = m_rightStick;
		m_prevLeftStick = m_leftStick;
		m_connection = true;

		//=== �{�^�����͏�ԍX�V
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

		//=== �E�X�e�B�b�N�̕␳
		float rx = m_controller.Gamepad.sThumbRX;
		float ry = m_controller.Gamepad.sThumbRY;
		float rLength = sqrtf(rx * rx + ry * ry);

		// �f�b�h�]�[����K��
		if (rLength > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
			if (rLength > STICK_MAX_INPUT) rLength = STICK_MAX_INPUT;
			// ���K��
			m_rightStick.length = (rLength - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) /
				(STICK_MAX_INPUT - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
			m_rightStick.direction = atan2f(ry, rx);
		}
		else {
			m_rightStick.length = 0.0f;
		}

		//=== ���X�e�B�b�N�̕␳
		float lx = m_controller.Gamepad.sThumbLX;
		float ly = m_controller.Gamepad.sThumbLY;
		float lLength = sqrtf(lx * lx + ly * ly);
		// �f�b�h�]�[����K��
		if (lLength > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			if (lLength > STICK_MAX_INPUT) lLength = STICK_MAX_INPUT;
			// ���K��
			m_leftStick.length = (lLength - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) /
				(STICK_MAX_INPUT - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
			m_leftStick.direction = atan2f(ly, lx);
		}
		else {
			m_leftStick.length = 0.0f;
		}

		//=== �E�g���K�[�̕␳
		// �f�b�h�]�[����K��
		if (m_controller.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			m_rightTrigger = (m_controller.Gamepad.bRightTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
				(TRIGGER_MAX_INPUT - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else {
			m_rightTrigger = 0.0f;
		}

		//=== ���g���K�[�̕␳
		// �f�b�h�]�[����K��
		if (m_controller.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			m_leftTrigger = (m_controller.Gamepad.bLeftTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
				(TRIGGER_MAX_INPUT - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else {
			m_leftTrigger = 0.0f;
		}

		//=== �U������
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
 * @brief �L�[���͂̎擾
 * @param[in] unsigned int �L�[�R�[�h
 * @return bool �L�[��������Ă�����true��Ԃ�
 */
bool Input::getKeyPress(UINT key) {

	return m_key[key] & 0x80;
}

/**
 * @brief �L�[�{�[�h�������ꂽ�u�Ԃ��擾
 * @param[in] unsigned int �L�[�R�[�h
 * @return bool �L�[�������ꂽ�ŏ��̃t���[������true��Ԃ�
 */
bool Input::getKeyTrigger(UINT key) {

	return m_keyCount[key] == 1;
}

/**
 * @brief �L�[�������ꂽ�u�Ԃ̎擾
 * @param[in] unsigned int �L�[�R�[�h
 * @return bool �L�[�������ꂽ�ŏ��̃t���[������true��Ԃ�
 */
bool Input::getKeyRelease(UINT key) {

	return m_keyCount[key] == UINT_MAX;
}

/**
 * @brief �L�[���͂����Ԋu�Ŏ擾
 * @param[in] unsigned int �L�[�R�[�h
 * @param[in] unsigned int ���s�[�g�Ԋu
 * @return bool �L�[�����͂���Ă�������Ԋu���Ƃ�true��Ԃ�
 */
bool Input::getKeyRepeat(UINT key, UINT interval) {

	if (interval <= 1) {
		return getKeyPress(key);
	}
	return getKeyHoldTime(key) % interval == 1;
}

/**
 * @brief �L�[���͌p�����Ԃ̎擾
 * @param[in] unsigned int �L�[�R�[�h
 * @return unsigned int ���͌p������
 */
UINT Input::getKeyHoldTime(UINT key) {

	m_keyCount.try_emplace(key, getKeyPress(key) ? 1 : 0);
	if (m_keyCount[key] == UINT_MAX) {
		return 0;
	}
	return m_keyCount[key];
}

/**
 * @brief �}�E�X�J�[�\���̃N���C�A���gx���W�̎擾
 * @return float �J�[�\��x���W
 */
float Input::getCursorPosX() {

	return static_cast<float>(m_cursorPos.x);
}

/**
 * @brief �}�E�X�J�[�\���̃N���C�A���gy���W�̎擾
 * @return float �J�[�\��y���W
 */
float Input::getCursorPosY() {

	return static_cast<float>(m_cursorPos.y);
}

/**
 * @brief �}�E�X�J�[�\����x�����x�̎擾
 * @return float �J�[�\��x�����x
 */
float Input::getCursorSpeedX() {

	return static_cast<float>(m_cursorPos.x - m_prevCursorPos.x);
}

/**
 * @brief �}�E�X�J�[�\����y�����x�̎擾
 * @return float �J�[�\��y�����x
 */
float Input::getCursorSpeedY() {

	return static_cast<float>(m_cursorPos.y - m_prevCursorPos.y);
}

/**
 * @brief �R���g���[���[�̐ڑ��󋵂̎擾
 * @return bool �R���g���[���[�ڑ��������true��Ԃ�
 */
bool Input::getControllerConnection() {

	return m_connection;
}

/**
 * @brief �R���g���[���[�̃{�^�����͂̎擾
 * @param[in] unsigned int �{�^���R�[�h
 * @return bool �{�^����������Ă�����true��Ԃ�
 */
bool Input::getButtonPress(UINT button) {

	if (!getControllerConnection()) {
		return false;
	}
	return m_controller.Gamepad.wButtons & button;
}

/**
 * @brief �R���g���[���[�̃{�^���������ꂽ�u�Ԃ̎擾
 * @param[in] unsigned int �{�^���R�[�h
 * @return bool �{�^���������ꂽ�ŏ��̃t���[������true��Ԃ�
 */
bool Input::getButtonTrigger(UINT button) {

	if (!getControllerConnection()) {
		return false;
	}
	return m_buttonCount[button] == 1;
}

/**
 * @brief �R���g���[���[�̃{�^���������ꂽ�u�Ԃ̎擾
 * @param[in] unsigned int �{�^���R�[�h
 * @return bool �{�^���������ꂽ�ŏ��̃t���[������true��Ԃ�
 */
bool Input::getButtonRelease(UINT button) {

	if (!getControllerConnection()) {
		return false;
	}
	return m_buttonCount[button] == UINT_MAX;
}

/**
 * @brief �{�^�����͂����Ԋu�Ŏ擾
 * @param[in] unsigned int �{�^���R�[�h
 * @param[in] unsigned int ���s�[�g�Ԋu
 * @return bool �{�^�������͂���Ă�������Ԋu���Ƃ�true��Ԃ�
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
 * @brief �{�^�����͌p�����Ԃ̎擾
 * @param[in] unsigned int �{�^���R�[�h
 * @return unsigned int ���͌p������
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
 * @brief �R���g���[���[�̉E�X�e�B�b�Nx�����͂̎擾
 * @return float �E�X�e�B�b�Nx������(-1.0~1.0)
 */
float Input::getRightStickX() {

	return cos(m_rightStick.direction) * m_rightStick.length;
}

/**
 * @brief �R���g���[���[�̉E�X�e�B�b�Ny�����͂̎擾
 * @return float �E�X�e�B�b�Ny������(-1.0~1.0)
 */
float Input::getRightStickY() {

	return sin(m_rightStick.direction) * m_rightStick.length;
}

/**
 * @brief �R���g���[���[�̍��X�e�B�b�Nx�����͂̎擾
 * @return float ���X�e�B�b�Nx������(-1.0~1.0)
 */
float Input::getLeftStickX() {

	return cos(m_leftStick.direction) * m_leftStick.length;
}

/**
 * @brief �R���g���[���[�̍��X�e�B�b�Ny�����͂̎擾
 * @return float ���X�e�B�b�Ny������(-1.0~1.0)
 */
float Input::getLeftStickY() {

	return sin(m_leftStick.direction) * m_leftStick.length;
}

/**
 * @brief �R���g���[���[�̉E�X�e�B�b�N�̓��͋��x�̎擾
 * @return float �E�X�e�B�b�N���͋��x(-1.0~1.0)
 */
float Input::getRightStickMagnitude() {

	return m_rightStick.length;
}

/**
 * @brief �R���g���[���[�̍��X�e�B�b�N�̓��͋��x�̎擾
 * @return float ���X�e�B�b�N���͋��x(-1.0~1.0)
 */
float Input::getLeftStickMagnitude() {

	return m_leftStick.length;
}

/**
 * @brief �R���g���[���[�̉E�X�e�B�b�Nx�����x�̎擾
 * @return float �E�X�e�B�b�Nx�����x(-1.0~1.0)
 */
float Input::getRightStickSpeedX() {

	return getRightStickX() -
		cos(m_prevRightStick.direction) * m_prevRightStick.length;
}

/**
 * @brief �R���g���[���[�̉E�X�e�B�b�Ny�����x�̎擾
 * @return float �E�X�e�B�b�Ny�����x(-1.0~1.0)
 */
float Input::getRightStickSpeedY() {

	return getRightStickY() -
		sin(m_prevRightStick.direction) * m_prevRightStick.length;
}

/**
 * @brief �R���g���[���[�̍��X�e�B�b�Ny�����x�̎擾
 * @return float ���X�e�B�b�Ny�����x(-1.0~1.0)
 */
float Input::getLeftStickSpeedX() {

	return getLeftStickX() -
		cos(m_prevLeftStick.direction) * m_prevLeftStick.length;
}

/**
 * @brief �R���g���[���[�̍��X�e�B�b�Ny�����x�̎擾
 * @return float ���X�e�B�b�Ny�����x(-1.0~1.0)
 */
float Input::getLeftStickSpeedY() {

	return getLeftStickY() -
		sin(m_prevLeftStick.direction) * m_prevLeftStick.length;
}

/**
 * @brief �R���g���[���[�̉E�X�e�B�b�N���͊p�x�̎擾
 * @return float �E�X�e�B�b�N���͊p�x(0.0~360.0)
 */
float Input::getRightStickDirection() {

	return fmodf((m_rightStick.direction + XM_2PI) * 180 / XM_PI, 360.0f);
}

/**
 * @brief �R���g���[���[�̍��X�e�B�b�N���͊p�x�̎擾
 * @return float ���X�e�B�b�N���͊p�x(0.0~360.0)
 */
float Input::getLeftStickDirection() {

	return fmodf((m_leftStick.direction + XM_2PI) * 180 / XM_PI, 360.0f);
}

/**
 * @brief �R���g���[���[�̉E�g���K�[���͂̎擾
 * @return float �E�g���K�[����(0.0~1.0)
 */
float Input::getRightTrigger() {

	return m_rightTrigger;
}

/**
 * @brief �R���g���[���[�̍��g���K�[���͂̎擾
 * @return float ���g���K�[����(0.0~1.0)
 */
float Input::getLeftTrigger() {

	return m_leftTrigger;
}

/**
 * @brief �R���g���[���[�̍����g�U���̐ݒ�
 * @param[in] float �U�����x(0.0~1.0)
 * @param[in] unsigned int �U���t���[����
 * @return bool true:����
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
 * @brief �R���g���[���[�̒���g�U���̐ݒ�
 * @param[in] float �U�����x(0.0~1.0)
 * @param[in] unsigned int �U���t���[����
 * @return bool true:����
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