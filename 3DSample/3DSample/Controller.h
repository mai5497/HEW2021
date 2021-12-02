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
 * @brief �C���v�b�g�N���X
 */
class Input {
private:
	const float STICK_MAX_INPUT = 32767.0f;
	const float TRIGGER_MAX_INPUT = 255.0f;
	const float MAX_VIBRATION = 65535.0f;

	BYTE  m_key[256];					//!< �L�[�{�[�h���
	map<UINT, UINT> m_keyCount;			//!< �L�[�̓��͌p������
	POINT m_cursorPos;					//!< �J�[�\�����W
	POINT m_prevCursorPos;				//!< �O�t���[���̃J�[�\�����W
	XINPUT_STATE m_controller;			//!< �R���g���[���[���
	map<UINT, UINT> m_buttonCount;		//!< �{�^���̓��͌p������
	Stick m_rightStick;					//!< �E�X�e�B�b�N�̏��
	Stick m_prevRightStick;				//!< �O�t���[���̉E�X�e�B�b�N�̏��
	Stick m_leftStick;					//!< ���X�e�B�b�N�̏��
	Stick m_prevLeftStick;				//!< �O�t���[���̍��X�e�B�b�N�̏��
	float m_rightTrigger;				//!< �E�g���K�[�̓��͒l
	float m_leftTrigger;				//!< ���g���K�[�̓��͒l
	map<float, int> m_rightVibration;	//!< �����g�U���f�[�^��ێ�����R���e�i
	map<float, int> m_leftVibration;	//!< ����g�U���f�[�^��ێ�����R���e�i
	bool m_connection;					//!< �R���g���[���[�̐ڑ���(true:�ڑ���/false:�ڑ��s��)

