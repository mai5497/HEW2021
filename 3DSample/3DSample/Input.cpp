#include "Input.h"
#include <map>
#include <stdexcept>
#include "Defines.h"
#include "MyMath.h"
#pragma comment (lib, "xinput.lib")

using namespace std;
using namespace DirectX;

constexpr float STICK_MAX_INPUT = 32767.0f;			// スティック各軸の最大入力値
constexpr float TRIGGER_MAX_INPUT = 255.0f;			// トリガーの最大入力値
constexpr float MAX_VIBRATION = 65535.0f;			// 振動の最大出力値

// スティックの方向を検知する範囲(3PI/8)
constexpr float STICK_DIR_DETECTION_RANGE = 1.178097245f;

// キーの入力継続時間
unsigned int g_keyCount[256] = {};
// 標準ボタンの入力継続時間
map<JPadButton, unsigned int> g_stdButtonCount = {
		{ JPadButton::DPAD_UP, 0 },
		{ JPadButton::DPAD_DOWN, 0 },
		{ JPadButton::DPAD_LEFT, 0 },
		{ JPadButton::DPAD_RIGHT, 0 },
		{ JPadButton::START, 0 },
		{ JPadButton::BACK, 0 },
		{ JPadButton::L_THUMB, 0 },
		{ JPadButton::R_THUMB, 0 },
		{ JPadButton::L_SHOULDER, 0 },
		{ JPadButton::R_SHOULDER, 0 },
		{ JPadButton::L_TRIGGER, 0 },
		{ JPadButton::R_TRIGGER, 0 },
		{ JPadButton::A, 0 },
		{ JPadButton::B, 0 },
		{ JPadButton::X, 0 },
		{ JPadButton::Y, 0 },
		{ JPadButton::L_THUMB_UP, 0 },
		{ JPadButton::L_THUMB_DOWN, 0 },
		{ JPadButton::L_THUMB_LEFT, 0 },
		{ JPadButton::L_THUMB_RIGHT, 0 },
		{ JPadButton::R_THUMB_UP, 0 },
		{ JPadButton::R_THUMB_DOWN, 0 },
		{ JPadButton::R_THUMB_LEFT, 0 }, 
		{ JPadButton::R_THUMB_RIGHT, 0 } };

DirectX::XMFLOAT2 g_cursorPos = XMFLOAT2_ZERO;		// カーソル座標
DirectX::XMFLOAT2 g_cursorMove = XMFLOAT2_ZERO;		// カーソル速度
DirectX::XMFLOAT2 g_curtRightThumb = XMFLOAT2_ZERO;	// 右スティックの入力値
DirectX::XMFLOAT2 g_prevRightThumb = XMFLOAT2_ZERO;	// 前フレームの右スティックの入力値
DirectX::XMFLOAT2 g_curtLeftThumb = XMFLOAT2_ZERO;	// 左スティックの入力値
DirectX::XMFLOAT2 g_prevLeftThumb = XMFLOAT2_ZERO;	// 前フレームの左スティックの入力値
float g_mouseWheelDelta = 0.0f;		// マウスホイール回転量
float g_curtLeftTrigger = 0.0f;		// 左トリガーの入力値
float g_prevLeftTrigger = 0.0f;		// 前フレームの左トリガーの入力値
float g_curtRightTrigger = 0.0f;	// 右トリガーの入力値
float g_prevRightTrigger = 0.0f;	// 前フレームの右トリガーの入力値
map<float, unsigned int> g_rightVibration;	// 高周波振動データを保持するコンテナ
map<float, unsigned int> g_leftVibration;	// 低周波振動データを保持するコンテナ
bool g_joyPadConnection = false;	// コントローラーの接続状況(true:接続中/false:接続不可)

