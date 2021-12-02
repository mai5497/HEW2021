#include "Collision.h"

#define EventRad1 (3.0f)
#define EventRad2 (3.0f)

Collision::Collision()
	:m_registerNum(0)
{
}
Collision::~Collision()
{
	Uninit();
}

bool Collision::Init()
{
	for (int i = 0; i < MAX_COLLISION_REGISTER; ++i)
	{
		m_pList[i][0] = m_pList[i][1] = NULL;
	}
	return true;
}
void Collision::Uninit()
{
	for (int i = 0; i < MAX_COLLISION_REGISTER; ++i)
	{
		m_pList[i][0] = m_pList[i][1] = NULL;
	}
}
void Collision::Update()
{
	//当たり判定処理
	for (int i = 0; i < MAX_COLLISION_REGISTER; i++)
	{
		GameObject *pA = m_pList[i][0];
		GameObject *pB = m_pList[i][1];
		//登録されていないデータは処理しない
		if (pA == NULL || pB == NULL)
		{
			continue;
		}
		
		//四角形同士の当たり判定
		//2Dでも3Dでも中心までの距離＜半分の大きさを足し合わせた数
		//は変わらない。計算する軸が増えるだけ
		DirectX::XMFLOAT3 aPos = pA->GetPos();
		DirectX::XMFLOAT3 bPos = pB->GetPos();
		DirectX::XMFLOAT3 aSize = pA->GetSize();
		DirectX::XMFLOAT3 bSize = pB->GetSize();

		DirectX::XMFLOAT3 distance(
			fabsf(bPos.x - aPos.x),
			fabsf(bPos.y - aPos.y),
			fabsf(bPos.z - aPos.z)
		);
		bool hitX = distance.x < (aSize.x + bSize.x) * 0.5f;
		bool hitY = distance.y < (aSize.y + bSize.y) * 0.5f;
		bool hitZ = distance.z < (aSize.z + bSize.z) * 0.5f;

		//手裏剣の当たり判定
		if ((bPos.x - aPos.x) * (bPos.x - aPos.x) +
			(bPos.y - aPos.y) * (bPos.y - aPos.y) +
			(bPos.z - aPos.z) * (bPos.z - aPos.z)
			<= (EventRad1 + EventRad2) * (EventRad1 + EventRad2))
		{
			if (pA->GetCollisionType() == COLLISION_DYNAMIC &&
				pB->GetCollisionType() == COLLISION_ENEMY)
			{
				pA->OnCollision(pB);
			}
		}

		//当たり判定の結果
		if (hitX && hitY && hitZ)
		{
			//dynamic - static
			if (pA->GetCollisionType() == COLLISION_DYNAMIC &&
				pB->GetCollisionType() == COLLISION_STATIC)
			{
				Push(pA, pB);
			}
			if (pA->GetCollisionType() == COLLISION_ENEMY &&
				pB->GetCollisionType() == COLLISION_STATIC)
			{
				Push(pA, pB);
			}
			if (pA->GetCollisionType() == COLLISION_STATIC &&
				pB->GetCollisionType() == COLLISION_DYNAMIC)
			{
				Push(pB, pA);
			}
			//dynamic - dynamic

			//dynamic - overlap
		}
	}
	m_registerNum = 0;
}


void Collision::Register(GameObject *pA, GameObject *pB)
{
	if (m_registerNum < MAX_COLLISION_REGISTER)
	{
		m_pList[m_registerNum][0] = pA;
		m_pList[m_registerNum][1] = pB;
		++m_registerNum;
	}
}


