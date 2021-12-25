#ifndef __STAGE_H__
#define __STAGE_H__

#include "FieldManager.h"

class Stage
{
public:
	Stage();
	~Stage();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	FieldManager *GetField(int index);
	int GetFieldNum();

private:
	FieldManager **m_ppFields;
	int m_nFieldNum;

};


#endif
