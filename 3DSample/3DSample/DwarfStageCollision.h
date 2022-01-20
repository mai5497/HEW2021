#ifndef __DWARFSTAGECOLLISION_H__
#define __DWARFSTAGECOLLISION_H__

#include "GameObject.h"

class DwarfStageCollision {
public:
	//---関数
	DwarfStageCollision();
	~DwarfStageCollision();
	void Init();
	void Uninit();
	//void Update();	// そこにデータとして存在するだけなので更新無し
	void Draw();		// そこにデータとして存在するだけなので描画無し。（テスト用に描画はいったん行う）
	GameObject* GetDwarfStageCollision(int num);
	int GetStageNum();

private:
	//---変数
	GameObject **m_ppDwarfStageCollision;	// 当たり判定とる用のオブジェクトたち
	int m_DawarfStageNum;
};



#endif // !__DWARFSTAGECOLLISION_H__
