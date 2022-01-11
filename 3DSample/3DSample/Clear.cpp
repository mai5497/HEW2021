//============== �C���N���[�h�� ======================
#include "clear.h"
#include "GameObject.h"
#include "Texture.h"
#include "Input.h"
#include "Camera.h"
#include "Defines.h"



//============== �萔��` ======================
#define CLEAR_CNT			(600)

//============== �O���[�o���ϐ���` ======================
static int g_nTimer;					// �^�C�}�[
ID3D11ShaderResourceView* g_pClearTex;	// �e�N�X�`��
static DrawBuffer g_pBuffer;			// ���_�o�b�t�@
GameObject* g_pClearObject;				// �Q�[���I�u�W�F�N�g
Camera* g_pClearCamera;


//=========================================================
//
//	������
//
//=========================================================
void InitClear() {
	// �^�C�}�[������
	g_nTimer = CLEAR_CNT;

	LoadTextureFromFile("Assets/Texture/Clear.png", &g_pClearTex);
	g_pClearObject = new GameObject;
	g_pClearObject->Init();
	g_pClearObject->SetPos(DirectX::XMFLOAT3(0, 0, 300));
	g_pClearObject->SetSize(DirectX::XMFLOAT3(1, (float)SCREEN_HEIGHT / SCREEN_WIDTH, 1));
	g_pClearCamera = new Camera;
	g_pClearCamera->Init();
	//g_pClearObject->SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));	// ������
}

//===========================================================
//
//	�I������
//
//===========================================================
void UninitClear() {
	SAFE_RELEASE(g_pClearTex);
	g_pClearCamera->Uninit();
	delete g_pClearCamera;
	g_pClearObject->Uninit();
	delete g_pClearObject;
}

//===========================================================
//
//	�X�V
//	�߂�l�F���̃X�e�[�W�ɍs���̂��I���̃V�[���ɖ߂邩�𐔎��ŕԂ�
//
//===========================================================
int	UpdateClear() {
	// �^�C�}�[�J�E���g�_�E��
	g_nTimer--;
	if (g_nTimer < 0) {
		return GO_SELECT;	// ��莞�Ԃ�������X�e�[�W�I���֖߂�
	}

	// �Ƃ肠�����P�Ŏ��̃X�e�[�W
	if (IsTrigger('1')) {
		return NEXTSTAGE;
	}
	// �Q�ŃX�e�[�W�I��
	if (IsTrigger('2')) {
		return GO_SELECT;
	}
	//g_pClearObject->Update();
}

//===================
//
//	�`��
//
//===================
void DrawClear() {
	SHADER->Bind(VS_WORLD, PS_PHONG);

	g_pClearCamera->Bind2D();

	SHADER->SetTexture(g_pClearTex);

	g_pClearObject->Draw();

	SHADER->SetTexture(NULL);
}

