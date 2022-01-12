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

#define LOGO_POS_X						(0.0f)				// X���W
#define LOGO_POS_Y						(0.1f)				// Y���W
#define LOGO_POS_Z						(300.0f)				// Z���W

#define	LOGO_SIZE_X					(1.0f)				// ��
#define	LOGO_SIZE_Y					(0.1f)				// �c
#define	LOGO_SIZE_Z					(0.1f)				// ���s
//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
static int g_nTimer;												// �^�C�}�[
ID3D11ShaderResourceView* g_pGameOverTex;		// �e�N�X�`��
static DrawBuffer g_pBuffer;									// ���_�o�b�t�@
GameObject* g_pGameOverObject;							// �Q�[���I�u�W�F�N�g
Camera* g_pGameOverCamera;								// �Q�[���J����

//=========================================================
//	������
//=========================================================
void InitGameOver()
{
	//---�^�C�}�[������
	g_nTimer = CHANGE_STATE_CNT;

	//---�e�N�X�`���ǂݍ���
	LoadTextureFromFile("Assets/Texture/GameOver.png", &g_pGameOverTex);

	//---�N���X�������m��
	g_pGameOverObject = new GameObject;
	g_pGameOverObject->Init();
	g_pGameOverObject->SetPos(XMFLOAT3(LOGO_POS_X, LOGO_POS_Y, LOGO_POS_Z));
	g_pGameOverObject->SetSize(XMFLOAT3(LOGO_SIZE_X, LOGO_SIZE_Y, LOGO_SIZE_Z));

	g_pGameOverCamera = new Camera;
	g_pGameOverCamera->Init();
}

//=========================================================
//	�I������
//=========================================================
void UninitGameOver()
{
	//---�e�N�X�`�����
	SAFE_RELEASE(g_pGameOverTex);

	//---�������J��
	g_pGameOverCamera->Uninit();
	delete g_pGameOverCamera;

	g_pGameOverObject->Uninit();
	delete g_pGameOverObject;
}

//=========================================================
//	�X�V����
//=========================================================
int UpdateGameOver()
{

	//---�^�C�}�[�J�E���g�_�E��
	g_nTimer--;

	if (g_nTimer < 0) {				
		return STATE_SELECT;					// ��莞�Ԍ�ɃX�e�[�W�I����
	}

	// 1�{�^���Ń��g���C
	if (IsRelease('1')) {
		return STATE_RETRY;						
	}

	// 2�{�^���ŃX�e�[�W�I��
	if (IsRelease('2')) {
		return STATE_SELECT;
	}

}

//=========================================================
//	�`�揈��
//=========================================================
void DrawGameOver()
{

	SHADER->Bind(VS_WORLD, PS_PHONG);
	g_pGameOverCamera->Bind2D();

	SHADER->SetTexture(g_pGameOverTex);

	g_pGameOverObject->Draw();

	SHADER->SetTexture(NULL);
}