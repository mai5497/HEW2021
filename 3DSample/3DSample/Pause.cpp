//====================================================================
//
// �Q�[���I�[�o�[[Pause.cpp]
// �쐬��:�g����
// 
// �X�V��:2022/01/30	�쐬
//====================================================================

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include	"Pause.h"
#include	"GameObject.h"
#include	"Texture.h"
#include	"Input.h"
#include	"Camera.h"
#include	"Defines.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
typedef enum {							// �`�悷��I�u�W�F�N�g
	PASUE_BG = 0,
	PAUSE_TITLE,
	PAUSE_CONTINUE,
	PAUSE_RETRAY,
	PAUSE_SELECT,
	PAUSE_END,

	PAUSE_MAX
}PauseObject;

#define MAX_PAUSE_TEX	(PAUSE_MAX)		// �g�p����e�N�X�`���̐�
#define SELECT_SIZE		(1.3f)			// 1.3�{�ɂ���(�I�΂�Ă���Ƃ�)
//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
const char* g_TexPath[MAX_PAUSE_TEX] = {		// �e�N�X�`���p�X
	"Assets/Texture/Pause/Translucent.png",		// ������
	"Assets/Texture/Pause/Pause.png",			// �|�[�Y�^�C�g��
	"Assets/Texture/Pause/Continue.png",		// �Q�[���𑱂���
	"Assets/Texture/Pause/Retry.png",			// ���g���C
	"Assets/Texture/Pause/Select.png",			// �Z���N�g
	"Assets/Texture/Pause/End.png",				// �Q�[���I��

};

ID3D11ShaderResourceView* g_pPauseTex[MAX_PAUSE_TEX];	// �e�N�X�`��
Camera* g_pPauseCamra;									// �J�����C���X�^���X
GameObject g_PauseObject[PAUSE_MAX];					// �I�u�W�F�N�g�C���X�^���X


//==============================================================
//
//	Pause::�R���X�g���N�^
// 
//==============================================================
Pause::Pause()
{

}

//==============================================================
//
//	Pause::�f�X�g���N�^
// 
//==============================================================
Pause::~Pause()
{

}


//==============================================================
//
//	Pause::������
// 
//==============================================================
void Pause::Init()
{
	//---�I�u�W�F�N�g�E�e�N�X�`���ǂݍ���
	for (int i = 0; i < MAX_PAUSE_TEX; i++) {
		LoadTextureFromFile(g_TexPath[i], &g_pPauseTex[i]);
		g_PauseObject[i].Init();
	}

	//---�������w�i
	g_PauseObject[PASUE_BG].SetPos(XMFLOAT3(0.0f, 0.0f, 12.0f));
	g_PauseObject[PASUE_BG].SetSize(XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
	g_PauseObject[PASUE_BG].SetCollor(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f));

	//---�|�[�Y
	g_PauseObject[PAUSE_TITLE].SetPos(XMFLOAT3(0.0f, 0.23f,11.0f));
	g_PauseObject[PAUSE_TITLE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
 
	//---�Q�[���𑱂���
	g_PauseObject[PAUSE_CONTINUE].SetPos(XMFLOAT3(0.0f, 0.1f,10.0f));
	g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	//---���g���C
	g_PauseObject[PAUSE_RETRAY].SetPos(XMFLOAT3(0.0f, 0.0f, 9.0f));
	g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	//---�X�e�[�W�Z���N�g
	g_PauseObject[PAUSE_SELECT].SetPos(XMFLOAT3(0.0f, -0.1f, 8.0f));
	g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	//---�Q�[���I��
	g_PauseObject[PAUSE_END].SetPos(XMFLOAT3(0.0f, -0.2f, 7.0f));
	g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	//---�J�����C���X�^���X
	g_pPauseCamra = new Camera;
	g_pPauseCamra->Init();

	m_SelectState = 1;
}

//=========================================================
//	�I��
//=========================================================
void Pause::Uninit()
{
	//---�I�u�W�F�N�g�E�e�N�X�`�����
	for (int i = 0; i < MAX_PAUSE_TEX; i++){
		SAFE_RELEASE(g_pPauseTex[i]);
		g_PauseObject[i].Uninit();
	}

	//---�J�������
	g_pPauseCamra->Uninit();
	delete  g_pPauseCamra;
}


//=========================================================
//	�X�V
//=========================================================
int Pause::Update()
{
	//---�F�̕ύX
	g_PauseObject->Update();

	//---�J�[�\���ړ�

	if (IsRelease(VK_DOWN) || IsRelease(JPadButton::DPAD_DOWN)) {		// ���ړ�
		CSound::Play(SE_SELECT_1);

		m_SelectState++;

		if (m_SelectState > 4) {
			m_SelectState = 4;
		}
	}

	if (IsRelease(VK_UP) || IsRelease(JPadButton::DPAD_UP)) {			// ��ړ�
		CSound::Play(SE_SELECT_1);
		m_SelectState--;
		if (m_SelectState < 1) {
			m_SelectState = 1;
		}
	}

	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {				// ���肫�[
		CSound::Play(SE_ENTER_1);
		
		// �I�΂ꂽ�l��Ԃ�
		return m_SelectState;
	
	}

	// �I������Ă���Ƃ��Ƀe�N�X�`���̃T�C�Y��1.3�{�ɂ���
	switch (m_SelectState)
	{
	case 1:
		g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f * SELECT_SIZE, 0.3 * SELECT_SIZE, 0.0f));

		g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f, 0.3 , 0.0f));

		break;

	case 2:
		g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f * SELECT_SIZE, 0.3 * SELECT_SIZE, 0.0f));

		g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

		break;

	case 3:
		g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f * SELECT_SIZE, 0.3 * SELECT_SIZE, 0.0f));

		g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

		break;

	case 4:
		g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f * SELECT_SIZE, 0.3 * SELECT_SIZE, 0.0f));

		g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	default:
		break;
	}

}
//=========================================================
//	�`��
//=========================================================
void Pause::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	g_pPauseCamra->Bind2D();

	for (int i = 0; i < MAX_PAUSE_TEX; i++){
		SHADER->SetTexture(g_pPauseTex[i]);
		g_PauseObject[i].Draw();
	}

	SHADER->SetTexture(NULL);
}
