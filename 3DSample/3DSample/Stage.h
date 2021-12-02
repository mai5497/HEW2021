#ifndef __STAGE_H__
#define __STAGE_H__

#include "Field.h"

class Stage
{
public:
	Stage();
	~Stage();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	Field *GetField(int index);
	int GetFieldNum();

private:
	Field **m_ppFields;
	int m_nFieldNum;

};


#endif
