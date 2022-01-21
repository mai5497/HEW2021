/**
 * @file Input.h
 * @Author ���c�đ�
 * @date 2020/08/07 �쐬
 * @brief �L�[�A�}�E�X�A�W���C�p�b�h���͂�����
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

// @brief ���͏��̎擾�E�X�V
void UpdateInput(HWND&, float);

// @brief �L�[�������Ă��邩���擾
// @param[in] key	VK_SPACE ���Ŏw��
// @return bool
bool IsPress(unsigned char key);

// @brief �L�[���������u�Ԃ��擾
// @param[in] key	VK_SPACE ���Ŏw��
// @return bool
bool IsTrigger(unsigned char key);

// @brief �L�[�𗣂����u�Ԃ��擾
// @param[in] key	VK_SPACE ���Ŏw��
// @return bool
bool IsRelease(unsigned char key);

// @brief �L�[�������Ă���Ԉ��Ԋu��true��Ԃ�
// @param[in] key	VK_SPACE ���Ŏw��
// @param[in] cycle	true��Ԃ�����
// @return bool
bool IsRepeat(unsigned char key, unsigned int cycle);
// @brief �L�[�𗣂����u�Ԃ��擾
// @param[in] key	VK_SPACE ���Ŏw��
// @return uint	�������݌p������
unsigned int HoldTime(unsigned char key);
// @brief �{�^���������Ă��邩���擾
// @param[in] button	JPadButton::A���Ŏw��
// @return bool
bool IsPress(JPadButton button);
// @brief �{�^�����������u�Ԃ��擾
// @param[in] button	JPadButton::A���Ŏw��
// @return bool
bool IsTrigger(JPadButton button);
// @brief �{�^���𗣂����u�Ԃ��擾
// @param[in] button	JPadButton::A���Ŏw��
// @return bool
bool IsRelease(JPadButton button);
// @brief �{�^���������Ă���Ԉ��Ԋu��true��Ԃ�
// @param[in] button	JPadButton::A���Ŏw��
// @param[in] cycle	true��Ԃ�����
// @return bool
bool IsRepeat(JPadButton button, unsigned int cycle);
// @brief �{�^���𗣂����u�Ԃ��擾
// @param[in] button	JPadButton::A���Ŏw��
// @return uint	�������݌p������
unsigned int HoldTime(JPadButton button);
// @brief �J�[�\�����W�̎擾
// @return DirectX::XMFLOAT2	�ʒu
DirectX::XMFLOAT2 CursorPosition();
// @brief �J�[�\�������x�̎擾
// @return DirectX::XMFLOAT2	�����x
DirectX::XMFLOAT2 CursorAcceleration();
// @brief �}�E�X�z�C�[����]���x�̎擾
// @return float	��]���x	
float MouseWheelDelta();
// @brief ���X�e�B�b�N�ʒu�̎擾
// @return DirectX::XMFLOAT2	�ʒu(���K���ς�)
DirectX::XMFLOAT2 LeftThumbPosition();
// @brief �E�X�e�B�b�N�ʒu�̎擾
// @return DirectX::XMFLOAT2	�ʒu(���K���ς�)
DirectX::XMFLOAT2 RightThumbPosition();
// @brief ���X�e�B�b�N�����x�̎擾
// @return DirectX::XMFLOAT2	�����x(���K���ς�)
DirectX::XMFLOAT2 LeftThumbAcceleration();
// @brief �E�X�e�B�b�N�����x�̎擾
// @return DirectX::XMFLOAT2	�����x(���K���ς�)
DirectX::XMFLOAT2 RightThumbAcceleration();
// @brief ���g���K�[�������݋��x�̎擾
// @return DirectX::XMFLOAT2	���x(0.0f~1.0f)
float LeftTriggerStrength();
// @brief �E�g���K�[�������݋��x�̎擾
// @return DirectX::XMFLOAT2	���x(0.0f~1.0f)
float RightTriggerStrength();
// @brief ���g���K�[�������݉����x�̎擾
// @return DirectX::XMFLOAT2	�����x(0.0f~1.0f)
float LeftTriggerAcceleration();
// @brief �E�g���K�[�������݉����x�̎擾
// @return DirectX::XMFLOAT2	�����x(0.0f~1.0f)
float RightTriggerAcceleration();
// @brief �����[�^�[�̐U����ݒ�
// @param[in] power	�U�����x(0.0f~1.0f)
// @param[in] frame �U���t���[��
void LeftVibration(float power, unsigned int frame);
// @brief �E���[�^�[�̐U����ݒ�
// @param[in] power	�U�����x(0.0f~1.0f)
// @param[in] frame �U���t���[��
void RightVibration(float power, unsigned int frame);
// @brief �R���g���[���[�̐ڑ���
// @return bool	true : �ڑ���
bool IsJoyPadConnection();