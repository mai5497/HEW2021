#include "SceneManager.h"
#include "Main.h"
#include "DirectX.h"
#include "Texture.h"
#include "Input.h"
#include "Shader.h"
#include "Defines.h"
#include "FBX/FBXLoader.h"
#include "DrawBuffer.h"
#include "Sound.h"


using namespace DirectX;


//---�O���[�o���ϐ�
DrawBuffer g_buffer;
SceneManager* g_pSceneManager;



HRESULT ErrorBox(HRESULT hr, const char* message)
{
	MessageBox(NULL, message, "Error", MB_OK);
	return hr;
}

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	//fbxsdk�̏�����
	ggfbx::Initialize();
	// DirectX
	hr = InitDX(hWnd, width, height, false);
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to DirectX."); }
	// �L�[�{�[�h
	//hr = InitKeyboard();
	//if (FAILED(hr)) { return ErrorBox(hr, "Failed to Keyboard."); }
	// �V�F�[�_
	hr = SHADER->Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Shader."); }

	CSound::Init();

	g_pSceneManager = new SceneManager();
	g_pSceneManager->Init();

	//---�Q�[���Ŏg���I�u�W�F�N�g�̏�����
	//���_�̏����������\����
	struct Vertex
	{
		float pos[3];		//x,y,z
		float color[4];		//r,g,b,a
		float uv[2];		//u,v
	};

	//���_�����`
	//DirectX�͍�����W�n
	//������W�n�̉�]�����͎��v���
	//�e�w�������Ɍ����Ď���������Ƃ�
	//������������̂܂܉�]�̌�����\��

	//�O�p�`��`�悷�邽�߂̒��_�̏�����
	//���ꂼ��̍��W�n�̉�]�����ɍ��킹��
	//����]�����ɍ��킹�邱�Ƃ�
	//  �O�p�`�̕\�ʂƗ��ʂ𔻕ʂł��邩��

	Vertex vtx[] = {
		//��O�̖�
		{ { -1, 1,-1 },{ 1,1,1,1 },{ 0,0 } },//����
		{ {  1, 1,-1 },{ 1,1,1,1 },{ 1,0 } },//�E��
		{ { -1,-1,-1 },{ 1,1,1,1 },{ 0,1 } },//����

		{ {  1, 1,-1 },{ 1,1,1,1 },{ 1,0 } },//�E��
		{ {  1,-1,-1 },{ 1,1,1,1 },{ 1,1 } },//�E��
		{ { -1,-1,-1 },{ 1,1,1,1 },{ 0,1 } },//����

		//�E�̖�
		{ { 1, 1,-1 },{ 1,1,1,1 },{ 0,0 } },//����
		{ { 1, 1, 1 },{ 1,1,1,1 },{ 1,0 } },//�E��
		{ { 1,-1,-1 },{ 1,1,1,1 },{ 0,1 } },//����
	
		{ { 1, 1, 1 },{ 1,1,1,1 },{ 1,0 } },//�E��
		{ { 1,-1, 1 },{ 1,1,1,1 },{ 1,1 } },//�E��
		{ { 1,-1,-1 },{ 1,1,1,1 },{ 0,1 } },//����

		//���̖�
		{ {  1, 1,1 },{ 1,1,1,1 },{ 1,1 } },//����
		{ { -1, 1,1 },{ 1,1,1,1 },{ 0,1 } },//�E��
		{ {  1,-1,1 },{ 1,1,1,1 },{ 1,0 } },//����

		{ { -1, 1,1 },{ 1,1,1,1 },{ 0,1 } },//�E��
		{ { -1,-1,1 },{ 1,1,1,1 },{ 0,0 } },//�E��
		{ {  1,-1,1 },{ 1,1,1,1 },{ 1,0 } },//����

		//���̖�
		{ { -1, 1, 1 },{ 1,1,1,1 },{ 0,0 } },//����
		{ { -1, 1,-1 },{ 1,1,1,1 },{ 1,0 } },//�E��
		{ { -1,-1, 1 },{ 1,1,1,1 },{ 0,1 } },//����

		{ { -1, 1,-1 },{ 1,1,1,1 },{ 1,0 } },//�E��
		{ { -1,-1,-1 },{ 1,1,1,1 },{ 1,1 } },//�E��
		{ { -1,-1, 1 },{ 1,1,1,1 },{ 0,1 } },//����

		//��̖�
		{ { -1, 1, 1 },{ 1,1,1,1 },{ 0,0 } },//����
		{ {  1, 1, 1 },{ 1,1,1,1 },{ 1,0 } },//�E��
		{ { -1, 1,-1 },{ 1,1,1,1 },{ 0,1 } },//����

		{ {  1, 1, 1 },{ 1,1,1,1 },{ 1,0 } },//�E��
		{ {  1, 1,-1 },{ 1,1,1,1 },{ 1,1 } },//�E��
		{ { -1, 1,-1 },{ 1,1,1,1 },{ 0,1 } },//����

	};
	//���_�o�b�t�@�̍쐬
	g_buffer.CreateVertexBuffer(
		vtx, sizeof(Vertex),
		sizeof(vtx) / sizeof(Vertex)
	);

	
	return hr;
}

void Uninit()
{
	g_pSceneManager->Uninit();
	delete g_pSceneManager;
	CSound::Fin();
	SHADER->Uninit();
	UninitDX();
	ggfbx::Terminate();
}

void Update()
{
	CSound::Update();
	g_pSceneManager->Update();
}

void Draw()
{
	BeginDrawDX();
	
	//�ŏI�I�ɉ�ʂɕ`�悳���܂ł�
	//GPU��
	//�@���_�����ۂɉ�ʂɕ`�悳���ʒu�̌v�Z
	//�A�`�悳����ʂ̐F�̌v�Z
	//���s����
	//���̏������V�F�[�_�[�ƌĂ�(�@�͒��_�V�F�[�_�A
	//�A�̓s�N�Z���V�F�[�_
	//���_�o�b�t�@��GPU�ɓn�������ł͉�ʂɕ`�悳�ꂸ
	//�ǂ̌v�Z�ŉ�ʂɕ\������̂�
	//(�V�F�[�_)��ݒ肷��K�v������B

	//�V�F�[�_�̏����͂����ōs���Ăˁ�
	g_pSceneManager->Draw();
	

	EndDrawDX();
}

// EOF