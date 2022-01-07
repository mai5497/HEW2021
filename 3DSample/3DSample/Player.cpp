/**
 * @file Player.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/19 �Ԑe���킯�đłĂ�悤��(�ɒn�c)
 * @brief �v���C���[�Ɋւ��鏈��
 */

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"Player.h"
#include	"Input.h"
#include	"TPSCamera.h"
#include	"MyVector.h"
#include	<math.h>
#include	"Controller.h"
#include	"MyMath.h"

// ���f���`��p
#include	"Texture.h"
#include	"FBX//FBXPlayer.h"
#include	"DrawBuffer.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define FPS				(60)
#define BULLET_SPEED	(0.2f)
#define PLAYER_SIZE		(0.25f)

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
XMFLOAT3 pOldCameraPos;
DrawBuffer *Player::m_pBuffer = NULL;
FBXPlayer *Player::m_pFBX = NULL;




//==============================================================
//
//	Player�N���X::�R���X�g���N�^
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����	�F void
//
//==============================================================
Player::Player():m_pControllCamera(nullptr),m_ppBullets(NULL),m_nBulletNum(0)
{
	//----- �ϐ������� -----
	LoadTextureFromFile("Assets/Model/princess.png", &m_pPlayerTex);

	// ---�ϐ�������
	m_pos.x = -10.0f;
	m_pos.y = 3.0f;
	m_pos.z = -10.0f;

	m_size = XMFLOAT3(PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE);


	m_Angle = XMFLOAT3(0, 0, 0);
	m_collisionType = COLLISION_DYNAMIC;



}

//==============================================================
//
//	Player�N���X::�f�X�g���N�^
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
Player::~Player()
{
	m_pControllCamera = nullptr;
	SAFE_RELEASE(m_pPlayerTex);
	Uninit();
}

//==============================================================
//
//	Player�N���X::Init
//	�쐬��	�F ���c�đ�
//	�߂�l	�F bool�^
//	����		�F void
//
//==============================================================
bool Player::Init()
{
	//----- �e�̏��� -----
	struct BulletSetting
	{
		XMFLOAT3 pos;
		XMFLOAT3 size;
	};


	BulletSetting settings[] = 
	{
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
	};

	//�����f�[�^����e�����v�Z
	m_nBulletNum = sizeof(settings) / sizeof(settings[0]);

	//�|�C���^���i�[����z����쐬
	m_ppBullets = new Bullet *[m_nBulletNum];

	//���ꂼ��̔z��ɒe���������m��
	for (int i = 0; i < m_nBulletNum; i++)
	{
		m_ppBullets[i] = new Bullet(settings[i].size);
		m_ppBullets[i]->SetPos(settings[i].pos);
		m_ppBullets[i]->Init();	// �e�p������
	}

	//----- �v���C���[���� -----
	GameObject::Init();	// �v���C���[�p�������H
	if (m_pBuffer == NULL) {
		Player::LoadPlayer("Assets/Model/princess.fbx");
	}


	return true;
}

//==============================================================
//
//	Player�N���X::Uninit
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Player::Uninit()
{
	if (m_ppBullets != NULL)
	{
		for (int i = 0; i < m_nBulletNum; i++)
		{
			m_ppBullets[i]->Uninit();
			//�ʂɍ폜
			delete m_ppBullets[i];
			m_ppBullets[i] = NULL;
		}
		//�z����폜
		delete[] m_ppBullets;
		m_ppBullets = NULL;
	}

	SAFE_RELEASE(m_pPlayerTex);

	GameObject::Uninit();
}

