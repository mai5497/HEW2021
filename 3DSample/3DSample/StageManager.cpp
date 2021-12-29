#include "StageManager.h"

StageManager::StageManager():m_ppStages(NULL),m_nStageNum(0)
{

}
StageManager::~StageManager()
{
	Uninit();
}

bool StageManager::Init()
{
	struct StageSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	StageSetting settings[] =
	{
		//大きい床
		{ DirectX::XMFLOAT3( 0.0f,-0.5f, 0.0f),
		  DirectX::XMFLOAT3(50.0f, 1.0f,50.0f),
		},
		//小人のステージ
		{ DirectX::XMFLOAT3( 0.0f,0.5f, 0.0f),
		 DirectX::XMFLOAT3( 19.0f,1.0f,19.0f),
		},
		//右の壁
		{DirectX::XMFLOAT3(12.5f,0.0f,0.0f),
		DirectX::XMFLOAT3(2.0f,3.0f,27.0f)
		},
		//左の壁
		{DirectX::XMFLOAT3(-12.5f,0.0f,0.0f),
		DirectX::XMFLOAT3(2.0f,3.0f,27.0f)
		},
		//奥の壁
		{DirectX::XMFLOAT3(0.0f,0.0f,12.5f),
		DirectX::XMFLOAT3(27.0f,3.0f,2.0f)
		},
		//手前の壁
		{DirectX::XMFLOAT3(0.0f,0.0f,-12.5f),
		DirectX::XMFLOAT3(27.0f,3.0f,2.0f)
		}

	};

	//初期データからフィールドの数を計算
	m_nStageNum = sizeof(settings) / sizeof(settings[0]);

	//ポインタを格納する配列を作成
	m_ppStages = new Stage *[m_nStageNum];

	//それぞれの配列にフィールドをメモリ確保
	for (int i = 0; i < m_nStageNum; i++)
	{
		m_ppStages[i] = new Stage(settings[i].size);
		m_ppStages[i]->SetPos(settings[i].pos);
		m_ppStages[i]->Init();
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
void StageManager::Uninit()
{
	if (m_ppStages != NULL){
		for (int i = 0; i < m_nStageNum; i++){
			//個別に削除
			delete m_ppStages[i];
		}
		//配列を削除
		delete[] m_ppStages;
		m_ppStages = NULL;
	}
}
void StageManager::Update()
{
	for (int i = 0; i < m_nStageNum; ++i)
	{
		m_ppStages[i]->Update();
	}
}
void StageManager::Draw()
{
	for (int i = 0; i < m_nStageNum; ++i)
	{
		m_ppStages[i]->Draw();
	}
}

Stage *StageManager::GetStage(int index)
{
	if (index < m_nStageNum)
	{
		return m_ppStages[index];
	}
	return NULL;
}

int StageManager::GetStageNum()
{
	return m_nStageNum;
}

