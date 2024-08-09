#pragma once
#include "qComponent.h"

enum class DATA_TYPE
{
	INT,
	FLOAT,
	VEC2,
	OBJECT,
};


struct tBlackboardData
{
	DATA_TYPE	Type;
	void*		pData;
};



class qFSM : public qComponent
{
public:
	//CLONE(qFSM);

	qFSM();
	~qFSM();

public:
	

private:

};