//押し出し処理
void Collision::Push(GameObject *pDynamic,GameObject *pStatic)
{
	//---事前に各オブジェクトの情報を抜き取る
	DirectX::XMFLOAT3 dPos = pDynamic->GetPos();
	DirectX::XMFLOAT3 sPos = pStatic->GetPos();
	DirectX::XMFLOAT3 dSize = pDynamic->GetSize();
	DirectX::XMFLOAT3 sSize = pStatic->GetSize();
	DirectX::XMFLOAT3 dMove = pDynamic->GetMove();

	//---計算情報を抜き出す
	//移動量から移動する方向を求める
	//※移動する方向は１か-1で表す
	//三項演算子A ? B : C
	//Aの条件が成立してたらB、不成立ならC
	DirectX::XMFLOAT3 dir(
		dMove.x > 0 ? 1 : -1,
		dMove.y > 0 ? 1 : -1,
		dMove.z > 0 ? 1 : -1);
	//これと一緒
	/*
	if (dMove.x > 0)
	{
		dMove.x = 1;
	}
	else
	{
		dMove.y = -1;
	}
	*/

	//実際に当たり判定のめり込んだのは、
	//オブジェクトの座標ではなく、角だけが
	//めり込んでいることもあるので、
	//対象の角を計算で求める
	DirectX::XMFLOAT3 dPoint(
		dPos.x + dir.x * dSize.x * 0.5f,
		dPos.y + dir.y * dSize.y * 0.5f,
		dPos.z + dir.z * dSize.z * 0.5f);
	//移動前の角の座標
	//そのままの移動量で移動前の座標を表そうと
	//すると浮動小数点の計算誤差により、移動
	//ベクトルの視点が面の内側にあることになり、
	//貫通していないと判定される。
	//これを回避するために移動の前の位置が遠くなる
	//ように計算の時だけ、移動量を大きくする
	DirectX::XMFLOAT3 prePoint(
		dPoint.x - dMove.x * 1.1f,
		dPoint.y - dMove.y * 1.1f,
		dPoint.z - dMove.z * 1.1f);
	//衝突された側の角を計算
	//衝突された側の角は移動方向を反転した
	//方向に向かって大きさの半分を足すと求められる
	DirectX::XMFLOAT3 sPoint(
		sPos.x - dir.x * sSize.x * 0.5f,
		sPos.y - dir.y * sSize.y * 0.5f,
		sPos.z - dir.z * sSize.z * 0.5f);
	//面上の一点から移動ベクトルの始点と終点へ
	//向かうベクトルを計算する
	DirectX::XMFLOAT3 vStart(
		prePoint.x - sPoint.x,
		prePoint.y - sPoint.y,
		prePoint.z - sPoint.z);
	DirectX::XMFLOAT3 vEnd(
		dPoint.x - sPoint.x,
		dPoint.y - sPoint.y,
		dPoint.z - sPoint.z);

	//それぞれの面と計算
	//各面の法線ベクトル
	DirectX::XMFLOAT3 Normal[] =
	{
		DirectX::XMFLOAT3(-dir.x, 0, 0),
		DirectX::XMFLOAT3(0, -dir.y, 0),
		DirectX::XMFLOAT3(0, 0, -dir.z),
	};
	for (int i = 0; i < _countof(Normal); i++)
	{
		//面の法線との内積を計算
		float dotS =
			vStart.x * Normal[i].x +
			vStart.y * Normal[i].y +
			vStart.z * Normal[i].z;
		float dotE =
			vEnd.x * Normal[i].x +
			vEnd.y * Normal[i].y +
			vEnd.z * Normal[i].z;
		//それぞれの内積の結果が正と負で
		//あれば移動ベクトル画面を貫通している
		//正と負の組み合わせかどうかは
		//掛け算で判定できる
		//(正x負=負/正x正=正/負x負=正)
		if (dotS * dotE < 0)
		{
			//移動ベクトルの方向にめり込んだ量を
			//戻すのではなく、面の方向に向かって
			//戻す(戻す距離は内積の値と等しい)
			dotE = fabsf(dotE);
			dPos.x += Normal[i].x * dotE;
			dPos.y += Normal[i].y * dotE;
			dPos.z += Normal[i].z * dotE;
			pDynamic->SetPos(dPos);
			//すべての移動量を0にしてしまうと
			//ほかのオブジェクトと押し出しの計算を
			//する際に移動量がないことになるので
			//移動量を0にしなければならない成分だけ
			//0にする
			dMove.x *= 1 - fabsf(Normal[i].x);
			dMove.y *= 1 - fabsf(Normal[i].y);
			dMove.z *= 1 - fabsf(Normal[i].z);
			pDynamic->SetMove(dMove);
			break;
		}
	}
}