//==============================================================
//
//	Player�N���X::Update
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Player::Update()
{
	//----- �ϐ������� -----
	XMFLOAT2 Axis = LeftThumbPosition();
	static bool rbFlg;
	bool moveFlg = false;

	bool keyL = IsPress('A');
	bool keyR = IsPress('D');
	bool keyU = IsPress('W');
	bool keyD = IsPress('S');
	bool keyBlue = IsPress('E');
	bool keyRed = IsPress('Q');
	bool keyJ = IsTrigger(VK_SPACE);

	//�P�b�ԁi60FPS�j��2M�i���Ƃ�\���B
	const float Move = (10.0f / 60) * 2;

	m_move = XMFLOAT3(Axis.x, m_move.y, Axis.y);

	float CameraRad = m_pControllCamera->GetxzAngle() * 3.14159265359f / 180.0f;
	
	//�v���C���[�ړ�
	m_move.y -= 0.01f;
	if (keyL){
		moveFlg = true;
		m_move.x -= Move;
		if (m_Angle.y >= -CameraRad - 90.0f * 3.1415926f / 180.0f){
			m_Angle.y -= 0.1f;
		}
	}

	if (keyR){ 
		moveFlg = true;
		m_move.x += Move;
		if (m_Angle.y <= -CameraRad + 90.0f * 3.1415926f / 180.0f){
			m_Angle.y += 0.1f;
		}
	}

	if (keyU){
		moveFlg = true;
		m_move.z += Move;
		if (m_Angle.y <= -CameraRad) {
			m_Angle.y += 0.1f;
		}
		if (m_Angle.y >= -CameraRad) {
			m_Angle.y -= 0.1f;
		}
	}

	if (keyRed) {	// �Ԃɐ؂�ւ�
		rbFlg = true;	// ��
	}

	if (keyBlue) {	// �ɐ؂�ւ�
		rbFlg = false;	// ��
	}

	if (keyD) { m_move.z -= Move; }
	if (keyJ) { m_move.y += 0.2f; }			// �W�����v

	if (IsPress(VK_UP)) {	// �e�̔�΂��ʒu�L�΂�
		/*todo �e�̔򋗗��L�΂�*/
	}
	if (IsPress(VK_DOWN)) {	// �e�̔�΂��ʒu�Z��
		/*todo �e�̔򋗗����Ƃ�*/
	}

	if (IsTrigger('Z')){	// �e��΂�
		//CreateBullet(m_pControllCamera,rbFlg);
		CreateBullet(rbFlg);
	}

	if (IsTrigger('F')) {	// �e��΂�

		CreateBullet(m_pControllCamera,rbFlg);

	}

	MyVector2 direction(0, 0);

	// �ɍ��W���g����TPS���_
	direction.x = m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	direction.y = m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);
	direction = direction.GetNormalize();

	////���W���X�V
	//m_pos.x += m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//m_pos.y += m_move.y;
	//m_pos.z += m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);

	//�����蔻��
	if (moveFlg = true) {
		m_DrawAngle = atan2(m_move.z, m_move.x);
		m_DrawAngle -= XM_PI * 0.5f;
	}
	m_move.x = direction.x * Move;
	m_move.z = direction.y * Move;


	for (int i = 0; i < m_pDwarfManager->GetDwarfNum(); i++) {
		for (int j = 0; j < m_nBulletNum; j++) {
			if (!CollisionSphere(m_pDwarfManager->GetDwarf(i), m_ppBullets[j])) {		// �߂��ɂ��Ȃ������牺�̏��������Ȃ�
				continue;
			}

			if (m_ppBullets[j]->GetRB() == m_pDwarfManager->GetDwarf(i)->GetRBFlg()) {	// �������e�Ə��l�̐F��������������
				//m_pDwarfManager->GetDwarf(i)->SetMoveFlg(true);		// �ړ�����
				m_pDwarfManager->GetDwarf(i)->SetFollowFlg(true);	// �ǐՂ��n�߂�
				m_pDwarfManager->GetDwarf(i)->SetrunFlg(false);		// �e���痣��Ȃ�
			} else {
				//m_pDwarfManager->GetDwarf(i)->SetMoveFlg(false);	// �ړ������Ȃ�
				m_pDwarfManager->GetDwarf(i)->SetFollowFlg(false);	// �ǐՂ��Ȃ�
				m_pDwarfManager->GetDwarf(i)->SetrunFlg(true);		// �e���痣���
			}
		}
	}

	BulletFiledCollision();


	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	for (int i = 0; i < m_nBulletNum; ++i){
		if (!m_ppBullets[i]->use){
			continue;
		}
		m_ppBullets[i]->Update();
	}
}

//==============================================================
//
//	Player�N���X::Draw
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Player::Draw()
{
	DirectX::XMFLOAT3 pPos = m_pos;
	DirectX::XMFLOAT3 pSize = m_size;

	for (int i = 0; i < m_nBulletNum; ++i){
		if (!m_ppBullets[i]->use){
			continue;
		}
		m_ppBullets[i]->Draw();
	}

	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-m_DrawAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pPlayerTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	//CharacterBase::Draw();
}

