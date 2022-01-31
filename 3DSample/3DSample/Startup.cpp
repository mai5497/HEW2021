#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include "Defines.h"
#include "Main.h"
#include "Input.h"
#include <stdio.h>
//���������[�N���o�̃w�b�_�t�@�C��
#include <crtdbg.h>

int g_nMouseWheelDelta;

// timeGetTime����̎g�p
#pragma comment(lib, "winmm.lib")

//--- �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// �G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�v���O�����I�����Ƀ��������[�N�̗L�����m�F
	_CrtSetDbgFlag(
		_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	
	   //--- �ϐ��錾
	   // �E�B���h�E�N���X����
	   // �ݒ肷��\����
	WNDCLASSEX wcex;
	// �쐬�����E�B���h�E�̃n���h��
	HWND hWnd;
	MSG message;

	// ---�E�B���h�N���X���̐ݒ�
	ZeroMemory(&wcex, sizeof(wcex));
	// �E�B���h�E�ƕR�Â�
	wcex.hInstance = hInstance;
	// �E�B���h�E�N���X�������ʂ��閼�O
	wcex.lpszClassName = "Class Name";
	// �E�B���h�E�v���V�[�W���̎w��
	wcex.lpfnWndProc = WndProc;
	// �E�B���h�E�̃X�^�C��(����)���w��
	wcex.style = CS_CLASSDC;
	// �\���̂̃T�C�Y���w��
	wcex.cbSize = sizeof(WNDCLASSEX);
	// �^�X�N�o�[�ɕ\������A�C�R�����w��
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// 16x16�T�C�Y�̃A�C�R��
	wcex.hIconSm = wcex.hIcon;
	// �J�[�\��
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	// �w�i�̎w��
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// �E�B���h�E�N���X���̓o�^
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	// ---�E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		// �ǉ��ŃE�B���h�E��
		// �X�^�C��(����)���w��
		WS_EX_OVERLAPPEDWINDOW,
		// �E�B���h�E���쐬���邽�߂�
		// �E�B���h�E�N���X���w��
		wcex.lpszClassName,
		// �L���v�V��������(��)��
		// �\�����閼�O
		"�^�C�g��",
		// ��{�̃E�B���h�E�X�^�C��
		WS_CAPTION | WS_SYSMENU,
		// �E�B���h�E�̕\���ʒuX
		CW_USEDEFAULT,
		// �E�B���h�E�̕\���ʒuY
		CW_USEDEFAULT,
		// �E�B���h�E�̉���
		SCREEN_WIDTH,
		// �E�B���h�E�̏c��
		SCREEN_HEIGHT,
		// �e�̃E�B���h�E�̎w��
		HWND_DESKTOP,
		// ���j���[�̎w��
		NULL,
		// �E�B���h�E��R�Â���
		// �A�v���P�[�V����
		hInstance,
		// �s�v
		NULL
	);

	// ---�E�B���h�E�̕\��
	ShowWindow(
		// �\������E�B���h�E
		hWnd,
		// �\�����@
		nCmdShow
	);
	// �E�B���h�E�̒��g�����t���b�V��
	UpdateWindow(hWnd);

	// ����������
	Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	// ���Ԍv���̐��x���w��
	timeBeginPeriod(1); // 1�~���b�Ԋu

						//--- FPS����̏�����
	int fpsCount = 0; // ��b�Ԃ̏�����
					  // �v���̊J�n����
	DWORD countStartTime = timeGetTime();
	// �O��̎��s����
	DWORD preExecTime = countStartTime;
	DWORD frameCount = 0;

	//--- �E�B���h�E�̊Ǘ�
	while (1)
	{
		// OS�Ŕ����������b�Z�[�W��
		// ���̃v���O�����̃L���[�Ɏ󂯎��
		if (PeekMessage(
			&message, NULL, 0, 0,
			PM_NOREMOVE))
		{
			// �L���[�ɗ��܂������b�Z�[�W��
			// ���o���Ă���
			if (!GetMessage(&message,
				NULL, 0, 0))
			{
				break;
			}
			else
			{
				// �󂯎�������b�Z�[�W��
				// �E�B���h�E�v���V�[�W���ɑ��M
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			// FPS�̐���
			DWORD nowTime = timeGetTime(); // ���ݎ���
										   // 1�b(1000�~���b)�o�߂���������
			if (nowTime - countStartTime >= 1000)
			{
				// �^�C�g��������FPS��\��
				char fpsText[20];
				sprintf(fpsText, "FPS:%d", fpsCount);
				SetWindowText(hWnd, fpsText);
				// ���̂P�b�Ԃ̌v������
				countStartTime = nowTime;
				fpsCount = 0;
			}

			// �Q�[���̏���
			// 60FPS(16�~���b)�o�߂���܂ł͏��������Ȃ�
			if (nowTime - preExecTime >= 1000 / 60)
			{
				UpdateInput(hWnd, g_nMouseWheelDelta);
				g_nMouseWheelDelta = 0;
				Update();
				Draw();
				//fpsCount++; // �Q�[���̏��������s��ꂽ
				preExecTime = nowTime;
			}
		}
	}


	//--- �I����
	timeEndPeriod(1); // ���Ԍv���̐��x��߂�
	Uninit();
	// �E�B���h�E�N���X���̓o�^����
	UnregisterClass(
		wcex.lpszClassName,
		hInstance
	);

	return 0;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// �󂯎�������b�Z�[�W���Ƃɏ���
	switch (message)
	{
	case WM_MOUSEWHEEL:
		g_nMouseWheelDelta += GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			ShowCursor(TRUE);
			int res = MessageBox(NULL, TEXT("�I�����܂����H"),
				TEXT(""), MB_OKCANCEL | MB_ICONQUESTION);
			if (res != IDCANCEL) {
				PostQuitMessage(0);
			}
		}
		break;
		// �E�B���h�E�����
	case WM_DESTROY:
		// WM_QUIT���b�Z�[�W�̔��s
		// �v���O���������S�I�������閽��
		PostQuitMessage(0);
		break;
	}

	// �ق��̃��b�Z�[�W��
	// ��{�̏������s�킹��
	return DefWindowProc(hWnd, message, wParam, lParam);
}