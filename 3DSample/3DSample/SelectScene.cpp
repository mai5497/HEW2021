//****************************************************
//
//	�Z���N�g�V�[��
//	�쐬�ҁF���c�đ�
//	
//	2021/12/27 : �쐬
//	2022/01/02 : �R�����g�ǉ��i�ɒn�c�j
//				 �X�e�[�W�ԍ��̕ϐ���ǉ��i�ɒn�c�j
//
//****************************************************

//========================= �C���N���[�h�� ===========================
#include "SelectScene.h"
#include "Input.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"

#define MAX_OBJ		(10)

//========================= �O���[�o���ϐ���` ===========================
ID3D11ShaderResourceView* g_pSelectTex[MAX_OBJ];
Camera* g_pSelectCamera;
GameObject g_pSelectObject[MAX_OBJ];

const char* g_pTexFName[MAX_OBJ] = {
	"Assets/Texture/SceneTexture/Select000.png",
	"Assets/Texture/SceneTexture/Select001.jpg",
	"Assets/Texture/SceneTexture/Select002.jpg",
	"Assets/Texture/SceneTexture/Select003.jpg",
	"Assets/Texture/SceneTexture/arrow_down.png",
	"Assets/Texture/SceneTexture/Select000.png",
	"Assets/Texture/SceneTexture/Select001.jpg",
	"Assets/Texture/SceneTexture/Select002.jpg",
	"Assets/Texture/SceneTexture/Select003.jpg",
	"Assets/Texture/SceneTexture/arrow_down.png",
};

float g_arrowPosX;
XMFLOAT3 g_pos;

//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
SelectScene::SelectScene(void)
{

}


//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
SelectScene::~SelectScene(void)
{

}


//====================================================================
//
//		������
//
//====================================================================
void SelectScene::Init()
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		LoadTextureFromFile(g_pTexFName[i], &g_pSelectTex[i]);

	}

	g_pSelectObject[0].Init();	// �w�i
	g_pSelectObject[0].SetPos(DirectX::XMFLOAT3(0, 11, -18));
	g_pSelectObject[0].SetSize(DirectX::XMFLOAT3(4, 2, 0));

	g_pSelectObject[1].Init();
	g_pSelectObject[1].SetPos(DirectX::XMFLOAT3(-4, 8, -18));
	g_pSelectObject[1].SetSize(DirectX::XMFLOAT3(2, 1, 0));

	g_pSelectObject[2].Init();
	g_pSelectObject[2].SetPos(DirectX::XMFLOAT3(0, 8, -18));
	g_pSelectObject[2].SetSize(DirectX::XMFLOAT3(2, 1, 0));

	g_pSelectObject[3].Init();
	g_pSelectObject[3].SetPos(DirectX::XMFLOAT3(4, 8, -18));
	g_pSelectObject[3].SetSize(DirectX::XMFLOAT3(2, 1, 0));

	g_pSelectObject[4].Init();
	g_pSelectObject[4].SetPos(DirectX::XMFLOAT3(0, 11, -18));
	g_pSelectObject[4].SetSize(DirectX::XMFLOAT3(4, 2, 0));

	g_pSelectObject[5].Init();
	g_pSelectObject[5].SetPos(DirectX::XMFLOAT3(-4, 8, -18));
	g_pSelectObject[5].SetSize(DirectX::XMFLOAT3(2, 1, 0));

	g_pSelectObject[6].Init();
	g_pSelectObject[6].SetPos(DirectX::XMFLOAT3(0, 8, -18));
	g_pSelectObject[6].SetSize(DirectX::XMFLOAT3(2, 1, 0));

	g_pSelectObject[7].Init();
	g_pSelectObject[7].SetPos(DirectX::XMFLOAT3(4, 8, -18));
	g_pSelectObject[7].SetSize(DirectX::XMFLOAT3(2, 1, 0));

	g_pSelectObject[8].Init();
	g_pSelectObject[8].SetPos(DirectX::XMFLOAT3(0, 11, -18));
	g_pSelectObject[8].SetSize(DirectX::XMFLOAT3(4, 2, 0));

	g_pSelectObject[9].Init();
	g_pSelectObject[9].SetPos(DirectX::XMFLOAT3(-4, 8, -18));
	g_pSelectObject[9].SetSize(DirectX::XMFLOAT3(2, 1, 0));




	// ���
	g_pSelectObject[4].Init();
	g_pSelectObject[4].SetPos(DirectX::XMFLOAT3(-4, 9, -18));
	g_pSelectObject[4].SetSize(DirectX::XMFLOAT3(1, 1, 0));

	g_pSelectCamera = new Camera;
	g_pSelectCamera->Init();
	

	g_arrowPosX = 0;

	CSound::Play(SELECT_BGM);
}


//====================================================================
//
//		�I������
//
//====================================================================
void SelectScene::Uninit()
{
	for (int i = 0; i < MAX_OBJ; ++i)
	{
		SAFE_RELEASE(g_pSelectTex[i]);
		g_pSelectObject[i].Uninit();
	}
	g_pSelectCamera->Uninit();

	delete g_pSelectCamera;

	CSound::Stop(SELECT_BGM);
}


//====================================================================
//
//		�X�V����
//
//====================================================================
SCENE SelectScene::Update()
{

	if (IsTrigger('1')) {	// �X�e�[�W�P
		m_StageNum = 1;
		g_arrowPosX = -4;

	}
	if (IsTrigger('2')) {	// �X�e�[�W�Q
		m_StageNum = 2;
		g_arrowPosX = 0;

	}
	if (IsTrigger('3')) {	// �X�e�[�W�R
		m_StageNum = 3;
		g_arrowPosX = 4;

	}
	// �I�����ꂽ�X�e�[�W�ɖ����ړ�
	g_pSelectObject[4].SetPos(DirectX::XMFLOAT3(g_arrowPosX, 9, -18));

	if (IsTrigger(VK_RETURN)) {
		CSound::Play(SE_ENTER_1);
		switch (m_StageNum)
		{
		case 1:
			return SCENE_GAME;
		case 2:
			return SCENE_GAME;
		case 3:
			return SCENE_GAME;
		default:
			break;
		}
	}



	return SCENE_SELECT;
}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void SelectScene::Draw()
{
	SHADER->Bind(VS_WORLD, PS_PHONG);




	g_pSelectCamera->Bind();



	for (int i = 0; i < MAX_OBJ; ++i)
	{
		SHADER->SetTexture(g_pSelectTex[i]);
		g_pSelectObject[i].Draw();
	}
	



	SHADER->SetTexture(NULL);

}


//====================================================================
//
//		�V�[���ԍ��擾
//
//====================================================================
int SelectScene::GetStageNum()
{
	return m_StageNum;
}