//==============================================================
//
//	Player�N���X::�v���C���[�ɒǐՂ��鏈��(�G�l�~�[��)
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F �Q�[���I�u�W�F�N�g�^
//
//==============================================================
void Player::PlayerToEnemy(GameObject* pObj)
{
	//�G�̈ʒu
	DirectX::XMFLOAT3 EnemyNear = pObj->GetPos();

	//�v���C���[�̈ʒu
	DirectX::XMFLOAT3 PlayerNear = m_pos;

	// �G�̈ړ�����(�ړ����x)���v���C���[�̕��֌�����
	DirectX::XMFLOAT3 dir;
	dir.x = m_pos.x - pObj->GetPos().x;
	dir.y = m_pos.y - pObj->GetPos().y;
	dir.z = m_pos.z - pObj->GetPos().z;

	//�x�N�g���̑傫��
	float L;
	L = sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));			// �������Œl�Z�o

	// dir �̒�����1�ɂ���(���K��)
	// ���K�� ... �x�N�g���̕����͈ێ������܂܁A�傫����1�̒l�ɂ��邱��
	dir.x = dir.x / L;
	dir.y = dir.y / L;
	dir.z = dir.z / L;

	// ������1�ɂȂ����x�N�g���Ɉړ������������x��������(�G�̑��x)
	dir.x = dir.x * 0.08f;
	dir.y = dir.y * 0.08f;
	dir.z = dir.z * 0.08f;

	pObj->SetMove(dir);

}


//==============================================================
//
//	Player�N���X::�J�������v���C���[�̈ʒu�ɃZ�b�g�H
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F �J�����N���X�^
//
//==============================================================
void Player::SetControllCamera(Camera* pCamera)
{
	m_pControllCamera = pCamera;
}


//==============================================================
//
//	Player�N���X::�J�����ʒu���擾
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F TPSCamera�^�̃|�W�V����
//
//==============================================================
void Player::GetCameraPos(TPSCamera* pCamera)
{
	pOldCameraPos = pCamera->GetCameraPos();
}


//==============================================================
//
//	Player�N���X::�e���擾
//	�쐬��	�F ���c�đ�
//	�߂�l	�F Bullet�^
//	����		�F int index	... �e�̐�
//
//==============================================================
Bullet *Player::GetBullet(int index)
{
	if (index < m_nBulletNum){ 
		return m_ppBullets[index];
	}
	return NULL;
}

//==============================================================
//
//	Player�N���X::�e�̐��̏��擾
//	�쐬��	�F ���c�đ�
//	�߂�l	�F int�^	... �e�̐�(m_nBUlletNum)��Ԃ�
//	����		�F void
//
//==============================================================
int Player::GetBulletNum()
{
	return m_nBulletNum;
}


//==============================================================
//
//	Player�N���X::�e�𐶐����鏈��
//	�쐬��	�F ���c�đ�
//	�ҏW��	�F �ɒn�c�^��
//	�߂�l	�F void
//	����		�F Camera�^�̈ʒu,�F����
//
//==============================================================
void Player::CreateBullet(Camera* pCamera , bool rbFlg)
{
	DirectX::XMFLOAT3 pCameraPos = pCamera->GetCameraPos();
	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (m_ppBullets[i]->use){
			continue;
		}

		m_ppBullets[i]->use = true;
		m_ppBullets[i]->SetRB(rbFlg);
		if (m_ppBullets[i]->GetRB()) {	// true����
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.5f));	// �Ԃ��Z�b�g
		} else {
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.5f));	// ���Z�b�g
		}

		m_ppBullets[i]->SetPos(m_pos);
		DirectX::XMFLOAT3 dir;

		float dirY;
		dirY = pCameraPos.y - pOldCameraPos.y;
		
		dir.x = m_pos.x - pCameraPos.x;
		dir.y = m_pos.y - dirY;
		dir.z = m_pos.z - pCameraPos.z;

		//�x�N�g���̑傫��
		float L;
		L = sqrtf((dir.x * dir.x)  + (dir.y * dir.y) +(dir.z * dir.z));

		//// dir �̒�����1�ɂ���(���K��)
		dir.x = dir.x / L;
		dir.y = dir.y / L;
		dir.z = dir.z / L;

		// ������1�ɂȂ����x�N�g���Ɉړ������������x��������(�藠���̑��x)
		dir.x = dir.x * BULLET_SPEED;
		dir.y = dir.y * BULLET_SPEED;
		dir.z = dir.z * BULLET_SPEED;

		//m_ppBullets[i]->SetMove(dir);
		m_ppBullets[i]->SetMove(dir);
		break;
	}
}