	/**
	 * @brief �R���X�g���N�^
	 */
	Input() = default;
	/**
	 * @brief �f�X�g���N�^
	 */
	~Input() = default;
	/**
	 * @brief �R�s�[�R���X�g���N�^
	 * @details �������֎~��
	 */
	Input(const Input&) = delete;
	/**
	 * @brief =���Z�q�̃I�[�o�[���[�h
	 * @details ������֎~��
	 */
	void operator=(const Input&) = delete;
public:
	/**
	 * @brief �V���O���g���C���X�^���X�̎擾
	 * @return static Input& �C���X�^���X
	 */
	static Input& instance();
	/**
	 * @brief ����������
	 * @details �E�B���h�E�n���h���̏�����
	 */
	void update(HWND& hWnd);
	/**
	 * @brief �L�[���͂̎擾
	 * @param[in] unsigned int �L�[�R�[�h
	 * @return bool �L�[��������Ă�����true��Ԃ�
	 */
	bool getKeyPress(UINT key);
	/**
	 * @brief �L�[�������ꂽ�u�Ԃ̎擾
	 * @param[in] unsigned int �L�[�R�[�h
	 * @return bool �L�[�������ꂽ�ŏ��̃t���[������true��Ԃ�
	 */
	bool getKeyTrigger(UINT key);
	/**
	 * @brief �L�[�������ꂽ�u�Ԃ̎擾
	 * @param[in] unsigned int �L�[�R�[�h
	 * @return bool �L�[�������ꂽ�ŏ��̃t���[������true��Ԃ�
	 */
	bool getKeyRelease(UINT key);
	/**
	 * @brief �L�[���͂����Ԋu�Ŏ擾
	 * @param[in] unsigned int �L�[�R�[�h
	 * @param[in] unsigned int ���s�[�g�Ԋu
	 * @return bool �L�[�����͂���Ă�������Ԋu���Ƃ�true��Ԃ�
	 */
	bool getKeyRepeat(UINT key, UINT interval);
	/**
	 * @brief �L�[���͌p�����Ԃ̎擾
	 * @param[in] unsigned int �L�[�R�[�h
	 * @return unsigned int ���͌p������
	 */
	UINT getKeyHoldTime(UINT key);
	/**
	 * @brief �}�E�X�J�[�\���̃N���C�A���gx���W�̎擾
	 * @return float �J�[�\��x���W
	 */
	float getCursorPosX();
	/**
	 * @brief �}�E�X�J�[�\���̃N���C�A���gy���W�̎擾
	 * @return float �J�[�\��y���W
	 */
	float getCursorPosY();
	/**
	 * @brief �}�E�X�J�[�\����x�����x�̎擾
	 * @return float �J�[�\��x�����x
	 */
	float getCursorSpeedX();
	/**
	 * @brief �}�E�X�J�[�\����y�����x�̎擾
	 * @return float �J�[�\��y�����x
	 */
	float getCursorSpeedY();
	/**
	 * @brief �R���g���[���[�̐ڑ��󋵂̎擾
	 * @return bool �R���g���[���[�ڑ��������true��Ԃ�
	 */
	bool getControllerConnection();
	/**
	 * @brief �R���g���[���[�̃{�^�����͂̎擾
	 * @param[in] unsigned int �{�^���R�[�h
	 * @return bool �{�^����������Ă�����true��Ԃ�
	 */
	bool getButtonPress(UINT button);
	/**
	 * @brief �R���g���[���[�̃{�^���������ꂽ�u�Ԃ̎擾
	 * @param[in] unsigned int �{�^���R�[�h
	 * @return bool �{�^���������ꂽ�ŏ��̃t���[������true��Ԃ�
	 */
	bool getButtonTrigger(UINT button);
	/**
	 * @brief �R���g���[���[�̃{�^���������ꂽ�u�Ԃ̎擾
	 * @param[in] unsigned int �{�^���R�[�h
	 * @return bool �{�^���������ꂽ�ŏ��̃t���[������true��Ԃ�
	 */
	bool getButtonRelease(UINT button);
	/**
	 * @brief �{�^�����͂����Ԋu�Ŏ擾
	 * @param[in] unsigned int �{�^���R�[�h
	 * @param[in] unsigned int ���s�[�g�Ԋu
	 * @return bool �{�^�������͂���Ă�������Ԋu���Ƃ�true��Ԃ�
	 */
	bool getButtonRepeat(UINT button, UINT interval);
	/**
	 * @brief �{�^�����͌p�����Ԃ̎擾
	 * @param[in] unsigned int �{�^���R�[�h
	 * @return unsigned int ���͌p������
	 */
	UINT getButtonHoldTime(UINT button);
	/**
	 * @brief �R���g���[���[�̉E�X�e�B�b�Nx�����͂̎擾
	 * @return float �E�X�e�B�b�Nx������(-1.0~1.0)
	 */
	float getRightStickX();
	/**
	 * @brief �R���g���[���[�̉E�X�e�B�b�Ny�����͂̎擾
	 * @return float �E�X�e�B�b�Ny������(-1.0~1.0)
	 */
	float getRightStickY();
	/**
	 * @brief �R���g���[���[�̍��X�e�B�b�Nx�����͂̎擾
	 * @return float ���X�e�B�b�Nx������(-1.0~1.0)
	 */
	float getLeftStickX();
	/**
	 * @brief �R���g���[���[�̍��X�e�B�b�Ny�����͂̎擾
	 * @return float ���X�e�B�b�Ny������(-1.0~1.0)
	 */
	float getLeftStickY();
	/**
	 * @brief �R���g���[���[�̉E�X�e�B�b�N�̓��͋��x�̎擾
	 * @return float �E�X�e�B�b�N���͋��x(-1.0~1.0)
	 */
	float getRightStickMagnitude();
	/**
	 * @brief �R���g���[���[�̍��X�e�B�b�N�̓��͋��x�̎擾
	 * @return float ���X�e�B�b�N���͋��x(-1.0~1.0)
	 */
	float getLeftStickMagnitude();
	/**
	 * @brief �R���g���[���[�̉E�X�e�B�b�Nx�����x�̎擾
	 * @return float �E�X�e�B�b�Nx�����x(-1.0~1.0)
	 */
	float getRightStickSpeedX();
	/**
	 * @brief �R���g���[���[�̉E�X�e�B�b�Ny�����x�̎擾
	 * @return float �E�X�e�B�b�Ny�����x(-1.0~1.0)
	 */
	float getRightStickSpeedY();
	/**
	 * @brief �R���g���[���[�̍��X�e�B�b�Ny�����x�̎擾
	 * @return float ���X�e�B�b�Ny�����x(-1.0~1.0)
	 */
	float getLeftStickSpeedX();
	/**
	 * @brief �R���g���[���[�̍��X�e�B�b�Ny�����x�̎擾
	 * @return float ���X�e�B�b�Ny�����x(-1.0~1.0)
	 */
	float getLeftStickSpeedY();
	/**
	 * @brief �R���g���[���[�̉E�X�e�B�b�N���͊p�x�̎擾
	 * @return float �E�X�e�B�b�N���͊p�x(0.0~360.0)
	 */
	float getRightStickDirection();
	/**
	 * @brief �R���g���[���[�̍��X�e�B�b�N���͊p�x�̎擾
	 * @return float ���X�e�B�b�N���͊p�x(0.0~360.0)
	 */
	float getLeftStickDirection();
	/**
	 * @brief �R���g���[���[�̉E�g���K�[���͂̎擾
	 * @return float �E�g���K�[����(0.0~1.0)
	 */
	float getRightTrigger();
	/**
	 * @brief �R���g���[���[�̍��g���K�[���͂̎擾
	 * @return float ���g���K�[����(0.0~1.0)
	 */
	float getLeftTrigger();
	/**
	 * @brief �R���g���[���[�̍����g�U���̐ݒ�
	 * @param[in] float �U�����x(0.0~1.0)
	 * @param[in] unsigned int �U���t���[����
	 * @return bool true:����
	 */
	bool setRightVibration(float power, UINT frame);
	/**
	 * @brief �R���g���[���[�̒���g�U���̐ݒ�
	 * @param[in] float �U�����x(0.0~1.0)
	 * @param[in] unsigned int �U���t���[����
	 * @return bool true:����
	 */
	bool setLeftVibration(float power, UINT frame);
};