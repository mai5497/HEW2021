//============== �C���N���[�h�� ======================
#include "clear.h"
#include "GameObject.h"
#include "Texture.h"
#include "Input.h"
#include "Camera.h"
#include "Defines.h"

//============== �萔��` ======================
#define CLEAR_CNT			(600)
#define MAX_CLAER_SCENE_TEX	(4)			// �e�N�X�`���̐�

//============== �O���[�o���ϐ���` ======================
static DrawBuffer			g_pBuffer;								// ���_�o�b�t�@
ID3D11ShaderResourceView*	g_pClearTex[MAX_CLAER_SCENE_TEX];		// �e�N�X�`��

Camera*			g_pClearCamera;									// �J����
GameObject		g_pClearObject[MAX_CLAER_SCENE_TEX];			// �Q�[���I�u�W�F�N�g
float			g_ArrowPosY;									// �J�[�\�����W
//static int		g_nTimer;										// �^�C�}�[
static int		g_SelectState;									// �V�[���̒l


const char* g_pClearTexFName[MAX_CLAER_SCENE_TEX] = {
	"Assets/Texture/Scene/GameClear.png",
	"Assets/Texture/Scene/NextStage.png",
	"Assets/Texture/Scene/StageSelect.png",
	"Assets/Texture/Scene/SelectObj_Block_Pencel.png",
};


//=========================================================
//
//	������
//
//=========================================================
void InitClear() {
	// �^�C�}�[������
	//g_nTimer = CLEAR_CNT;

	// �I�u�W�F�N�g�E�e�N�X�`���ǂݍ���
	for (int i = 0; i < MAX_CLAER_SCENE_TEX; i++){
		LoadTextureFromFile(g_pClearTexFName[i], &g_pClearTex[i]);
		g_pClearObject[i].Init();
	}

	//---�Q�[���N���A�e�N�X�`��
	g_pClearObject[0].SetPos(XMFLOAT3(0.0f, 0.15f, 4));			// ���W
	g_pClearObject[0].SetSize(XMFLOAT3(0.45f, 0.3f, 1));			// �T�C�Y
	//g_pClearObject[0].SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f));	// ������

	//---���̃X�e�[�W
	g_pClearObject[1].SetPos(XMFLOAT3(0.0f, 0.0f, 3));
	g_pClearObject[1].SetSize(XMFLOAT3(0.4f, 0.3f, 1));

	//---�X�e�[�W�Z���N�g
	g_pClearObject[2].SetPos(XMFLOAT3(0.0f, -0.15f, 2));
	g_pClearObject[2].SetSize(XMFLOAT3(0.4f, 0.34f, 1));

	//---�J�[�\��
	g_pClearObject[3].SetPos(XMFLOAT3(-0.35f, 0.0f, 1));
	g_pClearObject[3].SetSize(XMFLOAT3(0.2f, 0.1f, 1));

	//g_pClearObject = new GameObject;
	//g_pClearObject->Init();
	//g_pClearObject->SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));	// ������

	g_pClearCamera = new Camera;
	g_pClearCamera->Init();

	// �J�[�\���̏����ʒu
	g_ArrowPosY = 0.0f;

	// �V�[���̒l����
	g_SelectState = STATE_NEXT;
}

//===========================================================
//
//	�I������
//
//===========================================================
void UninitClear() {

	// �I�u�W�F�N�g�E�e�N�X�`�����
	for (int i = 0; i < MAX_CLAER_SCENE_TEX; i++)
	{
		SAFE_RELEASE(g_pClearTex[i]);
		g_pClearObject[i].Uninit();

	}

	// �J�����C���X�^���X���
	g_pClearCamera->Uninit();
	delete g_pClearCamera;

}

//===========================================================
//
//	�X�V
//	�߂�l�F���̃X�e�[�W�ɍs���̂��I���̃V�[���ɖ߂邩�𐔎��ŕԂ�
//
//===========================================================
int	UpdateClear() 
{
	// �^�C�}�[�J�E���g�_�E��
	//g_nTimer--;
	//if (g_nTimer < 0) {
	//	return STATE_SELECT;	// ��莞�Ԃ�������X�e�[�W�I���֖߂�
	//}


	//---�J�[�\���ړ�
	if (IsTrigger(VK_UP) || IsRelease(JPadButton::DPAD_UP)) {
		CSound::Play(SE_SELECT_1);

		g_ArrowPosY += 0.15f;

		g_SelectState = STATE_NEXT;
		if (g_ArrowPosY > 0.0f) {
			g_ArrowPosY = 0.0f;
			g_SelectState = STATE_NEXT;
		}
	}

	if (IsTrigger(VK_DOWN) || IsRelease(JPadButton::DPAD_DOWN)) {
		CSound::Play(SE_SELECT_1);

		g_ArrowPosY -= 0.15f;

		g_SelectState = STATE_SELECT;
		if (g_ArrowPosY < -0.15f) {
			g_ArrowPosY = 0.15f;
			g_SelectState = STATE_SELECT;
		}
	}

	//---�J�[�\���̃I�u�W�F�N�g�ĕ\��
	g_pClearObject[3].SetPos(XMFLOAT3(-0.35f, g_ArrowPosY, 0.9f));

	//---����
	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {
		CSound::Play(SE_ENTER_1);
		return g_SelectState;
	}
	// �Ƃ肠�����P�Ŏ��̃X�e�[�W
	//if (IsRelease('1') || IsRelease(JPadButton::Y)) {
	//	return STATE_NEXT;
	//}
	// �Q�ŃX�e�[�W�I��
	//if (IsRelease('2') || IsRelease(JPadButton::A)) {
	//	return STATE_SELECT;
	//}
	//g_pClearObject->Update();

	return -1;
}

//===================
//
//	�`��
//
//===================
void DrawClear() {
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	g_pClearCamera->Bind2D();

	for (int i = 0; i < MAX_CLAER_SCENE_TEX; i++)
	{
		SHADER->SetTexture(g_pClearTex[i]);
		g_pClearObject[i].Draw();

	}

	SHADER->SetTexture(NULL);
}