//==============================================================
//
//	Player�N���X::�e�𐶐����鏈��(�v���C���[���W������)
//	�쐬��	�F ���c�đ�
//	�ҏW��	�F �ɒn�c�^��
//	�߂�l	�F void
//	����		�F �F����
//
//==============================================================
void Player::CreateBullet(bool rbFlg)
{
	DirectX::XMFLOAT3 pPlayerPos = m_pos;
	for (int i = 0; i < m_nBulletNum; ++i){
		if (m_ppBullets[i]->use) {
			continue;
		}
		m_ppBullets[i]->use = true;
		m_ppBullets[i]->SetRB(rbFlg);
		if (m_ppBullets[i]->GetRB()) {	// true����
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));	// �Ԃ��Z�b�g
		}
		else {
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));	// ���Z�b�g
		}

		m_ppBullets[i]->SetPos(m_pos);
		DirectX::XMFLOAT3 dir;

		
		float dirY;
		dirY = 1.0f / FPS;

		dir.x = -(m_pos.x - m_Angle.x);
		dir.y = dirY;
		dir.z = -(m_pos.z - m_Angle.z);

		//�x�N�g���̑傫��
		float L;
		L = sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));

		//// dir �̒�����1�ɂ���(���K��)
		dir.x = dir.x / L;
		dir.y = dir.y / L;
		dir.z = dir.z / L;

		// ������1�ɂȂ����x�N�g���Ɉړ������������x��������(�藠���̑��x)
		dir.x = dir.x * BULLET_SPEED;
		dir.y = dir.y * BULLET_SPEED;
		dir.z = dir.z * BULLET_SPEED;

		//m_ppBullets[i]->SetMove(dir);
		m_ppBullets[i]->SetMove(dir);
		break;
	}
}

//==============================================================
//
//	Player�N���X::�e��j�󂷂鏈��
//	�쐬��	: ���c�đ�
//	�߂�l	: void
//	����		: void
//
//==============================================================
void Player::DestroyBullet()
{
	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->use = false;
		break;
	}
}


//=============================================================
//
//	�e���t�B�[���h�Ɛڂ��Ă��邩�̔��菈��
//	�쐬��	�F �g����
//	�ҏW��	�F �ɒn�c�^��
//	�߂�l	�F void
//�@����	�F void
//
//=============================================================
void Player::BulletFiledCollision() {
	for (int i = 0; i < m_nBulletNum; i++) {
		if (!m_ppBullets[i]->use) {	// �e�Ȃ������牺�̏�������
			continue;
		}
		if (!CollisionSphere(m_ppBullets[i], m_pStage->GetStage(0))) {	// �������ĂȂ������牺�̏�������
			m_ppBullets[i]->SetColFlg(false);
			continue;
		}
		m_ppBullets[i]->SetColFlg(true);
	}
}


//==============================================================
//
//	Player�N���X::���l�̏��̎擾
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����	: ���l�Ǘ��N���X�̃|�C���^
//
//==============================================================
void Player::SetDwarfInfo(DwarfManager *pDwarfManager)
{
	m_pDwarfManager = pDwarfManager;
}

//==============================================================
//
//	Player�N���X::�X�e�[�W�̏��̎擾
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����	: �X�e�[�W�Ǘ��N���X�̃|�C���^
//
//==============================================================
void Player::SetStageInfo(StageManager *pStage) {
	m_pStage = pStage;
}


//====================================================================
//
//		�e�N�X�`���ǂݍ���
//
//====================================================================
bool Player::LoadPlayer(const char* pFilePath) {
	/* �ȉ��̓��f����������g�p */
	HRESULT hr;
	m_pFBX = new FBXPlayer;
	hr = m_pFBX->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pFBX->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
		m_pBuffer[i].CreateVertexBuffer(
			m_pFBX->GetVertexData(i),
			m_pFBX->GetVertexSize(i),
			m_pFBX->GetVertexCount(i)
		);
		//�C���f�b�N�X�o�b�t�@�쐬
		m_pBuffer[i].CreateIndexBuffer(
			m_pFBX->GetIndexData(i),
			m_pFBX->GetIndexCount(i)
		);

	}
	return true;
}


