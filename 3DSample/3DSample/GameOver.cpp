//====================================================================
//
// �Q�[���I�[�o�[[GameOver.cpp]
// �쐬��:�g����
// 
// �X�V��:2022/01/10	�쐬
//====================================================================

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include	"GameOver.h"
#include	"GameObject.h"
#include	"Texture.h"
#include	"Input.h"
#include	"Camera.h"
#include	"Defines.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define	CHANGE_STATE_CNT			(600)				// �V�[���؂�ւ��܂ł̃^�C�}�[
#define	MAX_GAMEOVER_TEX			(5)					// �e�N�X�`���̐�

#define LOGO_POS_X					(0.0f)				// X���W
#define LOGO_POS_Y					(0.1f)				// Y���W
#define LOGO_POS_Z					(300.0f)			// Z���W

#define	LOGO_SIZE_X					(1.0f)				// ��
#define	LOGO_SIZE_Y					(0.1f)				// �c
#define	LOGO_SIZE_Z					(0.1f)				// ���s

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************

ID3D11ShaderResourceView*	g_pGameOverTex[MAX_GAMEOVER_TEX];		// �e�N�X�`��
static DrawBuffer			g_pBuffer;								// ���_�o�b�t�@

GameObject		g_pGameOverObject[MAX_GAMEOVER_TEX];				// �Q�[���I�u�W�F�N�g
Camera*			g_pGameOverCamera;									// �Q�[���J����

//static int g_nTimer;				// �^�C�}�[

const char* g_pGameOverTexFName[MAX_GAMEOVER_TEX] = {		// �e�N�X�`���f�[�^
	"Assets/Texture/Scene/SeceneBG.png",
	"Assets/Texture/Scene/GameOver.png",
	"Assets/Texture/Scene/Retry.png",
	"Assets/Texture/Scene/StageSelect.png",
	"Assets/Texture/Scene/SelectObj_Block_Pencel.png",
};

float	g_GO_ArrowPosY;										// �J�[�\���ړ�
int		g_GO_SelectState;									// �V�[���̒l


//=========================================================
//	������
//=========================================================
void InitGameOver()
{
	//---�^�C�}�[������
	//g_nTimer = CHANGE_STATE_CNT;

	//---�I�u�W�F�N�g�E�e�N�X�`���ǂݍ���
	for (int i = 0; i < MAX_GAMEOVER_TEX; i++){
		LoadTextureFromFile(g_pGameOverTexFName[i],&g_pGameOverTex[i]);
		g_pGameOverObject[i].Init();
	}

	//---�������w�i
	g_pGameOverObject[0].SetPos(XMFLOAT3(0.0f, 0.15f, 8));
	g_pGameOverObject[0].SetSize(XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 1));
	g_pGameOverObject[0].SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));

	//---�Q�[���I�[�o�[
	g_pGameOverObject[1].SetPos(XMFLOAT3(0.0f, 0.15f, 4));
	g_pGameOverObject[1].SetSize(XMFLOAT3(0.45f, 0.3f, 1));

	//---���g���C
	g_pGameOverObject[2].SetPos(XMFLOAT3(0.0f, 0.0f, 3));
	g_pGameOverObject[2].SetSize(XMFLOAT3(0.4f, 0.3f, 1));

	//---�X�e�[�W�Z���N�g
	g_pGameOverObject[3].SetPos(XMFLOAT3(0.0f, -0.15f, 2));
	g_pGameOverObject[3].SetSize(XMFLOAT3(0.4f, 0.34f, 1));

	//---�J�[�\��
	g_pGameOverObject[4].SetPos(XMFLOAT3(-0.35f, 0.0f, 1));
	g_pGameOverObject[4].SetSize(XMFLOAT3(0.2f, 0.1f, 1));


	//---�N���X�������m��
	g_pGameOverCamera = new Camera;
	g_pGameOverCamera->Init();

	// �J�[�\���̈ʒu
	g_GO_ArrowPosY = 0.0f;

	//---�V�[���̒l
	g_GO_SelectState = STATE_RETRY;
}

//=========================================================
//	�I������
//=========================================================
void UninitGameOver()
{
	//---�I�u�W�F�N�g�E�e�N�X�`�����
	for (int i = 0; i < MAX_GAMEOVER_TEX; i++){
		SAFE_RELEASE(g_pGameOverTex[i]);
		g_pGameOverObject[i].Uninit();

	}
	//---�������J��
	g_pGameOverCamera->Uninit();
	delete g_pGameOverCamera;

}

//=========================================================
//	�X�V����
//=========================================================
int UpdateGameOver()
{
	//---�^�C�}�[�J�E���g�_�E��
	//g_nTimer--;
	//if (g_nTimer < 0) {
	//	return STATE_SELECT;					// ��莞�Ԍ�ɃX�e�[�W�I����
	//}

	//---�J�[�\���ړ�
	if (IsTrigger(VK_UP) || IsRelease(JPadButton::DPAD_UP)) {
		CSound::Play(SE_SELECT_1);

		g_GO_ArrowPosY += 0.15f;
		g_GO_SelectState = STATE_RETRY;

		if (g_GO_ArrowPosY > 0.0f) {
			g_GO_ArrowPosY = 0.0f;
			g_GO_SelectState = STATE_RETRY;
		}
	}

	if (IsTrigger(VK_DOWN) || IsRelease(JPadButton::DPAD_DOWN)) {
		CSound::Play(SE_SELECT_1);

		g_GO_ArrowPosY -= 0.15f;
		g_GO_SelectState = STATE_SELECT;

		if (g_GO_ArrowPosY < -0.15f) {
			g_GO_ArrowPosY = 0.0f;
			g_GO_SelectState = STATE_SELECT;
		}
	}

	//---�J�[�\���̃I�u�W�F�N�g�ĕ\��
	g_pGameOverObject[4].SetPos(XMFLOAT3(-0.35f, g_GO_ArrowPosY, 0.9f));

	//---����
	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {
		CSound::Play(SE_ENTER_1);
		return g_GO_SelectState;
	}


	//// 1�{�^���Ń��g���C
	//if (IsRelease('1') || IsRelease(JPadButton::Y)) {
	//	return STATE_RETRY;						
	//}

	//// 2�{�^���ŃX�e�[�W�I��
	//if (IsRelease('2') || IsRelease(JPadButton::A)) {
	//	return STATE_SELECT;
	//}

	// �F�̕ύX�̂��߃I�u�W�F�N�g�̍X�V�������L�q
	g_pGameOverObject->Update();
	return -1;
}

//=========================================================
//	�`�揈��
//=========================================================
void DrawGameOver()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	g_pGameOverCamera->Bind2D();

	for (int i = 0; i < MAX_GAMEOVER_TEX; i++){
		SHADER->SetTexture(g_pGameOverTex[i]);
		g_pGameOverObject[i].Draw();
	}
	SHADER->SetTexture(NULL);
}