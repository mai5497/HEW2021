#include "Stage.h"

Stage::Stage():m_ppFields(NULL),m_nFieldNum(0)
{

}
Stage::~Stage()
{
	Uninit();
}

bool Stage::Init()
{
	struct FieldSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	FieldSetting settings[] =
	{
		//大きい床
		{ DirectX::XMFLOAT3(0,-0.5f,0),
		  DirectX::XMFLOAT3(50,1,50),
		},
		//小人のステージ
		{ DirectX::XMFLOAT3(0,0.5f,0),
		 DirectX::XMFLOAT3(13,1,13),
		},
		//右の壁
		{DirectX::XMFLOAT3(10,-0.5f,0),
		DirectX::XMFLOAT3(2.5f,3,20)},
		//左の壁
		{DirectX::XMFLOAT3(-10,-0.5f,0),
		DirectX::XMFLOAT3(2.5f,3,20) },
		//奥の壁
		{DirectX::XMFLOAT3(0,-0.5f,10),
		DirectX::XMFLOAT3(22.5,3,2.5f)},
		//手前の壁
		{DirectX::XMFLOAT3(0,-0.5f,-10),
		DirectX::XMFLOAT3(22.5,3,2.5f)}

	};

	//初期データからフィールドの数を計算
	m_nFieldNum = sizeof(settings) / sizeof(settings[0]);

	//ポインタを格納する配列を作成
	m_ppFields = new FieldManager *[m_nFieldNum];

	//それぞれの配列にフィールドをメモリ確保
	for (int i = 0; i < m_nFieldNum; i++)
	{
		m_ppFields[i] = new FieldManager(settings[i].size);
		m_ppFields[i]->SetPos(settings[i].pos);
		m_ppFields[i]->Init();
	}
	//※クラスを配列でメモリ確保する場合は
	//既定のコンストラクタ(引数のないコンストラクタ)
	//が必要。どうしても引数付きのコンストラクタを
	//配列で呼び出したいときは、ポインタを格納する
	//配列を確保し、配列一つ一つの要素にメモリ確報を
	//行うことで引数付きのコンストラクタを
	//呼び出すやり方がある。

	return true;
}
void Stage::Uninit()
{
	if (m_ppFields != NULL){
		for (int i = 0; i < m_nFieldNum; i++){
			//個別に削除
			delete m_ppFields[i];
		}
		//配列を削除
		delete[] m_ppFields;
		m_ppFields = NULL;
	}
}
void Stage::Update()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Update();
	}
}
void Stage::Draw()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Draw();
	}
}

FieldManager *Stage::GetField(int index)
{
	if (index < m_nFieldNum)
	{
		return m_ppFields[index];
	}
	return NULL;
}

int Stage::GetFieldNum()
{
	return m_nFieldNum;
}