void UpdateInput(HWND& hWnd, float mouseWheelDelta) {
	// キーボード入力更新
	unsigned char key[256];
	GetKeyboardState(key);
	for (int i = 0; i < 256; i++) {
		if (key[i] & 0x80) {
			g_keyCount[i]++;
		}
		else if (g_keyCount[i] == UINT_MAX) {
			g_keyCount[i] = 0;
		}
		else if (g_keyCount[i] != 0) {
			g_keyCount[i] = UINT_MAX;
		}
	}

	// マウスカーソル入力更新
	if (GetForegroundWindow() == hWnd) {
		POINT cursor;
		RECT rect;
		RECT deskRect;
		HWND hDeskWnd = GetDesktopWindow();

		ShowCursor(FALSE);

		GetCursorPos(&cursor);
		GetWindowRect(hWnd, &rect);
		GetWindowRect(hDeskWnd, &deskRect);

		XMFLOAT2 half(SCREEN_WIDTH / 2.0f,
					  SCREEN_HEIGHT / 2.0f);
		XMFLOAT2 deskHalf(deskRect.right / 2.0f,
						  deskRect.bottom / 2.0f);

		g_cursorMove = XMFLOAT2(cursor.x - rect.right + half.x,
								cursor.y - rect.bottom + half.y);

		SetCursorPos(rect.right - static_cast<int>(half.x), rect.bottom - static_cast<int>(half.y));

		g_cursorPos = Clamp(g_cursorPos + g_cursorMove, -half, half);
	}
	else
	{
		ShowCursor(TRUE);
		g_cursorMove = XMFLOAT2_ZERO;
	}

	// マウスホイール状態更新
	g_mouseWheelDelta = mouseWheelDelta;

	// コントローラー状態更新
	XINPUT_STATE joypad;
	ZeroMemory(&joypad, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &joypad);
	if (dwResult == ERROR_SUCCESS) {
		if (!g_joyPadConnection) {
			//SYSTEM_LOG("コントローラー接続");
			g_joyPadConnection = true;
		}

		// 左スティック入力更新
		g_prevLeftThumb = g_curtLeftThumb;
		XMFLOAT2 lsAxis =
		{ static_cast<float>(joypad.Gamepad.sThumbLX),
		  static_cast<float>(joypad.Gamepad.sThumbLY) };

		if (Magnitude(lsAxis) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			lsAxis = ClampMagnitude(lsAxis, 0.0f, STICK_MAX_INPUT);
			g_curtLeftThumb = MakeMagnitudeAndAngle(
				(Magnitude(lsAxis) - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) /
				(STICK_MAX_INPUT - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE),
				Angle(lsAxis));
		}
		else {
			g_curtLeftThumb = XMFLOAT2_ZERO;
		}

		// 右スティック入力更新
		g_prevRightThumb = g_curtRightThumb;
		XMFLOAT2 rsAxis =
		{ static_cast<float>(joypad.Gamepad.sThumbRX),
		  static_cast<float>(joypad.Gamepad.sThumbRY) };

		if (Magnitude(rsAxis) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
			g_curtRightThumb = MakeMagnitudeAndAngle(
				(Magnitude(rsAxis) - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) /
				(STICK_MAX_INPUT - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE),
				Angle(rsAxis));
		}
		else {
			g_curtRightThumb = XMFLOAT2_ZERO;
		}

		// 左トリガー入力更新
		g_prevLeftTrigger = g_curtLeftTrigger;
		if (joypad.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			g_curtLeftTrigger = (joypad.Gamepad.bLeftTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
				(TRIGGER_MAX_INPUT - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else {
			g_curtLeftTrigger = 0.0f;
		}

		// 右トリガー入力更新
		g_prevRightTrigger = g_curtRightTrigger;
		if (joypad.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			g_curtRightTrigger = (joypad.Gamepad.bRightTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
				(TRIGGER_MAX_INPUT - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		}
		else {
			g_curtRightTrigger = 0.0f;
		}

		// ボタン入力更新
		for (auto it = g_stdButtonCount.begin(); it != g_stdButtonCount.end(); it++) {
			JPadButton bIdx = it->first;
			unsigned int bCnt = it->second;
			float angle = 0.0f;
			bool IsPress = false;

			switch (bIdx)
			{
			case JPadButton::L_TRIGGER:
				IsPress = g_curtLeftTrigger > 0.0f;
				break;

			case JPadButton::R_TRIGGER:
				IsPress = g_curtRightTrigger > 0.0f;
				break;

			case JPadButton::L_THUMB_UP:
				if (IsZero(g_curtLeftThumb)) break;
				angle = Angle(g_curtLeftThumb);
				IsPress = (angle < XM_PIDIV2 * 3.0f + STICK_DIR_DETECTION_RANGE) & (angle > XM_PIDIV2 * 3.0f - STICK_DIR_DETECTION_RANGE);
				break;

			case JPadButton::L_THUMB_DOWN:
				if (IsZero(g_curtLeftThumb)) break;
				angle = Angle(g_curtLeftThumb);
				IsPress = (angle < XM_PIDIV2 + STICK_DIR_DETECTION_RANGE) & (angle > XM_PIDIV2 - STICK_DIR_DETECTION_RANGE);
				break;

			case JPadButton::L_THUMB_LEFT:
				if (IsZero(g_curtLeftThumb)) break;
				angle = Angle(g_curtLeftThumb);
				IsPress = (angle < STICK_DIR_DETECTION_RANGE) | (angle > XM_2PI - STICK_DIR_DETECTION_RANGE);
				break;

			case JPadButton::L_THUMB_RIGHT:
				if (IsZero(g_curtLeftThumb)) break;
				angle = Angle(g_curtLeftThumb);
				IsPress = (angle < XM_PI + STICK_DIR_DETECTION_RANGE) & (angle > XM_PI - STICK_DIR_DETECTION_RANGE);
				break;

			case JPadButton::R_THUMB_UP:
				if (IsZero(g_curtRightThumb)) break;
				angle = Angle(g_curtRightThumb);
				IsPress = (angle < XM_PIDIV2 + STICK_DIR_DETECTION_RANGE) & (angle > XM_PIDIV2 - STICK_DIR_DETECTION_RANGE);
				break;

			case JPadButton::R_THUMB_DOWN:
				if (IsZero(g_curtRightThumb)) break;
				angle = Angle(g_curtRightThumb);
				IsPress = (angle < XM_PIDIV2 * 3.0f + STICK_DIR_DETECTION_RANGE) & (angle > XM_PIDIV2 * 3.0f - STICK_DIR_DETECTION_RANGE);
				break;

			case JPadButton::R_THUMB_LEFT:
				if (IsZero(g_curtRightThumb)) break;
				angle = Angle(g_curtRightThumb);
				IsPress = (angle < XM_PI + STICK_DIR_DETECTION_RANGE) & (angle > XM_PI - STICK_DIR_DETECTION_RANGE);
				break;

			case JPadButton::R_THUMB_RIGHT:
				if (IsZero(g_curtRightThumb)) break;
				angle = Angle(g_curtRightThumb);
				IsPress = (angle < STICK_DIR_DETECTION_RANGE) | (angle > XM_2PI - STICK_DIR_DETECTION_RANGE);
				break;

			default:
				IsPress = joypad.Gamepad.wButtons &
					static_cast<WORD>(bIdx);
				break;
			}

			if (IsPress) {
				bCnt++;
			}
			else if (bCnt == UINT_MAX) {
				bCnt = 0;
			}
			else if (bCnt != 0) {
				bCnt = UINT_MAX;
			}

			it->second = bCnt;
		}

		// 振動出力更新
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		XInputSetState(0, &vibration);

		float lvPow = 0.0f;
		for (auto e = g_leftVibration.begin(); e != g_leftVibration.end();) {
			e->second--;
			if (e->second < 0 || e->second == UINT_MAX) {
				e = g_leftVibration.erase(e);
			}
			else {
				if (e->first > lvPow) {
					lvPow = e->first;
				}
				++e;
			}
		}
		if (lvPow > 0.0f) {
			vibration.wLeftMotorSpeed = static_cast<WORD>(lvPow * MAX_VIBRATION);
			XInputSetState(0, &vibration);
		}

		float rvPow = 0.0f;
		for (auto e = g_rightVibration.begin(); e != g_rightVibration.end();) {
			e->second--;
			if (e->second < 0 || e->second == UINT_MAX) {
				e = g_rightVibration.erase(e);
			}
			else {
				if (e->first > rvPow) {
					rvPow = e->first;
				}
				++e;
			}
		}
		if (rvPow > 0.0f) {
			vibration.wRightMotorSpeed = static_cast<WORD>(rvPow * MAX_VIBRATION);
			XInputSetState(0, &vibration);
		}
	}
	else {
		if (g_joyPadConnection) {
			//SYSTEM_LOG("コントローラー未接続");
			g_joyPadConnection = false;
		}
	}
}

bool IsPress(unsigned char key) {
	return HoldTime(key) > 0;
}
bool IsTrigger(unsigned char key) {
	if (g_keyCount[key] == 1) {
		return true;
	}
	return false;
}
bool IsRelease(unsigned char key) {
	if (g_keyCount[key] == UINT_MAX) {
		return true;
	}
	return false;
}
bool IsRepeat(unsigned char key, unsigned int cycle) {
	unsigned int count = HoldTime(key);
	if (cycle <= 1) {
		return count > 0;
	}
	return count % cycle == 1;
}
unsigned int HoldTime(unsigned char key) {
	unsigned int count = g_keyCount[key];
	if (count == UINT_MAX) {
		return 0;
	}
	return count;
}
bool IsPress(JPadButton button) {
	return HoldTime(button) > 0;
}
bool IsTrigger(JPadButton button) {
	if (g_stdButtonCount[button] == 1) {
		return true;
	}
	return false;
}
bool IsRelease(JPadButton button) {
	if (g_stdButtonCount[button] == UINT_MAX) {
		return true;
	}
	return false;
}
bool IsRepeat(JPadButton button, unsigned int cycle) {
	unsigned int count = HoldTime(button);
	if (cycle <= 1) {
		return count > 0;
	}
	return count % cycle == 1;
}
unsigned int HoldTime(JPadButton button) {
	unsigned int count = g_stdButtonCount[button];
	if (count == UINT_MAX) {
		return 0;
	}
	return count;
}
XMFLOAT2 CursorPosition() {
	return g_cursorPos;
}
XMFLOAT2 CursorAcceleration() {
	return g_cursorMove;
}	
float MouseWheelDelta() {
	return g_mouseWheelDelta;
}
XMFLOAT2 LeftThumbPosition() {
	return ClampAxes(g_curtLeftThumb, -1.0f, 1.0f);
}
XMFLOAT2 RightThumbPosition() {
	return ClampAxes(g_curtRightThumb, -1.0f, 1.0f);
}
XMFLOAT2 LeftThumbAcceleration() {
	return ClampAxes(g_curtLeftThumb - g_prevLeftThumb, -1.0f, 1.0f);
}
XMFLOAT2 RightThumbAcceleration() {
	return ClampAxes(g_curtRightThumb - g_prevRightThumb, -1.0f, 1.0f);
}
float LeftTriggerStrength() {
	return g_curtLeftTrigger;
}
float RightTriggerStrength() {
	return g_curtRightTrigger;
}
float LeftTriggerAcceleration() {
	return g_curtLeftTrigger - g_prevLeftTrigger;
}
float RightTriggerAcceleration() {
	return g_curtRightTrigger - g_prevRightTrigger;
}
void LeftVibration(float power, unsigned int frame) {
	g_leftVibration.emplace(power, frame);
}
void RightVibration(float power, unsigned int frame) {
	g_rightVibration.emplace(power, frame);
}
bool IsJoyPadConnection() {
	return g_joyPadConnection;
}