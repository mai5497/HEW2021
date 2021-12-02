#ifndef __FIELD_H__
#define __FIELD_H__

#include "GameObject.h"

class Field : public GameObject
{
public:
	Field(DirectX::XMFLOAT3 size);
	virtual ~Field();

};



#endif
